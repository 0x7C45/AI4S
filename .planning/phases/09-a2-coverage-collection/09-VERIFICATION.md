---
phase: 09-a2-coverage-collection
verified: 2026-07-14T23:45:00Z
status: partial_closed
score: 6/10 must-haves verified
behavior_unverified: 0
overrides_applied: 0
gaps:

  - truth: "RTL 静态分析：generate/if 死码识别，只对可达分支采 bin（避免 case1 53% 死码天花板）"
    status: failed
    reason: >
      dead_code_analyzer.py exists and produces output, but it is NOT WIRED into the
      pipeline. run.py stage 5 calls `collect_cov(str(sim_tb_dir), design_info)` with
      no dead_code_info argument; dead_code_analyzer is never imported by run.py.
      Additionally the analyzer has a known precision bug (marks case1 L243-679 = 437
      lines as dead, including the ACTIVE shrink else-branch), which is WHY it was
      disabled. Net effect: coverage denominators include all lines including
      parameterized dead code, so case1 line% is capped at ~82% instead of reaching
      the >95% that proper dead-code filtering would yield. SC #5 is unmet.
    artifacts:

      - path: "Track-A/A2-verification/src/dead_code_analyzer.py"
        issue: "Module exists, has if/else-block boundary bug (marks active else-branch as dead); never imported by run.py"

      - path: "Track-A/A2-verification/run.py"
        issue: "Stage 5 collect_cov() call omits dead_code_info; dead_code_analyzer not imported"
    missing:

      - "Import dead_code_analyzer in run.py, call analyze(), pass DeadCodeInfo to collect_cov()"
      - "Fix if/else-block boundary matching in dead_code_analyzer so the active else-branch is not marked dead"
  - truth: "生成的 testbench 含 functional_coverage.hit() 真实事务采样（不空 hit，不初始化一次性 hit）— 对 4 类模板普遍适用"
    status: failed
    reason: >
      Real transaction-parameter-based bin sampling (read_length/address_alignment/
      burst_size derived from actual driven transaction params) is implemented ONLY
      for the AXI s_axi+m_axi full-bus path (case1). For all other cases (case2-5),
      the template renders the 'non-AXI generic driver' branch whose bin sampling is
      deterministic modulo: `if index % 2 == 0: coverage.hit('data_width_boundary',
      'full_width')` and `if index % 3 == 0: coverage.hit('fifo_full_empty',
      'fifo_half')`. This always hits the same 2 bins regardless of DUT state, so
      case2-5 functional coverage is ~0-8% (2/26 to 1/25 bins). The template comment
      itself labels this '通用 bin hit (简化采样)' and the scoreboard as '占位'
      (placeholder). SC #2 requires real transaction sampling for the 4 templates;
      only the AXI template is truly sampled.
    artifacts:

      - path: "Track-A/A2-verification/templates/cocotb_tb.py.j2"
        issue: "Lines 214-221: non-AXI branch uses index-modulo placeholder sampling, not real transaction sampling; scoreboard marked 占位"
    missing:

      - "Implement real functional bin sampling for the non-AXI (valid-ready/SRAM/AXIS) driver path based on actual driven/sampled transaction state"
  - truth: "三类覆盖率齐全 + 综合 C>=65%（保底档），冲 C>=85%（满分档）— Phase 9 ROADMAP goal"
    status: failed
    reason: >
      Current composite C per case (num-seq=100, not the required 5000):
      case1=79.09% case2=49.14% case3=57.10% case4=50.27% case5=43.52%.
      Only case1 (79.09%) meets the C>=65% baseline; 4 of 5 cases are below 65%.
      Average = 55.82%. The C>=85% full-score band is met by 0/5 cases. Even case1
      (the best case) is at 79%, below 85%. The dominant cause is functional coverage
      being near-zero on case2-5 (placeholder sampling gap above) and 5000-seq not
      actually run (deviation: only 100 seq executed).
    artifacts:

      - path: "Track-A/A2-verification/smoke_out/case2/coverage_result.json"
        issue: "C=49.14%, below 65% baseline (functional=7.69% due to placeholder sampling)"

      - path: "Track-A/A2-verification/smoke_out/case5/coverage_result.json"
        issue: "C=43.52%, below 45% floor (functional=0.00%)"
    missing:

      - "Real functional bin sampling for non-AXI cases to lift functional coverage"
      - "Run at the required 5000 sequences (currently only 100 executed per the run.sequence_count field)"
  - truth: "约束随机：5000 序列，seed=20260630 穿透 random.Random(seed) + directed 边界值 — 端到端实际执行 5000 笔"
    status: partial
    reason: >
      constraint_gen.py correctly emits seed=20260630 and sequence_count=5000 (verified
      by direct call), and the testbench penetrates random.Random(seed). Directed
      boundary values [1,2,3,4,...,256] are present in read_lengths(). BUT every
      smoke_out/case*/report.json shows run.sequence_count=100, not 5000. The 5000-seq
      run was a documented deviation (timeout in Docker at 10 min). Phase 10 raised
      the timeout 600->1200s but the 5000-seq run was never actually re-executed to
      produce outputs. The infrastructure supports 5000; the deliverable evidence is
      at 100.
    artifacts:

      - path: "Track-A/A2-verification/smoke_out/case2/coverage_result.json"
        issue: "run.sequence_count=100, not 5000"
    missing:

      - "Execute and produce outputs at num-seq=5000 (the evaluation scale) to prove no timeout at the required scale"

---

# Phase 9: A2 Coverage Collection — Verification Report

**Phase Goal:** 三类覆盖率齐全 + 综合 C≥65%（保底档），冲 C≥85%（满分档）
**Verified:** 2026-07-14T23:45:00Z
**Status:** gaps_found
**Re-verification:** No — initial verification

## Goal Achievement

This verification was performed against the CURRENT codebase (post-Phase-10). Phase 10 modified several Phase 9 modules (notably coverage_collect.py gained a native coverage.dat parser replacing the silent-fail Docker-LCOV path, and sim timeouts were raised 600→1200s). Those changes are forward progress and are NOT counted as Phase 9 failures. The gaps below exist in the current shipping code regardless of which phase introduced them.

### Observable Truths

Must-haves are merged from ROADMAP Phase 9 Success Criteria (the contract) and PLAN 09-01 frontmatter `must_haves.truths` (plan-specific detail). ROADMAP SCs are authoritative; the plan adds detail but does not subtract scope.

| # | Truth (source) | Status | Evidence |
|---|----------------|--------|----------|
| 1 | 行/分支覆盖率：Verilator `--coverage-line --coverage-toggle` 插桩 → coverage.dat LCOV 解析（按文件过滤排除 wrapper）(SC#1) | ✓ VERIFIED | Makefile has `COMPILE_ARGS = -Wno-fatal --coverage-line --coverage-toggle` (case2/Makefile L16). coverage_collect.py has native coverage.dat parser (`_parse_native`) + Docker LCOV fallback + wrapper filter (`_WRAPPER_KEYWORDS = cocotb_top/wrapper/_top.v/tb_top`, `_is_wrapper()`). case2 coverage_result.json: line=88.24%, branch=38.46% — non-zero, parsed from coverage.dat. |
| 2 | 功能 bin 真实事务采样（cocotb hit），4 类模板（FSM/数据通路/存储器/AXI）(SC#2) | ✗ FAILED | 4 templates DEFINED in coverage_gen.py (`_BIN_TEMPLATES`: AXI/FSM/DATAPATH/MEMORY). But real transaction-parameter sampling only works for AXI s_axi+m_axi (case1 → func=100%). case2-5 use the non-AXI template branch with deterministic modulo placeholder sampling (`if index%2==0: hit("data_width_boundary","full_width")`, `if index%3==0: hit("fifo_full_empty","fifo_half")`). Result: case2 func=7.69% (2/26), case3 func=4.00%, case4 func=2.63%, case5 func=0.00%. Template comment self-labels this as "简化采样" (simplified) and scoreboard "占位" (placeholder). See gap #2. |
| 3 | 约束随机 5000 序列，seed=20260630 穿透 random.Random + directed 边界值 (SC#3) | ⚠️ PARTIAL | constraint_gen emits seed=20260630 + sequence_count=5000 (verified by direct call: seed=20260630, seq=5000, 8 AXI tx vars). Testbench penetrates `rng = random.Random(seed)` (template L110). Directed boundary values `[1,2,3,4,5,7,8,15,16,17,31,32,33,63,64,65,127,128,255,256]` in `read_lengths()`. BUT all 5 smoke_out outputs show `run.sequence_count=100` — the 5000-seq run was never actually executed end-to-end (documented timeout deviation). Infrastructure ✓, deliverable evidence ✗. See gap #4. |
| 4 | 7 JSON 产物齐全，coverage_result.json 综合公式写 0.4/0.3/0.3（禁止 0.42/0.28/0.30）(SC#4) | ✓ VERIFIED | report_gen.py computes `composite = 0.4*line + 0.3*branch + 0.3*functional` (L26-28), writes `formula="0.4 * line + 0.3 * branch + 0.3 * functional"` (L56). Verified by direct call: percent=75.6 for (60,72,100) inputs, formula correct. No 0.42/0.28/0.30 anywhere (only in comments as "禁止" warning). 7-JSON complete for case2/3/4/5 (case1 missing functional_coverage.json — stale pre-Phase-10 output, per instructions case1 is not canonical). |
| 5 | RTL 静态分析：generate/if 死码识别，只对可达分支采 bin (SC#5) | ✗ FAILED | dead_code_analyzer.py exists with `analyze()` returning DeadCodeInfo. BUT: (a) NOT WIRED — run.py stage 5 calls `collect_cov(str(sim_tb_dir), design_info)` with no dead_code_info; dead_code_analyzer is never imported by run.py (grep confirms 0 import sites in run.py). (b) Known precision bug: for case1 (S=32,M=16) it marks L243-679 = 437 lines as dead, including the ACTIVE shrink else-branch — exactly the deviation Phase 9 SUMMARY documents. The disabling is why the filtering is off. Net: coverage denominators include parameterized dead code, capping case1 line% at ~82% rather than the >95% proper filtering would yield. See gap #1. |
| 6 | constraint_gen 生成 constraints.json 含 seed=20260630, sequence_count=5000, transaction_variables (PLAN) | ✓ VERIFIED | Direct call on case1: seed=20260630, sequence_count=5000, 8 transaction_variables (address/length_bytes/size/burst/arid + 3 backpressure). Writes valid JSON. |
| 7 | coverage_gen 定义功能 bin 4 类模板，每个 bin 对应可解释场景 (PLAN) | ✓ VERIFIED | `_BIN_TEMPLATES` has all 4 classes (AXI 5 coverpoints, FSM 4, DATAPATH 4, MEMORY 5). `_detect_active_templates()` activates subset by protocol/signal scan. case1 → AXI+DATAPATH = 9 coverpoints, all bins named with interpretable scenarios. |
| 8 | coverage_collect 按文件过滤排除 wrapper（cocotb_top/wrapper） (PLAN) | ✓ VERIFIED | `_WRAPPER_KEYWORDS = ("cocotb_top", "wrapper", "_top.v", "tb_top")` + `_is_wrapper()` filter at L73-77. Verified in code. |
| 9 | coverage_result.json composite.formula == "0.4 * line + 0.3 * branch + 0.3 * functional"（非 0.42/0.28/0.30）(PLAN) | ✓ VERIFIED | All 5 case outputs contain the exact formula string. report_gen.py L56 hardcodes it. |
| 10 | 三类覆盖率齐全 + 综合 C≥65%（保底档），冲 C≥85%（满分档）(ROADMAP Goal) | ✗ FAILED | Per-case C (num-seq=100): case1=79.09% case2=49.14% case3=57.10% case4=50.27% case5=43.52%. Only case1 ≥65%. Average 55.82%. 0/5 cases ≥85%. See gap #3. |

**Score:** 6/10 truths verified. 3 FAILED (SC#2 functional sampling universality, SC#5 dead-code wiring, ROADMAP goal C≥65%), 1 PARTIAL (SC#3 5000-seq execution).

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| `src/constraint_gen.py` | generate() writes constraints.json with seed/seq/tx_vars | ✓ VERIFIED | 97 lines, `generate(design_info, seed, num_seq, out_dir)` implemented, AXI/SRAM/valid-ready branches. Wired in run.py L90-92. |
| `src/coverage_gen.py` | generate_bins() + 4 template classes | ✓ VERIFIED | 131 lines, `_BIN_TEMPLATES` 4 classes, `_detect_active_templates()`, `generate_bins()` + `get_bin_dict()`. Wired in run.py L91-93 + skeleton_gen L80-84. |
| `src/coverage_collect.py` | collect() parses coverage.dat, filters wrapper, sums line/branch/func | ✓ VERIFIED | 293 lines, native coverage.dat parser (Phase 10 improvement) + LCOV fallback + wrapper filter + functional read. Wired in run.py L118-130. |
| `src/report_gen.py` | generate() writes coverage_result.json with 0.4/0.3/0.3 formula | ✓ VERIFIED | 66 lines, formula hardcoded correctly, composite computed. Wired in run.py L119,133. |
| `src/dead_code_analyzer.py` | analyze() identifies unreachable generate/if/parameter branches | ⚠️ ORPHANED | 144 lines, `analyze()` + DeadCodeInfo exist. BUT never imported by run.py; collect_cov() called without dead_code_info. Has if/else-block precision bug. Substantive but UNWIRED. |

### Key Link Verification

| From | To | Via | Status | Details |
|------|----|----|--------|---------|
| run.py stage 3 | constraint_gen.generate() | `gen_constraint(design_info, args.seed, args.num_seq, str(out_dir))` (L92) | ✓ WIRED | Writes constraints.json |
| run.py stage 3 | coverage_gen.generate_bins() | `gen_bins(design_info, str(out_dir))` (L93) | ✓ WIRED | Writes coverage_bins.json |
| run.py stage 5 | coverage_collect.collect() | `collect_cov(str(sim_tb_dir), design_info)` (L130) | ⚠️ PARTIAL | Called but dead_code_info argument omitted — dead-code filtering not wired |
| run.py stage 5 | report_gen.generate() | `gen_report(cov_data, sim_info, str(out_dir))` (L133) | ✓ WIRED | Writes coverage_result.json |
| skeleton_gen | coverage_gen.get_bin_dict() | `from src.coverage_gen import get_bin_dict; bin_dict = get_bin_dict(design_info)` (L81-82) | ✓ WIRED | Injected into template as `bin_dict` |
| skeleton_gen | functional_coverage.py copy | `shutil.copy2(fc_src, tb_dir / "functional_coverage.py")` (L100) | ✓ WIRED | Copied to generated_tb/ for testbench import |
| testbench | FunctionalCoverage.hit() | `coverage.hit("coverpoint","bin")` in template | ⚠️ PARTIAL | Real sampling only in AXI full-bus branch; placeholder modulo sampling elsewhere |
| coverage_collect | dead_code_analyzer | (should pass DeadCodeInfo to collect()) | ✗ NOT WIRED | run.py never imports dead_code_analyzer; collect() called with default dead_code_info=None |
| report_gen | 0.4/0.3/0.3 formula | `0.4 * line_pct + 0.3 * branch_pct + 0.3 * func_pct` (L27) | ✓ WIRED | Formula correct, no 0.42/0.28/0.30 |

### Data-Flow Trace (Level 4)

| Artifact | Data Variable | Source | Produces Real Data | Status |
|----------|---------------|--------|--------------------|----|
| coverage_result.json (case2) | line=88.24 branch=38.46 | coverage.dat via `_parse_native` | Yes — non-zero DA/BRDA counts from real Verilator instrumentation | ✓ FLOWING |
| coverage_result.json (case2) | functional=7.69 (2/26) | functional_coverage.json from cocotb | Partial — 2 bins hit but via placeholder modulo, not real DUT state sampling | ⚠️ STATIC (placeholder-driven) |
| constraints.json (case2) | seed=20260630 seq=100 | constraint_gen.generate() with --num-seq 100 | Yes — but seq=100 reflects the debug scale, not the 5000 contract | ⚠️ SCALE MISMATCH |

### Behavioral Spot-Checks

| Behavior | Command | Result | Status |
|----------|---------|--------|--------|
| report_gen formula 0.4/0.3/0.3 | `python -c "...generate(CoverageData(60,72,100)..."` | formula="0.4 * line + 0.3 * branch + 0.3 * functional", percent=75.6 | ✓ PASS |
| constraint_gen AXI case1 | `python -c "...generate(parse(case1),20260630,5000,..."` | seed=20260630, seq=5000, 8 tx_vars | ✓ PASS |
| coverage_gen case1 bins | `python -c "...generate_bins(parse(case1)..."` | 9 coverpoints (AXI+DATAPATH), all bins named | ✓ PASS |
| dead_code_analyzer case1 | `python -c "...analyze([case1.v],{S:32,M:16})..."` | unreachable=437 lines (L243-679 marked dead — includes active else-branch) | ✗ FAIL (precision bug confirmed) |
| Composite formula in all outputs | inspect 5 case coverage_result.json | All 5 contain "0.4 * line + 0.3 * branch + 0.3 * functional" | ✓ PASS |
| C≥65% goal per case | inspect 5 case composite.percent | case1=79.09 ≥65; case2-5 = 49.14/57.10/50.27/43.52 <65 | ✗ FAIL (4/5 below baseline) |

### Probe Execution

Step 7c SKIPPED — Phase 9 declares no `scripts/*/tests/probe-*.sh` probes, and the PLAN/SUMMARY do not reference probe-based verification. Acceptance `<verify>` commands are Python one-liners (spot-checked individually above), not shell probes.

### Requirements Coverage

| Requirement | Source Plan | Description | Status | Evidence |
|-------------|-------------|-------------|--------|----------|
| A2-RAND-01 | 09-01 | 固定 seed + 5000 序列的约束随机测试 | ⚠️ PARTIAL | seed=20260630 locked ✓, 5000-seq config emitted ✓, but all outputs ran at 100 seq (timeout deviation, never re-run at 5000). random.Random(seed) penetration ✓. |
| A2-RAND-02 | 09-01 | 覆盖率 bin 定义（coverpoint + bin + 场景映射） | ✓ SATISFIED | coverage_gen.py 4 template classes, interpretable bin names, design-adaptive activation. coverage_bins.json produced for all cases. |
| A2-RAND-03 | 09-01 | 功能覆盖率采样和报告 | ⚠️ PARTIAL | Framework present (FunctionalCoverage.hit/write, functional_coverage.json produced). Real sampling only for AXI full-bus (case1=100%); placeholder modulo sampling for case2-5 (0-8%). Reporting ✓. |
| A2-COV-01 | 09-01 | 行覆盖率 + 分支覆盖率收集 | ✓ SATISFIED | coverage.dat → native parse → line/branch percents produced for all 5 cases (non-zero). Wrapper filter implemented. |
| A2-COV-02 | 09-01 | 综合覆盖率 ≥85%（目标） | ✗ BLOCKED | 0/5 cases reach 85%. Best is case1=79.09%. Average 55.82%. Even the 65% baseline is met by only 1/5. |

### Anti-Patterns Found

| File | Line | Pattern | Severity | Impact |
|------|------|---------|----------|--------|
| templates/cocotb_tb.py.j2 | 214 | `# scoreboard 占位：valid-ready 接口的基本数据比对` | ⚠️ Warning | Non-AXI scoreboard is a placeholder — no actual output comparison for valid-ready/SRAM/AXIS interfaces |
| templates/cocotb_tb.py.j2 | 216 | `# 通用 bin hit（data_width/fifo 等模板 bin 的简化采样）` | ⚠️ Warning | Non-AXI bin sampling is "简化" (simplified) — modulo-based, not real transaction sampling |
| templates/cocotb_tb.py.j2 | 217-220 | `if index % 2 == 0: coverage.hit("data_width_boundary", "full_width")` | ⚠️ Warning | Deterministic modulo hit — always same 2 bins, independent of DUT state |

No TBD/FIXME/XXX debt markers in any Phase 9 file. The placeholders are documented inline (self-labeled "占位"/"简化"), not hidden debt.

### Human Verification Required

None beyond the gap closure items. The remaining items are concrete code/wiring gaps, not judgment calls. (If the team chooses to accept the non-AXI placeholder sampling as "good enough for the 4-template framework requirement" rather than real per-DUT sampling, that would be a judgment-tier override — suggested below.)

### Gaps Summary

**Three blocking gaps prevent Phase 9 from meeting its goal:**

1. **SC#5 dead-code analysis is not wired (BLOCKER).** `dead_code_analyzer.py` exists but is never imported by `run.py`, and `collect_cov()` is called without `dead_code_info`. The module also has a precision bug (marks the active else-branch as dead). This is the single biggest lever for raising line coverage on parameterized designs like case1. Phase 9 SUMMARY documented this as a conservative choice; Phase 10 was supposed to refine it but the wiring still isn't there in the current tree.

2. **SC#2 functional bin sampling is only real for AXI full-bus (case1).** case2-5 (valid-ready/SRAM/AXIS/slave-only-AXI) fall into a template branch with deterministic modulo placeholder sampling (`index % 2`, `index % 3`), always hitting the same 2 bins. This is why case2-5 functional coverage is 0-8% and their composite C sits at 43-57%, below the 65% baseline. The template self-labels this path as "占位"/"简化".

3. **ROADMAP goal C≥65% (baseline) is met by only 1/5 cases.** case1=79.09% is the only case above 65%. case2=49.14%, case3=57.10%, case4=50.27%, case5=43.52% are all below. Average 55.82%. 0/5 reach the 85% full-score band. This is at num-seq=100 (debug scale), not the required 5000 — though scaling to 5000 alone won't fix the placeholder-sampling and dead-code-wiring root causes.

**One partial gap:**

4. **SC#3 5000-sequence execution evidence is absent.** The infrastructure correctly emits seed=20260630 + sequence_count=5000 in constraints.json, but every smoke_out output shows run.sequence_count=100. The 5000-seq run was a documented timeout deviation; Phase 10 raised the timeout but never re-ran at 5000 to produce evidence. The config is right; the proof at scale is missing.

**What IS solidly delivered:** line/branch coverage instrumentation and parsing (SC#1), the 0.4/0.3/0.3 composite formula with no forbidden weights (SC#4), the 7-JSON output structure, the 4-template bin definition library, constraint generation with locked seed and directed boundary values, and the native coverage.dat parser (Phase 10 improvement that made coverage collection actually work offline).

---

**Suggested override (if the team accepts the non-AXI sampling as framework-complete):**

```yaml
overrides:

  - must_have: "功能 bin 真实事务采样 — 4 类模板普遍适用"
    reason: "AXI template has real transaction sampling; non-AXI uses simplified modulo sampling as Phase 9 framework scope. Real per-protocol sampling deferred."
    accepted_by: "<team>"
    accepted_at: "<ISO timestamp>"
```

Note: even with this override, gaps #1 (dead-code wiring), #3 (C≥65%), and #4 (5000-seq) remain blocking.

_Verified: 2026-07-14T23:45:00Z_
_Verifier: ZCode (gsd-verifier)_
