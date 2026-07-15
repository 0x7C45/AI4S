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
    模板 cocotb_tb.py.j2 非 AXI 分支（{%% else %%}，L196-224）自标 '# scoreboard 占位'，
    只驱动输入随机值 + coverage.hit()，从不采样 DUT 输出、无比对、无失败检测。
    verification_skeleton.json 的 scoreboard 字段是 skeleton_gen.py L151-154 硬编码的静态字符串
    "assert read.data == expected_data"，对所有 case 都一样，不反映实际 testbench 实现。
    case1（AXI 双总线 s_axi+m_axi 路径，template L161-195）有真实 assert read.data == data，过门禁；case2-5 不过。
  root_cause: >
    cocotb_tb.py.j2 只在 AXI 双总线分支（_has_s_axi and _has_m_axi，template L161-195）发出真实
    assert read.data==data；其它协议路径全部落入 {%% else %%} 'scoreboard 占位' 分支（L196-224），
    仅 setimmediatevalue 驱动随机输入 + coverage.hit()，从不采样 DUT 输出、无比对。
    skeleton_gen.py L151-154 进一步对 verification_skeleton.json 硬编码 scoreboard 静态字符串，
    伪造门禁所需比对声明。次要 bug：rtl_parser._parse_single_file（L178-195）在 _extract_port_section
    后用 split(",") 拆端口，但未先剥离 /* */ 块注释；case2.v 的 s_axis_tdata/m_axis_tdata 端口声明前
    紧邻块注释（L102-105/L114-117），导致注释文本被并入端口块、_RE_PORT.match 失败，
    s_axis_tdata/m_axis_tdata 被 design.json 静默丢弃（RTL 23 端口 → design.json 21 端口），
    连 golden 模型要比对的 m_axis_tdata 都不可见。
  severity: blocker
  test: 5
  artifacts:
    - path: Track-A/A2-verification/templates/cocotb_tb.py.j2:196-224
      issue: "{% else %} 分支是 'scoreboard 占位'，只驱动随机输入 + coverage.hit() + await RisingEdge，0 assert/0 采样 DUT 输出"
    - path: Track-A/A2-verification/templates/cocotb_tb.py.j2:161-195
      issue: "仅 case1 的 AXI 双总线分支有 assert read.data == data（L193-194），是待复用的参考模式"
    - path: Track-A/A2-verification/src/skeleton_gen.py:151-154
      issue: "scoreboard 字段硬编码 'assert read.data == expected_data'，对所有 case 伪造比对声明"
    - path: Track-A/A2-verification/src/rtl_parser.py:178-195
      issue: "split(',') 前未剥离 /* */ 注释；case2.v 注释紧邻端口声明致 s_axis_tdata/m_axis_tdata 被 design.json 丢弃"
    - path: Track-A/A2-verification/smoke_out/case2/generated_tb/generated_test.py:136-145
      issue: "0 assert，L136 自标 'scoreboard 占位'，仅 coverage.hit() + await RisingEdge"
    - path: Track-A/A2-verification/smoke_out/case4/generated_tb/generated_test.py:106,121-151,158
      issue: "AxiMasterRead 实例化（L106）但主循环（L121-151）走通用 {%% else %%} 分支从未调用 master.read()，仅 L158 await master.wait_idle()，孤儿 driver"
    - path: Track-A/A2-verification/smoke_out/case2/design.json:41-189
      issue: "端口列表缺 s_axis_tdata/m_axis_tdata（RTL 有，L105/L117），因 parser 注释 bug 丢弃"
  missing:
    - "rtl_parser：在 _extract_port_section/_parse_single_file 的 split(',') 前剥离 /* */ 与 // 注释（否则 case2 m_axis_tdata 不可见，golden 模型无从比对）— src/rtl_parser.py:178-195,202-241"
    - "为 valid-ready stream 接口（case2 axis_fifo_adapter）实现 golden shift-register 参考模型 + assert dut.m_axis_tdata.value==expected（8:8 宽度 FIFO 即纯延迟）— 模板新增分支，template L196-224 区"
    - "为 AXI slave only（case4 axi_ram）把孤儿 master 接入主循环调用 master.read(addr,length)+assert read.data==data（复用 case1 ram 比对模式）— template L133-144, src/skeleton_gen.py"
    - "为 case3(axi_vfifo_raw_rd,m_axi master 指针输出)/case5(axi_crossbar_addr 地址译码) 实现 invariant check assert（指针单调推进/译码表参考），非完整 golden 但满足门禁 #5"
    - "skeleton_gen scoreboard 字段改为反映实际 testbench 渲染分支的比对逻辑（按 inferred_protocols+has_axi_bus 派生），非硬编码 — src/skeleton_gen.py:151-154"
    - "重新生成 case2-5 的 generated_test.py 与 case2 design.json（修复后 m_axis_tdata 复现）"
  diagnosis_ref: .planning/debug/case2-5-comparator-gate.md
