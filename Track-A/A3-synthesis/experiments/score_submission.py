#!/usr/bin/env python3
"""Score reproduced A3 points against the official public reference CSV."""

from __future__ import annotations

import argparse
import csv
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def hypervolume(points: list[tuple[float, float]], nadir: tuple[float, float]) -> float:
    """Return the dominated 2D minimization hypervolume clipped to ``nadir``."""
    usable = sorted((arrival, area) for arrival, area in points if arrival < nadir[0] and area < nadir[1])
    best_area = nadir[1]
    volume = 0.0
    for arrival, area in usable:
        if area < best_area:
            volume += (nadir[0] - arrival) * (best_area - area)
            best_area = area
    return volume


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("results", type=Path, help="results.csv from run_submission_baseline.py")
    parser.add_argument(
        "--reference",
        type=Path,
        default=ROOT / "testcases" / "references" / "reference_results_public.csv",
    )
    args = parser.parse_args()

    references: dict[str, list[tuple[float, float, float]]] = defaultdict(list)
    with args.reference.open(newline="") as handle:
        for row in csv.DictReader(handle):
            if row["status"] == "ok":
                references[row["id"]].append(
                    (float(row["arrival_ns"]), float(row["area"]), float(row["runtime_s"]))
                )

    attempts: dict[str, list[float]] = defaultdict(list)
    successful: dict[str, list[tuple[float, float]]] = defaultdict(list)
    with args.results.open(newline="") as handle:
        for row in csv.DictReader(handle):
            circuit = row["circuit"]
            attempts[circuit].append(float(row["runtime_s"]))
            if row["synth_status"] == "ok" and row["sta_status"] == "ok":
                successful[circuit].append((float(row["arrival_ns"]), float(row["area"])))

    rows = []
    for circuit in sorted(references):
        ref = references[circuit]
        nadir = (1.05 * max(p[0] for p in ref), 1.05 * max(p[1] for p in ref))
        ref_hv = hypervolume([(p[0], p[1]) for p in ref], nadir)
        user_hv = hypervolume(successful[circuit], nadir)
        q_ppa = min(2.0, user_hv / ref_hv) if ref_hv and successful[circuit] else 0.0
        ref_time = sum(p[2] for p in ref)
        user_time = sum(attempts[circuit])
        q_time = min(1.0, ref_time / user_time) if user_time else 0.0
        tech = 45.0 * q_ppa + 5.0 * q_time
        rows.append((circuit, q_ppa, q_time, tech, user_hv, ref_hv))

    print("circuit,q_ppa,q_time,tech_95,user_hv,reference_hv")
    for row in rows:
        print(f"{row[0]},{row[1]:.9f},{row[2]:.9f},{row[3]:.6f},{row[4]:.6f},{row[5]:.6f}")
    if rows:
        public_ppa = sum(45.0 * row[1] for row in rows) / len(rows)
        public_time = sum(5.0 * row[2] for row in rows) / len(rows)
        print(f"public_ppa_proxy_90={public_ppa:.6f}")
        print(f"public_time_proxy_5={public_time:.6f}")
        print(f"public_technical_proxy_95={public_ppa + public_time:.6f}")
        print("note=proxy only: official correctness simulation and hidden circuits are not represented")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
