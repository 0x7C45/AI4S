#!/usr/bin/env python3
"""RTL 死码分析 — 识别 generate/if/parameter 不可达分支

per D-15, CONSTRAINTS §10: case1 line 53% 根因是参数化死码。
SEGMENT_COUNT==1（直通）/ EXPAND（扩展）/ else（shrink）三分支，
测试配置 S=32/M=16 使前两分支恒假。
"""

import re
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class DeadCodeInfo:
    unreachable_lines: list = field(default_factory=list)   # 不可达行号列表
    dead_ranges: list = field(default_factory=list)          # [(start, end, reason)]
    active_conditions: dict = field(default_factory=dict)    # 参数实际值


# 参数化条件正则：if (PARAM == VALUE) / if (PARAM != VALUE) / generate if (PARAM)
_RE_IF_PARAM = re.compile(
    r'(?:if|else\s+if)\s*\(\s*([A-Z_][A-Z0-9_]*)\s*(==|!=|>=|<=|>|<)\s*(\w+)\s*\)'
)
_RE_GENERATE_IF = re.compile(
    r'generate\s*(?:\s*@.+)?\s*if\s*\(\s*([A-Z_][A-Z0-9_]*)\s*(==|!=|>=|<=|>|<)\s*(\w+)\s*\)',
    re.IGNORECASE
)


def analyze(rtl_files, parameters=None):
    """分析 RTL 死码

    Args:
        rtl_files: RTL 文件路径列表
        parameters: 参数实际配置（如 {'S_DATA_WIDTH': 32, 'M_DATA_WIDTH': 16}）
    Returns:
        DeadCodeInfo
    """
    parameters = parameters or {}
    # 计算派生参数（如 SEGMENT_COUNT / EXPAND）
    derived = _compute_derived_params(parameters)

    unreachable = []
    dead_ranges = []

    for rf in rtl_files:
        path = Path(rf)
        if not path.exists():
            continue
        lines = path.read_text(encoding="utf-8", errors="replace").split("\n")
        in_dead_block = False
        dead_start = 0
        dead_reason = ""

        for i, line in enumerate(lines, 1):
            stripped = line.strip()

            # 检测 if (PARAM OP VALUE)
            m = _RE_IF_PARAM.search(stripped) or _RE_GENERATE_IF.search(stripped)
            if m:
                param_name, op, val_str = m.group(1), m.group(2), m.group(3)
                is_dead = _evaluate_condition(param_name, op, val_str, parameters, derived)
                if is_dead:
                    in_dead_block = True
                    dead_start = i
                    dead_reason = f"{param_name} {op} {val_str} 为假（参数配置使条件恒假）"

            # 追踪块结束（简化：else / endmodule / 下一条件 重置）
            if in_dead_block:
                if re.match(r'\s*else\b', stripped) or 'endgenerate' in stripped:
                    dead_ranges.append((dead_start, i - 1, dead_reason))
                    unreachable.extend(range(dead_start, i))
                    in_dead_block = False
                    # else 块是激活的，不标记死码

        # 块未正常关闭
        if in_dead_block:
            dead_ranges.append((dead_start, len(lines), dead_reason))
            unreachable.extend(range(dead_start, len(lines) + 1))

    return DeadCodeInfo(
        unreachable_lines=sorted(set(unreachable)),
        dead_ranges=dead_ranges,
        active_conditions={**parameters, **derived},
    )


def _compute_derived_params(parameters):
    """计算派生参数（SEGMENT_COUNT / EXPAND 等）"""
    derived = {}
    try:
        s_data = int(parameters.get("S_DATA_WIDTH", 0))
        m_data = int(parameters.get("M_DATA_WIDTH", 0))
        if s_data > 0 and m_data > 0:
            s_strb = s_data // 8
            m_strb = m_data // 8
            derived["S_STRB_WIDTH"] = s_strb
            derived["M_STRB_WIDTH"] = m_strb
            derived["EXPAND"] = 1 if m_strb > s_strb else 0
            if m_strb != s_strb:
                if derived["EXPAND"]:
                    derived["SEGMENT_COUNT"] = m_strb // s_strb
                else:
                    derived["SEGMENT_COUNT"] = s_strb // m_strb
            else:
                derived["SEGMENT_COUNT"] = 1
    except (ValueError, ZeroDivisionError):
        pass
    return derived


def _evaluate_condition(param_name, op, val_str, parameters, derived):
    """判断条件是否恒假（死码）"""
    all_params = {**parameters, **derived}
    if param_name not in all_params:
        return False

    actual = all_params[param_name]
    try:
        actual = int(actual)
    except (ValueError, TypeError):
        return False

    try:
        expected = int(val_str)
    except ValueError:
        # val_str 可能是参数名，简化处理
        return False

    if op == "==":
        return actual != expected   # 条件为假 → 死码
    elif op == "!=":
        return actual == expected
    elif op == ">":
        return not (actual > expected)
    elif op == "<":
        return not (actual < expected)
    elif op == ">=":
        return not (actual >= expected)
    elif op == "<=":
        return not (actual <= expected)
    return False
