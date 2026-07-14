---
quick_task: 260715-aqi-basic03
slug: aqi-basic03
created: 2026-07-15
status: planned
phase: quick-260715-aqi-basic03
plan: 01
type: execute
wave: 1
depends_on: []
autonomous: true
files_modified:
  - Track-A/A1-simulator/src/sim_engine.cpp
  - Track-A/A1-simulator/src/sim_engine.h
  - Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/output.mem
must_haves:
  truths:
    - "basic03 argument-free make run terminates within 30 seconds and generates tb/output.mem."
    - "basic03 tb/output.mem exactly matches tb/output_ref.mem."
    - "basic01 remains a cheap exact-diff smoke regression when its fixture is available."
  artifacts:
    - path: "Track-A/A1-simulator/src/sim_engine.cpp"
      provides: "Terminating basic03 event scheduling, edge-wait, delay, NBA, and finish execution path."
  key_links:
    - from: "basic03 tb @(posedge clk), #1, and $finish"
      to: "SimulationEngine::run()"
      via: "bounded time-advancing scheduler and process termination state"
---

<objective>
Restore the basic03 critical path within the remaining half hour: identify why the current runtime never reaches output/diff, repair only the nonterminating scheduler, $finish, delay, or edge-wait behavior, and prove the testcase passes its reference comparison.

Purpose: basic03 is blocked after successful build and compile_sim because the runtime hangs before producing observable output. Scope is strictly this case and its shared scheduler path; basic04/basic05 and broader Phase 6 features are excluded.
Output: A targeted `sim_engine` fix and reproducible timeout-bounded basic03 zero-diff evidence.
</objective>

<execution_context>
@$HOME/.claude/gsd-core/workflows/execute-plan.md
@$HOME/.claude/gsd-core/templates/summary.md
</execution_context>

<context>
@.claude/CLAUDE.md
@.planning/STATE.md
@.planning/phases/06-a1-advanced-features/06-CONTEXT.md
@.planning/phases/06-a1-advanced-features/06-02-PLAN.md
@Track-A/A1-simulator/Makefile
@Track-A/A1-simulator/src/sim_engine.h
@Track-A/A1-simulator/src/sim_engine.cpp
@Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/filelist.txt
@Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/rtl/dut.v
@Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/tb.v
@Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/input.mem
@Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/output_ref.mem
</context>

<tasks>

<task type="auto" tdd="true">
  <name>Task 1: Reproduce and localize the basic03 runtime stall</name>
  <files>Track-A/A1-simulator/src/sim_engine.cpp, Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/output.mem</files>
  <behavior>
    - A clean build and `compile_sim` succeed from the basic03 CASE_DIR.
    - `timeout 30s make -f "$SIM/Makefile" run FILELIST=filelist.txt TOP=tb` returns rather than hanging.
    - The diagnostic establishes whether progress stops in repeated combinational propagation/always execution, edge-wait resumption, delay advancement, NBA handling, or before `$finish`.
  </behavior>
  <action>From `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03`, reproduce the reported hang using the Makefile contract with `timeout 30s`; remove `tb/output.mem` before each run so stale output cannot mask the result. Inspect only the live execution path in `SimulationEngine::run`, `propagateSignals`, `execItem`, and `execBlock` against basic03's `always #5 clk = ~clk`, `@(posedge clk)`, `#1`, posedge sequential block, and `$finish`. Add temporary, bounded diagnostic observations only if needed to identify a non-advancing loop or recursive re-entry; remove them before completion. Record the exact failing control-flow condition in the implementation work, then use it to choose the smallest repair in Task 2. Do not introduce basic04/basic05 behavior or change testcase/reference inputs.</action>
  <verify>
    <automated>set -euo pipefail; ROOT=/home/kali/Documents/github/AI4S; SIM="$ROOT/Track-A/A1-simulator"; CASE_DIR="$SIM/testcases/sim_public/benchmark/basic03"; make -C "$SIM" build; cd "$CASE_DIR"; make -f "$SIM/Makefile" compile_sim FILELIST=filelist.txt TOP=tb; rm -f tb/output.mem; timeout 30s make -f "$SIM/Makefile" run FILELIST=filelist.txt TOP=tb; test -f tb/output.mem</automated>
  </verify>
  <done>The executor can name the runtime loop or blocked continuation causing the stall, and the exact CASE_DIR command is preserved as the post-fix gate.</done>
</task>

<task type="auto" tdd="true">
  <name>Task 2: Repair the terminating basic03 scheduler path and prove exact output</name>
  <files>Track-A/A1-simulator/src/sim_engine.cpp, Track-A/A1-simulator/src/sim_engine.h, Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/output.mem</files>
  <behavior>
    - Clock transitions cause the `always @(posedge clk)` block to run once per rising transition rather than recursively from combinational propagation.
    - The testbench's edge wait and one-tick delay make finite progress, then `$finish` stops further execution.
    - The sequential register observes the required NBA ordering for basic03 and output has 33 lines matching the reference byte-for-byte.
  </behavior>
  <action>Implement the smallest correction in the shared scheduler/interpreter path identified by Task 1. Per D-02, D-04, D-05, and D-06, preserve the required basic03 semantics: actual rising clock transitions for the testbench wait, finite delay advancement, one execution of the synchronous posedge process per detected edge, basic nonblocking assignment behavior for `q`, post-update combinational propagation, and `$finish` termination. In particular, prevent `propagateSignals` from repeatedly or recursively executing edge-triggered always blocks without a qualifying signal transition, and replace any invalid NONBLOCKING_ASSIGN dispatch with a real bounded update path. Keep existing blocking assignments and file-I/O behavior intact. Do not expand scope beyond the basic03 scheduler/$finish/delay/edge-wait runtime. Rebuild, run from CASE_DIR under 30 seconds, require the generated output file, and require an exact reference diff. Run basic01 only as a smoke regression when its compile/run/diff completes cheaply under the same Makefile interface.</action>
  <verify>
    <automated>set -euo pipefail; ROOT=/home/kali/Documents/github/AI4S; SIM="$ROOT/Track-A/A1-simulator"; CASE_DIR="$SIM/testcases/sim_public/benchmark/basic03"; make -C "$SIM" clean; make -C "$SIM" build; cd "$CASE_DIR"; make -f "$SIM/Makefile" compile_sim FILELIST=filelist.txt TOP=tb; rm -f tb/output.mem; timeout 30s make -f "$SIM/Makefile" run FILELIST=filelist.txt TOP=tb; test -f tb/output.mem; diff -u tb/output_ref.mem tb/output.mem</automated>
  </verify>
  <done>From the basic03 CASE_DIR, the timeout-bounded no-argument run exits successfully, produces `tb/output.mem`, and `diff -u tb/output_ref.mem tb/output.mem` exits 0. A cheap basic01 smoke diff is retained if runnable without delaying the critical path.</done>
</task>

</tasks>

<threat_model>
## Trust Boundaries

| Boundary | Description |
|----------|-------------|
| basic03 RTL/testbench to scheduler | Delay, edge-wait, and finish constructs drive runtime control flow. |
| scheduler to generated output | Non-advancing events or recursive propagation can prevent output completion. |

## STRIDE Threat Register

| Threat ID | Category | Component | Severity | Disposition | Mitigation Plan |
|-----------|----------|-----------|----------|-------------|-----------------|
| T-quick-01 | Denial of Service | `sim_engine.cpp` event/propagation path | high | mitigate | Reproduce under a 30-second timeout, eliminate non-advancing or recursive execution, and make finish/queue exhaustion terminate deterministically. |
| T-quick-02 | Tampering | generated output acceptance evidence | medium | mitigate | Remove `tb/output.mem` before each run and compare only newly generated output with `diff -u`. |
</threat_model>

<verification>
Primary gate: from `basic03` CASE_DIR, clean-build the simulator, invoke `compile_sim`, remove `tb/output.mem`, invoke the argument-free `run` target under `timeout 30s`, verify output creation, then run `diff -u tb/output_ref.mem tb/output.mem`. Preserve a basic01 exact-diff smoke check only when it remains inexpensive.
</verification>

<success_criteria>
1. basic03 no longer hangs and completes the exact timeout-bounded command in at most 30 seconds.
2. basic03 generates a fresh `tb/output.mem` whose exact diff against `tb/output_ref.mem` is empty.
3. The repair is limited to the shared scheduler/$finish/delay/edge-wait/NBA execution path and excludes basic04/basic05 and unrelated cases.
</success_criteria>

<output>
Create `.planning/quick/260715-aqi-basic03/SUMMARY.md` when execution is complete.
</output>
