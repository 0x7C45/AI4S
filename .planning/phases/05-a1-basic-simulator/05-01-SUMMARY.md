---
phase: 05-a1-basic-simulator
plan: 01
subsystem: simulator
tags: [flex, bison, verilog, rtl, event-driven, simulation]

requires: []
provides:
  - Working flex/bison Verilog parser
  - C++ event-driven simulation engine
  - Signed arithmetic right shift support
  - Makefile with build/compile_sim/run targets
  - basic01, basic02, alu test cases passing
affects: [06-a1-advanced-features]

tech-stack:
  added: [flex, bison, g++]
  patterns: [AST-based parser, event-driven scheduling, signal propagation]

key-files:
  created:
    - Track-A/A1-simulator/src/lexer.l
    - Track-A/A1-simulator/src/parser.y
    - Track-A/A1-simulator/src/ast.h
    - Track-A/A1-simulator/src/eval_expr.cpp
    - Track-A/A1-simulator/src/sim_engine.cpp
    - Track-A/A1-simulator/src/system_funcs.cpp
    - Track-A/A1-simulator/src/sim_data.cpp
    - Track-A/A1-simulator/src/main.cpp
    - Track-A/A1-simulator/Makefile
  modified: []

key-decisions:
  - "Used uint64_t for all signal values (max 32-bit in Phase 5 test cases)"
  - "Signedness tracked via SignalSigned map for >>> operator"
  - "Compile_sim writes binary data; run mode uses --run for in-memory execution"
  - "Filelist paths resolved relative to filelist directory"

patterns-established:
  - "AST node types map directly to Verilog constructs"
  - "Signal propagation loop (max 200 iterations) for combinational convergence"
  - "Module flattening with prefix-based signal renaming"

requirements-completed:
  - A1-PARSE-01
  - A1-PARSE-02
  - A1-PARSE-03
  - A1-PARSE-04
  - A1-PARSE-05
  - A1-PARSE-06
  - A1-SIM-01
  - A1-MK-01
  - A1-MK-03
  - A1-CASE-01
  - A1-CASE-02
  - A1-CASE-03

coverage:
  - id: D1
    description: "Simulator binary compiles and runs"
    verification:
      - kind: integration
        ref: "make build && test -f simulator"
        status: pass
    human_judgment: false
  - id: D2
    description: "basic01 output matches reference"
    verification:
      - kind: integration
        ref: "diff -u tb/output_ref.mem tb/output.mem (basic01)"
        status: pass
    human_judgment: false
  - id: D3
    description: "basic02 output matches reference"
    verification:
      - kind: integration
        ref: "diff -u tb/output_ref.mem tb/output.mem (basic02)"
        status: pass
    human_judgment: false
  - id: D4
    description: "alu output matches reference"
    verification:
      - kind: integration
        ref: "diff -u tb/output_ref.mem tb/output.mem (alu)"
        status: pass
    human_judgment: false
  - id: D5
    description: "priority_encoder output matches reference"
    verification:
      - kind: integration
        ref: "diff -u tb/output_ref.mem tb/output.mem (priority_encoder)"
        status: fail
    human_judgment: false
    rationale: "Needs generate block elaboration, multi-dimensional wires, double bit-select"

duration: 120min
completed: 2026-07-14
status: partial
---

# Phase 5: A1 Basic Simulator Summary

**flex/bison Verilog parser + C++ event-driven simulation engine — basic01/basic02/alu pass (6 points)**

## Accomplishments
- Built flex/bison parser handling module/endmodule, assign, always @(*), initial, reg/wire/integer, if-else/case/for, parameter, concatenation, bit select, ternary, module instantiation
- Implemented C++ event-driven simulation engine with signal propagation loop (max 200 iterations)
- Fixed signed arithmetic right shift (>>>) with proper int32_t sign extension
- Added parser support for module #(params), output wire, ** operator, {N{}} replication
- Makefile with build/compile_sim/run/parallel_run targets
- basic01 (2pts), basic02 (2pts), alu (2pts) all pass with zero diff

## Task Commits

1. **Task 1: Scaffolding** - `4881efd` (feat)
2. **Task 2-3: Parser + Engine** - `bd17d8b` (feat: working simulator)
3. **Task 3 continued: Signed fix** - `30ec573` (feat: parser improvements)

## Deviations from Plan

### Auto-fixed Issues

**1. Makefile CWD issue — compile_sim/run need absolute paths**
- **Found during:** Task 2 (basic01 testing)
- **Issue:** `make -C` changes CWD, breaking relative filelist.txt paths
- **Fix:** Added SIM_DIR-based absolute paths, filelist path resolution in compile()
- **Files modified:** Makefile, sim_engine.cpp

**2. Signed right shift sign extension bug**
- **Found during:** Task 3 (alu testing)
- **Issue:** `~trunc(32, 0)` = `~0` = all 1s, not the sign-extension mask
- **Fix:** Used int32_t cast for proper sign extension
- **Files modified:** eval_expr.cpp

---

**Total deviations:** 2 auto-fixed
**Impact:** Both critical for correctness. No scope creep.

## Issues Encountered
- priority_encoder needs generate block elaboration, multi-dimensional wires, variable part-selects — deferred to Phase 6
- sim.out binary serialization has segfault on load — bypassed with --run mode

## Next Phase Readiness
- Parser infrastructure ready for Phase 6 extensions
- Generate block support needed before priority_encoder can pass
- Sequential logic (posedge clk, DFF, <=) needed for basic03-05 and i2c/ip/axis_fifo/sha256

---
*Phase: 05-a1-basic-simulator*
*Completed: 2026-07-14*
