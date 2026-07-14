---
status: complete
phase: 09-a2-coverage-collection
source: [.planning/phases/09-a2-coverage-collection/09-01-SUMMARY.md, .planning/phases/09-a2-coverage-collection/09-VERIFICATION.md]
started: 2026-07-15T00:00:00+08:00
updated: 2026-07-15T01:30:00+08:00
---

## Current Test
[testing complete]

## Tests

### 1. Phase 9 VERIFICATION 报告 PARTIAL —— 3 个 gap 决策与处置
expected: gsd-verifier 已产出 09-VERIFICATION.md（PARTIAL，6/10 truths）。3 个 gap 均为代码/wiring 缺陷
result: pass
resolution: |
  用户决策：Fix SC#5 only（dead-code wiring），接受 SC#2 为已知限制。
  SC#5 已修复并验证（case1 line 82.54%→96.08%）。
  SC#2（非 AXI 功能采样占位）接受为已知限制——深改 testbench 风险高，近 deadline 不修。
  C≥65% 目标：SC#5 修复后 case1 line% 提升，但 composite 因 functional bin 模板差异未达 65%。
  此为 SC#2 未修的直接后果（用户已知情接受）。

**Coverage auto-passed entries (独立复核 + verifier 确认):**

### D1. 5 模块齐全
expected: src/ 下 5 个覆盖率收集模块齐全且可 import
result: pass
source: automated

### D2. 行/分支覆盖率解析 + wrapper 过滤（SC#1）
expected: coverage_collect.py 解析 coverage.dat line/branch，排除 wrapper，保留 DUT
result: pass
source: automated

### D3. 功能 bin 4 类模板齐全（SC#2 部分）
expected: coverage_gen.py 含 AXI/FSM/DATAPATH/MEMORY 4 类 bin 模板
result: pass
source: automated

### D4. 约束随机 seed 穿透（SC#3）
expected: constraint_gen.py 用 random.Random(seed=20260630)，5000 序列写入 constraints.json
result: pass
source: automated

### D5. 7 JSON + 公式 0.4/0.3/0.3（SC#4）
expected: coverage_result.json formula 正确，无 0.42/0.28
result: pass
source: automated

### D6. dead_code_analyzer 存在
expected: src/dead_code_analyzer.py 存在（Phase 9 保守不启用）
result: pass
source: automated

## Summary

total: 7
passed: 7
issues: 0
pending: 0
skipped: 0

## Gaps (from 09-VERIFICATION.md, root-caused by gsd-verifier)

```yaml
- truth: "SC#5 RTL 静态分析：generate/if 死码识别，只对可达分支采 bin"
  status: failed
  reason: >
    dead_code_analyzer.py 存在但 run.py 从未 import，collect_cov() 调用未传 dead_code_info。
    模块本身有精度 bug（把 case1 L243-679 含激活的 else 分支整块标死）——这正是它被禁用的原因。
    覆盖率分母仍含参数化死码，case1 line% 卡在 ~82% 而非死码过滤后的 >95%。
  severity: major
  test: 1
  root_cause: "wiring 缺失 + 模块精度 bug 双重"
  artifacts: ["Track-A/A2-verification/run.py:130 (collect_cov 无 dead_code_info)", "src/dead_code_analyzer.py (if/else 边界误判)"]
  missing: ["run.py import + 传 dead_code_info", "dead_code_analyzer if/else 块匹配精化"]

- truth: "SC#2 功能 bin 真实事务采样（不空 hit，不初始化一次性 hit）"
  status: failed
  reason: >
    仅 case1（AXI 完整总线）走真实事务采样。case2-5 渲染非 AXI 分支，用确定性 modulo 占位采样
    （index % 2 → 同一 bin），与 DUT 状态无关。模板自标「简化采样/占位」。case2-5 functional = 0-8%。
  severity: major
  test: 1
  root_cause: "非 AXI 接口无真实事务采样逻辑，仅占位"
  artifacts: ["templates/cocotb_tb.py.j2 L216-220 (modulo 占位采样)"]
  missing: ["为 valid-ready/SRAM 接口实现真实事务驱动 + bin 采样"]

- truth: "ROADMAP 目标 C≥65% 保底（冲 C≥85% 满分）"
  status: failed
  reason: >
    per-case composite: case1=79.09%, case2=49.14%, case3=57.10%, case4=50.27%, case5=43.52%。
    平均 55.82%。仅 case1 达保底档；0/5 达满分档。此为 num-seq=100（调试规模），非 5000 评测规模。
    注：5000 序列覆盖率通常高于 100，但 case2-5 功能覆盖近 0，序列数提升帮助有限。
  severity: blocker
  test: 1
  root_cause: "SC#2 + SC#5 未达 → 直接导致 C 偏低"
  artifacts: ["smoke_out/case{1-5}/coverage_result.json"]
  missing: ["修 SC#2 + SC#5 后 C 自然提升"]
```
