# Roadmap: AI4S 赛道 A — EDA 工具

## Overview

61-hour sprint to deliver three EDA tools for competition submission. A3 (RTL Logic Synthesis, user-led) is the primary track with 4 phases building from framework to correct netlists to multi-point PPA to final submission. A1 (RTL Simulator, teammate 1) and A2 (Verification Auto-gen, teammate 2) run as independent parallel tracks throughout -- their requirements are mapped to their respective phases but execution is decoupled from A3 phases.

## Phases

**Parallel Tracks:**
- **A3 Track** (you): Phases 1-4, sequential dependency chain
- **A1 Track** (teammate 1): Independent, runs throughout
- **A2 Track** (teammate 2): Independent, runs throughout

- [ ] **Phase 1: A3 Framework + RTL Frontend** - Build tool scaffolding, parse Verilog, produce basic netlist for simple circuit
- [ ] **Phase 2: A3 Correctness — All 10 Public Circuits** - Every circuit LSV01-LSV10 produces functionally correct netlist
- [ ] **Phase 3: A3 Multi-Point PPA + Auto-Tuning** - Up to 7 points per circuit, config-driven optimization, auto-search for best PPA
- [ ] **Phase 4: Submission Package** - Final integration, all deliverables verified, submission archive ready

## Phase Details

### Phase 1: A3 Framework + RTL Frontend
**Goal**: Working build pipeline that reads Verilog, runs Yosys synthesis, and outputs a valid gate-level netlist for at least one simple circuit
**Depends on**: Nothing (first phase)
**Requirements**: A3-FW-01, A3-FW-02, A3-FW-03, A3-FW-04, A3-FW-05, A3-RTL-01, A3-RTL-02, A3-RTL-03, A3-RTL-04, A3-RTL-05, A3-OPT-01, A3-OPT-03, A3-OPT-04
**Success Criteria** (what must be TRUE):
  1. `make build` compiles source and produces `bin/synth_tool`
  2. `make synth` with valid arguments produces `OUT_DIR/netlist.v` containing only Nangate45 standard cells (no black boxes, no unauthorized cells)
  3. Tool parses Verilog constructs: module hierarchy, always blocks, assign statements, parameters, generate, wide vectors, signed operations
  4. Single-circuit synthesis (e.g., LSV01) completes end-to-end with a valid gate-level netlist
  5. config.json with per-circuit point configuration and `$default` fallback is read correctly
**Plans**: 1 plan

Plans:
- [ ] 01-01-PLAN.md — A3 Synthesis Framework + RTL Frontend (Makefile, config/yaml parsers, core Yosys synthesis script with unified flow + variable ABC, Icarus verification, LSV01 E2E validation)

### Phase 2: A3 Correctness — All 10 Public Circuits
**Goal**: Every public circuit (LSV01-LSV10) produces a functionally correct netlist that passes simulation verification
**Depends on**: Phase 1
**Requirements**: A3-OPT-02, A3-CASE-01, A3-CASE-02, A3-CASE-03, A3-CASE-04, A3-CASE-05, A3-CASE-06, A3-CASE-07, A3-CASE-08, A3-CASE-09, A3-CASE-10
**Success Criteria** (what must be TRUE):
  1. Running synth on each of LSV01-LSV10 individually produces a netlist.v that passes functional verification (simulation comparison)
  2. ABC optimization sequences (compress2rs, resyn2rs, dch, if -K 6 and variants) are applied during synthesis
  3. All netlists contain only Nangate45 liberty cells -- zero black boxes across all 10 circuits
  4. Each circuit synthesizes without errors or crashes regardless of Verilog complexity (FSMs, FSMs, wide buses, deep hierarchies)
**Plans**: TBD

Plans:
- [ ] 02-01: TBD
- [ ] 02-02: TBD

### Phase 3: A3 Multi-Point PPA + Auto-Tuning
**Goal**: Each circuit supports up to 7 optimization points with different synthesis strategies, and an auto-tuning search finds the best PPA configuration
**Depends on**: Phase 2
**Requirements**: A3-PPA-01, A3-PPA-02, A3-PPA-03, A3-SEARCH-01, A3-SEARCH-02
**Success Criteria** (what must be TRUE):
  1. Each circuit can produce between 1 and 7 distinct netlist points, each from a different synthesis strategy (not pre-generated)
  2. Auto-tuning search explores multiple ABC optimization sequences per circuit and selects the best PPA configuration
  3. PPA hypervolume approaches or exceeds official reference baseline
  4. config.json drives per-circuit strategy selection; `$default` fallback handles circuits without explicit config
**Plans**: TBD

Plans:
- [ ] 03-01: TBD
- [ ] 03-02: TBD

### Phase 4: Submission Package
**Goal**: Complete submission archive with all deliverables verified and ready for evaluation
**Depends on**: Phase 3
**Requirements**: A3-FW-04
**Success Criteria** (what must be TRUE):
  1. submission.yaml lists all required fields (tool type, team info, dependencies)
  2. ORIGINALITY_DECLARATION.md and THIRD_PARTY.md are present and properly filled
  3. All 10 public circuits synthesize correctly from a clean build with `make build && make synth` invocations
  4. Submission archive contains all binaries, configs, and source -- self-contained with no external dependencies
**Plans**: TBD

Plans:
- [ ] 04-01: TBD

### Parallel Track: A1 RTL Simulator (Teammate 1)
**Status**: Independent -- runs throughout Phases 1-4
**Requirements**: A1-PARSE-01, A1-PARSE-02, A1-PARSE-03, A1-PARSE-04, A1-PARSE-05, A1-PARSE-06, A1-PARSE-07, A1-SIM-01, A1-SIM-02, A1-SIM-03, A1-SIM-04, A1-INC-01, A1-PAR-01, A1-PAR-02, A1-MK-01, A1-MK-02, A1-MK-03, A1-MK-04, A1-CASE-01, A1-CASE-02, A1-CASE-03, A1-CASE-04, A1-CASE-05, A1-CASE-06, A1-CASE-07, A1-CASE-08
**Notes**: Teammate 1 drives this with GSD assistance. No phase dependencies on A3. Managed separately via teammate's own GSD workspace.

### Parallel Track: A2 Verification Auto-gen (Teammate 2)
**Status**: Independent -- runs throughout Phases 1-4
**Requirements**: A2-PARSE-01, A2-PARSE-02, A2-PARSE-03, A2-SKEL-01, A2-SKEL-02, A2-SKEL-03, A2-SKEL-04, A2-RAND-01, A2-RAND-02, A2-COV-01, A2-COV-02, A2-OUT-01, A2-OUT-02
**Notes**: Teammate 2 drives this with GSD assistance. No phase dependencies on A3. Managed separately via teammate's own GSD workspace.

## Progress

| Phase | Plans Complete | Status | Completed |
|-------|----------------|--------|-----------|
| 1. A3 Framework + RTL Frontend | 0/1 | In progress | - |
| 2. A3 Correctness — All 10 Circuits | 0/2 | Not started | - |
| 3. A3 Multi-Point PPA + Auto-Tuning | 0/2 | Not started | - |
| 4. Submission Package | 0/1 | Not started | - |
