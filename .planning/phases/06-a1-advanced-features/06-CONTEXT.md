# Phase 6: A1 Advanced Features - Context

**Gathered:** 2026-07-15
**Status:** Ready for replanning

<domain>
## Phase Boundary

快速完成 A1 RTL 仿真器的最小时序扩展，优先让 basic03、basic04、basic05 从 clean build 到 `compile_sim`、`run`、精确 `diff` 全部通过，并回归 Phase 5 的 basic01、basic02、alu、priority_encoder。只实现这三个目标用例实际需要的时序、预处理、内存、层次和系统任务语义；不在本阶段追求其余高级公开用例或性能能力。

</domain>

<decisions>
## Implementation Decisions

### Scope and Priority
- **D-01:** 本阶段只把 basic03、basic04、basic05 作为 Phase 6 功能目标；i2c、ip、axis_fifo、sha256 不阻塞本阶段完成，延期到后续阶段。
- **D-02:** 每个目标用例必须从 clean build 开始，运行 `compile_sim`、无参数 `run`，并对 `tb/output.mem` 与 `tb/output_ref.mem` 执行精确 `diff -u`。
- **D-03:** Phase 5 的 basic01、basic02、alu、priority_encoder 必须在修改后继续通过精确零差异回归。

### Minimal Sequential Semantics
- **D-04:** 采用实现 basic03/basic05 所需的最小离散时间调度：支持 `always @(posedge clk)`、实际时钟翻转、`@(posedge clk)` 等待和 `#delay` 事件。
- **D-05:** 支持非阻塞赋值的基本 NBA 行为：同一时刻先执行 active 语句，再提交 NBA 更新，然后重新传播组合逻辑；不为未覆盖的 Verilog 语义扩展复杂调度器。
- **D-06:** 支持 basic03/basic05 中的同步复位条件和寄存器保持/更新行为；异步复位、复杂多边沿敏感列表仅在不增加回归风险时实现，不作为本阶段验收门槛。

### Required Preprocessing, Memory, and System Tasks
- **D-07:** 支持 basic04/basic05 所需的对象宏、`include`（相对包含文件目录解析）和已存在的 `def.v` 形式；完整 SystemVerilog 预处理延期。
- **D-08:** 支持 `$readmemh`，并保留 `$readmemb` 的最小兼容入口；支持 basic04/basic05 使用的 unpacked memory、变量索引和初始化文件路径。
- **D-09:** 支持 `$time` 的当前仿真时间、现有 `$fopen`/`$fgets`/`$fscanf`/`$fdisplay`/`$display`/`$finish` 路径；`$dumpvars` 只要求可执行且不使 basic05 崩溃，不要求完整 VCD 波形文件。

### Hierarchy and Data Model
- **D-10:** 保留 Phase 5 的 AST、`uint64_t` 信号值、前缀扁平化命名和现有组合传播模式；只补 basic04/basic05 所需的参数化子模块、端口连接、generate 和 memory metadata。
- **D-11:** 多文件全局模块收集和通用层次 elaboration 不是本阶段目标；只保证 basic04/basic05 的实际 filelist、include 和两个 `add_leaf`/`basic05_leaf` 子模块路径可运行。

### Claude's Discretion
- 事件队列的具体容器、NBA 暂存结构和时钟生成实现。
- 是否以最小 no-op 方式记录 `$dumpvars`，只要 `$time` 和 basic05 输出正确。
- basic03/basic04/basic05 的实现顺序；建议 basic03 → basic04 → basic05，每完成一个即运行精确 diff。

</decisions>

<canonical_refs>
## Canonical References

**Downstream agents MUST read these before planning or implementing.**

### Phase definition and prior implementation
- `.planning/ROADMAP.md` §Phase 6 — original phase goal and requirement mapping; this context narrows the immediate acceptance gate.
- `.planning/REQUIREMENTS.md` §A1 — simulator requirements and public testcase definitions.
- `.planning/phases/05-a1-basic-simulator/05-01-SUMMARY.md` — Phase 5 architecture and four-case zero-diff baseline.
- `.planning/phases/06-a1-advanced-features/06-01-SUMMARY.md` — completed frontend/preprocessor/AST work already on the main branch.

### Target testcases
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/tb.v` — posedge clock, NBA register, generate, parameterized leaf.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic04/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic04/rtl/def.v` — include, macro, readmemh, unpacked memory, combinational selection.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic05/rtl/dut.v` and `Track-A/A1-simulator/testcases/sim_public/benchmark/basic05/rtl/def.v` — include, memory, parameterized hierarchy, sequential q, `$time`, `$dumpvars`.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic03/tb/output_ref.mem` — exact expected sequential output.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic04/tb/output_ref.mem` — exact expected memory output.
- `Track-A/A1-simulator/testcases/sim_public/benchmark/basic05/tb/output_ref.mem` — exact expected sequential/memory output.

### Existing implementation
- `Track-A/A1-simulator/src/sim_engine.cpp` — current runtime, signal propagation, hierarchy and delay handling.
- `Track-A/A1-simulator/src/eval_expr.cpp` — current expression, bit-select, concat and parameter evaluation.
- `Track-A/A1-simulator/src/system_funcs.cpp` — current file I/O and system task implementations.
- `Track-A/A1-simulator/src/ast.h` — current AST nodes after Phase 6 frontend expansion.
- `Track-A/A1-simulator/Makefile` — build, compile_sim and run contract.

</canonical_refs>

<code_context>
## Existing Code Insights

### Reusable Assets
- `propagateSignals()` already computes combinational fixed points and should remain the post-NBA propagation path.
- Existing system function handlers already cover most testbench file I/O and should be extended narrowly.
- The Phase 6 frontend commits already add preprocessing, event/function/system-task tokens, and serialized metadata; Wave 2 should consume those interfaces rather than replace them.

### Established Patterns
- Signals are stored as `uint64_t` with width/signedness maps.
- Hierarchy is flattened with prefixed signal names.
- AST node types map directly to Verilog constructs.
- Testcases are validated through testcase-relative `compile_sim`, argument-free `run`, and exact output diff.

### Integration Points
- `parser.y`/`lexer.l` feed ASTs consumed by `SimulationEngine::run()`.
- `sim_engine.cpp` owns scheduling, initial/always execution, signal propagation and module elaboration.
- `eval_expr.cpp` handles memory indexing and parameter expressions.
- `system_funcs.cpp` handles `$time`, `$readmemh`, file I/O and `$dumpvars` compatibility.

</code_context>

<specifics>
## Specific Ideas

- Time is critical: prefer a small, test-driven implementation over a general Verilog simulator.
- Run the exact diff after each target case; do not wait until the end to discover a scheduler mismatch.
- Preserve the already passing Phase 5 cases at every meaningful runtime change.

</specifics>

<deferred>
## Deferred Ideas

- i2c, ip, axis_fifo and sha256 full functional support — later A1 advanced phase.
- Full VCD generation for `$dumpfile`/`$dumpvars` — not needed for basic03-05.
- Complete asynchronous reset and arbitrary multi-edge sensitivity semantics — later hardening.
- Incremental compilation, GEMM, multicore simulation and performance tuning — Phase 7.
- Full Phase 6 four-wave plan and its broad exact-diff matrix — replaced by this short critical-path plan.

</deferred>

---

*Phase: 6-a1-advanced-features*
*Context gathered: 2026-07-15*
