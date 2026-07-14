# A2 验证环境自动生成 — win-ZCode GSD 工作区

## What This Is

赛题 A2（Agentic4Systems 赛道 A 第 2 题）：构建自动验证环境生成框架。读取 RTL 设计，自动生成 cocotb testbench + 约束随机测试 + 覆盖率报告。评测覆盖 10 个隐藏电路，每电路产出 7 JSON + `generated_tb/` + `generated_tests/`。

本工作区是 win-ZCode（Windows + Docker linux/amd64）独立 GSD 工作区，与顶层 AI4S/.planning（A3 track）隔离。

## Core Value

在评测截止前交付一个 `run.sh` 五参数入口的完整流水线：RTL 解析 → testbench 骨架 → 约束随机序列 → 仿真 → 覆盖率收集 → 7 JSON 输出。骨架门禁通过 + 覆盖率 C≥65% 拿保底，冲 C≥85% 拿满。

## Context

- **竞赛**: Agentic4Systems 暑期学校 2026，赛道 A（EDA 软件）
- **子题**: A2 验证环境自动生成
- **满分**: 100 = 10 电路 × 10 分（骨架门禁 3 + 覆盖率 7）
- **截止**: 2026-07-15 10:00（与赛道 A 其他子题同期）
- **实现端**: win-ZCode（三方竞赛之一：mac-CC / win-CC / win-ZCode）
- **环境**: Docker linux/amd64 + Verilator 5.050（与评测 OS 同构，覆盖率数字直接可交付）

### 技术路线（已锁定）

- cocotb 2.0.1 + Verilator 5.050
- 覆盖率插桩：`--coverage-line --coverage-toggle`（branch 由 `--coverage-line` 自动产出）
- 功能覆盖：cocotb `coverage.hit(bin)` 采样
- 选手自交 coverage_result.json，评测器不锁工具重算

### 现状

- 文档完备（PLAN/CONSTRAINTS/ENVIRONMENT/EXECUTOR/PITFALLS/THIRD_PARTY）
- 环境已验证（Docker + case1 烟雾测试通过，见 smoke_out/SMOKE_TEST_REPORT.md）
- 零实现代码（待 Phase 1 开发）
- 工作分支：exec/win-zcode

## Requirements

### Validated

(None yet — implement to validate)

### Active

- [ ] **A2-01**: run.sh 五参数入口跑通完整流水线（RTL→testbench→仿真→7JSON）
- [ ] **A2-02**: RTL 解析 — 端口方向/宽度/时钟/复位/参数/协议推断（AXI/SRAM/valid-ready）
- [ ] **A2-03**: cocotb+Verilator testbench 骨架 — 时钟/复位/驱动/监视/scoreboard/反压
- [ ] **A2-04**: 约束随机 — seed=20260630 穿透 random.Random，序列数 5000
- [ ] **A2-05**: 覆盖率采集 — 行/分支（Verilator --coverage-line）+ 功能（cocotb bin）
- [ ] **A2-06**: 7 JSON 产物齐全且语义正确
- [ ] **A2-07**: 综合公式 C = 0.4×行 + 0.3×分支 + 0.3×功能（禁止 0.42/0.28/0.30）
- [ ] **A2-08**: 10 隐藏电路通用化（禁硬编码/针对性优化）
- [ ] **A2-09**: 离线打包 — wheelhouse + requirements.txt + THIRD_PARTY.md

### Out of Scope

- iverilog / VCS / URG 路线（已弃用）
- 硬编码激励/bin/报告（违反原创性红线）
- 赛道 A 其他子题（A1 仿真器 / A3 综合）— 顶层 AI4S/.planning 管理

## Constraints

- **时间**: ~24 小时至截止（2026-07-14 → 07-15 10:00）
- **技术路线**: cocotb + Verilator 锁定（不可变）
- **评测**: Linux x86_64 断网，依赖全打包
- **门禁**: testbench 编译失败/端口错连/无驱动监视/scoreboard 静默 → 整电路 0 分
- **公式**: coverage_result.json 必须 0.4/0.3/0.3
- **seed**: 20260630 穿透 random.Random，否则覆盖率上限 3 分

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| cocotb + Verilator 路线 | iverilog 不支持 RTL 行/分支覆盖；Verilator 原生 --coverage-line | ✅ Locked (congress 评审 2026-07-14) |
| Docker linux/amd64 主环境 | 与评测 OS 同构，覆盖率数字直接可交付 | ✅ 烟雾测试验证 |
| 镜像 tag verilator/verilator:v5.050 | 文档误写 :5.050，正确带 v 前缀 | ✅ 已拉取验证 |
| COMPILE_ARGS 含 -Wno-fatal | Verilator 默认 lint 致命，case1 有 34 个 width warning | ✅ 烟雾测试确认 |
| 综合公式 0.4/0.3/0.3 | scoring.md 权威，禁抄公开样例 0.42/0.28/0.30 | ✅ Locked |

## Evolution

This document evolves at phase transitions and milestone boundaries.

---
*Last updated: 2026-07-14 (win-ZCode GSD 工作区初始化)*
