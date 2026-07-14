"""Conservative, netlist-level high-fanout gate sizing."""

from __future__ import annotations

import re
from pathlib import Path


_INSTANCE_RE = re.compile(
    r"(?ms)^(?P<indent>\s*)(?P<cell>[A-Za-z][A-Za-z0-9_$]*_X1)\s+"
    r"(?P<instance>\\?\S+)\s*\((?P<pins>.*?)\s*\);"
)
_PIN_RE = re.compile(r"\.([A-Za-z][A-Za-z0-9_$]*)\s*\(\s*([^()]+?)\s*\)")
_LIB_CELL_RE = re.compile(r"\bcell\s*\(\s*([A-Za-z][A-Za-z0-9_$]*)\s*\)")
_OUTPUT_PINS = {"Z", "ZN"}


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
