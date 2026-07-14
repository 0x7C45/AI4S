#!/usr/bin/env python3
"""Select the best seven generic points from reproduced candidate batches."""

from __future__ import annotations

import argparse
import csv
import itertools
import json
from collections import defaultdict
from pathlib import Path

from score_submission import hypervolume


ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--candidate", action="append", nargs=2,
        metavar=("CONFIG_JSON", "RESULTS_CSV"), required=True,
    )
    parser.add_argument(
        "--reference", type=Path,
        default=ROOT / "testcases" / "references" / "reference_results_public.csv",
    )
    args = parser.parse_args()

    references: dict[str, list[tuple[float, float]]] = defaultdict(list)
    with args.reference.open(newline="") as handle:
        for row in csv.DictReader(handle):
            if row["status"] == "ok":
                references[row["id"]].append((float(row["arrival_ns"]), float(row["area"])))
    nadirs = {
        circuit: (1.05 * max(p[0] for p in points), 1.05 * max(p[1] for p in points))
        for circuit, points in references.items()
    }
    reference_hv = {
        circuit: hypervolume(points, nadirs[circuit]) for circuit, points in references.items()
    }

    candidates = []
    for config_name, results_name in args.candidate:
        config_path, results_path = Path(config_name), Path(results_name)
        point_configs = json.loads(config_path.read_text())["$default"]
        measured: dict[int, dict[str, tuple[float, float]]] = defaultdict(dict)
        with results_path.open(newline="") as handle:
            for row in csv.DictReader(handle):
                if row["synth_status"] != "ok" or row["sta_status"] != "ok":
                    raise SystemExit(f"candidate failed: {results_path} {row['circuit']} p{row['point']}")
                measured[int(row["point"])][row["circuit"]] = (
                    float(row["arrival_ns"]), float(row["area"])
                )
        for point, point_config in enumerate(point_configs, 1):
            missing = sorted(set(references) - set(measured[point]))
            if missing:
                raise SystemExit(f"missing circuits in {results_path} point {point}: {', '.join(missing)}")
            candidates.append((config_path.name, point_config, measured[point]))

    if len(candidates) < 7:
        raise SystemExit("at least seven candidate points are required")
    best_score, best_indices = -1.0, None
    for indices in itertools.combinations(range(len(candidates)), 7):
        score = 0.0
        for circuit in references:
            points = [candidates[index][2][circuit] for index in indices]
            score += min(2.0, hypervolume(points, nadirs[circuit]) / reference_hv[circuit])
        if score > best_score:
            best_score, best_indices = score, indices

    assert best_indices is not None
    mean_q = best_score / len(references)
    print(f"public_q_ppa_mean={mean_q:.9f}")
    print(f"public_ppa_proxy_90={45.0 * mean_q:.6f}")
    print("selected_default=")
    print(json.dumps([candidates[index][1] for index in best_indices], ensure_ascii=False, indent=2))
    print("sources=")
    for index in best_indices:
        print(f"{candidates[index][0]}: {candidates[index][1]['name']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
