#!/usr/bin/env python3
"""报告生成 — coverage_result.json

per D-16: 综合 C = 0.4×line + 0.3×branch + 0.3×functional（禁止 0.42/0.28/0.30）
"""

import json
from pathlib import Path


def generate(coverage_data, sim_info, out_dir):
    """生成 coverage_result.json

    Args:
        coverage_data: CoverageData（coverage_collect 输出）
        sim_info: dict，含 seed/sequence_count/sim_time_ns 等
        out_dir: 输出目录
    Returns:
        coverage_result.json 路径
    """
    line_pct = coverage_data.line_pct
    branch_pct = coverage_data.branch_pct
    func_pct = coverage_data.functional_pct

    # per D-16: 公式 0.4/0.3/0.3（禁止 0.42/0.28/0.30）
    composite_pct = round(
        0.4 * line_pct + 0.3 * branch_pct + 0.3 * func_pct, 2
    )

    result = {
        "coverage_result": {
            "simulator": "Verilator 5.050",
            "coverage_scope": "RTL subtree (wrapper excluded)",
            "run": {
                "seed": sim_info.get("seed", 20260630),
                "sequence_count": sim_info.get("sequence_count", 5000),
                "sim_time_ns": sim_info.get("sim_time_ns", 0),
            },
            "coverage": {
                "line": {
                    "covered": coverage_data.line_covered,
                    "total": coverage_data.line_total,
                    "percent": line_pct,
                },
                "branch": {
                    "covered": coverage_data.branch_covered,
                    "total": coverage_data.branch_total,
                    "percent": branch_pct,
                },
                "functional": {
                    "covered": coverage_data.func_covered,
                    "total": coverage_data.func_total,
                    "percent": func_pct,
                },
                "composite": {
                    "formula": "0.4 * line + 0.3 * branch + 0.3 * functional",
                    "percent": composite_pct,
                },
            },
        }
    }

    out_path = Path(out_dir) / "coverage_result.json"
    out_path.write_text(json.dumps(result, indent=2, ensure_ascii=False), encoding="utf-8")
    return str(out_path)
