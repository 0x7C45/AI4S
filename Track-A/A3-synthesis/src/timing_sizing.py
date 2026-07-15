"""OpenSTA-guided critical-path gate sizing."""

from __future__ import annotations

import collections
import re
import shutil
import subprocess
from pathlib import Path


_INSTANCE_RE = re.compile(
    r"(?m)^(?P<indent>\s*)(?P<cell>[A-Za-z][A-Za-z0-9_$]*_X1)(?P<space>\s+)"
    r"(?P<instance>\\?\S+)(?P<tail>\s*\()"
)
_PATH_CELL_RE = re.compile(
    r"[v^]\s+(?P<instance>\S+)/[A-Za-z][A-Za-z0-9_$]*\s+"
    r"\((?P<cell>[A-Za-z][A-Za-z0-9_$]*_X1)\)"
)
_LIB_CELL_RE = re.compile(r"\bcell\s*\(\s*([A-Za-z][A-Za-z0-9_$]*)\s*\)")


def upsize_reported_critical_cells(
    netlist: Path,
    liberty: Path,
    report: Path,
    *,
    strength: int,
    paths: int,
    max_cells: int,
) -> int:
    """Upgrade frequently recurring X1 cells from the worst reported paths."""

    blocks = report.read_text(errors="ignore").split("Startpoint:")[1 : paths + 1]
    frequency: collections.Counter[str] = collections.Counter()
    for block in blocks:
        frequency.update(
            {
                match.group("instance")
                for match in _PATH_CELL_RE.finditer(block)
                if not match.group("cell").startswith(("DFF", "SDFF", "LATCH"))
            }
        )
    available = set(_LIB_CELL_RE.findall(liberty.read_text(errors="ignore")))
    text = netlist.read_text(encoding="utf-8")
    mapped = {match.group("instance"): match.group("cell") for match in _INSTANCE_RE.finditer(text)}
    selected: set[str] = set()
    for instance, _ in frequency.most_common():
        source = mapped.get(instance)
        if source is None or source[:-1] + str(strength) not in available:
            continue
        selected.add(instance)
        if len(selected) >= max_cells:
            break
    if not selected:
        return 0

    def replace(match: re.Match[str]) -> str:
        if match.group("instance") not in selected:
            return match.group(0)
        return (
            match.group("indent")
            + match.group("cell")[:-1]
            + str(strength)
            + match.group("space")
            + match.group("instance")
            + match.group("tail")
        )

    netlist.write_text(_INSTANCE_RE.sub(replace, text), encoding="utf-8")
    return len(selected)


def run_critical_path_sizing(
    netlist: Path,
    liberty: Path,
    sdc: Path,
    top: str,
    work_dir: Path,
    *,
    strength: int,
    paths: int,
    max_cells: int,
) -> int:
    """Run one bounded OpenSTA feedback pass, returning the changed cell count."""

    sta = shutil.which("sta")
    if sta is None:
        return 0
    if any(char.isspace() for char in top) or any(char in top for char in ";\n\r\""):
        return 0
    report = work_dir / "critical_paths.rpt"
    script = work_dir / "critical_paths.tcl"
    log = work_dir / "critical_paths.log"
    eval_sdc = work_dir / "critical_paths.sdc"
    sdc_text = sdc.read_text(errors="ignore")
    sdc_text = re.sub(r"set\s+CLK_PERIOD\s+[0-9.]+", "set CLK_PERIOD 0.000", sdc_text)
    sdc_text = re.sub(r"set_input_delay\s+[0-9.]+", "set_input_delay 0.000", sdc_text)
    sdc_text = re.sub(r"set_output_delay\s+[0-9.]+", "set_output_delay 0.000", sdc_text)
    sdc_text = re.sub(r"set_max_delay\s+\$CLK_PERIOD", "set_max_delay 0.000", sdc_text)
    sdc_text = re.sub(r"set_max_delay\s+[0-9.]+", "set_max_delay 0.000", sdc_text)
    eval_sdc.write_text(sdc_text, encoding="utf-8")
    script.write_text(
        "\n".join(
            (
                f"read_liberty {liberty.resolve()}",
                f"read_verilog {netlist.resolve()}",
                f"link_design {top}",
                f"read_sdc {eval_sdc.resolve()}",
                "report_checks -path_delay max -group_path_count "
                f"{paths} -endpoint_path_count 1 -unique_paths_to_endpoint "
                f"-format full -fields {{capacitance slew input_pin net}} -digits 4 > {report.resolve()}",
                "exit",
                "",
            )
        ),
        encoding="utf-8",
    )
    try:
        completed = subprocess.run(
            [sta, str(script)],
            cwd=work_dir.parent,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=60,
            check=False,
        )
    except (OSError, subprocess.TimeoutExpired):
        return 0
    log.write_text(completed.stdout, encoding="utf-8")
    if completed.returncode or not report.is_file() or "Startpoint:" not in report.read_text(errors="ignore"):
        return 0
    return upsize_reported_critical_cells(
        netlist,
        liberty,
        report,
        strength=strength,
        paths=paths,
        max_cells=max_cells,
    )
