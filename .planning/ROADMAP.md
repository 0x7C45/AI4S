# Roadmap: AI4S 赛道 A — EDA 工具

## Overview

61-hour sprint to deliver three EDA tools for competition submission. A3 (RTL Logic Synthesis, user-led) is the primary track with 4 phases building from framework to correct netlists to multi-point PPA to final submission. A1 (RTL Simulator, teammate 1) and A2 (Verification Auto-gen, teammate 2) run as independent parallel tracks throughout -- their requirements are mapped to their respective phases but execution is decoupled from A3 phases.

## Phases

**Parallel Tracks:**
- **A3 Track** (队友): Phases 1-4, sequential dependency chain
- **A1 Track** (你): Phases 5-7, sequential dependency chain
- **A2 Track** (队友2): Phases 8-10, sequential dependency chain

- [ ] **Phase 1: A3 Framework + RTL Frontend** - Build tool scaffolding, parse Verilog, produce basic netlist for simple circuit *(队友)*
- [ ] **Phase 2: A3 Correctness — All 10 Public Circuits** - Every circuit LSV01-LSV10 produces functionally correct netlist *(队友)*
- [ ] **Phase 3: A3 Multi-Point PPA + Auto-Tuning** - Up to 7 points per circuit, config-driven optimization, auto-search for best PPA *(队友)*
- [ ] **Phase 4: A3 Submission Package** - Final integration, all deliverables verified, submission archive ready *(队友)*
- [x] **Phase 5: A1 Basic Simulator** - flex/bison parser + combinational logic simulation + basic01-05/alu/priority_encoder *(你)*
- [ ] **Phase 6: A1 Advanced Features** - Sequential logic, DFF, multi-file hierarchy, system functions, i2c/ip/axis_fifo/sha256 *(你)*
- [ ] **Phase 7: A1 Performance + GEMM** - GEMM test case, incremental compilation, multicore parallel simulation *(你)*
- [x] **Phase 8: A2 Skeleton Gate — RTL Parse + testbench Gen** - RTL 解析 + cocotb/Verilator testbench 骨架 + case1 门禁 *(队友2)*
- [x] **Phase 9: A2 Coverage Collection** - 行/分支/功能覆盖率 + 约束随机 5000 序列 + 综合 C≥65% *(队友2)*
- [ ] **Phase 10: A2 Generalization + Offline Packaging** - 10 隐藏电路通用化 + wheelhouse 离线包 + Docker 复验 *(队友2)*

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

### Phase 5: A1 Basic Simulator
**Goal**: flex/bison Verilog parser + combinational logic simulation engine, passing basic01, basic02, alu, priority_encoder (8 points)
**Depends on**: Nothing (independent track)
**Requirements**: A1-PARSE-01, A1-PARSE-02, A1-PARSE-03, A1-PARSE-04, A1-PARSE-05, A1-PARSE-06, A1-SIM-01, A1-MK-01, A1-MK-02, A1-MK-03, A1-CASE-01, A1-CASE-02, A1-CASE-03
**Success Criteria**:
  1. `make build` compiles flex/bison/C++ source and produces simulator executable
  2. `make compile_sim FILELIST=filelist.txt TOP=tb` parses RTL and produces self-contained sim.out
  3. `make run` (no args) generates `tb/output.mem` that matches `tb/output_ref.mem` for basic01, basic02, alu, priority_encoder
  4. Parser handles: module/endmodule, assign, always @(*), initial, reg/wire/integer, if-else/case/for, parameter, generate, `{}` concatenation, bit select, module instantiation
  5. System functions: $fopen, $fscanf, $fdisplay, $fgets, $display, $finish, $fclose
**Scope note**: basic03-05 deferred to Phase 6 (they need sequential logic: posge clk, DFF, non-blocking assign)
**Plans**: 1 plan

Plans:
- [ ] 05-01-PLAN.md — A1 Basic Simulator: flex/bison parser + C++ event-driven engine, passing basic01/basic02/alu/priority_encoder (8 points)

### Phase 6: A1 Advanced Features
**Goal**: Sequential logic simulation (posedge clk, DFF, non-blocking assign), multi-file hierarchy, passing i2c/ip/axis_fifo/sha256 (8 points)
**Depends on**: Phase 5
**Requirements**: A1-PARSE-07, A1-SIM-02, A1-SIM-03, A1-SIM-04, A1-INC-01, A1-CASE-01, A1-CASE-04, A1-CASE-05, A1-CASE-06, A1-CASE-07
**Success Criteria**:
  1. Always @(posedge clk) with non-blocking assignment (<=) works correctly
  2. DFF with async reset modeled properly
  3. `define / `include preprocessing works
  4. Multi-file module hierarchy instantiation works (i2c has 5 RTL files)
  5. tb/output.mem matches reference for i2c, ip, axis_fifo, sha256
**Plans**: TBD

### Phase 7: A1 Performance + GEMM
**Goal**: GEMM test case passes with competitive performance (11 points — compile perf + sim perf + multicore speedup)
**Depends on**: Phase 6
**Requirements**: A1-MK-04, A1-PAR-01, A1-PAR-02, A1-CASE-08
**Success Criteria**:
  1. GEMM tb/output.mem matches reference
  2. Incremental compilation: file-level dependency analysis, single-file change only recompiles affected modules
  3. `make parallel_run THREADS=4` produces cycle-identical output to single-threaded
  4. Performance competitive with baseline (compile time, sim time, multicore speedup)
**Plans**: TBD

### Phase 8: A2 Skeleton Gate — RTL Parse + testbench Gen
**Goal**: run.py 跑通 RTL → testbench → 仿真 → 结果，case1 骨架门禁通过（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）
**Depends on**: Nothing（环境已验证，见 SMOKE_TEST_REPORT.md）
**Requirements**: A2-PARSE-01, A2-PARSE-02, A2-PARSE-03, A2-SKEL-01, A2-SKEL-02, A2-SKEL-03, A2-SKEL-04, A2-OUT-01
**Success Criteria** (what must be TRUE):
  1. run.py 五参数入口跑通：`--rtl --top --out --seed --num-seq`
  2. RTL 解析输出 design.json：端口方向/宽度/时钟/复位/参数/协议推断（AXI/SRAM/valid-ready）
  3. 生成的 cocotb testbench 能用 Verilator 后端编译（COMPILE_ARGS 含 `-Wno-fatal`）并仿真通过
  4. DUT 端口正确连接，有时钟/复位生成、输入驱动、输出监视、scoreboard、ready 反压
  5. case1 跑通骨架门禁（门禁五项不命中任一：编译失败/端口错连/握手不可用/无驱动监视/scoreboard 静默）
**Plans**: 1 plan (complete)

Plans:
- [x] 08-01-PLAN.md — A2 骨架门禁：run.py 五参数 + rtl_parser + skeleton_gen + sim_runner + case1 门禁验收

### Phase 9: A2 Coverage Collection
**Goal**: 三类覆盖率齐全 + 综合 C≥65%（保底档），冲 C≥85%（满分档）
**Depends on**: Phase 8
**Requirements**: A2-RAND-01, A2-RAND-02, A2-RAND-03, A2-COV-01, A2-COV-02
**Success Criteria** (what must be TRUE):
  1. 行/分支覆盖率：Verilator `--coverage-line --coverage-toggle` 插桩 → coverage.dat LCOV 解析（按文件过滤排除 wrapper）
  2. 功能覆盖率：cocotb bin 真实事务采样（不空 hit，不初始化一次性 hit），4 类模板（FSM/数据通路/存储器/AXI）
  3. 约束随机：5000 序列，seed=20260630 穿透 `random.Random(seed)` + directed 边界值
  4. 7 JSON 产物齐全，coverage_result.json 综合公式写 0.4/0.3/0.3（禁止 0.42/0.28/0.30）
  5. RTL 静态分析：`generate/if` 死码识别，只对可达分支采 bin（避免 case1 53% 死码天花板）
**Plans**: 1 plan (complete)

Plans:
- [x] 09-01-PLAN.md — A2 覆盖率收集：constraint_gen + coverage_gen(4类bin) + coverage_collect(LCOV) + report_gen + dead_code_analyzer + case1 7JSON

### Phase 10: A2 Generalization + Offline Packaging
**Goal**: 10 隐藏电路通用化 + 离线打包 + Docker 复验，准备提交
**Depends on**: Phase 9
**Requirements**: A2-OUT-02
**Success Criteria** (what must be TRUE):
  1. 框架对 10 个隐藏电路通用化（禁硬编码/针对性优化，自适应 AXI/SRAM/valid-ready 接口）
  2. requirements.txt 每包钉死 ==X.Y.Z；wheelhouse/ 离线包齐全，评测机 `pip install --no-index` 可装
  3. THIRD_PARTY.md 齐全（版本/许可/调用边界）
  4. Docker linux/amd64 复跑 5 公开 case，覆盖率与本地无漂移
  5. run.sh 独自跑通完整流水线，评测人员无需手改任何生成文件
**Plans**: 1 plan (in progress — Task 1-3 done, Task 4 验收 pending)

Plans:
- [ ] 10-01-PLAN.md — A2 通用化+离线打包：非AXI接口适配 + 死码精化 + timeout=1200 + wheelhouse(7包) + README/run.sh 离线安装 + 5 case Docker 复验

## Progress

| Phase | Plans Complete | Status | Completed |
|-------|----------------|--------|-----------|
| 1. A3 Framework + RTL Frontend | 0/1 | Planned (队友) | - |
| 2. A3 Correctness — All 10 Circuits | 0/2 | Not started | - |
| 3. A3 Multi-Point PPA + Auto-Tuning | 0/2 | Not started | - |
| 4. A3 Submission Package | 0/1 | Not started | - |
| 5. A1 Basic Simulator | 1/1 | **Complete** | 2026-07-14 |
| 6. A1 Advanced Features | 0/0 | Not started | - |
| 7. A1 Performance + GEMM | 0/0 | Not started | - |
| 8. A2 Skeleton Gate | 1/1 | **Complete** | 2026-07-14 |
| 9. A2 Coverage Collection | 1/1 | **Complete** | 2026-07-14 |
| 10. A2 Generalization + Packaging | 0/1 | In Progress (Task 1-3) | - |
