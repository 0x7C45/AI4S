#!/usr/bin/env python3
"""Reproduce every configured public A3 point in the official Docker image."""

from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import json
import re
import subprocess
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
IMAGE = "my_siliconcompiler_image:latest"
AREA_RE = re.compile(r"Chip area for module '[^']+':\s*([0-9.]+)")
CELLS_RE = re.compile(r"Number of cells:\s*([0-9]+)")
SLACK_RE = re.compile(r"worst slack(?:\s+max)?\s+(-?[0-9.]+)")
CELL_RE = re.compile(r"\bcell\s*\(\s*([A-Za-z][A-Za-z0-9_$]*)\s*\)")
INSTANCE_RE = re.compile(r"(?m)^\s*([A-Za-z][A-Za-z0-9_$]*)\s+(?:\\\S+|\S+)\s*\(")


def liberty_areas(path: Path) -> dict[str, float]:
    text = path.read_text(errors="ignore")
    matches = list(CELL_RE.finditer(text))
    areas = {}
    for index, match in enumerate(matches):
        segment = text[match.end() : matches[index + 1].start() if index + 1 < len(matches) else len(text)]
        area = re.search(r"\barea\s*:\s*([0-9.]+)\s*;", segment)
        if area:
            areas[match.group(1)] = float(area.group(1))
    return areas


def netlist_area(path: Path, areas: dict[str, float]) -> float:
    cells = [cell for cell in INSTANCE_RE.findall(path.read_text(errors="ignore")) if cell != "module"]
    missing = sorted({cell for cell in cells if cell not in areas})
    if missing:
        raise ValueError(f"cells missing Liberty area: {', '.join(missing)}")
    return sum(areas[cell] for cell in cells)


def load_opensta_helpers():
    path = ROOT / "testcases" / "scripts" / "run_opensta.py"
    spec = importlib.util.spec_from_file_location("a3_run_opensta", path)
    assert spec and spec.loader
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.sanitize_for_opensta, module.write_eval_sdc


def docker(
    command: str,
    output: Path,
    timeout: int,
    *,
    submission_read_only: bool = True,
) -> subprocess.CompletedProcess[str]:
    submission_mount = f"{ROOT}:/submission" + (":ro" if submission_read_only else "")
    cmd = [
        "docker", "run", "--rm", "--platform", "linux/amd64", "--network", "none",
        "--cpus", "1", "--memory", "10g", "--pids-limit", "512",
        "-e", "MAKEFLAGS=-j1", "-e", "OMP_NUM_THREADS=1", "-e", "OPENBLAS_NUM_THREADS=1",
        "-v", submission_mount, "-v", f"{output}:/output", "-w", "/submission",
        IMAGE, "/bin/bash", "-lc", f"export PATH=/root/.local/bin:$PATH; {command}",
    ]
    return subprocess.run(cmd, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=timeout)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path, default=Path("/tmp/a3-official-baseline"))
    parser.add_argument("--only", help="Optional circuit ID, for example LSV01")
    parser.add_argument("--config", type=Path, default=ROOT / "config.json")
    parser.add_argument("--timeout", type=int, default=300)
    args = parser.parse_args()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    sanitize, write_sdc = load_opensta_helpers()
    cell_areas = liberty_areas(ROOT / "testcases" / "lib" / "nangate45" / "NangateOpenCellLibrary_typical.lib")
    config_path = args.config.resolve()
    try:
        config_in_container = "/submission/" + str(config_path.relative_to(ROOT))
    except ValueError as exc:
        raise SystemExit("--config must be inside the A3 submission directory") from exc
    config = json.loads(config_path.read_text())
    with (ROOT / "testcases" / "MANIFEST.csv").open(newline="") as handle:
        cases = [row for row in csv.DictReader(handle) if row["split"] == "public"]
    if args.only:
        cases = [row for row in cases if row["id"] == args.only]
    if not cases:
        raise SystemExit("no matching public circuits")

    metadata_path = output / "run_metadata.json"
    metadata = {
        "config_sha256": hashlib.sha256(config_path.read_bytes()).hexdigest(),
        "image": IMAGE,
    }
    if metadata_path.exists() and json.loads(metadata_path.read_text()) != metadata:
        raise SystemExit("output directory belongs to a different config or image; choose a fresh --output")
    metadata_path.write_text(json.dumps(metadata, indent=2) + "\n")

    build_dir = output / "build"
    build_dir.mkdir(exist_ok=True)
    build = docker("make -j1 build", build_dir, args.timeout, submission_read_only=False)
    (build_dir / "build.console.log").write_text(build.stdout)
    if build.returncode != 0:
        raise SystemExit("submission build failed; see build/build.console.log")

    results_path = output / "results.csv"
    fields = ["circuit", "point", "name", "synth_status", "sta_status", "runtime_s", "cells", "area", "wns_ns", "arrival_ns", "output"]
    existing = {}
    if results_path.exists():
        with results_path.open(newline="") as handle:
            existing = {(r["circuit"], int(r["point"])): r for r in csv.DictReader(handle)}
    selected_circuits = {row["id"] for row in cases}
    results = {key: value for key, value in existing.items() if key[0] not in selected_circuits}
    for row in cases:
        point_list = config.get(row["id"], config["$default"])
        for point, point_config in enumerate(point_list, 1):
            key = (row["id"], point)
            point_dir = output / row["id"] / f"p{point}"
            point_dir.mkdir(parents=True, exist_ok=True)
            rtl = f"/submission/testcases/{row['path']}/{row['rtl']}"
            sdc = f"/submission/testcases/{row['path']}/constraints.sdc"
            lib = "/submission/testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib"
            synth = " ".join([
                "make -j1 synth", f"RTL={rtl}", f"TOP={row['top']}", f"SDC={sdc}",
                f"LIBERTY={lib}", f"CONFIG={config_in_container}", f"CIRCUIT={row['id']}",
                f"POINT={point}", "OUT_DIR=/output",
            ])
            start = time.monotonic()
            try:
                proc = docker(synth, point_dir, args.timeout)
                runtime = time.monotonic() - start
                (point_dir / "synth.console.log").write_text(proc.stdout)
                synth_ok = proc.returncode == 0 and (point_dir / "netlist.v").stat().st_size > 0
            except (subprocess.TimeoutExpired, FileNotFoundError) as exc:
                runtime, synth_ok, proc = time.monotonic() - start, False, None
                (point_dir / "synth.console.log").write_text(str(exc))
            log = (point_dir / ".synth_tool" / "yosys.log").read_text(errors="ignore") if (point_dir / ".synth_tool" / "yosys.log").exists() else ""
            areas, cells = AREA_RE.findall(log), CELLS_RE.findall(log)
            sta_status, wns = "not_run", None
            final_area = netlist_area(point_dir / "netlist.v", cell_areas) if synth_ok else None
            if synth_ok:
                sanitize(point_dir / "netlist.v", point_dir / "netlist.opensta.v")
                write_sdc(ROOT / "testcases" / row["path"] / "constraints.sdc", point_dir / "constraints.eval.sdc")
                tcl = "\n".join([
                    f"read_liberty {lib}", "read_verilog /output/netlist.opensta.v", f"link_design {row['top']}",
                    "read_sdc /output/constraints.eval.sdc", "report_worst_slack > /output/wns.rpt", "exit", "",
                ])
                (point_dir / "run_sta.tcl").write_text(tcl)
                try:
                    sta = docker("sta /output/run_sta.tcl", point_dir, 120)
                    (point_dir / "opensta.log").write_text(sta.stdout)
                    slack_text = (point_dir / "wns.rpt").read_text(errors="ignore") if (point_dir / "wns.rpt").exists() else ""
                    match = SLACK_RE.search(slack_text)
                    wns = float(match.group(1)) if match else None
                    sta_status = "ok" if sta.returncode == 0 and wns is not None and final_area is not None and "Error:" not in sta.stdout else "fail"
                except subprocess.TimeoutExpired as exc:
                    sta_status = "timeout"
                    (point_dir / "opensta.log").write_text(str(exc))
            record = {
                "circuit": row["id"], "point": point, "name": point_config.get("name", f"p{point}"),
                "synth_status": "ok" if synth_ok else "fail", "sta_status": sta_status,
                "runtime_s": f"{runtime:.3f}", "cells": cells[-1] if cells else "",
                "area": f"{final_area:.6f}" if final_area is not None else (areas[-1] if areas else ""), "wns_ns": "" if wns is None else f"{wns:.6f}",
                "arrival_ns": "" if wns is None else f"{max(0.0, -wns):.6f}", "output": str(point_dir),
            }
            results[key] = record
            with results_path.open("w", newline="") as handle:
                writer = csv.DictWriter(handle, fieldnames=fields)
                writer.writeheader(); writer.writerows(results[k] for k in sorted(results))
            print(f"{row['id']} p{point}: synth={record['synth_status']} sta={sta_status} t={record['runtime_s']} area={record['area']} arrival={record['arrival_ns']}", flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
