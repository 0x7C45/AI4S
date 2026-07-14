"""Randomized gate-level equivalence checking for generated A3 netlists.

The supplied Nangate behavioral model contains UDP primitives that Yosys cannot
parse, but Icarus Verilog accepts it.  This checker therefore compiles the RTL
and its mapped netlist side by side, drives identical vectors, and compares
every top-level output.  It is intentionally a gate-level check: it catches
bad cell pins, missing drivers, and sequential-reset mistakes that area/STA
numbers cannot reveal.
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import tempfile
from pathlib import Path


class VerificationError(RuntimeError):
    """Raised when the sampled equivalence proof cannot be completed."""


_IDENTIFIER = re.compile(r"\\[^\s,;()]+|[A-Za-z_$][A-Za-z0-9_$]*")

_IDEAL_SEQUENTIAL_MODELS = {
    "DFF_X1": """module DFF_X1 (D, CK, Q, QN); input D, CK; output reg Q; output QN; always @(posedge CK) Q <= D; assign QN = ~Q; endmodule""",
    "DFF_X2": """module DFF_X2 (D, CK, Q, QN); input D, CK; output reg Q; output QN; always @(posedge CK) Q <= D; assign QN = ~Q; endmodule""",
    "DFFR_X1": """module DFFR_X1 (D, RN, CK, Q, QN); input D, RN, CK; output reg Q; output QN; always @(posedge CK or negedge RN) if (!RN) Q <= 1'b0; else Q <= D; assign QN = ~Q; endmodule""",
    "DFFR_X2": """module DFFR_X2 (D, RN, CK, Q, QN); input D, RN, CK; output reg Q; output QN; always @(posedge CK or negedge RN) if (!RN) Q <= 1'b0; else Q <= D; assign QN = ~Q; endmodule""",
    "DFFS_X1": """module DFFS_X1 (D, SN, CK, Q, QN); input D, SN, CK; output reg Q; output QN; always @(posedge CK or negedge SN) if (!SN) Q <= 1'b1; else Q <= D; assign QN = ~Q; endmodule""",
    "DFFS_X2": """module DFFS_X2 (D, SN, CK, Q, QN); input D, SN, CK; output reg Q; output QN; always @(posedge CK or negedge SN) if (!SN) Q <= 1'b1; else Q <= D; assign QN = ~Q; endmodule""",
}


def _module_text(source: str, top: str) -> str:
    match = re.search(rf"\bmodule\s+{re.escape(top)}\b", source)
    if not match:
        raise VerificationError(f"top module {top!r} was not found")
    end = re.search(r"\bendmodule\b", source[match.start() :])
    if not end:
        raise VerificationError(f"top module {top!r} has no endmodule")
    return source[match.start() : match.start() + end.end()]


def _port_names(header: str) -> list[str]:
    cleaned = re.sub(r"//.*", "", header)
    ports = []
    for item in cleaned.split(","):
        names = _IDENTIFIER.findall(item)
        if not names:
            continue
        ports.append(names[-1])
    return ports


def _declaration_names(body: str, direction: str) -> set[str]:
    names: set[str] = set()
    body = re.sub(r"//[^\n]*", "", body)
    for match in re.finditer(rf"\b{direction}\b\s+([^;]+);", body, re.DOTALL):
        # A range has a colon (`[7:0]`).  Do not strip `[0]` from an escaped
        # scalar identifier such as `\\A[0]`.
        declaration = re.sub(r"\[[^\]]*:[^\]]*\]", " ", match.group(1))
        declaration = re.sub(r"\b(?:wire|reg|logic|signed|unsigned|tri)\b", " ", declaration)
        names.update(_IDENTIFIER.findall(declaration))
    return names


def _header_directions(header: str) -> tuple[set[str], set[str], set[str], dict[str, str]]:
    """Parse ANSI-style directions from a module port list."""
    inputs: set[str] = set()
    outputs: set[str] = set()
    inouts: set[str] = set()
    widths: dict[str, str] = {}
    current_direction: str | None = None
    current_width: str | None = None
    for item in re.sub(r"//.*", "", header).split(","):
        direction = re.search(r"\b(input|output|inout)\b", item)
        if direction:
            current_direction = direction.group(1)
            range_match = re.search(r"(\[[^\]]*:[^\]]*\])", item)
            current_width = range_match.group(1) if range_match else None
        if not current_direction:
            continue
        names = _IDENTIFIER.findall(re.sub(r"\[[^\]]*:[^\]]*\]", " ", item))
        if not names:
            continue
        name = names[-1]
        {"input": inputs, "output": outputs, "inout": inouts}[current_direction].add(name)
        if current_width:
            widths[name] = current_width
    return inputs, outputs, inouts, widths


def _port_widths(body: str) -> dict[str, str]:
    """Return Verilog range text for vector ports, keyed by their port name."""
    widths: dict[str, str] = {}
    body = re.sub(r"//[^\n]*", "", body)
    for direction in ("input", "output"):
        for match in re.finditer(rf"\b{direction}\b\s+([^;]+);", body, re.DOTALL):
            declaration = match.group(1)
            range_match = re.search(r"(\[[^\]]*:[^\]]*\])", declaration)
            if not range_match:
                continue
            range_text = range_match.group(1)
            names_text = declaration[: range_match.start()] + declaration[range_match.end() :]
            names_text = re.sub(r"\b(?:wire|reg|logic|signed|unsigned|tri)\b", " ", names_text)
            for name in _IDENTIFIER.findall(names_text):
                widths[name] = range_text
    return widths


def _parameter_values(module: str) -> dict[str, str]:
    """Extract simple numeric defaults needed to size ANSI top-level ports."""
    return {
        match.group(1): match.group(2)
        for match in re.finditer(r"\bparameter(?:\s+integer)?\s+([A-Za-z_$][A-Za-z0-9_$]*)\s*=\s*([0-9]+)", module)
    }


def parse_top_interface(rtl: Path, top: str) -> tuple[list[str], set[str], set[str]]:
    """Return ordered ports plus input/output sets for a non-ANSI Verilog top."""
    module = _module_text(rtl.read_text(encoding="utf-8"), top)
    header = re.search(rf"\bmodule\s+{re.escape(top)}\b\s*(?:#\s*\(.*?\))?\s*\((.*?)\)\s*;", module, re.DOTALL)
    if not header:
        raise VerificationError(f"could not parse port list for top module {top!r}")
    ports = _port_names(header.group(1))
    # Only inspect declarations after the port list.  Otherwise the first
    # ANSI `input` captures the rest of the module header up to its semicolon.
    body = module[header.end() :]
    header_inputs, header_outputs, header_inouts, _ = _header_directions(header.group(1))
    inputs = _declaration_names(body, "input") | header_inputs
    outputs = _declaration_names(body, "output") | header_outputs
    unknown = set(ports) - inputs - outputs
    if unknown:
        raise VerificationError(f"could not determine directions for ports: {sorted(unknown)}")
    if inputs & outputs or header_inouts:
        raise VerificationError("inout ports are not supported by the verifier")
    return ports, inputs, outputs


def _rename_top(source: str, top: str, replacement: str) -> str:
    changed, count = re.subn(rf"(\bmodule\s+){re.escape(top)}\b", rf"\1{replacement}", source, count=1)
    if count != 1:
        raise VerificationError(f"could not rename top module {top!r}")
    return changed


def _netlist_cell_types(netlist: Path) -> set[str]:
    """Find standard-cell module types instantiated by a mapped netlist."""
    source = netlist.read_text(encoding="utf-8")
    return {
        match.group(1)
        for match in re.finditer(r"(?:^|[;\n])\s*([A-Z][A-Z0-9_]*)\s+[^;()]+\(", source)
    }


def _ideal_cell_library(cell_library: Path, netlist: Path) -> str:
    """Extract only used combinational cells and idealize the used flip-flops.

    The full Nangate model intentionally models power-up uncertainty through
    UDP primitives.  That is useful for timing simulation but prevents a
    reset-driven RTL/netlist comparison.  The ideal sequential subset keeps
    the mapped cells' documented functional behavior and leaves all mapped
    combinational cells from the supplied library untouched.
    """
    source = cell_library.read_text(encoding="utf-8")
    modules = {
        match.group(1): match.group(0)
        for match in re.finditer(r"\bmodule\s+([A-Za-z0-9_]+)\b.*?\bendmodule\b", source, re.DOTALL)
    }
    extracted = []
    missing = []
    for cell_type in sorted(_netlist_cell_types(netlist)):
        if cell_type in _IDEAL_SEQUENTIAL_MODELS:
            extracted.append(_IDEAL_SEQUENTIAL_MODELS[cell_type])
        elif cell_type in modules:
            extracted.append(modules[cell_type])
        else:
            missing.append(cell_type)
    if missing:
        raise VerificationError(f"cell models are unavailable for: {', '.join(missing)}")
    return "\n\n".join(extracted) + "\n"


def render_testbench(
    *,
    ports: list[str],
    inputs: set[str],
    outputs: set[str],
    clock: str | None,
    reset: str | None,
    reset_active: str | None,
    samples: int,
    port_widths: dict[str, str] | None = None,
) -> str:
    if samples < 1:
        raise VerificationError("samples must be positive")
    if clock and clock not in inputs:
        raise VerificationError(f"clock port {clock!r} is not an input")
    if reset and reset not in inputs:
        raise VerificationError(f"reset port {reset!r} is not an input")
    signal = {port: f"sig_{index}" for index, port in enumerate(ports)}
    gold = {port: f"gold_{index}" for index, port in enumerate(ports)}
    gate = {port: f"gate_{index}" for index, port in enumerate(ports)}
    declarations = []
    port_widths = port_widths or {}
    for port in ports:
        width = f" {port_widths[port]}" if port in port_widths else ""
        if port in inputs:
            declarations.append(f"  reg{width} {signal[port]};")
        elif port in outputs:
            declarations.extend((f"  wire{width} {gold[port]};", f"  wire{width} {gate[port]};"))
    gold_ports = ", ".join(signal[p] if p in inputs else gold[p] for p in ports)
    gate_ports = ", ".join(signal[p] if p in inputs else gate[p] for p in ports)
    comparison = "\n".join(
        f'      if ((^{gold[p]} === 1\'bx) || (^{gate[p]} === 1\'bx)) begin $display("UNKNOWN output {p} at sample %0d: gold=%b gate=%b", sample, {gold[p]}, {gate[p]}); errors = errors + 1; end else if ({gold[p]} !== {gate[p]}) begin $display("MISMATCH output {p} at sample %0d: gold=%b gate=%b", sample, {gold[p]}, {gate[p]}); errors = errors + 1; end'
        for p in ports
        if p in outputs
    )
    drive_inputs = "\n".join(f"      {signal[p]} = $random;" for p in ports if p in inputs and p not in {clock, reset})
    reset_value = "1'b1" if reset_active == "high" else "1'b0"
    reset_release = "1'b0" if reset_active == "high" else "1'b1"
    setup = ""
    clock_cycle = "      #1;"
    if clock:
        setup += f"    {signal[clock]} = 1'b0;\n"
        if reset:
            # Start inactive, then assert reset.  A gate-level UDP must see a
            # real transition; assigning active reset at time zero can leave
            # its power-up state unknown even when RTL has reset to zero.
            setup += f"    {signal[reset]} = {reset_release}; #1; {signal[reset]} = {reset_value}; #1; {signal[clock]} = 1'b1; #1; {signal[clock]} = 1'b0; #1; {signal[reset]} = {reset_release};\n"
        clock_cycle = f"      #1; {signal[clock]} = 1'b1; #1; {signal[clock]} = 1'b0; #1;"
    elif reset:
        setup += f"    {signal[reset]} = {reset_release};\n"
    return f"""`timescale 1ns/1ps
module tb;
{chr(10).join(declarations)}
  integer sample;
  integer errors;
  golden dut_gold({gold_ports});
  gate dut_gate({gate_ports});
  initial begin
    errors = 0;
{setup}    for (sample = 0; sample < {samples}; sample = sample + 1) begin
{drive_inputs}
{clock_cycle}
{comparison}
    end
    if (errors != 0) begin $display("RANDOM_EQUIV_FAIL %0d mismatches", errors); $finish_and_return(1); end
    $display("RANDOM_EQUIV_PASS {samples} samples");
    $finish;
  end
endmodule
"""


def run_randomized_equivalence(
    *, rtl: Path, netlist: Path, top: str, cell_library: Path, clock: str | None, reset: str | None,
    reset_active: str | None, samples: int = 100, timeout_seconds: int = 120,
) -> str:
    """Compile and compare RTL/netlist in Icarus; return its success message."""
    iverilog = shutil.which("iverilog")
    vvp = shutil.which("vvp")
    if not iverilog or not vvp:
        raise VerificationError("iverilog/vvp are required; run this in the official contest image")
    ports, inputs, outputs = parse_top_interface(rtl, top)
    module = _module_text(rtl.read_text(encoding="utf-8"), top)
    header = re.search(rf"\bmodule\s+{re.escape(top)}\b\s*(?:#\s*\(.*?\))?\s*\((.*?)\)\s*;", module, re.DOTALL)
    assert header is not None
    _, _, _, header_widths = _header_directions(header.group(1))
    widths = {**_port_widths(module[header.end() :]), **header_widths}
    parameters = _parameter_values(module)
    for port, width in list(widths.items()):
        for name, value in parameters.items():
            widths[port] = re.sub(rf"\b{re.escape(name)}\b", value, widths[port])
    with tempfile.TemporaryDirectory(prefix="a3-equivalence-") as directory:
        root = Path(directory)
        golden = root / "golden.v"
        gate = root / "gate.v"
        tb = root / "tb.v"
        ideal_cells = root / "ideal_cells.v"
        executable = root / "simv"
        golden.write_text(_rename_top(rtl.read_text(encoding="utf-8"), top, "golden"), encoding="utf-8")
        gate.write_text(_rename_top(netlist.read_text(encoding="utf-8"), top, "gate"), encoding="utf-8")
        ideal_cells.write_text(_ideal_cell_library(cell_library, netlist), encoding="utf-8")
        tb.write_text(render_testbench(ports=ports, inputs=inputs, outputs=outputs, clock=clock, reset=reset, reset_active=reset_active, samples=samples, port_widths=widths), encoding="utf-8")
        compiled = subprocess.run([iverilog, "-g2012", "-o", str(executable), str(ideal_cells), str(golden), str(gate), str(tb)], text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=timeout_seconds, check=False)
        if compiled.returncode:
            raise VerificationError(f"Icarus compile failed:\n{compiled.stdout[-4000:]}")
        simulated = subprocess.run([vvp, str(executable)], text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=timeout_seconds, check=False)
        if simulated.returncode:
            raise VerificationError(f"equivalence simulation failed:\n{simulated.stdout[-4000:]}")
        if "RANDOM_EQUIV_PASS" not in simulated.stdout:
            raise VerificationError(f"equivalence result was incomplete:\n{simulated.stdout[-4000:]}")
        return simulated.stdout.strip()


def main() -> int:
    parser = argparse.ArgumentParser(description="Randomized RTL-to-netlist gate-level equivalence check")
    parser.add_argument("--rtl", required=True, type=Path)
    parser.add_argument("--netlist", required=True, type=Path)
    parser.add_argument("--top", required=True)
    parser.add_argument("--lib", required=True, dest="cell_library", type=Path)
    parser.add_argument("--clock")
    parser.add_argument("--reset")
    parser.add_argument("--reset-active", choices=("high", "low"))
    parser.add_argument("--samples", type=int, default=100)
    args = parser.parse_args()
    print(run_randomized_equivalence(rtl=args.rtl, netlist=args.netlist, top=args.top, cell_library=args.cell_library, clock=args.clock, reset=args.reset, reset_active=args.reset_active, samples=args.samples))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
