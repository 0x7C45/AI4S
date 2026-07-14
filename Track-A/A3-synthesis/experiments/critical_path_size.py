#!/usr/bin/env python3
"""Prototype OpenSTA-guided sizing on a mapped netlist."""

from __future__ import annotations

import argparse
import collections
import re
from pathlib import Path


INSTANCE_RE = re.compile(
    r"(?m)^(?P<indent>\s*)(?P<cell>[A-Za-z][A-Za-z0-9_$]*_X1)(?P<space>\s+)"
    r"(?P<instance>\\?\S+)(?P<tail>\s*\()"
)
PATH_CELL_RE = re.compile(
    r"[v^]\s+(?P<instance>\S+)/[A-Za-z][A-Za-z0-9_$]*\s+"
    r"\((?P<cell>[A-Za-z][A-Za-z0-9_$]*_X1)\)"
)
LIB_CELL_RE = re.compile(r"\bcell\s*\(\s*([A-Za-z][A-Za-z0-9_$]*)\s*\)")


def size_critical_cells(
    netlist: Path,
    report: Path,
    liberty: Path,
    output: Path,
    *,
    strength: int,
    paths: int,
    max_cells: int,
) -> list[str]:
    blocks = report.read_text(errors="ignore").split("Startpoint:")[1 : paths + 1]
    frequency: collections.Counter[str] = collections.Counter()
    for block in blocks:
        seen = {
            match.group("instance")
            for match in PATH_CELL_RE.finditer(block)
            if not match.group("cell").startswith(("DFF", "SDFF", "LATCH"))
        }
        frequency.update(seen)
    available = set(LIB_CELL_RE.findall(liberty.read_text(errors="ignore")))
    text = netlist.read_text(encoding="utf-8")
    mapped = {match.group("instance"): match.group("cell") for match in INSTANCE_RE.finditer(text)}
    selected = []
    for instance, _ in frequency.most_common():
        source = mapped.get(instance)
        if source is None:
            continue
        target = source[:-1] + str(strength)
        if target not in available:
            continue
        selected.append(instance)
        if len(selected) >= max_cells:
            break
    selected_set = set(selected)

    def replace(match: re.Match[str]) -> str:
        if match.group("instance") not in selected_set:
            return match.group(0)
        target = match.group("cell")[:-1] + str(strength)
        return (
            match.group("indent")
            + target
            + match.group("space")
            + match.group("instance")
            + match.group("tail")
        )

    output.write_text(INSTANCE_RE.sub(replace, text), encoding="utf-8")
    return selected


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--netlist", required=True, type=Path)
    parser.add_argument("--report", required=True, type=Path)
    parser.add_argument("--liberty", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--strength", type=int, choices=(2, 4), default=2)
    parser.add_argument("--paths", type=int, default=20)
    parser.add_argument("--max-cells", type=int, default=50)
    args = parser.parse_args()
    selected = size_critical_cells(
        args.netlist,
        args.report,
        args.liberty,
        args.output,
        strength=args.strength,
        paths=args.paths,
        max_cells=args.max_cells,
    )
    print(f"upsized={len(selected)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
