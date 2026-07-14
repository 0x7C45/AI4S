"""Auto-generated cocotb testbench — win-ZCode A2 验证环境自动生成

DUT: axi_adapter_rd
Clock: clk, Reset: rst (high active)
Protocols: AXI
Seed: 20260630, Sequences: 5000
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

# 功能覆盖采样（Phase 2 完整实现，Phase 1 占位）


def load_constraints():
    """从环境变量或默认 constraints.json 加载约束配置"""
    path = os.environ.get("CONSTRAINT_JSON", "constraints.json")
    if not os.path.exists(path):
        return {"seed": 20260630, "sequence_count": 5000}
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f).get("constraint_random_test", {"seed": 20260630, "sequence_count": 5000})


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
    sequence_count = int(config.get("sequence_count", 5000))
    rng = random.Random(seed)  # seed 穿透（CONSTRAINTS §3 硬约束）

    logging.getLogger("cocotb").setLevel(logging.WARNING)

    # 时钟生成（per D-04：cocotb 2.0 unit= 非 units=）
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    # AXI 驱动（per D-08：cocotbext-axi）
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

    size_choices = [None, 0, 1, 2]
    test_count = 0

    for index, length in enumerate(read_lengths(rng, sequence_count)):
        addr = read_address(rng, index, length)
        # 写入 RAM 预期数据（scoreboard 比对基准）
        data = bytes((index + offset * 19 + rng.randrange(256)) & 0xff for offset in range(length))
        ram.write(addr, data)

        size = size_choices[index % len(size_choices)]

        # 读 + scoreboard 比对（per 门禁五项第5项：scoreboard 实际比对，不静默）
        read = await master.read(addr, length, size=size)
        assert read.data == data, \
            "read %d addr=0x%x len=%d size=%s mismatch" % (index, addr, length, size)
        test_count += 1

        if index % 257 == 0:
            for _ in range(rng.randint(0, 8)):
                await RisingEdge(dut.clk)

    await master.wait_idle() if hasattr(master, 'wait_idle') else await master.wait()
    for _ in range(16):
        await RisingEdge(dut.clk)

    dut._log.info("Test complete: %d transactions passed (seed=%d, seq=%d)",
                  test_count, seed, sequence_count)