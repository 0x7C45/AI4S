---
phase: 08-a2-skeleton-gate
verified: 2026-07-14T23:59:00Z
status: passed
score: 12/12 must-haves verified
behavior_unverified: 0
overrides_applied: 0
re_verification:
  previous_status: none
  note: "Initial verification — Phase 8 verified against current codebase (Phase 9/10 additions intact)."
---

# Phase 8: A2 Skeleton Gate — RTL Parse + testbench Gen — Verification Report

**Phase Goal:** run.py 跑通 RTL → testbench → 仿真 → 结果，case1 骨架门禁通过（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）
**Verified:** 2026-07-14T23:59:00Z
**Status:** PASSED
**Re-verification:** No — initial verification (against current codebase; Phase 9/10 additions are improvements, not regressions)

## Goal Achievement

### Observable Truths

Verified against ROADMAP Phase 8 Goal + 5 Success Criteria + PLAN must_haves.truths (12 truths, merged & deduplicated). Behavior-dependent truths (gate items 3-5) are backed by behavioral evidence: case1 simulation exit 0 with testcase PASS, plus all 5 cases pass — not symbol presence alone.

| #  | Truth | Status | Evidence |
| -- | ----- | ------ | -------- |
| 1  | run.py 接受五参数 `--rtl --top --out --seed --num-seq` 并启动完整流水线 | ✓ VERIFIED | `run.py:24-28` defines all 5 args (rtl/top required, seed=20260630, num-seq=5000 defaults); main() calls parse→skeleton→constraint→simulate→coverage in order (run.py:54-171); AST parses OK |
| 2  | rtl_parser 解析 case1 RTL 输出真实模块名 `axi_adapter_rd`（非 design.json 的 case1 别名） | ✓ VERIFIED | Live exec: `parse('testcases/.../case1/rtl', top_hint='case1')` returns `top_module=axi_adapter_rd` (D-07 honored — `_find_top_module` ignores misleading caseN hint) |
| 3  | rtl_parser 识别时钟 clk、复位 rst、端口方向/宽度、AXI 协议分组（s_axi/m_axi 前缀） | ✓ VERIFIED | Live exec returns `clock=clk, reset=rst, reset_active=high`; 40 ports classified: 19 axi_slave + 19 axi_master + clk + rst; widths preserved (e.g. `ADDR_WIDTH-1:0`, `7:0`, `2:0`) |
| 4  | 生成的 testbench 含时钟生成 `Clock(dut.clk, 10, unit="ns")` + 复位序列（rst 高 8 拍低 8 拍） | ✓ VERIFIED | `generated_test.py:103` has exact `Clock(dut.clk, 10, unit="ns")` (cocotb 2.0 API per D-04); `reset_dut` (line 79-89): setimmediatevalue(0) → 4 edges → value=1 for 8 edges → value=0 for 8 edges |
| 5  | 生成的 testbench 含 s_axi 读驱动 (AxiMasterRead/AxiReadBus.from_prefix) + m_axi 内存模型 (AxiRamRead) | ✓ VERIFIED | `generated_test.py:106-107`: `master = AxiMasterRead(AxiReadBus.from_prefix(dut, "s_axi"), dut.clk, dut.rst)` + `ram = AxiRamRead(AxiReadBus.from_prefix(dut, "m_axi"), dut.clk, dut.rst, size=2**16)` |
| 6  | 生成的 testbench 含 scoreboard（读后比对 RAM 预期数据） | ✓ VERIFIED | `generated_test.py:162-164`: inside the per-transaction loop — `ram.write(addr, data)` before read, then `assert read.data == data, "read %d addr=0x%x len=%d size=%s mismatch"` — assertion fires every transaction (non-silent, satisfies gate item ⑤) |
| 7  | 生成的 testbench 含 ready 反压 (cycle_pause/backpressure generator) | ✓ VERIFIED | `generated_test.py:113-116`: 4 channels wired with `set_pause_generator` — `master.ar_channel` (random_pause), `master.r_channel` (cycle_pause), `ram.ar_channel` (random_pause), `ram.r_channel` (random_pause) |
| 8  | 生成的 Makefile 默认 `SIM=verilator`，`COMPILE_ARGS` 含 `-Wno-fatal` | ✓ VERIFIED | Live skeleton_gen output: Makefile contains `SIM ?= verilator` (D-05), `COMPILE_ARGS = -Wno-fatal --coverage-line --coverage-toggle` (D-03), `TOPLEVEL = axi_adapter_rd` |
| 9  | case1 在 Docker verilator/verilator:v5.050 容器内编译通过 + 仿真 exit 0 | ✓ VERIFIED | `smoke_out/case1/report.json` pipeline.simulate `{status: passed, exit_code: 0}`; sim_log contains `MAKE_EXIT=0`; `results.xml` shows 1 testcase `run_generated_test` with 0 failures, sim_time=41220ns; compiled `sim_build/Vtop` binary (585KB) + 8 .o files + `coverage.dat` (207KB) prove real compile+run |
| 10 | design.json 含顶层模块名、文件列表、时钟/复位、端口方向/宽度/类型/协议分组、推断协议 | ✓ VERIFIED | `design.json` has all fields: `name`, `top_module`, `rtl_files[1]`, `parameters[14]`, `clock_reset{clock,reset,reset_active}`, `ports[40]` (each with name/direction/width/type/protocol_group), `inferred_protocols: ["AXI"]` |
| 11 | verification_skeleton.json 含时钟/复位生成方法、驱动列表、监视列表、DUT 输出、testbench 路径 | ✓ VERIFIED | `verification_skeleton.json` has top_module, clock_reset_generation{clock, clock_period_ns, reset, reset_active, reset_sequence}, input_drivers[2] (s_axi_read_master, m_axi_memory_model), output_monitors[2], scoreboard{model, compare}, dut_outputs[19], generated_testbench_path, makefile_path |
| 12 | 产物输出到 `--out` 目录，不写 testcases（locked） | ✓ VERIFIED | `run.py:39-41` resolves `out_dir = Path(args.out).resolve()`; all writes target `out_dir` (design.json, verification_skeleton.json, generated_tb/, report.json). No hardcoded `testcases/` write paths. Confirmed: case1 outputs in `smoke_out/case1/`, testcases/ untouched (read-only reference) |

**Score:** 12/12 truths verified (0 present, behavior-unverified)

Behavioral evidence is strong: not just symbol presence but a passing simulation (exit 0, testcase PASS, 41us sim time, 207KB coverage.dat). All 5 cases (case1-5) pass simulation end-to-end (verified via their report.json `simulate.exit_code=0`), which is stronger evidence than case1 alone — the gate infrastructure generalizes.

### Required Artifacts

| Artifact | Expected | Status | Details |
| -------- | -------- | ------ | ------- |
| `Track-A/A2-verification/run.py` | 五参数入口 + 完整流水线 | ✓ VERIFIED | 236 lines; argparse with 5 args; parse→skeleton→constraint→simulate→coverage stages; report.json writer; test-param extractor for dead-code analysis |
| `Track-A/A2-verification/run.sh` | bash wrapper forwarding 5 args | ✓ VERIFIED | 33 lines; Docker image auto-selection (AI4S_A2_IMAGE > local ai4s-a2 > verilator base); wheelhouse offline bootstrap; `exec python3 run.py "$@"` |
| `Track-A/A2-verification/src/rtl_parser.py` | RTL 接口解析 (parse → DesignInfo) | ✓ VERIFIED | 334 lines; `parse(rtl_dir, top_hint)` returns DesignInfo; regex-based (PyVerilog dep unused, CONTEXT.md Claude's Discretion authorized); port/param/clock/reset/protocol classification; `has_axi_bus(prefix)` (Phase 10 add); `to_design_json(path)` |
| `Track-A/A2-verification/src/skeleton_gen.py` | 骨架生成 (generate → testbench + Makefile + skel.json) | ✓ VERIFIED | 175 lines; `generate(design_info, out_dir, seed, num_seq)` returns SkeletonResult; Jinja2 render; RTL copy to generated_tb/rtl/; Makefile with SIM=verilator + -Wno-fatal; verification_skeleton.json writer |
| `Track-A/A2-verification/src/sim_runner.py` | 仿真执行 (run → Docker/make) | ✓ VERIFIED | 190 lines; `run(out_dir, seed, docker=True)` returns SimResult; Docker verilator:v5.050 + apt/pip bootstrap OR prebuilt image; `SIM_TIMEOUT_SECONDS=1200` (Phase 10 add); local-make fallback |
| `Track-A/A2-verification/templates/cocotb_tb.py.j2` | cocotb testbench Jinja2 模板 (cocotb 2.0) | ✓ VERIFIED | 243 lines; `Clock(dut.clock, 10, unit="ns")`; AXI-aware branching (has_axi_bus check, Phase 9/10 add); reset_dut; AxiMasterRead + AxiRamRead; 4-channel set_pause_generator; per-transaction assert scoreboard; functional coverage hit() (Phase 9 add); non-AXI valid-ready fallback with TypeError handling (Phase 10 add) |
| `Track-A/A2-verification/requirements.txt` | 5 包钉死版本 | ✓ VERIFIED | 7 lines: cocotb==2.0.1, cocotb-test==0.2.6, cocotbext-axi==0.1.28, cocotb-bus==0.3.0, scapy==2.7.0, Jinja2==3.1.6, PyVerilog==1.3.0 (all `==X.Y.Z` pinned; Phase 10 added cocotb-bus + scapy for transitive deps) |

### Key Link Verification

| From | To | Via | Status | Details |
| ---- | -- | --- | ------ | ------- |
| run.py | rtl_parser.parse | `parse_rtl(str(rtl_path), top_hint=args.top)` (run.py:56) | ✓ WIRED | Returns DesignInfo; `.to_design_json()` writes design.json; stages.parse records top_module/clock/reset |
| run.py | skeleton_gen.generate | `gen_skeleton(design_info, str(out_dir), args.seed, args.num_seq)` (run.py:75) | ✓ WIRED | Returns SkeletonResult; renders testbench + Makefile + verification_skeleton.json; stages.skeleton records testbench_path |
| run.py | sim_runner.run | `run_sim(str(out_dir), seed=args.seed)` (run.py:106) | ✓ WIRED | Returns SimResult; stages.simulate records passed/exit_code; sim_log captured |
| skeleton_gen | Jinja2 cocotb_tb.py.j2 | `env.get_template("cocotb_tb.py.j2")` + `template.render(design_info=..., seed=..., num_seq=..., bin_dict=...)` (skeleton_gen.py:73-91) | ✓ WIRED | Renders generated_test.py with DUT ports/protocols injected |
| sim_runner | Makefile SIM=verilator + COMPILE_ARGS=-Wno-fatal | Docker script: `make SIM=verilator MODULE={test_module}` (sim_runner.py:41, 69); Makefile has `SIM ?= verilator` + `COMPILE_ARGS = -Wno-fatal ...` | ✓ WIRED | MAKE_EXIT=0 confirmed in case1 sim_log |

### Data-Flow Trace (Level 4)

| Artifact | Data Variable | Source | Produces Real Data | Status |
| -------- | ------------- | ------ | ------------------ | ------ |
| `generated_test.py` | `master`/`ram` AXI handles | `AxiMasterRead(AxiReadBus.from_prefix(dut, "s_axi"))` + `AxiRamRead(...)` (lines 106-107) | ✓ Yes — RTL has all 8 AXI handshake signals (s_axi_arvalid/arready/rvalid/rready + m_axi_*) confirmed in case1.v | ✓ FLOWING |
| `generated_test.py` | `data` (scoreboard expected) | `bytes((index + offset*19 + rng.randrange(256)) & 0xff for offset in range(length))` (line 131) | ✓ Yes — pseudo-random per-transaction, written to RAM via `ram.write(addr, data)` then read back | ✓ FLOWING |
| `design.json` ports | `ports[]` | `rtl_parser._parse_single_file` regex extraction → `to_design_json` (rtl_parser.py:178-195, 56-80) | ✓ Yes — 40 ports from case1.v with real names/widths (ADDR_WIDTH-1:0 etc.) | ✓ FLOWING |
| `verification_skeleton.json` drivers | `input_drivers[]` | Conditional on `"AXI" in design_info.inferred_protocols` (skeleton_gen.py:125-137) | ✓ Yes — 2 drivers (s_axi_read_master, m_axi_memory_model) populated from DesignInfo protocol inference | ✓ FLOWING |

### Behavioral Spot-Checks

| Behavior | Command | Result | Status |
| -------- | ------- | ------ | ------ |
| run.py parses + 5 args defined | `py -c "import ast; ast.parse(open('run.py').read())"` + `grep add_argument run.py` | AST OK; 5 args: --rtl/--top/--out/--seed(default=20260630)/--num-seq(default=5000) | ✓ PASS |
| rtl_parser identifies real top (D-07) | `py -c "from src.rtl_parser import parse; d=parse('testcases/.../case1/rtl', top_hint='case1'); print(d.top_module)"` | `axi_adapter_rd` (not case1 alias) | ✓ PASS |
| rtl_parser identifies clock/reset/protocols | (same call) | clock=clk, reset=rst (high), protocols=['AXI'], 19 axi_slave + 19 axi_master ports | ✓ PASS |
| skeleton_gen renders testbench + Makefile | `py -c "from src.skeleton_gen import generate; ..."` in tmpdir | All 3 paths exist; Makefile has SIM=verilator + -Wno-fatal + TOPLEVEL=axi_adapter_rd | ✓ PASS |
| Gate item ① compile: Clock + cocotb.test + unit="ns" | grep on generated testbench | `Clock(dut.clk, 10, unit="ns")` present; `@cocotb.test()` present | ✓ PASS |
| Gate item ② DUT ports: AxiReadBus.from_prefix s_axi + m_axi | grep on generated testbench | Both prefixes present; RTL has all 8 required AXI handshake signals | ✓ PASS |
| Gate item ③ clock/reset: reset_dut high/low 8 cycles | grep on generated testbench | `dut.rst.value = 1` (8 RisingEdge) → `dut.rst.value = 0` (8 RisingEdge) | ✓ PASS |
| Gate item ④ driver/monitor/backpressure: AxiMasterRead + AxiRamRead + set_pause_generator | grep on generated testbench | All present; 4 channels wired with set_pause_generator | ✓ PASS |
| Gate item ⑤ scoreboard: assert read.data == data | grep on generated testbench | Inside per-transaction loop (line 163), non-silent; assertion fires every iteration | ✓ PASS |
| case1 simulation actually ran | `cat smoke_out/case1/generated_tb/results.xml` | 1 testcase `run_generated_test`, 0 failures, sim_time=41220ns | ✓ PASS |
| case1 sim exit 0 | `py -c "import json; r=json.load(open('report.json')); print(r['report']['pipeline']['simulate'])"` | `{status: passed, exit_code: 0}`; sim_log has `MAKE_EXIT=0` + `Verilog $finish` | ✓ PASS |
| case1 compiled binary exists | `ls sim_build/Vtop` | 585KB ELF binary + 8 .o files + Vtop.cpp/h/mk | ✓ PASS |
| All 5 cases pass simulation (stronger evidence) | Iterate case2-5 report.json simulate stage | case2 (axis_fifo_adapter), case3 (axi_vfifo_raw_rd), case4 (axi_ram), case5 (axi_crossbar_addr) all exit=0 | ✓ PASS |

### Probe Execution

Step 7c SKIPPED — Phase 8 does not declare probe scripts (`scripts/*/tests/probe-*.sh`); gate verification is performed via the live `run.py` end-to-end pipeline (behavioral spot-checks above serve as the probe equivalent). The persisted `smoke_out/case1/` artifacts (report.json, results.xml, coverage.dat, Vtop binary) are the canonical probe output.

### Requirements Coverage

| Requirement | Source Plan | Description | Status | Evidence |
| ----------- | ----------- | ----------- | ------ | -------- |
| A2-PARSE-01 | 08-01 | 识别时钟、复位、参数、端口方向/宽度 | ✓ SATISFIED | rtl_parser live exec: clock=clk, reset=rst (high), 14 parameters, 40 ports with direction+width |
| A2-PARSE-02 | 08-01 | 协议分组（AXI/AXI-Lite、SRAM-like、valid/ready stream） | ✓ SATISFIED | `_classify_protocol` (rtl_parser.py:112-131) groups ports by prefix/pattern: axi_slave/axi_master/sram/valid_ready/clock/reset/other; case1 yields 19+19 AXI ports |
| A2-PARSE-03 | 08-01 | 推断接口协议类型 | ✓ SATISFIED | `inferred_protocols` derived from protocol_group set (rtl_parser.py:316-323): case1 → ['AXI']; SRAM/valid-ready branches present |
| A2-SKEL-01 | 08-01 | 时钟/复位生成 | ✓ SATISFIED | Template has `Clock(dut.clk, 10, unit="ns")` + `reset_dut` (8-high/8-low); verification_skeleton.json clock_reset_generation block |
| A2-SKEL-02 | 08-01 | 输入驱动 + 输出监视 | ✓ SATISFIED | input_drivers[2] (AxiMasterRead + AxiRamRead), output_monitors[2], dut_outputs[19] in verification_skeleton.json |
| A2-SKEL-03 | 08-01 | 自动比对框架 | ✓ SATISFIED | `assert read.data == data` per-transaction (gate item ⑤, non-silent); scoreboard{model, compare} documented in skel.json |
| A2-SKEL-04 | 08-01 | 生成可编译可运行的 testbench | ✓ SATISFIED | case1 testbench compiled (Vtop binary 585KB) + ran (results.xml: 1 testcase, 0 failures, exit 0); 5/5 cases compile+run |
| A2-OUT-01 | 08-01 | run.sh/run.py 入口 — RTL 到结果完整流水线 | ✓ SATISFIED | run.py 5-arg entry; run.sh bash wrapper with Docker image auto-selection; full pipeline parse→skeleton→simulate→coverage; report.json with reproducible_command |

### Anti-Patterns Found

| File | Line | Pattern | Severity | Impact |
| ---- | ---- | ------- | -------- | ------ |
| (none) | — | — | — | No TBD/FIXME/XXX/PLACEHOLDER/not-yet-implemented markers in any Phase 8 deliverable file. Empty-handler and hardcoded-empty-data stub patterns absent. |

Phase 9/10 additions to Phase 8 modules (sim_runner timeout constant + image selection; cocotb_tb.py.j2 AXI-bus-aware branching + TypeError handling + functional sampling; rtl_parser has_axi_bus method; run.py stages 3-5 + dead-code wiring) are ADDITIONS that extend functionality without regressing the Phase 8 skeleton-gate scope. The Phase 8 deliverable (gate infrastructure) is intact and improved.

### Human Verification Required

None. All 12 truths resolved to VERIFIED with behavioral evidence (passing simulation). No ⚠️ PRESENT_BEHAVIOR_UNVERIFIED items.

### Gaps Summary

No gaps. All 12 must-have truths verified, all 7 required artifacts substantive and wired, all 5 key links wired with real data flow, all 8 requirements (A2-PARSE-01/02/03, A2-SKEL-01/02/03/04, A2-OUT-01) satisfied, all 5 gate-check items pass against case1's generated_test.py, and behavioral spot-checks confirm the simulation actually ran (exit 0, testcase PASS, compiled binary, coverage.dat).

The phase goal — "run.py 跑通 RTL → testbench → 仿真 → 结果，case1 骨架门禁通过" — is fully achieved. Stronger evidence than required: all 5 public cases pass simulation, not just case1.

---

_Verified: 2026-07-14T23:59:00Z_
_Verifier: ZCode/GLM (gsd-verifier)_
