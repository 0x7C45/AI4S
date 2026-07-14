#!/usr/bin/env python3
"""验证骨架生成 — cocotb testbench + Makefile + verification_skeleton.json

用 Jinja2 渲染 testbench 模板，生成 Makefile（SIM=verilator + -Wno-fatal）。
"""

import json
import os
import shutil
from dataclasses import dataclass
from pathlib import Path

from jinja2 import Environment, FileSystemLoader


@dataclass
class SkeletonResult:
    testbench_path: str        # 生成的 testbench .py 路径
    makefile_path: str         # 生成的 Makefile 路径
    skeleton_json_path: str    # verification_skeleton.json 路径
    generated_tb_dir: str      # generated_tb/ 目录
    generated_tests_dir: str   # generated_tests/ 目录


# Makefile 模板（per D-03 -Wno-fatal, D-05 SIM=verilator）
_MAKEFILE_TEMPLATE = """\
# Auto-generated Makefile — win-ZCode A2 验证环境自动生成
# DUT: {top_module}
TOPLEVEL_LANG = verilog

# per D-05: 默认 verilator（非 vcs）
SIM ?= verilator
WAVES ?= 0

COCOTB_HDL_TIMEUNIT = 1ns
COCOTB_HDL_TIMEPRECISION = 1ps

TOPLEVEL = {top_module}
MODULE = {test_module}

# per D-03: -Wno-fatal 必须（Verilator lint 致命，RTL 有 width warning）
COMPILE_ARGS = -Wno-fatal --coverage-line --coverage-toggle

CASE_ROOT = $(abspath .)

{source_lines}

include $(shell cocotb-config --makefiles)/Makefile.sim
"""


def generate(design_info, out_dir, seed, num_seq):
    """生成 testbench 骨架 + Makefile + verification_skeleton.json

    Args:
        design_info: DesignInfo（rtl_parser 输出）
        out_dir: 产物输出目录（--out）
        seed: 固定种子
        num_seq: 序列数
    Returns:
        SkeletonResult
    """
    out_path = Path(out_dir)
    tb_dir = out_path / "generated_tb"
    tests_dir = out_path / "generated_tests"
    tb_dir.mkdir(parents=True, exist_ok=True)
    tests_dir.mkdir(parents=True, exist_ok=True)

    # ── 1. 渲染 testbench（Jinja2）──
    templates_dir = Path(__file__).parent.parent / "templates"
    env = Environment(loader=FileSystemLoader(str(templates_dir)),
                      trim_blocks=True, lstrip_blocks=True)
    template = env.get_template("cocotb_tb.py.j2")

    test_module = "generated_test"
    tb_filename = f"{test_module}.py"
    tb_path = tb_dir / tb_filename

    # bin 定义注入（per D-13：从 coverage_gen 获取 bin 字典供模板 hit()）
    try:
        from src.coverage_gen import get_bin_dict
        bin_dict = get_bin_dict(design_info)
    except ImportError:
        bin_dict = {}

    rendered = template.render(
        design_info=design_info,
        seed=seed,
        num_seq=num_seq,
        bin_dict=bin_dict,
    )
    tb_path.write_text(rendered, encoding="utf-8")

    # ── 1b. 复制 functional_coverage.py 到 generated_tb/（供 testbench import）──
    fc_src = Path(__file__).parent.parent / "testcases" / "A2_public_dataset" / "functional_coverage.py"
    if not fc_src.exists():
        # 相对路径兜底
        fc_src = Path(__file__).parent.parent.parent / "testcases" / "A2_public_dataset" / "functional_coverage.py"
    if fc_src.exists():
        shutil.copy2(fc_src, tb_dir / "functional_coverage.py")

    # ── 2. 复制 RTL 源到 generated_tb/rtl/（供 Makefile 引用）──
    rtl_copy_dir = tb_dir / "rtl"
    rtl_copy_dir.mkdir(exist_ok=True)
    source_lines = []
    for rf in design_info.files:
        src = Path(rf)
        dst = rtl_copy_dir / src.name
        if src.resolve() != dst.resolve():
            shutil.copy2(src, dst)
        source_lines.append(f"VERILOG_SOURCES += $(CASE_ROOT)/rtl/{src.name}")

    # ── 3. 生成 Makefile ──
    makefile_path = tb_dir / "Makefile"
    makefile_content = _MAKEFILE_TEMPLATE.format(
        top_module=design_info.top_module,
        test_module=test_module,
        source_lines="\n".join(source_lines),
    )
    makefile_path.write_text(makefile_content, encoding="utf-8")

    # ── 4. 写 verification_skeleton.json（spec §3 schema）──
    drivers = []
    monitors = []
    if "AXI" in design_info.inferred_protocols:
        drivers.append({
            "name": "s_axi_read_master",
            "interface": "AXI slave read",
            "class": "AxiMasterRead(AxiReadBus.from_prefix(dut, 's_axi'))",
        })
        drivers.append({
            "name": "m_axi_memory_model",
            "interface": "AXI master read (RAM)",
            "class": "AxiRamRead(AxiReadBus.from_prefix(dut, 'm_axi'), size=2**16)",
        })
        monitors.append({"name": "s_axi_read_monitor", "sample_at": "transaction complete"})
        monitors.append({"name": "m_axi_read_monitor", "sample_at": "RAM read/write"})

    skel_json = {
        "verification_skeleton": {
            "top_module": design_info.top_module,
            "clock_reset_generation": {
                "clock": design_info.clock,
                "clock_period_ns": 10,
                "reset": design_info.reset,
                "reset_active": design_info.reset_active,
                "reset_sequence": "rst high 8 cycles, then low 8 cycles",
            },
            "input_drivers": drivers,
            "output_monitors": monitors,
            "scoreboard": {
                "model": "byte-addressed memory model on m_axi side",
                "compare": "assert read.data == expected_data after each transaction",
            },
            "dut_outputs": [p.name for p in design_info.ports if p.direction == "output"],
            "generated_testbench_path": str(tb_path),
            "makefile_path": str(makefile_path),
        }
    }
    skel_path = out_path / "verification_skeleton.json"
    skel_path.write_text(json.dumps(skel_json, indent=2, ensure_ascii=False), encoding="utf-8")

    # ── 5. generated_tests/ 占位（Phase 2 填约束随机序列）──
    (tests_dir / "README.md").write_text(
        f"# Generated Tests\n\nPhase 2 填约束随机序列（seed={seed}, num_seq={num_seq}）。\n",
        encoding="utf-8",
    )

    return SkeletonResult(
        testbench_path=str(tb_path),
        makefile_path=str(makefile_path),
        skeleton_json_path=str(skel_path),
        generated_tb_dir=str(tb_dir),
        generated_tests_dir=str(tests_dir),
    )
