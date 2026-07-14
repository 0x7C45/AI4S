"""Conservative, netlist-level high-fanout gate sizing and buffering."""

from __future__ import annotations

import re
from pathlib import Path


_INSTANCE_RE = re.compile(
    r"(?ms)^(?P<indent>\s*)(?P<cell>[A-Za-z][A-Za-z0-9_$]*_X[0-9]+)\s+"
    r"(?P<instance>\\?\S+)\s*\((?P<pins>.*?)\s*\);"
)
_PIN_RE = re.compile(r"\.([A-Za-z][A-Za-z0-9_$]*)\s*\(\s*([^()]+?)\s*\)")
_LIB_CELL_RE = re.compile(r"\bcell\s*\(\s*([A-Za-z][A-Za-z0-9_$]*)\s*\)")
_MODULE_RE = re.compile(r"(?m)^(module\b[^;]*;\s*\n)")
_OUTPUT_PINS = {"Z", "ZN", "Q", "QN"}


def _verilog_net(net: str) -> str:
    """Preserve the mandatory whitespace terminator on escaped identifiers."""
    return net + " " if net.startswith("\\") else net


def _braced_body(text: str, pattern: str) -> str | None:
    match = re.search(pattern, text)
    if match is None:
        return None
    depth = 1
    cursor = match.end()
    while cursor < len(text) and depth:
        if text[cursor] == "{":
            depth += 1
        elif text[cursor] == "}":
            depth -= 1
        cursor += 1
    if depth:
        return None
    return text[match.end() : cursor - 1]


def _liberty_buffer_is_compatible(text: str, cell: str) -> bool:
    """Require the fixed A-input/Z-output interface used by this pass."""

    body = _braced_body(text, rf"\bcell\s*\(\s*{re.escape(cell)}\s*\)\s*\{{")
    if body is None:
        return False
    input_a = _braced_body(body, r"\bpin\s*\(\s*A\s*\)\s*\{")
    output_z = _braced_body(body, r"\bpin\s*\(\s*Z\s*\)\s*\{")
    return bool(
        input_a is not None
        and output_z is not None
        and re.search(r"\bdirection\s*:\s*input\s*;", input_a)
        and re.search(r"\bdirection\s*:\s*output\s*;", output_z)
    )


def upsize_high_fanout_gates(
    netlist: Path,
    liberty: Path,
    *,
    threshold: int,
    strength: int,
) -> int:
    """Upgrade pin-compatible X1 combinational gates driving many loads.

    The Yosys Verilog backend emits one standard-cell instance per block.  We
    count pin connections to each internal output net and only rename a cell
    when the requested drive-strength variant exists in the supplied Liberty.
    Sequential cells are excluded because their state behavior and pin sets can
    vary across drive variants.
    """

    text = netlist.read_text(encoding="utf-8")
    available = set(_LIB_CELL_RE.findall(liberty.read_text(encoding="utf-8", errors="ignore")))
    connection_count: dict[str, int] = {}
    matches = list(_INSTANCE_RE.finditer(text))
    for match in matches:
        for _, net in _PIN_RE.findall(match.group("pins")):
            key = net.strip()
            connection_count[key] = connection_count.get(key, 0) + 1

    replacements: dict[tuple[int, int], str] = {}
    for match in matches:
        source = match.group("cell")
        if not source.endswith("_X1"):
            continue
        if source.startswith(("DFF", "SDFF", "LATCH")):
            continue
        target = source[:-1] + str(strength)
        if target not in available:
            continue
        outputs = [net.strip() for pin, net in _PIN_RE.findall(match.group("pins")) if pin in _OUTPUT_PINS]
        if not outputs:
            continue
        fanout = max(connection_count.get(net, 1) - 1 for net in outputs)
        if fanout >= threshold:
            replacements[(match.start("cell"), match.end("cell"))] = target

    if not replacements:
        return 0
    chunks: list[str] = []
    cursor = 0
    for (start, end), target in sorted(replacements.items()):
        chunks.extend((text[cursor:start], target))
        cursor = end
    chunks.append(text[cursor:])
    netlist.write_text("".join(chunks), encoding="utf-8")
    return len(replacements)


def insert_high_fanout_buffers(
    netlist: Path,
    liberty: Path,
    *,
    threshold: int,
    strength: int,
) -> int:
    """Insert one strong, pin-compatible buffer after overloaded drivers.

    This preserves every sink connection while isolating the original cell
    from a large aggregate input capacitance.  It also works for sequential
    outputs and for cells already mapped at the largest available drive size.
    """

    text = netlist.read_text(encoding="utf-8")
    # The transformation deliberately operates on the single flattened module
    # emitted by our Yosys flow.  Skipping unexpected multi-module inputs is
    # safer than placing generated declarations in the wrong scope.
    if len(list(_MODULE_RE.finditer(text))) != 1:
        return 0
    liberty_text = liberty.read_text(encoding="utf-8", errors="ignore")
    buffer_cell = f"BUF_X{strength}"
    if not _liberty_buffer_is_compatible(liberty_text, buffer_cell):
        return 0
    matches = list(_INSTANCE_RE.finditer(text))
    connection_count: dict[str, int] = {}
    for match in matches:
        for _, net in _PIN_RE.findall(match.group("pins")):
            key = net.strip()
            connection_count[key] = connection_count.get(key, 0) + 1

    replacements: dict[tuple[int, int], str] = {}
    declarations: list[str] = []
    inserted = 0
    for match in matches:
        updated = match.group(0)
        buffers: list[str] = []
        for pin, raw_net in _PIN_RE.findall(match.group("pins")):
            net = raw_net.strip()
            if pin not in _OUTPUT_PINS or connection_count.get(net, 1) - 1 < threshold:
                continue
            while True:
                buffered_net = f"__a3_buffer_net_{inserted}"
                buffer_instance = f"__a3_buffer_{inserted}"
                if buffered_net not in text and buffer_instance not in text:
                    break
                inserted += 1
            pin_pattern = re.compile(
                rf"(\.{re.escape(pin)}\s*\(\s*){re.escape(net)}(\s*\))"
            )
            updated, count = pin_pattern.subn(rf"\g<1>{buffered_net}\g<2>", updated, count=1)
            if count != 1:
                continue
            declarations.append(f"  wire {buffered_net};\n")
            indent = match.group("indent")
            buffers.append(
                f"\n{indent}{buffer_cell} {buffer_instance} "
                f"( .A({buffered_net}), .Z({_verilog_net(net)}) );"
            )
            inserted += 1
        if buffers:
            replacements[(match.start(), match.end())] = updated + "".join(buffers)

    if not replacements:
        return 0
    chunks: list[str] = []
    cursor = 0
    for (start, end), replacement in sorted(replacements.items()):
        chunks.extend((text[cursor:start], replacement))
        cursor = end
    chunks.append(text[cursor:])
    rewritten = "".join(chunks)
    module = _MODULE_RE.search(rewritten)
    if module is None:
        return 0
    rewritten = rewritten[: module.end()] + "".join(declarations) + rewritten[module.end() :]
    netlist.write_text(rewritten, encoding="utf-8")
    return len(declarations)
