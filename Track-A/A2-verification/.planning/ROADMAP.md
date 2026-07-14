# Roadmap: A2 验证环境自动生成 — win-ZCode

## Overview

win-ZCode 独立实现 A2 验证环境自动生成流水线（cocotb + Verilator 5.050）。三阶段递进：骨架门禁（能编译能跑）→ 覆盖率收集（三类覆盖率 + 综合公式）→ 通用化（10 隐藏电路 + 离线打包）。环境已通过 case1 烟雾测试验证（见 smoke_out/SMOKE_TEST_REPORT.md）。

## Phases

- [ ] **Phase 1: 骨架门禁 — RTL 解析 + cocotb/Verilator testbench 生成** - 解析 RTL 接口，生成能编译能跑的 testbench，通过 case1 门禁（3 分/电路基础）
- [ ] **Phase 2: 覆盖率收集 — 行/分支/功能 + 约束随机** - Verilator 覆盖率插桩解析 + cocotb 功能 bin + 5000 序列约束随机，C≥65% 保底
- [ ] **Phase 3: 通用化 + 离线打包** - 10 隐藏电路自适应 + 禁硬编码 + wheelhouse 离线包 + Docker 复验

## Phase Details

### Phase 1: 骨架门禁 — RTL 解析 + cocotb/Verilator testbench 生成
**Goal**: run.py 跑通 RTL → testbench → 仿真 → 结果，case1 骨架门禁通过（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）
**Depends**: Nothing（环境已验证，见 SMOKE_TEST_REPORT.md）
**Requirements**: A2-01, A2-02, A2-03
**Success Criteria** (what must be TRUE):
  1. run.py 五参数入口跑通：`--rtl --top --out --seed --num-seq`
  2. RTL 解析输出 design.json：端口方向/宽度/时钟/复位/参数/协议推断（AXI/SRAM/valid-ready）
  3. 生成的 cocotb testbench 能用 Verilator 后端编译（COMPILE_ARGS 含 `-Wno-fatal`）并仿真通过
  4. DUT 端口正确连接，有时钟/复位生成、输入驱动、输出监视、scoreboard、ready 反压
  5. case1 跑通骨架门禁（门禁五项不命中任一：编译失败/端口错连/握手不可用/无驱动监视/scoreboard 静默）
**Plans**: TBD

Plans:
- [ ] 01-01: TBD

### Phase 2: 覆盖率收集 — 行/分支/功能 + 约束随机
**Goal**: 三类覆盖率齐全 + 综合 C≥65%（保底档），冲 C≥85%（满分档）
**Depends**: Phase 1
**Requirements**: A2-04, A2-05, A2-06, A2-07
**Success Criteria** (what must be TRUE):
  1. 行/分支覆盖率：Verilator `--coverage-line --coverage-toggle` 插桩 → coverage.dat LCOV 解析（按文件过滤排除 wrapper）
  2. 功能覆盖率：cocotb bin 真实事务采样（不空 hit，不初始化一次性 hit），4 类模板（FSM/数据通路/存储器/AXI）
  3. 约束随机：5000 序列，seed=20260630 穿透 `random.Random(seed)` + directed 边界值
  4. 7 JSON 产物齐全，coverage_result.json 综合公式写 0.4/0.3/0.3（禁止 0.42/0.28/0.30）
  5. RTL 静态分析：`generate/if` 死码识别，只对可达分支采 bin（避免 case1 53% 死码天花板）
**Plans**: TBD

Plans:
- [ ] 02-01: TBD

### Phase 3: 通用化 + 离线打包
**Goal**: 10 隐藏电路通用化 + 离线打包 + Docker 复验，准备提交
**Depends**: Phase 2
**Requirements**: A2-08, A2-09
**Success Criteria** (what must be TRUE):
  1. 框架对 10 个隐藏电路通用化（禁硬编码/针对性优化，自适应 AXI/SRAM/valid-ready 接口）
  2. requirements.txt 每包钉死 ==X.Y.Z；wheelhouse/ 离线包齐全，评测机 `pip install --no-index` 可装
  3. THIRD_PARTY.md 齐全（版本/许可/调用边界）
  4. Docker linux/amd64 复跑 5 公开 case，覆盖率与本地无漂移
  5. run.sh 独自跑通完整流水线，评测人员无需手改任何生成文件
**Plans**: TBD

Plans:
- [ ] 03-01: TBD

## Progress

| Phase | Plans Complete | Status | Completed |
|-------|----------------|--------|-----------|
| 1. 骨架门禁 | 0/1 | Not started | - |
| 2. 覆盖率收集 | 0/1 | Not started | - |
| 3. 通用化+打包 | 0/1 | Not started | - |

## Key Risks

| Risk | Mitigation |
|------|------------|
| Verilator lint 致命（-Wno-fatal 必传）| COMPILE_ARGS 参数化，烟雾测试已确认 |
| VCS/Verilator 覆盖率口径不同（branch 分母差 20x）| 选手自交，coverage_result.json 注明 Verilator 口径 |
| 参数化死码拉低行覆盖（case1 53%）| RTL generate/if 静态分析，只采可达分支 |
| 功能 bin 空 hit 灰色地带 | 真实事务采样，设 hits 阈值 |
| 镜像无 pip | run.sh/Dockerfile 含 apt bootstrap |
| cocotb 2.0 API 弃用警告 | 生成的 testbench 适配 unit=/Immediate()/cancel() |

---
*Last updated: 2026-07-14 (win-ZCode GSD 工作区初始化)*
