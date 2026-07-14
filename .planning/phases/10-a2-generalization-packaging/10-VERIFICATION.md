---
phase: 10-a2-generalization-packaging
verified: 2026-07-14T20:32:09Z
status: gaps_found
score: 4/6 must-haves verified
behavior_unverified: 0
overrides_applied: 0
gaps:
  - truth: "testbench 比对器实际比对 DUT 行为（scoring.md §1 门禁 #5：比对器未比对 DUT 行为或静默忽略比对失败 → 该电路 0 分）"
    status: failed
    reason: "case2/3/4/5 generated_test.py 含 0 个 assert、0 个 DUT 输出端口采样、0 个比对逻辑。cocotb_tb.py.j2 的 {% else %} 非 AXI 分支自标 'scoreboard 占位'（placeholder），仅按 index%2/index%3 枚举覆盖 bin，不读任何 DUT 输出。per scoring.md §1 门禁失败条件 #5，这 4 个电路骨架门禁失败 → 各得 0 分，覆盖率不计。仅 case1（s_axi+m_axi 完整 AXI 分支）含真实 assert read.data == data 比对。"
    artifacts:
      - path: "Track-A/A2-verification/templates/cocotb_tb.py.j2"
        issue: "第 196-224 行 {% else %} 非 AXI 分支：自标 'scoreboard 占位'，无 assert/无 DUT 输出读取/无参考模型比对。第 214 行注释 'scoreboard 占位：valid-ready 接口的基本数据比对（驱动后采样输出）' 但代码未采样任何输出端口。"
      - path: "Track-A/A2-verification/smoke_out/case2/generated_tb/generated_test.py"
        issue: "DUT=axis_fifo_adapter（valid-ready）。assert 计数=0。第 136 行 '# scoreboard 占位'。驱动仅对全部端口盲写随机值（setimmediatevalue），不读输出。verification_skeleton.json 声称 scoreboard 'assert read.data == expected_data' 但代码无此 assert——声明与实现不符（fabricated declaration）。"
      - path: "Track-A/A2-verification/smoke_out/case3/generated_tb/generated_test.py"
        issue: "DUT=axi_vfifo_raw_rd（AXI+SRAM+valid-ready）。assert 计数=0。第 141 行 '# scoreboard 占位'。AXI 分支走 'pass'（第 108 行，DUT 为 master 不实例化 cocotbext-axi），落入非 AXI 通用驱动路径，无比对。"
      - path: "Track-A/A2-verification/smoke_out/case4/generated_tb/generated_test.py"
        issue: "DUT=axi_ram（AXI, 仅 s_axi）。assert 计数=0。第 142 行 '# scoreboard 占位'。虽然实例化了 AxiMasterRead（第 106 行），但从未调用 master.read()——驱动对象被孤立（orphaned），仅第 158 行 await master.wait_idle()。无读事务、无比对。"
      - path: "Track-A/A2-verification/smoke_out/case5/generated_tb/generated_test.py"
        issue: "DUT=axi_crossbar_addr（AXI+valid-ready）。assert 计数=0。第 141 行 '# scoreboard 占位'。AXI 分支走 'pass'（s_axi 部分信号，has_axi_bus 返回 false），落入非 AXI 通用驱动路径，无比对。"
      - path: "Track-A/A2-verification/src/skeleton_gen.py"
        issue: "第 151-154 行 verification_skeleton.json 的 scoreboard 字段是对所有 case 硬编码的静态字符串（'assert read.data == expected_data after each transaction'），与实际 testbench 是否含 assert 无关。case2-5 的 skeleton 声称有比对器但 testbench 无比对代码——声明伪造。"
    missing:
      - "为非 AXI 接口（valid-ready stream / SRAM-like）实现真实参考模型或输出比对器：采样 DUT 输出端口，与预期比对，mismatch 时 assert/raise 使测试失败"
      - "cocotb_tb.py.j2 的 {% else %} 分支移除 'scoreboard 占位'，改为按协议生成对应 monitor+scoreboard（valid-ready: 采样 tdata/tvalid/tready 与驱动数据比对；SRAM: 采样 dout 与预期比对）"
      - "case4：调用 master.read() 实际发起读事务并与 RAM 预期数据 assert 比对（当前 master 对象被孤立）"
      - "skeleton_gen.py：scoreboard 字段应反映实际 testbench 比对能力，非硬编码字符串；非 AXI case 不应声称 'm_axi side memory model'"
  - truth: "功能覆盖 bin 对应真实 DUT 行为采样（scoring.md §2：仅枚举随机值而无测试采样证据的 bin 不计）"
    status: failed
    reason: "case2-5 的 functional_coverage 命中 bin 来自模板第 217-220 行 if index%2==0 / if index%3==0 的循环计数枚举，与 DUT 实际输出完全无关。如 case2 的 full_width(50 hits)/fifo_half(34 hits) 仅因循环迭代次数命中，非 DUT 行为采样。per scoring.md §2 '仅枚举随机值而无测试采样证据的 bin 不计'，这些 bin 应被判无效 → 功能覆盖率=0%。"
    artifacts:
      - path: "Track-A/A2-verification/templates/cocotb_tb.py.j2"
        issue: "第 217-220 行：if index % 2 == 0: coverage.hit('data_width_boundary','full_width'); if index % 3 == 0: coverage.hit('fifo_full_empty','fifo_half') —— 纯循环索引枚举，无 DUT 输出采样依据"
      - path: "Track-A/A2-verification/smoke_out/case2/functional_coverage.json"
        issue: "covered_bins=2 (full_width hits=50, fifo_half hits=34)，但这两个 bin 命中与 DUT axis_fifo_adapter 的实际输出行为无关"
    missing:
      - "功能覆盖 bin 的 hit() 必须基于采样的 DUT 输出信号值（如 tdata 宽度、fifo 状态信号），而非循环索引"
  - truth: "SUMMARY.md 覆盖率数据真实反映 coverage_result.json（无漂移）"
    status: failed
    reason: "SUMMARY.md 'Accomplishments' 表声称 case1 composite=79.09%（line 82.54%/branch 53.57%/func 100%），但实际 smoke_out/case1/coverage_result.json 为 composite=63.57%（line 96.08%/branch 41.67%/func 42.11%）。func 100% 系伪造（实际 42.11%）。SC4 '覆盖率与本地无漂移' 的前提数据本身失真。"
    artifacts:
      - path: ".planning/phases/10-a2-generalization-packaging/10-01-SUMMARY.md"
        issue: "第 140-144 行覆盖率表 case1 行：82.54/53.57/100/79.09 与实际 coverage_result.json 96.08/41.67/42.11/63.57 不符"
      - path: "Track-A/A2-verification/smoke_out/case1/coverage_result.json"
        issue: "实际 composite=63.57%, functional=42.11%（非 SUMMARY 声称的 79.09%/100%）"
    missing:
      - "修正 SUMMARY.md 覆盖率表为实际 coverage_result.json 数值"
---

# Phase 10: A2 Generalization + Offline Packaging — Verification Report

**Phase Goal:** 10 隐藏电路通用化 + 离线打包 + Docker 复验，准备提交
**Verified:** 2026-07-14T20:32:09Z
**Status:** gaps_found
**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

Roadmap Phase 10 Success Criteria (SC1-SC5) plus the competition-scoring gate truth derived from the OFFICIAL `Track-A/A2-verification/scoring.md` §1 (source of truth for what "done" means at submission).

| #   | Truth | Status | Evidence |
| --- | ----- | ------ | -------- |
| 1   | SC1: 框架对隐藏电路通用化（禁硬编码/针对性优化，自适应 AXI/SRAM/valid-ready 接口） | ✓ VERIFIED | `rtl_parser.has_axi_bus(prefix)` 运行时探测关键 AXI 握手信号（arvalid/arready/rvalid/rready）；模板按探测结果分支。grep `case[1-5]` src/ templates/ 命中均为注释/docstring（解释自适应逻辑），无 `if case=="case1"` 业务逻辑硬编码。inferred_protocols 对 case2(valid-ready)/case3(AXI+SRAM+valid-ready)/case4(AXI)/case5(AXI+valid-ready) 非空。 |
| 2   | SC2: requirements.txt 每包钉死 ==X.Y.Z；wheelhouse/ 离线包齐全，评测机 pip install --no-index 可装 | ✓ VERIFIED | requirements.txt 7 包全 `==` 钉版（cocotb==2.0.1, cocotbext-axi==0.1.28, cocotb-bus==0.3.0, scapy==2.7.0, Jinja2==3.1.6, PyVerilog==1.3.0, cocotb-test==0.2.6）。wheelhouse/ 含 13 个文件：cocotb-2.0.1-cp312-manylinux2014_x86_64.whl, cocotb_bus-0.3.0, cocotbext_axi-0.1.28, jinja2-3.1.6, pyverilog-1.3.0, scapy-2.7.0, markupsafe, ply, pip, setuptools, wheel, find_libpython（含传递依赖 cocotb-bus+scapy，per FIX3）。run.sh 第 34 行 `pip install --no-index --find-links=wheelhouse -r requirements.txt`。 |
| 3   | SC3: THIRD_PARTY.md 齐全（版本/许可/调用边界） | ✓ VERIFIED | THIRD_PARTY.md 214 行，32 个表格行，覆盖 cocotb/cocotb-test/cocotbext-axi/cocotb-bus/scapy/Jinja2/PyVerilog/Verilator 等（含 GPL scapy 许可声明 per SUMMARY FIX3）。 |
| 4   | SC4: Docker linux/amd64 复跑 5 公开 case，覆盖率与本地无漂移 | ⚠️ PARTIAL | 5 case 均产 7 JSON，composite 全 > 0（case1=63.57%, case2=49.14%, case3=57.1%, case4=50.27%, case5=43.52%）。但 "Docker linux/amd64 复跑无漂移" 无法在本环境验证（需 Docker linux/amd64 实跑对比）；且 SUMMARY 覆盖率表本身失真（见 truth #6），"无漂移" 基准不可信。 |
| 5   | SC5: run.sh 独自跑通完整流水线，评测人员无需手改任何生成文件 | ✓ VERIFIED | `bash -n run.sh` 语法 OK；含 run.py 调用（exec python3 run.py "$@"）；含离线安装段（wheelhouse 检测 + pip --no-index）；Docker 镜像自动选择（AI4S_A2_IMAGE 优先级）。 |
| 6   | **GATE TRUTH (scoring.md §1 #5): testbench 比对器实际比对 DUT 行为** | ✗ FAILED | **case2/3/4/5 generated_test.py assert 计数=0，0 个 DUT 输出端口采样，0 个比对逻辑。** 模板 `{% else %}` 非 AXI 分支自标 "scoreboard 占位"。仅 case1 含 `assert read.data == data`。per scoring.md §1 门禁失败条件 #5，case2-5 骨架门禁失败 → 各 0 分，覆盖率不计。详见 Gaps。 |

**Score:** 4/6 truths verified (SC1, SC2, SC3, SC5 VERIFIED; SC4 PARTIAL; GATE TRUTH FAILED)

### Competition Scoring Gate Analysis (scoring.md §1 — OFFICIAL source of truth)

scoring.md §1 lists 5 门禁失败条件 (gate-failure conditions). "验证骨架是门禁项。若某电路的 testbench 无法编译、无法启动仿真、无法正确连接 DUT 或缺少有效的驱动/监视/比对器，该电路得 0 分，覆盖率不计。"

Per-case gate assessment (read from actual `smoke_out/caseN/generated_tb/generated_test.py`):

| Case | DUT | ① compiles+sim starts | ② ports connected | ③ clk/rst/handshake | ④ valid driver/monitor | ⑤ comparator compares DUT behavior | Gate |
| ---- | --- | --- | --- | --- | --- | --- | --- |
| case1 | axi_adapter_rd | ✓ Clock+reset | ✓ AxiReadBus.from_prefix s_axi+m_axi | ✓ clk/rst/ready 反压 | ✓ AxiMasterRead+AxiRamRead | ✓ `assert read.data == data` (line 163) | **PASS** |
| case2 | axis_fifo_adapter | ✓ Clock+reset | ⚠ 盲写所有端口 | ✓ clk/rst | ✗ 无有效驱动（盲写随机值非协议驱动）；monitor=[] | ✗ 0 assert，"scoreboard 占位" | **FAIL (#5 + #4)** |
| case3 | axi_vfifo_raw_rd | ✓ Clock+reset | ⚠ 盲写所有端口 | ✓ clk/rst | ✗ AXI 分支 `pass`（第 108 行）；落入盲写路径 | ✗ 0 assert，"scoreboard 占位" | **FAIL (#5 + #4)** |
| case4 | axi_ram | ✓ Clock+reset | ⚠ AxiMasterRead 建但孤立 | ✓ clk/rst | ⚠ master 实例化但从未 master.read()（orphaned） | ✗ 0 assert，"scoreboard 占位" | **FAIL (#5)** |
| case5 | axi_crossbar_addr | ✓ Clock+reset | ⚠ 盲写所有端口 | ✓ clk/rst | ✗ AXI 分支 `pass`；落入盲写路径 | ✗ 0 assert，"scoreboard 占位" | **FAIL (#5 + #4)** |

**Conclusion:** Per the OFFICIAL scoring.md §1, **case2/3/4/5 fail the skeleton gate** (primarily condition #5 — comparator does not compare DUT behavior; case2/3/5 also fail #4 — no valid driver/monitor). Gate failure = 0 points per case, coverage not counted. Only **case1 passes the gate**.

**Scoring impact estimate (5 public cases only; 10 hidden cases unknown):**
- case1: gate PASS, composite 63.57% → 45%≤C<65% band → coverage 2.8 pts + skeleton 3 pts = **5.8/10**
- case2-5: gate FAIL → **0/10 each**
- Public-case subtotal: ~5.8 / 50 (if hidden cases behave like case2-5, the submission is near-zero).

This is the primary reason Phase 10 cannot be marked passed: the generalization claim (SC1) is technically true at the code-structure level, but the generalized non-AXI path produces testbenches that fail the competition's own scoring gate.

### Required Artifacts

| Artifact | Expected | Status | Details |
| -------- | -------- | ------ | ------- |
| `Track-A/A2-verification/wheelhouse/` | 离线 wheel 目录 ≥4 包 | ✓ VERIFIED | 13 文件（含 cocotb/jinja2/pyverilog/cocotb-bus/scapy/pip/setuptools/wheel/markupsafe/ply/find_libpython） |
| `Track-A/A2-verification/run.sh` | 含离线安装 + run.py 调用 | ✓ VERIFIED | bash -n OK；第 34 行 pip --no-index --find-links=wheelhouse；exec run.py |
| `Track-A/A2-verification/THIRD_PARTY.md` | 8+ 依赖条目 | ✓ VERIFIED | 214 行，32 表行 |
| `Track-A/A2-verification/README.md` | 离线安装/运行章节 | ✓ VERIFIED | 含 install/offline/离线 |
| `Track-A/A2-verification/templates/cocotb_tb.py.j2` | 通用化模板（AXI/SRAM/valid-ready） | ✗ STUB (非 AXI 比对分支) | AXI 完整分支（s_axi+m_axi）有真实 assert 比对；{% else %} 非 AXI 分支为 "scoreboard 占位"，无比对逻辑 |
| `Track-A/A2-verification/src/skeleton_gen.py` | 生成真实 skeleton | ⚠ WARNING | scoreboard 字段硬编码静态字符串，case2-5 声称有比对器但 testbench 无比对代码 |
| `Track-A/A2-verification/src/sim_runner.py` | timeout=1200 | ✓ VERIFIED | SIM_TIMEOUT_SECONDS=1200（第 25 行），Docker+local 两路引用 |
| `Track-A/A2-verification/src/rtl_parser.py` | has_axi_bus 协议推断 | ✓ VERIFIED | 第 34 行 has_axi_bus(prefix)；_classify_protocol 第 112 行 |

### Key Link Verification

| From | To | Via | Status | Details |
| ---- | -- | --- | ------ | ------- |
| rtl_parser | cocotb_tb.py.j2 | has_axi_bus() → 模板 {% if %} 分支 | ✓ WIRED | 探测结果驱动模板分支选择 |
| skeleton_gen | cocotb_tb.py.j2 | Jinja2 render(design_info, bin_dict) | ✓ WIRED | 第 86-91 行 render |
| run.sh | run.py | exec python3 run.py "$@" | ✓ WIRED | 第 47 行 |
| run.sh | wheelhouse | pip install --no-index --find-links | ✓ WIRED | 第 32-35 行 |
| cocotb_tb.py.j2 {% else %} 分支 | DUT 输出比对 | assert / monitor 采样 | ✗ NOT_WIRED | 非 AXI 分支无任何 DUT 输出读取或比对 — **gate #5 断链** |
| case4 AxiMasterRead | master.read() + assert | 读事务 + 比对 | ✗ NOT_WIRED | master 对象建后孤立，仅 wait_idle，无 read/无 assert |

### Data-Flow Trace (Level 4)

| Artifact | Data Variable | Source | Produces Real Data | Status |
| -------- | ------------- | ------ | ------------------ | ------ |
| case1 testbench | `read.data` vs `data` | master.read() + ram.write(addr,data) | ✓ 真实 DUT 读出 vs 预期 | ✓ FLOWING |
| case2-5 testbench | (无比对变量) | 盲写随机值到端口；不读输出 | ✗ 无 DUT 输出数据流 | ✗ DISCONNECTED |
| case2-5 functional_coverage | `full_width`/`fifo_half` hits | `if index%2==0`/`if index%3==0` 循环枚举 | ✗ 与 DUT 行为无关 | ✗ HOLLOW (枚举非采样) |

### Behavioral Spot-Checks

| Behavior | Command | Result | Status |
| -------- | ------- | ------ | ------ |
| assert count per case | `grep -c "assert " caseN/generated_test.py` | case1=1, case2-5=0 | ✗ FAIL (case2-5) |
| master.read actual call (case4) | `grep "master.read\|= await master" case4/...` | 仅 wait_idle，无 read | ✗ FAIL (case4 driver 孤立) |
| sim_runner timeout | `grep SIM_TIMEOUT_SECONDS src/sim_runner.py` | =1200 | ✓ PASS |
| run.sh syntax | `bash -n run.sh` | exit 0 | ✓ PASS |
| wheelhouse whl count | `ls wheelhouse/*.whl \| wc -l` | 11 whl + 2 tar.gz | ✓ PASS |
| red-line hardcode scan | `grep -rn 'case[1-5]' src/ templates/` | 仅注释/docstring | ✓ PASS |

### Probe Execution

No `scripts/*/tests/probe-*.sh` probes declared for this phase. Step 7c SKIPPED (no probes).

### Requirements Coverage

| Requirement | Source Plan | Description | Status | Evidence |
| ----------- | ----------- | ----------- | ------ | -------- |
| A2-OUT-02 | 10-01-PLAN | 完整 JSON 报告（design/verification_skeleton/constraints/coverage_bins/functional_coverage/coverage_result/report） | ⚠ PARTIAL | 5 case 各产 7 JSON（结构完整），但 verification_skeleton.json 的 scoreboard 字段对 case2-5 为伪造声明（声称有比对器，实际无），与 spec.md §1 "自动比对框架" 要求不符 |

### Anti-Patterns Found

| File | Line | Pattern | Severity | Impact |
| ---- | ---- | ------- | -------- | ------ |
| `templates/cocotb_tb.py.j2` | 214 | "scoreboard 占位" (placeholder scoreboard) | 🛑 BLOCKER | 非 AXI 分支无比对 → scoring.md §1 门禁 #5 失败 |
| `templates/cocotb_tb.py.j2` | 217-220 | `if index%2==0: coverage.hit(...)` 循环枚举 | 🛑 BLOCKER | 功能 bin 无采样依据 → scoring.md §2 判无效 |
| `templates/cocotb_tb.py.j2` | 199-212 | 盲写所有端口随机值（非协议驱动） | 🛑 BLOCKER | 无有效驱动/监视 → 门禁 #4 失败 |
| `src/skeleton_gen.py` | 151-154 | scoreboard 硬编码静态字符串 | ⚠ WARNING | 声明与实现不符（fabricated declaration） |
| `10-01-SUMMARY.md` | 140-144 | case1 覆盖率 79.09%/100% 与实际 63.57%/42.11% 不符 | ⚠ WARNING | SUMMARY 数据失真 |

### Human Verification Required

无新增 human-verification 项。本阶段产物为代码/打包，gate 失败由代码静态分析确证（assert 计数=0），无需人工判定。Docker linux/amd64 "无漂移" 复跑属 SC4 但非阻塞性（gate 失败已独立成立）。

### Gaps Summary

**Primary blocker — competition scoring gate failure (scoring.md §1 #5):**

Phase 10 的 SC1-SC3/SC5（通用化代码结构 + 离线打包 + run.sh）确实达成，wheelhouse/THIRD_PARTY/run.sh 质量高。但通用化的**实质行为**未达成：非 AXI 接口（valid-ready stream / SRAM-like / 残缺 AXI）的 testbench 生成了"骨架"却**没有比对器**。模板 `cocotb_tb.py.j2` 的 `{% else %}` 分支自标 "scoreboard 占位"，对 case2/3/4/5 生成 0 个 assert、0 个 DUT 输出采样的 testbench。

per OFFICIAL `scoring.md` §1 门禁失败条件 #5（"比对器未比对 DUT 行为或静默忽略比对失败"），case2/3/4/5 骨架门禁失败 → 各 0 分，覆盖率不计。仅 case1（完整 AXI 分支）含真实 `assert read.data == data` 通过门禁。

**根因：** `templates/cocotb_tb.py.j2` 第 196-224 行 `{% else %}` 分支只实现了"驱动输入端口"（且是盲写随机值，非协议驱动），未实现"采样输出 + 参考模型比对"。`src/skeleton_gen.py` 第 151-154 行的 `verification_skeleton.json` scoreboard 字段是对所有 case 硬编码的静态字符串，造成"声明有比对器、实现无比对器"的虚假骨架。

**次要 gap：** case2-5 功能覆盖 bin 命中来自 `if index%2==0`/`if index%3==0` 循环枚举（非 DUT 行为采样），per scoring.md §2 应判无效。SUMMARY.md 覆盖率表 case1 数据失真（声称 79.09%/100%，实际 63.57%/42.11%）。

**修复方向（供 /gsd-plan-phase 10 --gaps）：** 为 valid-ready stream / SRAM-like / 残缺 AXI 接口实现真实 monitor+scoreboard：采样 DUT 输出端口（tdata/tvalid/tready/dout 等），与参考模型预期比对，mismatch 时 assert/raise 使测试失败。case4 需调用 master.read() 并 assert 比对。skeleton_gen 的 scoreboard 字段应反映实际比对能力。

---

_Verified: 2026-07-14T20:32:09Z_
_Verifier: Claude (gsd-verifier)_
