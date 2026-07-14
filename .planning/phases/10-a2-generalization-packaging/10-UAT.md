---
status: complete
phase: 10-a2-generalization-packaging
source: [.planning/phases/10-a2-generalization-packaging/10-01-SUMMARY.md, .planning/phases/10-a2-generalization-packaging/10-VERIFICATION.md]
started: 2026-07-14T23:30:00+08:00
updated: 2026-07-15T02:30:00+08:00
---

## Current Test
[testing complete]

## Tests

### 1. Phase 10 流水线/打包/红线自动化验证（D1-D4 通过）
expected: 4 个交付物（D1-D4：流水线跑通/coverage-zero 修复/离线可跑/红线合规）均由自动化验证覆盖
result: pass

**Coverage auto-passed entries (#1602):**

### D1. case1-5 全部跑通完整流水线，7 JSON 齐全，composite > 0
expected: case1-5 全部跑通完整流水线，7 JSON 齐全，composite > 0
result: pass
source: automated
coverage_id: D1

### D2. coverage-zero bug 修复：case1 composite 0%→79.09%（原生 coverage.dat 解析）
expected: coverage-zero bug 修复：case1 composite 0%→79.09%（原生 coverage.dat 解析）
result: pass
source: automated
coverage_id: D2

### D3. 离线评测机可跑：预装镜像 ai4s-a2:verilator-cocotb（零运行时网络）+ wheelhouse fallback
expected: 离线评测机可跑：预装镜像 ai4s-a2:verilator-cocotb（零运行时网络）+ wheelhouse fallback
result: pass
source: automated
coverage_id: D3

### D4. 红线合规：src/ + templates/ 无 case[1-5] 业务逻辑硬编码
expected: 红线合规：src/ + templates/ 无 case[1-5] 业务逻辑硬编码
result: pass
source: automated
coverage_id: D4

### 5. 比对器门禁（官方 scoring.md §1 门禁失败条件 #5）— gap 发现
expected: case1-5 生成的 testbench 必须有真实 DUT 输出比对（assert/raise/mismatch），否则命中门禁失败条件 #5「比对器未比对 DUT 行为或静默忽略比对失败」，该 case 0 分且覆盖率不计
result: issue
reported: "case2-5 generated testbench 有 0 个 assert/比对逻辑（case1 有 assert read.data==data）。模板 cocotb_tb.py.j2 非 AXI 分支自标'scoreboard 占位'。verification_skeleton.json 的 scoreboard 字段是 skeleton_gen 硬编码的静态字符串，不反映实际 testbench。按官方门禁 #5，case2-5 判 0 分（覆盖率也不计）。"
severity: blocker

## Summary

total: 5
passed: 4
issues: 1
pending: 0
skipped: 0

## Gaps

- truth: "case1-5 生成的 testbench 必须有真实 DUT 输出比对，满足官方 scoring.md §1 门禁失败条件 #5（比对器未比对 DUT 行为 = 该 case 0 分，覆盖率不计）"
  status: failed
  reason: >
    case2-5 generated testbench 有 0 个 assert（grep assert/raise/mismatch/comparison 命中数=0）。
    模板 cocotb_tb.py.j2 非 AXI 分支（{%% else %%}，L214-223）自标 '# scoreboard 占位'，
    只驱动输入随机值 + coverage.hit()，从不采样 DUT 输出、无比对、无失败检测。
    verification_skeleton.json 的 scoreboard 字段是 skeleton_gen.py L151-154 硬编码的静态字符串
    "assert read.data == expected_data"，对所有 case 都一样，不反映实际 testbench 实现。
    case1（AXI 路径）有真实 assert read.data == data，过门禁；case2-5 不过。
  severity: blocker
  test: 5
  artifacts:
    - path: Track-A/A2-verification/templates/cocotb_tb.py.j2
      issue: "非 AXI 分支 L214-223 是 'scoreboard 占位'，无真实比对"
    - path: Track-A/A2-verification/src/skeleton_gen.py
      issue: "L151-154 硬编码 scoreboard 静态字符串，对所有 case 伪造比对声明"
    - path: Track-A/A2-verification/smoke_out/case2/generated_tb/generated_test.py
      issue: "0 assert，L136 自标占位"
  missing:
    - "为 valid-ready stream 接口（case2）实现 golden shift-register 参考模型 + assert"
    - "为 AXI slave only（case4）实现 master.read() + assert（复用 case1 ram 模式）"
    - "为 case3/case5 实现 invariant check assert（信号合法性）"
    - "skeleton_gen scoreboard 字段改为反映实际 testbench 比对逻辑（非硬编码）"
