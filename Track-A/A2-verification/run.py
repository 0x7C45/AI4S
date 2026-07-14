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

    # ── 阶段 3: 约束随机序列 + 功能 bin 定义 ──
    try:
        from src.constraint_gen import generate as gen_constraint
        from src.coverage_gen import generate_bins as gen_bins
        constraint_path = gen_constraint(design_info, args.seed, args.num_seq, str(out_dir))
        bins_path = gen_bins(design_info, str(out_dir))
        stages["constraint"] = {"status": "passed", "seed": args.seed,
                                "sequence_count": args.num_seq}
        artifacts["constraints_json"] = constraint_path
        artifacts["coverage_bins_json"] = bins_path
        print(f"[constraint] OK — seed={args.seed}, seq={args.num_seq}")
    except Exception as e:
        stages["constraint"] = {"status": "failed", "error": str(e)}
        print(f"[constraint] FAILED: {e}", file=sys.stderr)

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

    # ── 阶段 5: 覆盖率收集 ──
    try:
        from src.coverage_collect import collect as collect_cov
        from src.report_gen import generate as gen_report
        from src.dead_code_analyzer import analyze as analyze_dead_code
        import shutil

        # 仿真产物路径（coverage.dat + functional_coverage.json 在 generated_tb/）
        sim_tb_dir = out_dir / "generated_tb"
        fc_in_tb = sim_tb_dir / "functional_coverage.json"

        # 把 functional_coverage.json 复制到 out_dir 根（spec 要求 7 JSON 在 --out 下）
        if fc_in_tb.exists():
            shutil.copy2(fc_in_tb, out_dir / "functional_coverage.json")

        # ── 死码分析（per SC#5：识别 generate/if 参数化死码，从分母排除）──
        # 测试配置参数来自 cocotb_top wrapper（如 case1_cocotb_top.v 的 S=32/M=16），
        # 不是 RTL 默认值（默认 S=M=32 → SEGMENT_COUNT=1 全活）。
        # 向上搜 testcase 目录找 *_cocotb_top.v 或 *_top.v，提取其 parameter 实例化值。
        dead_code_info = None
        test_params = _extract_test_params(rtl_path)
        rtl_files_abs = [str(rtl_path / f) if rtl_path.is_dir() else str(rtl_path)
                         for f in (design_info.files or [])]
        # 兜底：若 design_info.files 是相对路径，补全到 rtl_path
        rtl_files_abs = [f if Path(f).is_absolute() else str(rtl_path.parent / f)
                         for f in rtl_files_abs] if rtl_files_abs else [str(rtl_path)]
        try:
            dead_code_info = analyze_dead_code(rtl_files_abs, test_params)
            if dead_code_info.unreachable_lines:
                print(f"[coverage] 死码过滤: {len(dead_code_info.unreachable_lines)} 行不可达 "
                      f"(参数 {test_params})")
        except Exception as dc_err:
            # 死码分析失败不应阻断覆盖率收集（保守不过滤）
            print(f"[coverage] 死码分析失败（保守不过滤）: {dc_err}", file=sys.stderr)
            dead_code_info = None

        cov_data = collect_cov(str(sim_tb_dir), design_info, dead_code_info=dead_code_info)

        sim_info = {"seed": args.seed, "sequence_count": args.num_seq, "sim_time_ns": 0}
        result_path = gen_report(cov_data, sim_info, str(out_dir))
        stages["coverage"] = {
            "status": "passed",
            "line": cov_data.line_pct, "branch": cov_data.branch_pct,
            "functional": cov_data.functional_pct,
        }
        artifacts["coverage_result_json"] = result_path
        artifacts["functional_coverage_json"] = str(out_dir / "functional_coverage.json")
        print(f"[coverage] OK — line={cov_data.line_pct}% branch={cov_data.branch_pct}% "
              f"func={cov_data.functional_pct}%")
    except Exception as e:
        stages["coverage"] = {"status": "failed", "error": str(e),
                              "traceback": traceback.format_exc()}
        print(f"[coverage] FAILED: {e}", file=sys.stderr)

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


def _extract_test_params(rtl_path):
    """提取测试实例化参数（per SC#5 死码分析需要真实配置，非 RTL 默认值）。

    case1 的 RTL 默认 S=M=32（SEGMENT_COUNT=1，全活），但测试 cocotb_top 用 S=32/M=16
    （SEGMENT_COUNT=2，前两分支死）。参数源优先级：
      1. testcase 目录下 *_cocotb_top.v / *_top.v 的顶层 parameter 声明
      2. 空字典（fallback：用 RTL 默认，不过滤死码）

    Returns: dict 如 {'S_DATA_WIDTH': 32, 'M_DATA_WIDTH': 16}
    """
    import re
    params = {}
    # rtl_path 可能是目录或文件；找 testcase 根（含 cocotb_top 的目录）
    search_dirs = []
    if rtl_path.is_dir():
        search_dirs.append(rtl_path)
        search_dirs.append(rtl_path.parent)  # testcase 根通常在 rtl/ 的上一层
    else:
        search_dirs.append(rtl_path.parent)

    for d in search_dirs:
        for top_file in list(d.glob("*_cocotb_top.v")) + list(d.glob("*_top.v")):
            try:
                text = top_file.read_text(encoding="utf-8", errors="replace")
                # 匹配顶层 `parameter NAME = VALUE;`（cocotb_top wrapper 风格）
                for m in re.finditer(
                    r'^\s*parameter\s+([A-Z_][A-Z0-9_]*)\s*=\s*([^;,]+)\s*;',
                    text, re.MULTILINE
                ):
                    name, val = m.group(1), m.group(2).strip()
                    # 只保留整数值（跳过表达式如 S_DATA_WIDTH/8）
                    try:
                        params[name] = int(val)
                    except ValueError:
                        pass
                if params:
                    return params  # 第一个找到的 cocotb_top 即返回
            except Exception:
                continue
    return params


if __name__ == "__main__":
    main()
