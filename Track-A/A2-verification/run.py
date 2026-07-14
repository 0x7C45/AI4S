#!/usr/bin/env python3
"""A2 验证环境自动生成 — 主入口

完整流水线: RTL 解析 → testbench 骨架 → 约束随机序列 → 仿真 → 覆盖率收集 → 7 JSON 报告
Phase 1: 解析 → testbench 骨架 → 仿真（骨架门禁）
"""

import argparse
import json
import os
import sys
import traceback
from datetime import datetime
from pathlib import Path

# 确保能 import src 包（无论从哪个 CWD 调用）
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))


def parse_args():
    p = argparse.ArgumentParser(
        description="A2 验证环境自动生成 — RTL → testbench → 仿真 → 覆盖率"
    )
    p.add_argument("--rtl", required=True, help="RTL 源目录或文件（单/多文件）")
    p.add_argument("--top", required=True, help="顶层模块名（逻辑 top，可由 RTL 解析纠正）")
    p.add_argument("--out", required=True, help="单电路结果目录 submission_out/case_name/")
    p.add_argument("--seed", type=int, default=20260630, help="固定随机种子（默认 20260630）")
    p.add_argument("--num-seq", type=int, default=5000, help="约束随机序列数（默认 5000）")
    return p.parse_args()


def main():
    args = parse_args()

    # seed 穿透硬约束（CONSTRAINTS §3）：必须穿透到 random.Random(seed)
    import random
    rng = random.Random(args.seed)

    rtl_path = Path(args.rtl).resolve()
    out_dir = Path(args.out).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    # report.json 各阶段状态（spec §3 report.json schema）
    stages = {
        "parse": {"status": "pending"},
        "skeleton": {"status": "pending"},
        "constraint": {"status": "pending"},
        "simulate": {"status": "pending"},
        "coverage": {"status": "pending"},
    }
    artifacts = {}

    # ── 阶段 1: RTL 解析 → design.json ──
    try:
        from src.rtl_parser import parse as parse_rtl
        design_info = parse_rtl(str(rtl_path), top_hint=args.top)
        design_info.to_design_json(str(out_dir / "design.json"))
        stages["parse"] = {"status": "passed",
                           "top_module": design_info.top_module,
                           "clock": design_info.clock, "reset": design_info.reset}
        artifacts["design_json"] = str(out_dir / "design.json")
        print(f"[parse] OK — top_module={design_info.top_module}, "
              f"clock={design_info.clock}, reset={design_info.reset}, "
              f"protocols={design_info.inferred_protocols}")
    except Exception as e:
        stages["parse"] = {"status": "failed", "error": str(e),
                           "traceback": traceback.format_exc()}
        _write_report(out_dir, stages, artifacts, args)
        print(f"[parse] FAILED: {e}", file=sys.stderr)
        sys.exit(1)

    # ── 阶段 2: testbench 骨架生成 → verification_skeleton.json + generated_tb/ ──
    try:
        from src.skeleton_gen import generate as gen_skeleton
        skel_result = gen_skeleton(design_info, str(out_dir), args.seed, args.num_seq)
        stages["skeleton"] = {"status": "passed",
                              "testbench_path": skel_result.testbench_path}
        artifacts["verification_skeleton_json"] = str(out_dir / "verification_skeleton.json")
        artifacts["generated_tb"] = str(out_dir / "generated_tb")
        print(f"[skeleton] OK — testbench={skel_result.testbench_path}")
    except Exception as e:
        stages["skeleton"] = {"status": "failed", "error": str(e),
                              "traceback": traceback.format_exc()}
        _write_report(out_dir, stages, artifacts, args)
        print(f"[skeleton] FAILED: {e}", file=sys.stderr)
        sys.exit(1)

    # ── 阶段 3: 约束随机序列（Phase 2 完整实现，Phase 1 占位）──
    stages["constraint"] = {"status": "skipped_phase1",
                            "note": "Phase 2: seed+num_seq 约束随机生成"}

    # ── 阶段 4: 仿真 ──
    try:
        from src.sim_runner import run as run_sim
        sim_result = run_sim(str(out_dir), seed=args.seed)
        stages["simulate"] = {"status": "passed" if sim_result.passed else "failed",
                              "exit_code": sim_result.exit_code}
        artifacts["sim_log"] = sim_result.stdout[-2000:] if sim_result.stdout else ""
        print(f"[simulate] {'OK' if sim_result.passed else 'FAILED'} — exit={sim_result.exit_code}")
    except Exception as e:
        stages["simulate"] = {"status": "failed", "error": str(e),
                              "traceback": traceback.format_exc()}
        print(f"[simulate] FAILED: {e}", file=sys.stderr)

    # ── 阶段 5: 覆盖率收集（Phase 2 完整实现，Phase 1 占位）──
    stages["coverage"] = {"status": "skipped_phase1",
                          "note": "Phase 2: line/branch/functional 覆盖率收集"}

    # ── 写 report.json ──
    _write_report(out_dir, stages, artifacts, args)
    print(f"\n[done] 产物目录: {out_dir}")


def _write_report(out_dir, stages, artifacts, args):
    """写 report.json（spec §3 report.json schema）"""
    report = {
        "report": {
            "pipeline": stages,
            "artifacts": artifacts,
            "coverage_summary": {},
            "reproducible_command": (
                f"python3 run.py --rtl {args.rtl} --top {args.top} "
                f"--out {args.out} --seed {args.seed} --num-seq {args.num_seq}"
            ),
            "timestamp": datetime.now().isoformat(),
        }
    }
    with open(out_dir / "report.json", "w", encoding="utf-8") as f:
        json.dump(report, f, indent=2, ensure_ascii=False)


if __name__ == "__main__":
    main()
