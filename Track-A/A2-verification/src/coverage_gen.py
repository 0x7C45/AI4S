#!/usr/bin/env python3
"""功能 bin 定义 — coverage_bins.json

per D-17: 4 类模板（FSM/数据通路/存储器/AXI 协议），按 design_info 激活子集。
per D-18: 每个 bin 对应可解释的功能场景。
"""

import json
from pathlib import Path


# ── 4 类 bin 模板（per D-17）──

_BIN_TEMPLATES = {
    "AXI": [
        {"name": "read_length", "values": [
            "1", "2_to_3", "4", "5_to_15", "16_to_31",
            "32_to_63", "64_to_127", "128_to_256"]},
        {"name": "address_alignment", "values": [
            "aligned_4_byte", "aligned_2_byte", "unaligned", "near_4k_boundary"]},
        {"name": "burst_size", "values": [
            "size_1_byte", "size_2_byte", "size_4_byte", "default_max_size"]},
        {"name": "adapter_path", "values": [
            "width_conversion", "merge_master_beats", "narrow_size_read", "partial_last_beat"]},
        {"name": "backpressure", "values": [
            "source_rready_pause", "downstream_arready_pause",
            "downstream_rvalid_pause", "combined_pause"]},
    ],
    "FSM": [
        {"name": "state_transition", "values": [
            "idle_to_active", "active_to_complete", "active_to_error",
            "complete_to_idle", "error_to_idle"]},
        {"name": "state_visited", "values": [
            "state_idle", "state_active", "state_complete", "state_error"]},
        {"name": "state_self_loop", "values": [
            "idle_self_loop", "active_self_loop"]},
        {"name": "state_exit_reset", "values": [
            "reset_to_idle", "reset_to_active"]},
    ],
    "DATAPATH": [
        {"name": "data_width_boundary", "values": [
            "min_width", "half_width", "full_width", "over_width"]},
        {"name": "data_alignment", "values": [
            "byte_aligned", "halfword_aligned", "word_aligned", "unaligned"]},
        {"name": "sign_extension", "values": [
            "positive_extend", "negative_extend", "zero_extend"]},
        {"name": "overflow_underflow", "values": [
            "no_overflow", "overflow", "underflow"]},
    ],
    "MEMORY": [
        {"name": "read_after_write", "values": [
            "raw_same_addr", "raw_diff_addr"]},
        {"name": "write_after_read", "values": [
            "war_same_addr", "war_diff_addr"]},
        {"name": "address_boundary", "values": [
            "addr_zero", "addr_max", "addr_mid"]},
        {"name": "fifo_full_empty", "values": [
            "fifo_empty_read", "fifo_full_write", "fifo_half"]},
        {"name": "concurrent_access", "values": [
            "simultaneous_rw", "sequential_rw"]},
    ],
}


def _detect_active_templates(design_info):
    """扫描 design_info 特征，激活对应 bin 模板类"""
    active = []
    port_names_lower = [p.name.lower() for p in design_info.ports]
    param_names = set(design_info.parameters.keys())
    all_text = " ".join(port_names_lower)

    # AXI：s_axi_/m_axi_ 前缀
    if "AXI" in design_info.inferred_protocols:
        active.append("AXI")

    # FSM：state_reg/next_state 信号（需读 RTL 文本，这里按端口名近似）
    if any("state" in n for n in port_names_lower):
        active.append("FSM")

    # 数据通路：DATA_WIDTH 参数
    if any("DATA_WIDTH" in p for p in param_names) or any("width" in n for n in port_names_lower):
        active.append("DATAPATH")

    # 存储器：ram/fifo/mem 关键字
    if any(kw in all_text for kw in ("ram", "fifo", "mem", "dout", "din")):
        active.append("MEMORY")

    return active if active else ["AXI"]  # 默认 AXI


def generate_bins(design_info, out_dir):
    """生成 coverage_bins.json

    Args:
        design_info: DesignInfo
        out_dir: 输出目录
    Returns:
        coverage_bins.json 路径
    """
    active = _detect_active_templates(design_info)
    bins = []
    for tpl_name in active:
        for cp in _BIN_TEMPLATES[tpl_name]:
            bins.append({"name": cp["name"], "values": list(cp["values"])})

    result = {
        "coverage_bins": {
            "name": f"{design_info.top_module}_functional_bins",
            "measurement": (
                "Bin hits are sampled by generated testbench via FunctionalCoverage.hit() "
                "and reported in functional_coverage.json."
            ),
            "active_templates": active,
            "bins": bins,
        }
    }

    out_path = Path(out_dir) / "coverage_bins.json"
    out_path.write_text(json.dumps(result, indent=2, ensure_ascii=False), encoding="utf-8")
    return str(out_path)


def get_bin_dict(design_info):
    """返回 bin 字典供 testbench 模板注入（coverpoint → [bin_names]）"""
    active = _detect_active_templates(design_info)
    result = {}
    for tpl_name in active:
        for cp in _BIN_TEMPLATES[tpl_name]:
            result[cp["name"]] = list(cp["values"])
    return result
