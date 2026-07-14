#!/usr/bin/env python3
"""约束随机配置生成 — constraints.json

per D-17, CONSTRAINTS §3: seed=20260630, sequence_count=5000。
按 design_info.inferred_protocols 生成 transaction_variables。
"""

import json
from pathlib import Path


def generate(design_info, seed, num_seq, out_dir):
    """生成 constraints.json

    Args:
        design_info: DesignInfo（rtl_parser 输出）
        seed: 固定种子（20260630）
        num_seq: 序列数（5000）
        out_dir: 输出目录
    Returns:
        constraints.json 路径
    """
    # 按协议生成 transaction_variables
    tx_vars = {}
    hard_constraints = []
    coverage_guidance = []

    protocols = design_info.inferred_protocols

    if "AXI" in protocols:
        # 从参数推断位宽（默认值兜底）
        params = design_info.parameters
        addr_width = _extract_int(params.get("ADDR_WIDTH", "32"), 32)
        id_width = _extract_int(params.get("ID_WIDTH", "8"), 8)

        tx_vars["address"] = {"type": "bitvec", "width": addr_width}
        tx_vars["length_bytes"] = {"type": "int", "min": 1, "max": 256}
        tx_vars["size"] = {"type": "int", "values": [0, 1, 2]}
        tx_vars["burst"] = {"type": "enum", "values": ["INCR"]}
        tx_vars["arid"] = {"type": "bitvec", "width": id_width}
        tx_vars["source_backpressure"] = {"type": "enum", "values": ["none", "light", "heavy"]}
        tx_vars["downstream_backpressure"] = {"type": "enum", "values": ["none", "light", "heavy"]}
        tx_vars["combined_backpressure"] = {"type": "enum", "values": ["none", "light", "heavy"]}

        addr_max = (1 << addr_width) - 1
        hard_constraints = [
            f"0 <= address < {addr_max}",
            "1 <= length_bytes <= 256",
            f"address + length_bytes <= {addr_max}",
            "size in [0, 1, 2]",
        ]
        coverage_guidance = [
            "覆盖 read_length 边界值: 1,2,4,8,16,32,64,128,256",
            "覆盖 address 4K 边界和对齐",
            "覆盖 burst_size 全部取值",
            "覆盖 backpressure 各通道组合",
        ]

    elif "SRAM" in protocols:
        tx_vars["address"] = {"type": "bitvec", "width": 16}
        tx_vars["data"] = {"type": "bitvec", "width": 32}
        tx_vars["we"] = {"type": "enum", "values": ["read", "write"]}
        hard_constraints = ["0 <= address < 65536"]

    elif "valid-ready" in protocols:
        tx_vars["data"] = {"type": "bitvec", "width": 32}
        tx_vars["valid_delay"] = {"type": "int", "min": 0, "max": 10}
        tx_vars["ready_backpressure"] = {"type": "enum", "values": ["none", "light", "heavy"]}

    config = {
        "constraint_random_test": {
            "name": design_info.top_module,
            "solver_target": "directed_random",
            "seed": seed,
            "sequence_count": num_seq,
            "transaction_variables": tx_vars,
            "hard_constraints": hard_constraints,
            "coverage_guidance_constraints": coverage_guidance,
            "objective": "maximize functional coverage across protocol scenarios and corner cases",
            "coverage_feedback_adjustments": [],
        }
    }

    out_path = Path(out_dir) / "constraints.json"
    out_path.write_text(json.dumps(config, indent=2, ensure_ascii=False), encoding="utf-8")
    return str(out_path)


def _extract_int(param_expr, default):
    """从参数表达式提取整数值（如 '32' → 32, '(S_DATA_WIDTH/8)' → default）"""
    if isinstance(param_expr, int):
        return param_expr
    s = str(param_expr).strip()
    if s.isdigit():
        return int(s)
    return default
