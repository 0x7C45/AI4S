#!/usr/bin/env python3
"""RTL 接口解析 — 端口/时钟/复位/参数/协议推断

用正则解析 Verilog module 声明（不依赖 PyVerilog，更轻量可控）。
识别真实顶层模块名（per D-07：不盲信 design.json 的 caseN 别名）。
"""

import re
import json
from pathlib import Path
from dataclasses import dataclass, field, asdict


@dataclass
class Port:
    name: str
    direction: str        # input / output / inout
    width: str            # 原始宽度表达式，如 "ADDR_WIDTH-1:0" 或 "1"
    width_bits: str       # 简化的位宽标记（供模板用）
    protocol_group: str = ""   # axi_slave / axi_master / sram / valid_ready / clock_reset / other


@dataclass
class DesignInfo:
    top_module: str
    files: list = field(default_factory=list)
    parameters: dict = field(default_factory=dict)
    ports: list = field(default_factory=list)   # list[Port]
    clock: str = ""
    reset: str = ""
    reset_active: str = "high"   # high / low
    inferred_protocols: list = field(default_factory=list)

    def to_design_json(self, path: str):
        """写 design.json（spec §3 schema）"""
        ports_json = []
        for p in self.ports:
            ports_json.append({
                "name": p.name, "direction": p.direction,
                "width": p.width, "type": "wire",
                "protocol_group": p.protocol_group,
            })
        design = {
            "design": {
                "name": self.top_module,
                "top_module": self.top_module,
                "rtl_files": self.files,
                "parameters": self.parameters,
                "clock_reset": {
                    "clock": self.clock,
                    "reset": self.reset,
                    "reset_active": self.reset_active,
                },
                "ports": ports_json,
                "inferred_protocols": self.inferred_protocols,
            }
        }
        with open(path, "w", encoding="utf-8") as f:
            json.dump(design, f, indent=2, ensure_ascii=False)


# ── 端口方向/宽度正则 ──
_RE_PORT = re.compile(
    r'^\s*(input|output|inout)\s+(?:wire\s+|reg\s+)?'      # direction + 可选 wire/reg
    r'(?:\[(.*?)\])?\s*'                                     # 可选 [width]
    r'([a-zA-Z_][\w]*)\s*,?\s*$',                            # name
)

# ── 模块声明正则 ──
_RE_MODULE = re.compile(r'module\s+([a-zA-Z_][\w]*)')
_RE_MODULE_END = re.compile(r'endmodule')

# ── 参数正则 ──
_RE_PARAM = re.compile(
    r'parameter\s+(?:integer\s+)?([a-zA-Z_][\w]*)\s*=\s*([^,)]+)'
)

# ── 时钟/复位信号名识别 ──
_CLOCK_NAMES = {"clk", "clock", "i_clk", "aclk", "ACLK"}
_RESET_NAMES_HIGH = {"rst", "reset", "rst_n", "nrst"}  # rst_n/nrst 实际低有效，但名匹配后单独判
_RESET_NAMES_LOW = {"rst_n", "reset_n", "nrst", "nreset"}


def _parse_width_str(width_expr):
    """简化宽度表达式为标记（供模板参考，不展开参数化表达式）"""
    if not width_expr:
        return "1"
    return width_expr.strip()


def _classify_protocol(port_name, all_port_names):
    """推断端口所属协议分组（per D-10）"""
    name_lower = port_name.lower()
    # AXI 分组（s_axi_ / m_axi_ 前缀）
    if name_lower.startswith("s_axi_"):
        return "axi_slave"
    if name_lower.startswith("m_axi_"):
        return "axi_master"
    # 时钟/复位
    if name_lower in _CLOCK_NAMES:
        return "clock"
    if name_lower in _RESET_NAMES_HIGH or name_lower in _RESET_NAMES_LOW:
        return "reset"
    # valid/ready stream
    if name_lower.endswith("_valid") or name_lower.endswith("_ready") or name_lower.endswith("_tvalid") or name_lower.endswith("_tready"):
        return "valid_ready"
    # SRAM-like
    if any(kw in name_lower for kw in ("_addr", "_din", "_dout", "_we", "_en", "_cs", "_oe")):
        return "sram"
    return "other"


def _parse_single_file(filepath):
    """解析单个 .v 文件，返回 (module_name, parameters, ports) 列表"""
    text = filepath.read_text(encoding="utf-8", errors="replace")

    # 找所有 module 块
    modules = []
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        line = lines[i]
        m = _RE_MODULE.search(line)
        if m:
            mod_name = m.group(1)
            # 收集 parameter 和 port（直到 endmodule 或下一个 module）
            params = {}
            ports = []
            # 参数可能在 #(...) 块里，端口在 (...) 块里
            # 合并从 module 行到 ; 的所有文本
            block_lines = []
            depth = 0
            j = i
            while j < len(lines):
                bl = lines[j]
                block_lines.append(bl)
                if ";" in bl and depth == 0:
                    # 简单判断：module 声明结束（parameter+port 块完成）
                    # 但要确认 () 配平
                    if bl.count("(") <= bl.count(")"):
                        break
                depth += bl.count("(") - bl.count(")")
                if _RE_MODULE_END.search(bl):
                    break
                j += 1
            block_text = "\n".join(block_lines)

            # 提取参数
            for pm in _RE_PARAM.finditer(block_text):
                pname, pval = pm.group(1).strip(), pm.group(2).strip()
                params[pname] = pval

            # 提取端口（逐行匹配端口声明）
            # 先把块文本按逗号拆分（端口列表里逗号分隔）
            # 但参数块里也有逗号，需要只看 port 列表部分（第一个 ( 到匹配的 )）
            # 简化：找 module 行之后的第一个 ( 开始的段
            port_section = _extract_port_section(block_text)
            if port_section:
                for pline in port_section.split(","):
                    pline = pline.strip()
                    if not pline:
                        continue
                    pm = _RE_PORT.match(pline + ",")
                    if not pm:
                        # 可能跨行，尝试补全
                        continue
                    direction = pm.group(1)
                    width = pm.group(2).strip() if pm.group(2) else ""
                    pname = pm.group(3)
                    ports.append(Port(
                        name=pname, direction=direction,
                        width=width if width else "1",
                        width_bits=_parse_width_str(width),
                    ))

            modules.append((mod_name, params, ports))
        i += 1
    return modules


def _extract_port_section(block_text):
    """从 module 声明块提取端口列表（第一个匹配的括号段）"""
    # 找 module ... ( 之后的段
    # 跳过 #(...) 参数块
    idx = block_text.find("module")
    if idx < 0:
        return ""
    after_module = block_text[idx:]
    # 找第一个非参数块的 ( （即端口列表）
    # 先跳过 #(...)
    hash_idx = after_module.find("#")
    search_start = 0
    if hash_idx >= 0:
        # 找 #(...) 的结束
        depth = 0
        k = hash_idx
        while k < len(after_module):
            if after_module[k] == "(":
                depth += 1
            elif after_module[k] == ")":
                depth -= 1
                if depth == 0:
                    search_start = k + 1
                    break
            k += 1
    # 从 search_start 找端口列表的 (
    port_start = after_module.find("(", search_start)
    if port_start < 0:
        return ""
    depth = 0
    k = port_start
    while k < len(after_module):
        if after_module[k] == "(":
            depth += 1
        elif after_module[k] == ")":
            depth -= 1
            if depth == 0:
                return after_module[port_start + 1:k]
        k += 1
    return ""


def _find_top_module(modules, top_hint):
    """识别真实顶层模块（per D-07）

    策略：top_hint 可能是目录别名 caseN（与真实模块名不符）。
    1. 若 top_hint 匹配某 module 名 → 用它
    2. 否则取未被其他 module 例化的顶层 module
    """
    mod_names = [m[0] for m in modules]
    # 策略1：精确匹配
    if top_hint in mod_names:
        return top_hint
    # 策略2：取唯一 module（或第一个，若无嵌套例化关系）
    if len(modules) == 1:
        return modules[0][0]
    # 策略3：找未被例化的 module（顶层）
    instantiated = set()
    # 扫描所有文件文本找例化（简化：module 名作为实例化的第一个 token）
    # 但这里只传了 modules 列表，需要原始文本
    # 简化：返回第一个 module（文件顺序）
    return modules[0][0]


def parse(rtl_dir, top_hint=None):
    """解析 RTL 目录，返回 DesignInfo

    Args:
        rtl_dir: RTL 源目录或单文件
        top_hint: 顶层模块名提示（可能是目录别名，不可盲信 per D-07）
    Returns:
        DesignInfo
    """
    rtl_path = Path(rtl_dir)
    if rtl_path.is_file():
        vfiles = [rtl_path]
    else:
        vfiles = sorted(rtl_path.glob("*.v")) + sorted(rtl_path.glob("*.sv"))

    all_modules = []
    for vf in vfiles:
        mods = _parse_single_file(vf)
        all_modules.extend(mods)

    # 识别顶层
    top_name = _find_top_module(all_modules, top_hint or "")
    top_mod = None
    for name, params, ports in all_modules:
        if name == top_name:
            top_mod = (name, params, ports)
            break
    if top_mod is None:
        raise ValueError(f"顶层模块 '{top_name}' 未找到。可用模块: {[m[0] for m in all_modules]}")

    name, params, ports = top_mod

    # 收集所有端口名用于协议分类
    all_port_names = [p.name for p in ports]
    for p in ports:
        p.protocol_group = _classify_protocol(p.name, all_port_names)

    # 识别时钟/复位
    clock = ""
    reset = ""
    reset_active = "high"
    for p in ports:
        nl = p.name.lower()
        if nl in _CLOCK_NAMES and not clock:
            clock = p.name
        if (nl in _RESET_NAMES_HIGH or nl in _RESET_NAMES_LOW) and not reset:
            reset = p.name
            reset_active = "low" if nl in _RESET_NAMES_LOW else "high"

    # 推断协议类型
    protocols = set()
    groups = {p.protocol_group for p in ports}
    if "axi_slave" in groups or "axi_master" in groups:
        protocols.add("AXI")
    if "sram" in groups:
        protocols.add("SRAM")
    if "valid_ready" in groups:
        protocols.add("valid-ready")

    return DesignInfo(
        top_module=name,
        files=[str(vf) for vf in vfiles],
        parameters=params,
        ports=ports,
        clock=clock,
        reset=reset,
        reset_active=reset_active,
        inferred_protocols=sorted(protocols),
    )
