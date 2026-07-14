# Milestone Summary: A1 Phase 5 — Basic Simulator

**Version:** 5 (Basic Simulator)
**Date:** 2026-07-13
**Status:** Partially Complete (2/4 test cases passing)

---

## 1. Overview

Phase 5 implements a lightweight Verilog RTL simulator using flex/bison for parsing and a C++ event-driven simulation engine. The simulator reads Verilog source files, compiles them into an internal representation, and executes testbench-driven simulations producing output files that can be diffed against reference outputs.

**Test Results:**
| Test Case | Status | Notes |
|-----------|--------|-------|
| basic01 | ✅ PASS | Combinational assign logic |
| basic02 | ✅ PASS | `always @(*)` with `case`, `for` loop |
| alu | ❌ 1/40 mismatch | Signed arithmetic right shift (`>>>`) issue |
| priority_encoder | ❌ Parse error | Parameterized modules `#(parameter ...)` unsupported |

---

## 2. Architecture

```
flex lexer.l → lexer.yy.c
bison parser.y → parser.tab.c/h
                 ↓
           AST (ASTNode tree)
                 ↓
         buildModule() → ModuleDef (signals, items)
                 ↓
         flattenModule() → flat items with port connections
                 ↓
         writeModuleDefs() → binary serialization → sim.out
                 ↓
         readModuleDefs() → reconstruct AST
                 ↓
         execItem() / propagateSignals() → simulation
                 ↓
         output.mem (via $fopen/$fdisplay)
```

**Key components:**
- `src/lexer.l` — Flex lexer for Verilog-2001 tokens
- `src/parser.y` — Bison grammar (~66 shift/reduce conflicts, 0 reduce/reduce)
- `src/ast.h/cpp` — AST node types and tree operations
- `src/eval_expr.cpp` — Expression evaluator (BINOP, UNOP, TERNARY, CONCAT, BITSEL, $clog2)
- `src/sim_engine.cpp` — Compile + run engine (flattening, propagation, execution)
- `src/sim_data.cpp` — Binary serialization of ModuleDef + AST
- `src/main.cpp` — CLI: `--compile`, `--run`, `--sim`

---

## 3. Phases Completed

### Phase 5.1: Parser (flex/bison)
- Full Verilog-2001 lexer with keywords, operators, sized number literals
- Bison grammar supporting: modules, ports, wire/reg/integer declarations, assign, always/initial blocks, if/case/for, module instantiation, generate blocks, system tasks ($fopen, $fscanf, $fgets, $fdisplay, $display, $finish, $clog2)
- **Critical fix:** Flex's `#define INITIAL 0` (start condition macro) conflicted with bison token `INITIAL=273`. Renamed to `INITIAL_KW`.

### Phase 5.2: AST & Expression Evaluator
- 32 node types covering all parsed constructs
- `evalExpr()` returns `{value, width}` pair for proper truncation
- Handles sized/unsized number literals, signal lookups, all arithmetic/logic/comparison operators

### Phase 5.3: Simulation Engine
- **Compile phase:** Parse → buildModule → flatten hierarchy → serialize to binary
- **Run phase:** Load binary → setup signals → execute initial/always blocks → propagate assignments
- **Port connection flattening:** Bidirectional `ASSIGN` nodes for each port connection
- **Signal propagation:** Iterative convergence loop (up to 200 iterations) with always block re-execution

### Phase 5.4: Test Case Verification
- basic01: Pure combinational logic with `$fopen`/`$fscanf`/`$fdisplay` I/O
- basic02: `always @(*)` with `for` loop and `case` statement

---

## 4. Key Decisions

| Decision | Rationale |
|----------|-----------|
| **flex/bison over hand-written parser** | Competition time constraint; handles complex Verilog grammar |
| **Binary serialization for compile→run** | Supports separate `make compile_sim` and `make run` steps per spec |
| **In-memory pass-through** | `compiledModules` member allows `--run` mode to skip binary roundtrip |
| **Iterative propagation with always blocks** | Handles combinational feedback loops (basic02's `always @(*)`) |
| **Re-entrancy guard on propagateSignals** | Prevents infinite recursion when always blocks trigger propagation |
| **`--sim PATH` argument** | Solves CWD issue (simulator reads sim.out from CWD) |

---

## 5. Requirements Status

| Requirement | Status | Evidence |
|-------------|--------|----------|
| `make build` produces simulator binary | ✅ | flex → bison → g++ -O2 |
| `make compile_sim FILELIST=f TOP=t` | ✅ | Produces sim.out binary |
| `make run` executes simulation | ✅ | Reads sim.out, writes output.mem |
| basic01 `diff output.mem output_ref.mem` | ✅ | Exact match |
| basic02 `diff output.mem output_ref.mem` | ✅ | Exact match |
| alu exact match | ❌ | 1/40 lines differ (signed `>>>`) |
| priority_encoder exact match | ❌ | Parse error on parameterized modules |

---

## 6. Technical Debt & Known Issues

### Bugs to Fix
1. **Signed arithmetic right shift (`>>>`)** — alu DUT uses `signed_a >>> b[4:0]` but evaluator treats all values as unsigned. Need to check `is_signed` flag and sign-extend before shifting.
2. **Parameterized modules** — priority_encoder uses `module name #(parameter ...) (ports)` syntax. Parser needs `module_header` rule with parameter list.
3. **Serializer child index bug** — `std::find` returns `flat.end()` for children not in flat vector, writing index 0 as fallback. Works around with in-memory pass-through but needs proper fix for standalone compile→run.

### Architecture Concerns
- **Global state** (`g_assignItems`, `g_alwaysBlocks`) — coupling between propagateSignals and execItem
- **No `always @(posedge clk)` support** — only combinational (`always @(*)`) works
- **No generate block runtime expansion** — parser handles generate but compile may not expand correctly
- **66 shift/reduce conflicts** — bison defaults work but may cause incorrect parses in edge cases

### Missing Features (not needed for Phase 5 tests)
- `casez`/`casex` (wildcard matching)
- `wire` concatenation on LHS of assign
- Multi-dimensional arrays
- Task/function definitions
- `defparam` overrides

---

## 7. Getting Started

```bash
# Build the simulator
cd Track-A/A1-simulator
make build

# Run basic01 (combined compile+run)
cd testcases/sim_public/benchmark/basic01
/path/to/simulator --run -f filelist.txt --top tb
diff -u tb/output_ref.mem tb/output.mem

# Or use separate compile and run
/path/to/simulator --compile -f filelist.txt --top tb -o sim.out
/path/to/simulator --sim sim.out
diff -u tb/output_ref.mem tb/output.mem

# Run all passing tests
for tc in basic01 basic02; do
  cd testcases/sim_public/benchmark/$tc
  ../../../simulator --run -f filelist.txt --top tb
  diff tb/output_ref.mem tb/output.mem && echo "$tc PASS" || echo "$tc FAIL"
  cd -
done
```

---

*Generated: 2026-07-13 by Claude Code*
