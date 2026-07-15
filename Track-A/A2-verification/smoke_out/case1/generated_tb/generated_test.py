"""Auto-generated cocotb testbench — win-ZCode A2 验证环境自动生成

DUT: axi_adapter_rd
Clock: clk, Reset: rst (high active)
Protocols: AXI
Seed: 20260630, Sequences: 100
"""
import json
import logging
import os
import random
import sys

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

from cocotbext.axi import AxiMasterRead, AxiRamRead, AxiReadBus

# 功能覆盖采样（per D-13, D-18：真实事务采样，不空 hit）
import sys as _sys, os as _os
_sys.path.insert(0, _os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))
try:
    from functional_coverage import FunctionalCoverage
    _HAS_FC = True
except ImportError:
    _HAS_FC = False


def load_constraints():
    """从环境变量或默认 constraints.json 加载约束配置"""
    path = os.environ.get("CONSTRAINT_JSON", "constraints.json")
    if not os.path.exists(path):
        return {"seed": 20260630, "sequence_count": 100}
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f).get("constraint_random_test", {"seed": 20260630, "sequence_count": 100})


def cycle_pause():
    """固定反压模式（per ready 反压要求）"""
    while True:
        for value in (0, 0, 1, 0, 0, 0, 1, 0):
            yield value


def random_pause(rng, numerator=1, denominator=9):
    """随机反压生成器"""
    while True:
        yield 1 if rng.randrange(denominator) < numerator else 0


def read_lengths(rng, count):
    """读长度生成：directed 边界值 + 随机（per seed 穿透）"""
    directed = [1, 2, 3, 4, 5, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65, 127, 128, 255, 256]
    for index in range(count):
        if index < len(directed):
            yield directed[index]
        elif index % 101 == 0:
            yield rng.choice([1, 3, 4, 7, 8, 15, 16, 31, 32, 63, 64, 127, 128, 255])
        else:
            yield rng.randint(1, 96)


def read_address(rng, index, length, address_space=65536):
    """读地址生成：边界值 + 随机（per seed 穿透）"""
    max_addr = address_space - length - 1
    if max_addr < 0:
        max_addr = 0
    if index % 97 == 0:
        return max(0, 4096 - rng.randint(1, min(64, max_addr + 1)))
    if index % 89 == 0:
        base = rng.choice([0x0000, 0x1000, 0x2000, 0x3000])
        return min(max_addr, base + rng.randint(0, 63))
    if index % 17 == 0:
        return rng.randrange(0, max_addr + 1) & ~0x3
    return rng.randrange(0, max_addr + 1)


async def reset_dut(dut):
    """复位序列：rst 高 8 拍 + 低 8 拍（per verification_skeleton.json）"""
    dut.rst.setimmediatevalue(0)
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 1
    for _ in range(8):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    for _ in range(8):
        await RisingEdge(dut.clk)


@cocotb.test()
async def run_generated_test(dut):
    """win-ZCode 生成的约束随机测试"""
    config = load_constraints()
    seed = int(config.get("seed", 20260630))
    sequence_count = int(config.get("sequence_count", 100))
    rng = random.Random(seed)  # seed 穿透（CONSTRAINTS §3 硬约束）

    logging.getLogger("cocotb").setLevel(logging.WARNING)

    # 时钟生成（per D-04：cocotb 2.0 unit= 非 units=）
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())


    # golden 比对的状态初始化（valid-ready golden / invariant 共用）

    # AXI 驱动（per D-08：cocotbext-axi）— DUT 有完整 s_axi + m_axi 总线（如 case1 读适配器）
    master = AxiMasterRead(AxiReadBus.from_prefix(dut, "s_axi"), dut.clk, dut.rst)
    ram = AxiRamRead(AxiReadBus.from_prefix(dut, "m_axi"), dut.clk, dut.rst, size=2**16)

    master.log.setLevel(logging.WARNING)
    ram.log.setLevel(logging.WARNING)

    # ready 反压（per 门禁五项第4项：valid/ready 接口必须设反压）
    master.ar_channel.set_pause_generator(random_pause(random.Random(seed ^ 0x13579), 1, 11))
    master.r_channel.set_pause_generator(cycle_pause())
    ram.ar_channel.set_pause_generator(random_pause(random.Random(seed ^ 0x2468), 1, 13))
    ram.r_channel.set_pause_generator(random_pause(random.Random(seed ^ 0x369c), 1, 7))

    await reset_dut(dut)

    # 功能覆盖初始化（per D-13, D-18：bin 从 coverage_gen 注入，真实事务采样）
    coverage = None
    if _HAS_FC:
        coverage = FunctionalCoverage("axi_adapter_rd", {"adapter_path": ["width_conversion", "merge_master_beats", "narrow_size_read", "partial_last_beat"], "address_alignment": ["aligned_4_byte", "aligned_2_byte", "unaligned", "near_4k_boundary"], "backpressure": ["source_rready_pause", "downstream_arready_pause", "downstream_rvalid_pause", "combined_pause"], "burst_size": ["size_1_byte", "size_2_byte", "size_4_byte", "default_max_size"], "data_alignment": ["byte_aligned", "halfword_aligned", "word_aligned", "unaligned"], "data_width_boundary": ["min_width", "half_width", "full_width", "over_width"], "overflow_underflow": ["no_overflow", "overflow", "underflow"], "read_length": ["1", "2_to_3", "4", "5_to_15", "16_to_31", "32_to_63", "64_to_127", "128_to_256"], "sign_extension": ["positive_extend", "negative_extend", "zero_extend"]})

    size_choices = [None, 0, 1, 2]
    test_count = 0

    for index, length in enumerate(read_lengths(rng, sequence_count)):
        addr = read_address(rng, index, length)
        # 写入 RAM 预期数据（scoreboard 比对基准）
        data = bytes((index + offset * 19 + rng.randrange(256)) & 0xff for offset in range(length))
        ram.write(addr, data)

        size = size_choices[index % len(size_choices)]

        # 功能覆盖 hit()（per D-18：真实事务采样，非空 hit）
        if coverage:
            # read_length bin
            if length == 1: lb = "1"
            elif length <= 3: lb = "2_to_3"
            elif length == 4: lb = "4"
            elif length <= 15: lb = "5_to_15"
            elif length <= 31: lb = "16_to_31"
            elif length <= 63: lb = "32_to_63"
            elif length <= 127: lb = "64_to_127"
            else: lb = "128_to_256"
            coverage.hit("read_length", lb)
            # address_alignment bin
            if addr // 4096 != (addr + length - 1) // 4096 or addr % 4096 >= 4032:
                coverage.hit("address_alignment", "near_4k_boundary")
            elif addr % 4 == 0:
                coverage.hit("address_alignment", "aligned_4_byte")
            elif addr % 2 == 0:
                coverage.hit("address_alignment", "aligned_2_byte")
            else:
                coverage.hit("address_alignment", "unaligned")
            # burst_size bin
            sb = {None: "default_max_size", 0: "size_1_byte", 1: "size_2_byte", 2: "size_4_byte"}[size]
            coverage.hit("burst_size", sb)

        # 读 + scoreboard 比对（per 门禁五项第5项：scoreboard 实际比对，不静默）
        read = await master.read(addr, length, size=size)
        assert read.data == data, \
            "read %d addr=0x%x len=%d size=%s mismatch" % (index, addr, length, size)
        test_count += 1

        if index % 257 == 0:
            for _ in range(rng.randint(0, 8)):
                await RisingEdge(dut.clk)

    # master 仅在 s_axi 可用时实例化（完整 AXI 或 slave-only 分支）
    await master.wait_idle() if hasattr(master, 'wait_idle') else await master.wait()
    for _ in range(16):
        await RisingEdge(dut.clk)

    # 功能覆盖写出（per D-13：写 functional_coverage.json）
    if coverage:
        fc_out = _os.environ.get("FUNCTIONAL_COVERAGE_OUTPUT", "functional_coverage.json")
        coverage.write(path=fc_out, source="cocotb transaction sampling")

    dut._log.info("Test complete: %d transactions passed (seed=%d, seq=%d)",
                  test_count, seed, sequence_count)