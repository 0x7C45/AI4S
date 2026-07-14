# Phase 6: A1 Advanced Features - Context

**Gathered:** 2026-07-14
**Status:** Ready for planning

<domain>
## Phase Boundary

Extend the Phase 5 flex/bison C++ RTL simulator from combinational execution to sequential RTL simulation and multi-file designs. The phase must target basic03, basic04, basic05, i2c, ip, axis_fifo, and sha256, including clocked logic, DFF/reset behavior, non-blocking assignment, preprocessing, memory initialization, and hierarchical multi-file module elaboration. Each completed testcase must pass from a clean build with zero output diff.

</domain>

<decisions>
## Implementation Decisions

### Timing and Scheduling
- **D-01:** Use a discrete simulation-time event queue. `#delay` advances simulation time, clock generators schedule future toggles, and posedge/negedge waits trigger only on actual signal transitions.
- **D-02:** Implement standard Active/NBA/delta semantics: execute active statements first, collect non-blocking assignments, commit all NBA updates at the same simulation time, then re-evaluate combinational logic until delta convergence.
- **D-03:** Support both synchronous reset conditions and asynchronous reset edges, including common forms such as `posedge clk or posedge rst` and `negedge rst`.
- **D-04:** End simulation when the event queue is exhausted, while honoring `$finish` as an immediate termination that flushes/ closes observable output state.

### Preprocessing, Memory, and System Functions
- **D-05:** Support common Verilog preprocessing: object-like macros, function-like macros, nested includes, and include recursion protection. The implementation should cover the existing `def.v` and `i2c` macro/include patterns without requiring a full SystemVerilog preprocessor.
- **D-06:** Resolve `` `include `` paths relative to the including source file. Resolve `$fopen`, `$readmemh`, and `$readmemb` paths relative to the testbench/runtime working directory, with absolute paths preserved.
- **D-07:** Support both `$readmemh` and `$readmemb`, including optional start/end address ranges, numeric token parsing, and writes into unpacked memory arrays.
- **D-08:** Implement `$time` as the current simulation time and keep `$display` formatting functional. Implement full VCD waveform output for `$dumpfile`/`$dumpvars` so waveform probes are observable and do not merely parse.

### Hierarchy and Data Model
- **D-09:** Collect all modules from all filelist sources before elaboration, then resolve parameter overrides, instantiate the hierarchy, connect ports by direction, and flatten/execute the resulting design.
- **D-10:** Preserve the Phase 5 AST and `uint64_t` scalar signal model where possible, extending it with packed vectors plus unpacked memory arrays. Support variable-index memory reads/writes from procedural and combinational logic.

### Test Strategy and Completion
- **D-11:** Prioritize basic03, basic04, and basic05 first because they validate the core sequential, preprocessing, and memory features. Then proceed to i2c, ip, axis_fifo, and sha256.
- **D-12:** A testcase is complete only after clean build, `compile_sim`, `run`, and exact `diff` against its reference output all pass. Partial output matching or merely non-crashing execution does not count as completion.

### Claude's Discretion
- Choose the concrete event-queue data structures, AST extensions, and internal ownership/lifetime strategy.
- Choose the exact VCD handling as long as `$dumpvars` does not break Phase 6 testcases and `$time` is correct.
- Choose implementation order within the stated priority and stop lower-priority work if the deadline requires preserving already-passing cases.

</decisions>

<canonical_refs>
## Canonical References

**Downstream agents MUST read these before planning or implementing.**

### Phase definition and requirements
- `.planning/ROADMAP.md` §Phase 6 — phase goal, requirements, and success criteria.
- `.planning/REQUIREMENTS.md` §A1 — parser, simulator, incremental, parallel, Makefile, and testcase requirements.
- `.planning/phases/05-a1-basic-simulator/05-01-SUMMARY.md` — locked Phase 5 architecture, decisions, known serialization limitation, and clean regression result.

### Existing simulator implementation
- `Track-A/A1-simulator/src/parser.y` — current AST grammar, non-blocking assignment node, event controls, module instances, and generated constructs.
- `Track-A/A1-simulator/src/lexer.l` — current tokenization and directive handling boundary.
- `Track-A/A1-simulator/src/sim_engine.cpp` — current compilation, hierarchy flattening, signal propagation, procedural execution, and delay handling.
- `Track-A/A1-simulator/src/eval_expr.cpp` — current expression, bit-select, concatenation, parameter, and `$clog2` evaluation.
- `Track-A/A1-simulator/src/sim_data.h` — current `ModuleDef`, `SignalDef`, and serialized simulation data model.
- `Track-A/A1-simulator/Makefile` — build, compile_sim, run, and parallel_run interface.

### Phase 6 reference testcases
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/tb.v` — first sequential target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic04/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic04/rtl/def.v` — include/macro and memory initialization target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic05/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic05/rtl/def.v` — sequential, memory, parameter, `$time`, and `$dumpvars` syntax target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/i2c/filelist.txt` and `Track-A/A1-simulator/testcases/sim_public/benchmark/i2c/rtl/i2c_master_defines.v` — multi-file hierarchy and include target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/ip/filelist.txt` — multi-file IP target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/axis_fifo/filelist.txt` — sequential FIFO target.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/sha256/filelist.txt` — multi-file sequential/hash target.

</canonical_refs>

<code_context>
## Existing Code Insights

### Reusable Assets
- Flex/bison parser and AST node model already cover modules, parameters, generate constructs, blocking/non-blocking assignment nodes, event controls, and system tasks.
- `propagateSignals()` already provides combinational fixed-point evaluation and can become the delta-cycle combinational phase after NBA commits.
- Existing filelist-relative source resolution and Makefile targets provide the Phase 6 command-line/test harness foundation.
- Existing `$fopen`, `$fscanf`, `$fgets`, `$fdisplay`, `$display`, `$finish`, and `$fclose` handling can be extended rather than replaced.

### Established Patterns
- Signal values are stored as `uint64_t`, with separate width and signedness maps.
- Module hierarchy is currently flattened with prefixed signal names; Phase 6 should preserve this observable naming pattern while making port direction and multi-file elaboration correct.
- AST node types map directly to Verilog constructs; new timing/preprocessor/memory behavior should follow the same mapping rather than introduce an unrelated frontend.
- Every testcase is validated through `compile_sim`, `run`, and exact output comparison.

### Integration Points
- Parser/lexer changes feed `ASTNode` trees consumed by `buildModule()`, hierarchy elaboration, and `SimulationEngine::run()`.
- `sim_data` is the compile/run handoff boundary, though the current in-memory `--run -f FILELIST --top TOP` path is the reliable execution path and its serialization limitation is documented.
- Testbench file I/O is relative to the testcase runtime directory; generated `tb/output.mem` remains the primary observable artifact.

</code_context>

<specifics>
## Specific Ideas

- The intended timing behavior is conventional Verilog-like discrete time, not the Phase 5 wait-driven clock approximation.
- The priority is explicit: finish basic03-05 before spending effort on i2c, ip, axis_fifo, and sha256.
- Full VCD support was considered but is not a Phase 6 acceptance requirement; `$dumpvars` must remain executable and `$time` must be meaningful.

</specifics>

<deferred>
## Deferred Ideas

- Full VCD waveform generation with `$dumpfile`/`$dumpvars` output is deferred unless a target testcase requires it.
- GEMM performance, incremental compilation, and multicore speedup remain Phase 7 scope.
- Broader SystemVerilog preprocessing beyond common Verilog macros/includes remains outside this phase.

</deferred>

---

*Phase: 6-A1 Advanced Features*
*Context gathered: 2026-07-14*
