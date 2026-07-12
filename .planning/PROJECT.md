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

- **负责人（你）**: YSYX（一生一芯）经历，Verilog/C/Python/Yosys/STA/Verilator 全栈
- **队友1**: 主要靠 Claude+GSD 辅助
- **队友2**: 主要靠 Claude+GSD 辅助

## Requirements

### Validated

(None yet — ship to validate)

### Active

- [ ] **A3-01**: 交付 A3 RTL 逻辑综合工具 — 基于 Yosys 增强，读取 Verilog + SDC + Nangate45 Liberty，输出合法门级网表
- [ ] **A3-02**: 10 个公开电路（LSV01-LSV10）功能正确 — 网表通过仿真验证比对
- [ ] **A3-03**: 每电路支持多 Point 配置（最多7个）— 通过 config.json 驱动不同优化策略
- [ ] **A3-04**: PPA Hypervolume 达到或超过官方参考水平
- [ ] **A3-05**: 统一 Makefile 接口（build / synth / clean）
- [ ] **A1-01**: 队友交付 A1 轻量 RTL 仿真器 — 事件驱动 Verilog 仿真器
- [ ] **A1-02**: 12 个公开测试用例通过（basic01-05, alu, priority_encoder, i2c, ip, axis_fifo, sha256, GEMM）
- [ ] **A1-03**: 支持增量编译和并行仿真（GEMM 用例重点）
- [ ] **A2-01**: 队友交付 A2 验证环境自动生成工具 — 读取 RTL 自动生成 testbench
- [ ] **A2-02**: 支持约束随机测试（固定seed，5000序列）和覆盖率反馈
- [ ] **A2-03**: 覆盖率 ≥85% 尽可能多的电路

### Out of Scope

- 赛道 B (GPGPU RTL) 和赛道 C (编译器/Runtime) — 不在赛道 A 范围
- A3 隐藏电路的针对性优化 — 违反竞赛规则
- 商业 EDA 工具调用 — 评测环境无网络，仅开源工具
- A3 from_scratch 模式 — 基于 Yosys 增强（open_source_based）更符合61小时时限

## Constraints

- **时间**: 约61小时（7月12日21:00 → 7月15日10:00）
- **人力**: 仅1人有 EDA 技术背景，2人依赖 GSD 辅助
- **语言**: A1 C/C++, A2 Python, A3 Python (Yosys 脚本) + C++ (自定义 pass)
- **依赖**: 所有第三方依赖须随提交包提供，评测无网络
- **正确性门禁**: A3 功能不正确则该 Point 0 分；A1 F1/F2 不通过则 P1/P2/P3 为0

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| 赛道选择 A | 团队有 EDA 经验，与 YSYX 背景匹配 | — Pending |
| 分工：你做 A3，队友做 A1/A2 | 你有 Yosys/STA 经验，A3 PPA 90分可最大化你的经验价值 | — Pending |
| A3 基于 Yosys 增强 | open_source_based 类型，61小时内最快出成果 | — Pending |
| A3 策略：先正确后优化 | 功能正确是评分前提，不正确 = 0 分 | — Pending |
| A1/A2 用 GSD 辅助队友开发 | 队友无 EDA 背景，GSD 可提供从零到交付的完整辅助 | — Pending |

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
