#!/usr/bin/env python3
"""覆盖率收集 — coverage.dat LCOV 解析 + 功能覆盖汇总

per D-11: 行覆盖率 LCOV DA 解析
per D-12: 分支覆盖率 LCOV BRDA 解析
per D-14: 按文件过滤排除 wrapper
per D-15: 死码过滤（从分母排除不可达行）
"""

import json
import subprocess
import os
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class CoverageData:
    line_pct: float = 0.0
    branch_pct: float = 0.0
    functional_pct: float = 0.0
    line_covered: int = 0
    line_total: int = 0
    branch_covered: int = 0
    branch_total: int = 0
    func_covered: int = 0
    func_total: int = 0
    per_file: dict = field(default_factory=dict)


# wrapper 文件名特征（per D-14）
_WRAPPER_KEYWORDS = ("cocotb_top", "wrapper", "_top.v", "tb_top")


def collect(sim_out_dir, design_info, dead_code_info=None, use_docker=True):
    """收集覆盖率

    Args:
        sim_out_dir: 仿真输出目录（含 coverage.dat + functional_coverage.json）
        design_info: DesignInfo
        dead_code_info: DeadCodeInfo（可选，死码过滤）
        use_docker: True=用 Docker 容器跑 verilator_coverage
    Returns:
        CoverageData
    """
    sim_path = Path(sim_out_dir)
    cov_dat = sim_path / "coverage.dat"

    # ── 1. 转 LCOV .info ──
    info_text = ""
    if cov_dat.exists():
        info_text = _convert_to_lcov(cov_dat, use_docker)

    # ── 2. 解析 LCOV ──
    file_data = _parse_lcov(info_text) if info_text else {}

    # ── 3. 按文件过滤（排除 wrapper，per D-14）──
    rtl_files = {Path(f).name: f for f in design_info.files}
    filtered = {}
    for fname, fdata in file_data.items():
        short = Path(fname).name
        if _is_wrapper(short):
            continue
        filtered[short] = fdata

    # ── 4. 死码过滤（per D-15）──
    dead_lines = set()
    if dead_code_info:
        dead_lines = set(dead_code_info.unreachable_lines)

    # ── 5. 汇总 line/branch ──
    total_line_hit = total_line_all = 0
    total_br_hit = total_br_all = 0

    for fname, fdata in filtered.items():
        # line
        da_all = [d for d in fdata["DA"]]
        if dead_lines:
            # 排除死码行（行号在 dead_lines 中的 DA）
            da_all = [d for d in da_all if d[0] not in dead_lines]
        da_hit = sum(1 for d in da_all if d[1] > 0)
        total_line_hit += da_hit
        total_line_all += len(da_all)

        # branch
        br_all = fdata["BRDA"]
        if dead_lines:
            br_all = [b for b in br_all if b[0] not in dead_lines]
        br_hit = sum(1 for b in br_all if b[3] not in ("0", "-", "") and int(b[3] or 0) > 0)
        total_br_hit += br_hit
        total_br_all += len(br_all)

    line_pct = 100.0 * total_line_hit / total_line_all if total_line_all else 0.0
    branch_pct = 100.0 * total_br_hit / total_br_all if total_br_all else 0.0

    # ── 6. 功能覆盖（从 functional_coverage.json 读）──
    func_pct = 0.0
    func_covered = func_total = 0
    fc_path = sim_path / "functional_coverage.json"
    if not fc_path.exists():
        # 可能在上层目录
        fc_path = sim_path.parent / "functional_coverage.json"
    if fc_path.exists():
        try:
            fc = json.loads(fc_path.read_text(encoding="utf-8"))
            fc_data = fc.get("functional_coverage", fc)
            func_covered = fc_data.get("covered_bins", 0)
            func_total = fc_data.get("total_bins", 0)
            func_pct = 100.0 * func_covered / func_total if func_total else 0.0
        except (json.JSONDecodeError, KeyError):
            pass

    return CoverageData(
        line_pct=round(line_pct, 2),
        branch_pct=round(branch_pct, 2),
        functional_pct=round(func_pct, 2),
        line_covered=total_line_hit, line_total=total_line_all,
        branch_covered=total_br_hit, branch_total=total_br_all,
        func_covered=func_covered, func_total=func_total,
        per_file={f: {"line": d.get("line_pct", 0), "branch": d.get("branch_pct", 0)}
                  for f, d in filtered.items()},
    )


def _is_wrapper(filename):
    """判断是否 wrapper 文件（per D-14）"""
    lower = filename.lower()
    return any(kw in lower for kw in _WRAPPER_KEYWORDS)


def _convert_to_lcov(cov_dat_path, use_docker=True):
    """用 verilator_coverage 转 LCOV .info 格式"""
    cov_abs = str(cov_dat_path.resolve()).replace("\\", "/")
    if cov_abs[1:3] == ":/":
        drive = cov_abs[0].lower()
        docker_mount = f"//{drive}{cov_abs[2:]}"
    else:
        docker_mount = cov_abs

    if use_docker:
        cmd = [
            "docker", "run", "--rm",
            "--platform", "linux/amd64",
            "--entrypoint", "bash",
            "-v", f"{docker_mount}:/work/coverage.dat:ro",
            "verilator/verilator:v5.050",
            "-c", "verilator_coverage -write-info /dev/stdout /work/coverage.dat 2>/dev/null",
        ]
        env = os.environ.copy()
        env["MSYS_NO_PATHCONV"] = "1"
        try:
            r = subprocess.run(cmd, capture_output=True, text=True, timeout=60, env=env)
            return r.stdout
        except (subprocess.TimeoutExpired, FileNotFoundError):
            return ""
    else:
        try:
            r = subprocess.run(
                ["verilator_coverage", "-write-info", "/dev/stdout", str(cov_dat_path)],
                capture_output=True, text=True, timeout=30,
            )
            return r.stdout
        except (subprocess.TimeoutExpired, FileNotFoundError):
            return ""


def _parse_lcov(info_text):
    """解析 LCOV .info 格式

    Returns: {filename: {DA: [(line, count)], BRDA: [(line, block, branch, taken)], line_pct, branch_pct}}
    """
    files = {}
    cur_file = None
    cur_data = None

    for line in info_text.split("\n"):
        line = line.strip()
        if line.startswith("SF:"):
            cur_file = line[3:].split("/")[-1]  # 取文件名
            cur_data = {"DA": [], "BRDA": []}
            files[cur_file] = cur_data
        elif line.startswith("DA:") and cur_data is not None:
            parts = line[3:].split(",")
            if len(parts) >= 2:
                cur_data["DA"].append((int(parts[0]), int(parts[1])))
        elif line.startswith("BRDA:") and cur_data is not None:
            parts = line[5:].split(",")
            if len(parts) >= 4:
                cur_data["BRDA"].append(
                    (int(parts[0]), parts[1], parts[2], parts[3])
                )
        elif line == "endef" or line == "end_of_record":
            cur_file = None
            cur_data = None

    # 算每文件百分比
    for fname, fdata in files.items():
        da = fdata["DA"]
        fdata["line_pct"] = 100.0 * sum(1 for d in da if d[1] > 0) / len(da) if da else 0.0
        br = fdata["BRDA"]
        fdata["branch_pct"] = 100.0 * sum(1 for b in br if b[3] not in ("0", "-", "") and int(b[3] or 0) > 0) / len(br) if br else 0.0

    return files
