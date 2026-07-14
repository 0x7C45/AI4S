# AI4S GPGPU 竞赛 — 赛道 A EDA 工具

## What This Is

三人为一队参加 Agentic4Systems 暑期学校 GPGPU 智能体加速设计竞赛 2026，选择赛道 A（EDA 软件），需完成三道子题：A1 轻量 RTL 仿真器、A2 验证环境自动生成、A3 RTL 逻辑综合工具。每题 100 分，三题平均为赛道总分。

## Core Value

7月15日上午10点前提交三道可运行的 EDA 工具，功能正确性优先，在此基础上追求性能和覆盖率。

## Context

- **竞赛**: Agentic4Systems 暑期学校 GPGPU 智能体加速设计竞赛 2026
- **赛道**: A — EDA 软件（为赛道 B GPGPU RTL 设计提供工具链）
- **ISA**: AEC 128-bit 定长指令集
- **截止时间**: 2026年7月15日上午10:00（约 61 小时）
- **环境**: Linux x86_64，评测无网络，依赖需随提交包提供

### 团队背景

- **负责人（你）**: YSYX（一生一芯）经历，Verilog/C/Python/Yosys/STA/Verilator 全栈 → **负责 A1 RTL 仿真器**（代码复用最多：NEMU/Verilator）
- **队友**: **负责 A3 逻辑综合**；A3 在本规划框架之外独立维护
- **队友2**: 主要靠 Claude+GSD 辅助 → **负责 A2 验证生成**

## Requirements

### Validated

(None yet — ship to validate)

### Active

- [ ] **A1-01**: 队友交付 A1 轻量 RTL 仿真器 — 事件驱动 Verilog 仿真器
- [ ] **A1-02**: 12 个公开测试用例通过（basic01-05, alu, priority_encoder, i2c, ip, axis_fifo, sha256, GEMM）
- [ ] **A1-03**: 支持增量编译和并行仿真（GEMM 用例重点）
- [ ] **A2-01**: 队友交付 A2 验证环境自动生成工具 — 读取 RTL 自动生成 testbench
- [ ] **A2-02**: 支持约束随机测试（固定seed，5000序列）和覆盖率反馈
- [ ] **A2-03**: 覆盖率 ≥85% 尽可能多的电路

### Out of Scope

- 赛道 B (GPGPU RTL) 和赛道 C (编译器/Runtime) — 不在赛道 A 范围
- 商业 EDA 工具调用 — 评测环境无网络，仅开源工具

## Constraints

- **时间**: 约61小时（7月12日21:00 → 7月15日10:00）
- **人力**: 仅1人有 EDA 技术背景，A1/A2 仍使用现有规划流程协作
- **语言**: A1 C/C++, A2 Python, A3 Python (Yosys 脚本) + C++ (自定义 pass)
- **依赖**: 所有第三方依赖须随提交包提供，评测无网络
- **正确性门禁**: A3 功能不正确则该 Point 0 分；A1 F1/F2 不通过则 P1/P2/P3 为0

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| 赛道选择 A | 团队有 EDA 经验，与 YSYX 背景匹配 | — Pending |
| A1/A2 用 GSD 辅助队友开发 | 队友无 EDA 背景，GSD 可提供从零到交付的完整辅助 | — Pending |
| A2: cocotb + Verilator 路线 | iverilog 不支持 RTL 行/分支覆盖；Verilator 原生 --coverage-line | ✅ Locked (congress 2026-07-14) |
| A2: Docker linux/amd64 主环境 | 与评测 OS 同构，覆盖率数字直接可交付 | ✅ 烟雾测试验证 |
| A2: 镜像 tag verilator/verilator:v5.050 | 文档误写 :5.050，正确带 v 前缀 | ✅ 已拉取验证 |
| A2: COMPILE_ARGS 含 -Wno-fatal | Verilator 默认 lint 致命，case1 有 34 个 width warning | ✅ 烟雾测试确认 |
| A2: 综合公式 0.4/0.3/0.3 | scoring.md 权威，禁抄公开样例 0.42/0.28/0.30 | ✅ Locked |

## Evolution

This document evolves at phase transitions and milestone boundaries.

**After each phase transition** (via `/gsd-transition`):
1. Requirements invalidated? → Move to Out of Scope with reason
2. Requirements validated? → Move to Validated with phase reference
3. New requirements emerged? → Add to Active
4. Decisions to log? → Add to Key Decisions
5. "What This Is" still accurate? → Update if drifted

**After each milestone** (via `/gsd-complete-milestone`):
1. Full review of all sections
2. Core Value check — still the right priority?
3. Audit Out of Scope — reasons still valid?
4. Update Context with current state

---
*Last updated: 2026-07-12 after initialization*
