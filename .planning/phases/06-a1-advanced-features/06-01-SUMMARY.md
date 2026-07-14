---
phase: 06-a1-advanced-features
plan: 01
subsystem: simulator-frontend
tags: [flex, bison, verilog, preprocessing, ast, parser]

requires:
  - phase: 05-a1-basic-simulator
    provides: Phase 5 flex/bison grammar, AST, and simulator build path
provides:
  - Recursive preprocessing and serialized AST/data contracts from the inherited Task 1-2 commits
  - Phase 6 lexer and grammar coverage for sequential RTL, memories, functions, ports, system tasks, and indexed selects
  - Cleanly regenerated flex/bison sources with truthful parser failure propagation
affects: [06-a1-advanced-features, A1 parser and elaboration consumers]

tech-stack:
  added: []
  patterns: [tool-generated flex/bison artifacts, AST-preserving grammar extensions, source-mapped parser diagnostics]

key-files:
  created:
    - Track-A/A1-simulator/src/preprocessor.h
    - Track-A/A1-simulator/src/preprocessor.cpp
  modified:
    - Track-A/A1-simulator/src/lexer.l
    - Track-A/A1-simulator/src/parser.y
    - Track-A/A1-simulator/src/lexer.yy.c
    - Track-A/A1-simulator/src/parser.tab.c
    - Track-A/A1-simulator/src/parser.tab.h
    - Track-A/A1-simulator/src/ast.h
    - Track-A/A1-simulator/src/ast.cpp
    - Track-A/A1-simulator/src/sim_data.h
    - Track-A/A1-simulator/src/sim_data.cpp
    - Track-A/A1-simulator/src/sim_engine.cpp

key-decisions:
  - "Kept Phase 5 module-port productions intact after a broader ANSI declaration attempt introduced reduce/reduce ambiguity."
  - "Represented memories, functions, procedural declarations, event controls, and indexed part-select direction explicitly in AST nodes."
  - "Regenerated lexer.yy.c, parser.tab.c, and parser.tab.h exclusively through the Makefile flex/bison rules."
  - "Made parser errors fail compile commands through the shared g_parse_ok handoff."

patterns-established:
  - "Parser source locations resolve through PreprocessResult records for diagnostics."
  - "System tasks and function calls are retained as AST nodes even when runtime execution is deferred."

requirements-completed:
  - A1-PARSE-07

coverage:
  - id: D1
    description: "Recursive preprocessing and serialized frontend contracts remain buildable and feed nested include sources into parsing."
    requirement: A1-PARSE-07
    verification:
      - kind: integration
        ref: "make -C Track-A/A1-simulator build"
        status: pass
      - kind: integration
        ref: "simulator --compile basic04 filelist.txt --top tb"
        status: pass
      - kind: integration
        ref: "simulator --compile i2c filelist.txt --top tb"
        status: pass
    human_judgment: true
    rationale: "The build and nested-include compile paths pass, but no standalone automated assertion inspects every dependency-graph record."
  - id: D2
    description: "AST and serialized metadata expose event, function, procedural, memory, port, source, and indexed-select fields."
    requirement: A1-PARSE-07
    verification:
      - kind: other
        ref: "rg metadata contract fields in ast.h, sim_data.h, and sim_data.cpp"
        status: pass
      - kind: integration
        ref: "make -C Track-A/A1-simulator build"
        status: pass
    human_judgment: true
    rationale: "Field presence and compilation are automated; a dedicated binary round-trip assertion for every new field was not added in this plan."
  - id: D3
    description: "Regenerated grammar parses basic03, basic04, basic05, i2c, sha256, and all Phase 5 parser regression cases."
    requirement: A1-PARSE-07
    verification:
      - kind: integration
        ref: "clean flex/bison regeneration followed by make build"
        status: pass
      - kind: integration
        ref: "parser compile checks: basic03, basic04, basic05"
        status: pass
      - kind: integration
        ref: "parser compile checks: i2c, sha256, basic01, basic02, alu, priority_encoder"
        status: pass
    human_judgment: false

# Metrics
duration: 79min
completed: 2026-07-15
status: complete
---

# Phase 6 Plan 1: Frontend Contracts and Grammar Summary

**Recursive preprocessing, AST metadata, and regenerated flex/bison grammar now parse the required Phase 6 RTL vocabulary while preserving Phase 5 cases.**

## Performance

- **Duration:** 79 min
- **Started:** 2026-07-15T00:48:02+08:00
- **Completed:** 2026-07-15T02:07:14+08:00
- **Tasks:** 3/3 complete
- **Files modified or created across plan commits:** 14 source/generated frontend files

## Accomplishments

- Carried the committed preprocessing boundary and AST/serialized metadata contracts into this isolated worktree and validated their build and nested-include paths.
- Extended lexer/parser coverage for multiple edge events, memories, named blocks, generate case/if forms, function declarations and calls, procedural declarations, positional and named ports, `$readmemh`/`$readmemb`, `$dumpfile`/`$dumpvars`, `$error`, `$unsigned`, `$time`, and `+:`/`-:` selects.
- Regenerated `lexer.yy.c`, `parser.tab.c`, and `parser.tab.h` from source after an explicit clean removal and verified the clean `make build` path.
- Added parser failure propagation so syntax errors return nonzero from `--compile` instead of producing false-success artifacts.
- Preserved Phase 5 parser behavior: basic01, basic02, alu, and priority_encoder all compile successfully after regeneration.

## Task Commits

1. **Task 1: Add recursive preprocessing and dependency contracts** - `a53d2da` (feat; cherry-picked committed source change)
2. **Task 2: Extend AST and serialized simulation metadata** - `c1ef067` (feat; cherry-picked committed source change)
3. **Task 3: Expand flex/bison grammar for Phase 6 RTL** - `6ba2557` (feat)

No plan metadata commit was created yet; this summary is intentionally committed separately below. Shared `STATE.md` and `ROADMAP.md` were not modified in this isolated worktree per the execution request.

## Files Created/Modified

- `Track-A/A1-simulator/src/preprocessor.h` and `preprocessor.cpp` - recursive include/macro preprocessing contracts and implementation.
- `Track-A/A1-simulator/src/ast.h` and `ast.cpp` - explicit event, function, procedural, memory, source, and indexed-select AST fields.
- `Track-A/A1-simulator/src/sim_data.h` and `sim_data.cpp` - versioned serialized module, signal, memory, dependency, and AST metadata.
- `Track-A/A1-simulator/src/lexer.l` - Phase 6 keyword, system-task, attribute, and indexed-select tokens.
- `Track-A/A1-simulator/src/parser.y` - Phase 6 grammar and source-mapped parser diagnostics.
- `Track-A/A1-simulator/src/lexer.yy.c`, `parser.tab.c`, and `parser.tab.h` - generated only by flex/bison tooling.
- `Track-A/A1-simulator/src/sim_engine.cpp` - compile-time parser failure propagation.

## Decisions Made

- Kept the established Phase 5 module-port grammar after testing showed that adding a generalized declaration-list form caused broad ambiguity and regressions.
- Accepted bison conflict warnings as an existing/permissive grammar characteristic while requiring clean generation and passing testcase compile checks.
- Did not modify shared planning state because this executor is operating in an isolated worktree and the request explicitly prohibited those changes.

## Deviations from Plan

### Auto-fixed Issues

**1. [Rule 1 - Bug] Parser compile checks reported success after syntax errors**
- **Found during:** Task 3 validation
- **Issue:** `yyerror` printed diagnostics but `parseFiles` and `SimulationEngine::compile` continued, returning zero for some rejected sources.
- **Fix:** Added `g_parse_ok`, reset it per parse, set it from `yyerror`, and return a compile failure before elaboration/serialization.
- **Files modified:** `Track-A/A1-simulator/src/parser.y`, `Track-A/A1-simulator/src/sim_engine.cpp`
- **Verification:** Rejected optional axis_fifo syntax now returns `rc=1`; required parser checks return `rc=0`.
- **Committed in:** `6ba2557`

**2. [Rule 3 - Blocking] Required grammar gaps prevented basic03/basic05 parsing**
- **Found during:** Task 3 acceptance verification
- **Issue:** Generate-case syntax and `$dumpvars`/`$time` constructs were not accepted; later sha256 indexed selects also failed.
- **Fix:** Added focused grammar/token productions and regenerated parser artifacts through Makefile tooling.
- **Files modified:** `Track-A/A1-simulator/src/lexer.l`, `parser.y`, `lexer.yy.c`, `parser.tab.c`, `parser.tab.h`
- **Verification:** basic03, basic04, basic05, i2c, sha256, and Phase 5 parser regressions compile successfully.
- **Committed in:** `6ba2557`

**Total deviations:** 2 auto-fixed (1 bug, 1 blocking grammar gap).
**Impact on plan:** Both changes were directly required for truthful validation and the stated parser acceptance criteria; no shared state or unrelated runtime architecture was changed.

## Issues Encountered

- Bison reports 86 shift/reduce and 82 reduce/reduce conflicts in the permissive combined grammar. Generation and required parser checks pass, but future grammar cleanup should reduce ambiguity before adding broader Verilog syntax.
- The optional `axis_fifo` probe still rejects a later module-scope generate branch at `axis_fifo.v:499`; it is outside the required basic03/basic04/basic05 acceptance matrix.
- The optional `ip` probe still rejects an advanced localparam declaration form at `ip_eth_rx.v:121`; it was not required for this plan's acceptance criteria.
- No runtime simulation output comparison was attempted because this plan's success criteria are frontend regeneration and parser compile checks; execution scheduling remains a later Phase 6 plan.

## Known Stubs

- Empty alternatives in `parser.y` are intentional grammar productions for optional lists and empty procedural blocks.
- `TODO` comments in `lexer.yy.c` are flex-generated boilerplate, not application placeholders. No goal-blocking application stubs were introduced.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness

- Required frontend gate is ready for the next Phase 6 scheduler/elaborator work: clean generation, build, basic03/basic04/basic05, i2c, sha256, and Phase 5 parser checks pass.
- Keep the generated parser files synchronized by changing `lexer.l`/`parser.y` and rerunning the Makefile rules; do not hand-edit generated tables.
- Optional axis_fifo and ip grammar coverage remains a documented follow-up boundary.

## Self-Check: PASSED

- Summary path exists at `.planning/phases/06-a1-advanced-features/06-01-SUMMARY.md`.
- Task commits `a53d2da`, `c1ef067`, and `6ba2557` are present in git history.
- Required parser compile checks and clean regeneration/build passed.

---
*Phase: 06-a1-advanced-features*
*Plan: 01*
*Completed: 2026-07-15*
