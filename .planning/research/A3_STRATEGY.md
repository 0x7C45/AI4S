# A3 RTL Logic Synthesis Hackathon Strategy

**Document Purpose:** Comprehensive strategy for building a lightweight RTL logic
synthesis tool based on Yosys, targeting the A3 hackathon competition.

**Deadline:** July 15, 2026 10:00 AM (~61 hours from start)
**Input:** Verilog + SDC + Nangate45 Liberty
**Output:** Gate-level netlist (.v)
**Scoring:** PPA Hypervolume (90pts) + Runtime (5pts) + Originality (5pts)

---

## Table of Contents

1. [Competition Scoring Model](#1-competition-scoring-model)
2. [Recommended Yosys Synthesis Flow](#2-recommended-yosys-synthesis-flow)
3. [ABC Optimization Sequences Reference](#3-abc-optimization-sequences-reference)
4. [Multi-Point Config Strategy](#4-multi-point-config-strategy)
5. [Per-Circuit Category Strategies](#5-per-circuit-category-strategies)
6. [Advanced Optimization Levers](#6-advanced-optimization-levers)
7. [Known Pitfalls and Gotchas](#7-known-pitfalls-and-gotchas)
8. [Time Budget Allocation](#8-time-budget-allocation)
9. [Originality Points Strategy](#9-originality-points-strategy)
10. [Quick Reference: Key Commands](#10-quick-reference-key-commands)

---

## 1. Competition Scoring Model

### PPA Hypervolume (90 points)

The hypervolume indicator measures the quality of a Pareto frontier. For each
circuit, you submit up to 7 "optimization points" (synthesis configurations).
Each point has (area, delay) coordinates. The hypervolume is the area of
objective space dominated by the Pareto front of your points.

**Key insight:** More points does NOT equal more score. The score is the
hypervolume of the convex hull of your non-dominated points. The goal is to
spread points across the area-delay tradeoff curve so the dominated volume
is maximized.

```
Score per circuit = Hypervolume(Pareto_front(your_points))
                    / Hypervolume(reference_7_points)

Total PPA = sum over all 20 circuits (weighted equally or by difficulty)
```

**Strategy implications:**
- Cover the FULL tradeoff spectrum: one aggressive-area point, one
  aggressive-timing point, and points in between.
- Dominated points (worse in both area AND delay than another of your points)
  contribute zero to hypervolume -- avoid them.
- A point that is marginally better than the reference on one axis but much
  worse on the other may not help. Focus on dominating the reference frontier.

### Runtime (5 points)

Total synthesis runtime across all 20 circuits. Lower is better. This means:
- Do NOT use extremely long ABC scripts on every circuit.
- Budget runtime: spend more time on high-value circuits, less on easy ones.
- Parallelize circuit synthesis if the framework allows it.

### Originality (5 points)

Judged on novelty of approach. This rewards:
- Custom Yosys passes or scripts beyond just calling `abc` with different flags.
- Novel pre-processing or post-processing techniques.
- Adaptive strategies (different flow per circuit category).

---

## 2. Recommended Yosys Synthesis Flow

### Phase 1: Elaboration and Pre-Processing

```yosys
# 1. Read technology library
read_liberty -lib Nangate45_typ.lib

# 2. Read design
read_verilog <circuit>.v

# 3. Read timing constraints
# (SDC constraints passed via -constr to abc, not read here)

# 4. Hierarchy processing
hierarchy -check -top <top_module>

# 5. Flatten (optional -- can help or hurt depending on circuit)
# flatten   # Aggressive: eliminates module boundaries for cross-module opt

# 6. Process behavioral constructs
proc
opt_expr
opt_clean
opt_merge

# 7. FSM optimization (for sequential circuits)
fsm
opt_clean
```

### Phase 2: Logic Optimization (Pre-Mapping)

```yosys
# 8. Word-size reduction
wreduce

# 9. Peephole optimizations
peepopt

# 10. Arithmetic optimizations
alumacc

# 11. Resource sharing
share

# 12. General optimization
opt -full
opt_clean
```

### Phase 3: Memory Handling (if applicable)

```yosys
# 13. Map memories to flip-flops
memory_map
opt -full
```

### Phase 4: Technology Mapping via ABC

```yosys
# 14. ABC with Nangate45 liberty
# The -script flag controls ABC's internal optimization sequence.
# The -constr flag passes SDC timing constraints.
# The -D flag sets target delay (ps).
abc -liberty Nangate45_typ.lib \
    -constr <constraints>.sdc \
    -script "<abc_script>"

# 15. Map flip-flops to library cells
dfflibmap -liberty Nangate45_typ.lib

# 16. Final cleanup
opt_clean
hilomap -hicell <hi_cell> -locell <lo_cell>
```

### Phase 5: Output

```yosys
# 17. Remove unused
opt_clean

# 18. Write gate-level netlist
write_verilog -noattr <output>.v
```

### Important Yosys `abc` Command Options

| Flag | Purpose |
|------|---------|
| `-liberty <file>` | Target technology library (Nangate45) |
| `-script <str>` | Custom ABC optimization script |
| `-constr <file>` | SDC timing constraints file |
| `-D <num>` | Target delay constraint (ps) |
| `-S <num>` | Number of LUT inputs (FPGA mapping) |
| `-G <num>` | Number of levels for gain-based area recovery |
| `-fast` | Use fast/minimal optimization |
| `-lut <width>` | Map to K-LUTs (for FPGA, not applicable here) |
| `-sop` | Map to SOP cells |

**Default ABC script** (when no `-script` is given):
```
strash; ifraig; scorr; dc2; dch; -h; mfs;
```
This does: structural hashing, incremental FRAIG, signal correspondence,
DAG-aware synthesis, choice computation, and multi-level functional
simplification -- then technology maps with `if` (integrated mapper).

**Important:** When `-script` is specified, the ENTIRE ABC flow is replaced.
You must include the technology mapping command (`map`, `amap`, or the `&`-based
flow with `&nf`) at the end of your script, or no mapping will occur.

---

## 3. ABC Optimization Sequences Reference

### Core ABC Concepts

ABC works on And-Inverter Graphs (AIGs). The key optimization primitives are:

| Command | Description | Best For |
|---------|-------------|----------|
| `strash` | Convert to AIG (structural hashing) | Always first |
| `balance` | Rebalance AIG to reduce depth | Delay |
| `rewrite` | DAG-aware local rewriting | Area + Delay |
| `rewrite -z` | Zero-cost rewrite variant | Area |
| `refactor` | Ashenhurst decomposition | Area |
| `refactor -z` | Zero-cost refactor variant | Area |
| `resub` | AIG resubstitution | Area + Delay |
| `resub -z` | Zero-cost resubstitution | Area |
| `dc2` | DAG-aware AIG rewriting (advanced) | Area + Delay |
| `dch` | Choice computation (enables mapping flexibility) | Area + Delay |
| `dch -f` | Choice computation (fast mode) | Speed |
| `ifraig` | Incremental FRAIG optimization | Cleanup |
| `scorr` | Signal correspondence (redundancy removal) | Area |
| `mfs` | Multi-level functional simplification | Area |
| `mfs2` | Advanced multi-level simplification | Area |
| `retime` | Register retiming for delay | Delay |
| `dretime` | Reverse retiming for area | Area |

### Built-in Script Aliases

| Script | Target | Underlying Operations |
|--------|--------|-----------------------|
| `resyn` | Delay | balance; rewrite; refactor; balance; rewrite; rewrite -z; refactor; refactor -z; balance |
| `resyn2` | Delay | Two rounds of `resyn` operations |
| `resyn2rs` | Delay | `resyn2` + resubstitution passes |
| `compress` | Area | Area-focused rewrite/refactor sequence |
| `compress2` | Area | Two rounds of `compress` operations |
| `compress2rs` | Area | `compress2` + resubstitution passes |

### Official Reference Points (Competition Baseline)

| Point | ABC Script | Mapping | Notes |
|-------|-----------|---------|-------|
| `yosys_p1` | `compress2rs` then `dch` | Nangate45 | Area-oriented |
| `yosys_p2` | `if -K 6 -g -C 8` then `dch` | Nangate45 | IF-mapper with K=6 |
| `yosys_p3` | `resyn2rs` then `dch` | Nangate45 | Delay-oriented |
| `yosys_p4` | 2x `compress2rs` then `dch` | Nangate45 | Double area optimization |
| `yosys_p5` | 2x `if -K 6 -g -C 8` then `dch` | Nangate45 | Double IF optimization |

### Sequences to Try Beyond the Reference

#### Aggressive Area Sequences
```
# Triple-compress with resubstitution
strash; compress2rs; compress2rs; compress2rs; dch; map -a

# Compress + refactor + resub
strash; compress2rs; refactor -z; resub -z; dch; map -a

# Full area pipeline with choice computation
strash; scorr; ifraig; compress2rs; dch; dch; compress2rs; map -a
```

#### Aggressive Delay Sequences
```
# Resyn + balance + retiming
strash; resyn2rs; balance; dch; map -D 0

# Multi-round delay optimization
strash; resyn2rs; resyn2; balance; dch; map

# Delay with retime
strash; resyn2rs; retime; dch; map
```

#### Balanced / Novel Sequences
```
# Mixed area-delay with two mapping passes
strash; resyn2rs; compress2rs; dch; map
strash; compress2rs; resyn2rs; dch; map

# Aggressive choice computation
strash; dc2; dch; dch -f; dch; resyn2rs; dch; map

# Balance-first for timing-critical paths
strash; balance; balance; resyn2rs; dch; map

# Area recovery after delay mapping
strash; resyn2rs; dch; map; unmap; map -a
```

#### Using the `&` (New-Generation) Commands
The `&` commands in ABC use a newer, often more effective data structure:

```
strash; &get -n; &dch -f; &nf; &put
strash; &get -n; &dch; &nf -p; &put
strash; &get -n; &dc2; &dch; &nf; &put
strash; &get -n; &fraig; &dch; &nf; &put
```

These use the new fast-mapping infrastructure (`&nf` = new fast mapper,
`&dch` = new choice computation, `&dc2` = new DAG-aware rewriting).

---

## 4. Multi-Point Config Strategy

### Goal: Maximize Hypervolume per Circuit

For each circuit, submit up to 7 points that span the area-delay tradeoff.
The reference provides 7 points (5 Yosys variants + 2 DC commercial).
Your goal is to match or beat the reference hypervolume on each circuit.

### Recommended Point Distribution

```
Point 1 (AREA_MIN):     Maximum area reduction, relaxed timing
Point 2 (AREA):         Strong area focus, moderate timing
Point 3 (BALANCED_1):   Balanced, slight area lean
Point 4 (BALANCED_2):   Balanced, slight delay lean
Point 5 (DELAY):        Strong delay focus, moderate area
Point 6 (DELAY_MIN):    Minimum delay, relaxed area
Point 7 (WILDCARD):     Novel/custom strategy or circuit-specific
```

### Config JSON Structure

```json
{
  "circuits": {
    "LSV01": {
      "points": [
        {
          "name": "area_min",
          "abc_script": "strash; compress2rs; compress2rs; compress2rs; dch; map -a",
          "flatten": true,
          "description": "Maximum area optimization"
        },
        {
          "name": "area",
          "abc_script": "strash; compress2rs; dch; map -a",
          "flatten": true,
          "description": "Area-focused"
        },
        {
          "name": "balanced_1",
          "abc_script": "strash; compress2rs; resyn2rs; dch; map",
          "flatten": true,
          "description": "Balanced area-leaning"
        },
        {
          "name": "balanced_2",
          "abc_script": "strash; resyn2rs; compress2rs; dch; map",
          "flatten": true,
          "description": "Balanced delay-leaning"
        },
        {
          "name": "delay",
          "abc_script": "strash; resyn2rs; dch; map",
          "flatten": true,
          "description": "Delay-focused"
        },
        {
          "name": "delay_min",
          "abc_script": "strash; resyn2rs; balance; dch; map -D 0",
          "flatten": true,
          "description": "Minimum delay"
        },
        {
          "name": "wildcard",
          "abc_script": "strash; &get -n; &dch; &nf; &put",
          "flatten": true,
          "description": "New-gen mapper"
        }
      ]
    }
  }
}
```

### Per-Category Default Configurations

Rather than a single config for all circuits, use category-specific configs:

**Combinational circuits (LSV01, LSV02, LSV03, LSV05, LSV06):**
- ABC sees the full combinational logic, no flip-flop mapping issues.
- Can use aggressive flattening.
- More aggressive optimization scripts are safe.

**Sequential circuits (LSV04, LSV07, LSV08, LSV09, LSV10):**
- Must handle flip-flop mapping carefully (`dfflibmap`).
- FSM extraction may help or hurt -- test both.
- Be careful with `flatten` on hierarchical sequential designs.
- Memory mapping may be needed for LSV09/LSV10.

---

## 5. Per-Circuit Category Strategies

### Combinational Circuits (LSV01-LSV03, LSV05, LSV06)

**Priority:** These are easiest to synthesize correctly. Focus optimization here.

| Circuit | Type | Strategy |
|---------|------|----------|
| LSV01 (priority) | Combinational priority | Simple logic -- all ABC sequences work well. Try aggressive multi-pass. |
| LSV02 (cavlc) | Combinational control | Control logic -- `compress2rs` likely dominates. |
| LSV03 (adder) | Arithmetic | Arithmetic-heavy -- `alumacc` pre-processing is critical. Try `wreduce` too. |
| LSV05 (axi_downsizer) | AXI control | Bus logic -- likely mux-heavy. `compress2rs` + `dch` good baseline. |
| LSV06 (f2i) | Float conversion | Datapath -- `wreduce` + `alumacc` before ABC. |

**Key passes to add for arithmetic circuits (LSV03, LSV06):**
```yosys
wreduce
peepopt
alumacc
share
opt -full
```

### Sequential / FSM Circuits (LSV04, LSV07, LSV08)

| Circuit | Type | Strategy |
|---------|------|----------|
| LSV04 (b11) | Sequential FSM | FSM extraction likely helps. Test with/without `fsm` pass. |
| LSV07 (qdiv) | Sequential divider | Complex control + datapath. Test `flatten` carefully. |
| LSV08 (stage_mult) | Multiplier pipeline | Pipeline registers -- retiming may help delay. |

**Key considerations for sequential circuits:**
```yosys
# Test FSM extraction (may help or hurt)
fsm
fsm_opt
fsm_map

# Flip-flop optimization
opt_dff

# Consider retiming for timing-critical sequential paths
# (ABC supports retime -D <delay> and retime -M <area>)
```

### Complex / Hard Circuits (LSV09, LSV10)

| Circuit | Type | Strategy |
|---------|------|----------|
| LSV09 (sha256_wishbone) | Crypto/Bus | Likely has memory structures. Use `memory_map`. |
| LSV10 (vexriscv_small) | CPU core | Large, hierarchical. May benefit from selective flattening. |

**Key considerations for complex circuits:**
- May have memory elements that need `memory_map`.
- Hierarchical: test with and without `flatten`.
- Runtime is a concern -- do not use extremely long ABC scripts on these.
- The CPU core (LSV10) may have many module instances -- verify correctness.

---

## 6. Advanced Optimization Levers

### 6.1 Pre-ABC Yosys Passes

These passes run BEFORE sending logic to ABC and can significantly affect QoR:

| Pass | Effect | When to Use |
|------|--------|-------------|
| `wreduce` | Reduces bit-width of signals | Arithmetic circuits (LSV03, LSV06, LSV08) |
| `peepopt` | Peephole optimizations | Generally helpful |
| `alumacc` | Optimizes ALU/multiply-accumulate | Arithmetic circuits |
| `share` | Resource sharing | When multiple similar operations exist |
| `opt -full` | Aggressive general optimization | Always |
| `opt_share` | Share equivalent operations | When area is critical |
| `flatten` | Eliminate hierarchy | Combinational circuits; test on sequential |
| `fsm` | FSM extraction + optimization | FSM circuits (LSV04) |
| `opt_dff` | Flip-flop optimization | Sequential circuits |
| `memory_map` | Map memories to FFs | When memories present (LSV09, LSV10) |
| `clean` | Remove unused signals | Always, before and after ABC |

### 6.2 ABC Technology Mapping Options

After optimization, the mapping step itself has options:

```
map            # Standard delay-driven mapping
map -a         # Area-driven mapping
map -D <ps>    # Mapping with specific delay target
map -a -D <ps> # Area mapping with delay constraint
```

Area recovery after delay mapping:
```
strash; resyn2rs; dch; map      # Delay-oriented
strash; resyn2rs; dch; map -a   # Area-oriented (often produces different topology)
```

### 6.3 Choice Computation (`dch`)

The `dch` command is critical -- it computes structural choices that give the
technology mapper more options. Running `dch` multiple times or after different
optimization passes can produce different (and sometimes better) choices:

```
strash; compress2rs; dch; map          # Single dch after area opt
strash; compress2rs; dch; resyn2rs; dch; map  # Two dch passes
strash; dc2; dch; dch; map             # Double dch
```

### 6.4 Using ABC's `&` (New) Commands

The `&` prefix activates ABC's newer engine with potentially better algorithms:

```
&get -n    # Move AIG to new engine
&dch       # New choice computation
&dch -f    # Fast choice computation
&dc2       # New DAG-aware rewriting
&fraig     # New FRAIG computation
&nf        # New fast mapper
&nf -p     # New fast mapper (area mode)
&put       # Move result back to old engine
```

Example novel sequence:
```
strash; &get -n; &dc2; &dch; &nf -p; &put
```

### 6.5 Post-Mapping Optimization

After ABC maps to cells, some additional Yosys passes can help:

```yosys
# Clean up after mapping
opt_clean

# I/O mapping (if required by competition)
hilomap -hicell <VDD> -locell <VSS>

# Buffer insertion for high fanout nets (if timing allows)
# (Not always available in standard Yosys)

# Final stat check
stat -liberty Nangate45_typ.lib
```

### 6.6 SDC Constraint Handling

The SDC constraints file controls timing-aware optimization. Key considerations:

- The `-constr` flag to `abc` passes timing constraints.
- ABC uses these to determine critical paths during mapping.
- If no constraints are provided, ABC optimizes without timing awareness.
- For delay-minimum points, consider passing very tight constraints.
- For area-minimum points, consider relaxed or no constraints.

---

## 7. Known Pitfalls and Gotchas

### Pitfall 1: Missing Technology Mapping in Custom ABC Scripts
**Problem:** When using `-script`, if you forget the `map` (or `&nf; &put`) command
at the end, ABC will optimize the AIG but never map to cells. The output will
be invalid.

**Fix:** Always end your `-script` with a mapping command:
```
-strash; compress2rs; dch; map
```

### Pitfall 2: Incorrect Liberty File Path
**Problem:** Liberty file path is relative to the working directory, not the
Yosys binary location.

**Fix:** Use absolute paths or verify CWD before running.

### Pitfall 3: Flip-Flop Mapping After ABC
**Problem:** ABC only maps combinational logic. Flip-flops must be mapped
separately with `dfflibmap`.

**Fix:** Always run `dfflibmap -liberty Nangate45_typ.lib` after `abc`.

### Pitfall 4: Undefined Signals Causing Mismatches
**Problem:** Uninitialized signals (X) in Verilog can cause simulation vs.
synthesis mismatches and incorrect netlists.

**Fix:** Use `setundef -zero` or `setundef -one` before synthesis to resolve
all undefined values to a deterministic state.

### Pitfall 5: Flatten Breaking Sequential Circuits
**Problem:** Aggressive flattening can sometimes create issues with
sequential elements, especially if there are clock domain crossings or
complex reset structures.

**Fix:** Test sequential circuits with and without `flatten`. Compare area/timing.

### Pitfall 6: Memory Elements Not Mapped
**Problem:** If the design has inferred memories that are not mapped to
flip-flops, the output netlist will contain unsupported primitives.

**Fix:** Run `memory_map` before ABC for designs with memory constructs.

### Pitfall 7: Bus Width Issues
**Problem:** Multi-bit signals (buses) can sometimes cause issues with
certain ABC optimization passes.

**Fix:** Run `splitnets` before ABC if bus-related issues arise.

### Pitfall 8: Competition Runtime Limits
**Problem:** Using extremely long ABC scripts (e.g., 10 rounds of
`compress2rs`) on large circuits (LSV09, LSV10) can hit runtime limits.

**Fix:** Use shorter scripts for large circuits. Profile runtime on the
10 public circuits and extrapolate for hidden ones.

### Pitfall 9: ABC Version Compatibility
**Problem:** Different Yosys versions bundle different ABC versions. The
available commands and their behavior can vary.

**Fix:** Verify which ABC version is bundled with your Yosys. Test all
scripts with the competition's Yosys version.

### Pitfall 10: Over-Optimization
**Problem:** Running too many optimization passes can sometimes INCREASE
area or delay (optimization passes can interact non-monotonically).

**Fix:** Always measure `stat` output after each synthesis run. More passes
is not always better.

---

## 8. Time Budget Allocation

### Phase 0: Setup (Hours 0-2)
- [ ] Verify toolchain (Yosys, ABC, liberty files)
- [ ] Run baseline synthesis on all 10 public circuits
- [ ] Validate output correctness (functional equivalence check)
- [ ] Establish baseline metrics for each circuit

### Phase 1: Correctness (Hours 2-6)
- [ ] Ensure all 10 public circuits produce valid gate-level netlists
- [ ] Run formal verification or simulation to check correctness
- [ ] Fix any issues with memory mapping, FSM handling, etc.
- [ ] Document any circuit-specific quirks

### Phase 2: Baseline Optimization (Hours 6-14)
- [ ] Implement all 5 reference Yosys points (p1-p5) for each circuit
- [ ] Measure area/timing for each point
- [ ] Calculate hypervolume for each circuit
- [ ] Identify which circuits have the most room for improvement

### Phase 3: Advanced Optimization (Hours 14-30)
- [ ] Try novel ABC sequences beyond the reference
- [ ] Experiment with pre-ABC passes (wreduce, peepopt, alumacc)
- [ ] Test flattening strategies per circuit
- [ ] Explore the `&` command sequences
- [ ] Try circuit-specific optimizations
- [ ] Measure incremental improvements

### Phase 4: Multi-Point Tuning (Hours 30-45)
- [ ] For each circuit, select the best 7 points for max hypervolume
- [ ] Ensure points span the full area-delay tradeoff
- [ ] Remove dominated points
- [ ] Fine-tune point spacing for maximum hypervolume

### Phase 5: Runtime Optimization (Hours 45-52)
- [ ] Profile synthesis runtime per circuit
- [ ] Replace expensive scripts with cheaper equivalents where the
  quality difference is small
- [ ] Parallelize independent circuit synthesis if possible
- [ ] Ensure total runtime fits within limits

### Phase 6: Testing and Submission (Hours 52-58)
- [ ] Full end-to-end run on all 10 public circuits
- [ ] Validate all netlists
- [ ] Calculate final scores
- [ ] Prepare submission package

### Phase 7: Buffer (Hours 58-61)
- [ ] Fix any last-minute issues
- [ ] Test on hidden circuit names (if structure is known)
- [ ] Submit

---

## 9. Originality Points Strategy

To earn originality points (5% of score), go beyond simply calling `abc`
with different flags. Consider:

### Custom Yosys Script
Write a Python/Tcl script that:
1. Analyzes circuit characteristics (logic depth, register count, mux density)
2. Selects an optimal synthesis strategy based on the analysis
3. Adapts ABC script parameters per circuit

### Custom Pre-Processing
- Implement custom peephole optimizations in Yosys's `techmap` format.
- Add circuit-specific constant propagation or dead code elimination.
- Implement custom arithmetic optimizations (e.g., carry-save for adders).

### Adaptive Strategy Selection
- Classify circuits automatically (combinational vs sequential, arithmetic
  vs control, small vs large).
- Apply category-specific synthesis flows automatically.
- Use a simple heuristic to select the number of optimization rounds.

### Novel ABC Sequences
- Test sequences that are not in the reference and document why they work.
- Explore using `retime` for sequential circuits.
- Try `mfs2` and `mfs` in combination with standard scripts.

---

## 10. Quick Reference: Key Commands

### Yosys Essential Commands

```yosys
# Reading
read_liberty -lib <file>       # Load technology library
read_verilog <file>            # Load Verilog
read_sdc <file>                # Load SDC constraints

# Hierarchy
hierarchy -check -top <mod>    # Process and check hierarchy
flatten                        # Flatten design

# Behavioral to structural
proc                           # Convert processes to FFs and muxes

# Optimization
opt -full                      # Full optimization
opt_expr                       # Constant expression optimization
opt_clean                      # Remove unused cells/wires
opt_merge                      # Merge identical cells
opt_dff                        # Optimize flip-flops
opt_share                      # Resource sharing

# Arithmetic
wreduce                        # Bit-width reduction
peepopt                        # Peephole optimizations
alumacc                        # ALU/MAC optimization
share                          # Resource sharing

# FSM
fsm                            # Full FSM flow (detect, extract, opt, map)
fsm_extract                    # Extract FSMs
fsm_opt                        # Optimize FSMs
fsm_map                        # Map FSMs

# Memory
memory_map                     # Map memories to FFs
memory_collect                 # Collect memory operations

# Technology mapping
techmap                        # Generic technology mapping
abc -liberty <lib>             # ABC mapping with library
abc -liberty <lib> -script "..."  # ABC with custom script
abc -liberty <lib> -D <ps>    # ABC with delay target
dfflibmap -liberty <lib>       # Map flip-flops

# Output
write_verilog -noattr <file>   # Write gate-level netlist
stat -liberty <lib>            # Print design statistics
```

### ABC Essential Commands

```
# Structure
strash                   # Convert to AIG

# Built-in scripts (area)
compress                 # Area optimization (1 round)
compress2                # Area optimization (2 rounds)
compress2rs              # Area optimization + resubstitution

# Built-in scripts (delay)
resyn                    # Delay optimization (1 round)
resyn2                   # Delay optimization (2 rounds)
resyn2rs                 # Delay optimization + resubstitution

# Primitive operations
balance                  # Rebalance AIG (reduce depth)
rewrite                  # DAG-aware local rewriting
rewrite -z               # Zero-cost rewrite
refactor                 # Ashenhurst decomposition
refactor -z              # Zero-cost refactor
resub                    # Resubstitution
resub -z                 # Zero-cost resubstitution

# Advanced
dc2                      # DAG-aware AIG rewriting (advanced)
dch                      # Choice computation
dch -f                   # Fast choice computation
ifraig                   # Incremental FRAIG
scorr                    # Signal correspondence
mfs                      # Multi-level functional simplification
mfs2                     # Advanced MFS
retime                   # Register retiming
dretime                  # Reverse retiming

# New-generation commands
&get -n                  # Move to new engine
&dch                     # New choice computation
&dc2                     # New DAG-aware rewriting
&fraig                   # New FRAIG
&nf                      # New fast mapper
&nf -p                   # New fast mapper (area mode)
&put                     # Move back to old engine

# Technology mapping
map                      # Delay-driven mapping
map -a                   # Area-driven mapping
map -D <ps>              # Mapping with delay target
amap                     # Area mapping (alternative)
```

---

## Appendix A: Experimental Sequences to Try

These are untested sequences that may produce novel Pareto points.
Test on the public circuits and keep if they improve hypervolume.

```bash
# EXP-1: Triple pass with alternating focus
"strash; compress2rs; resyn2rs; compress2rs; dch; map"

# EXP-2: Heavy choice computation
"strash; dc2; dch; dc2; dch; resyn2rs; dch; map"

# EXP-3: New-gen with area recovery
"strash; &get -n; &dc2; &dch; &nf -p; &put"

# EXP-4: New-gen with delay focus
"strash; &get -n; &dch; &nf; &put"

# EXP-5: Retiming for sequential
"strash; resyn2rs; retime -D 0; dch; map"

# EXP-6: Maximum area compression
"strash; compress2rs; compress2rs; compress2rs; compress2rs; dch; map -a"

# EXP-7: Balance-first for timing
"strash; balance; balance; balance; resyn2rs; dch; map"

# EXP-8: MFS-heavy area optimization
"strash; scorr; mfs2; compress2rs; mfs2; dch; map -a"

# EXP-9: Mixed old/new engine
"strash; dc2; dch; &get -n; &dch; &nf; &put"

# EXP-10: Refactor-heavy area optimization
"strash; refactor; refactor; refactor -z; compress2rs; dch; map -a"
```

---

## Appendix B: Quick Diagnostic Commands

```yosys
# After synthesis, check area and timing:
stat -liberty Nangate45_typ.lib

# Check for unmap cells (indicates incomplete mapping):
# Look for cells not in the Nangate45 library in the stat output.

# Verify design is fully structural (no behavioral constructs):
# The output .v should only contain `module`, `wire`, `assign`,
# and cell instantiations -- no `always` blocks.

# Check for X values:
setundef -zero  # Resolve X to 0
```

---

## Appendix C: Circuit-Specific Notes

### LSV03 (epfl_adder) - Arithmetic
- Use `alumacc` and `wreduce` before ABC.
- Adders decompose into carry chains; ABC's `refactor` may help area.
- Consider `compress2rs` for area and `resyn2rs` for delay.

### LSV04 (itc99_b11) - FSM
- FSM extraction with `fsm` pass may significantly help.
- Test: with FSM extraction vs without.
- State encoding matters: test binary vs one-hot.

### LSV09 (sha256_wishbone) - Crypto
- Likely has complex combinational logic (hash rounds).
- May have bus interfaces -- check for memory structures.
- Runtime-sensitive: avoid overly long ABC scripts.

### LSV10 (vexriscv_small) - CPU
- Largest and most complex circuit.
- Hierarchical design -- test flattening carefully.
- May have many small modules; flattening exposes cross-module optimization.
- Be mindful of runtime.

---

## References

- [Yosys Documentation](https://yosys.readthedocs.io/)
- [Yosys abc Command Reference](https://yosys.readthedocs.io/projects/yosys/en/0.9/cmd/abc.html)
- [ABC: System for Synthesis and Verification](https://people.eecs.berkeley.edu/~alanmi/abc/)
- [ABC GitHub Repository](https://github.com/berkeley-abc/abc)
- [Nangate45 PDK Documentation](https://openroad.readthedocs.io/en/latest/contrib/Database-Format/Nangate45.html)
- [OpenROAD Flow Scripts](https://openroad-flow-scripts.readthedocs.io/en/latest/)
- [ABC Tutorial - ECE 565, University of Victoria](https://www.ece.uvic.ca/~fhu/ece565/abctutorial.pdf)
- [Yosys GitHub](https://github.com/YosysHQ/yosys)
- [Multi-Objective Logic Synthesis using Deep RL](https://arxiv.org/abs/2306.13405)
- [IWLS Competition](https://iwls.org/)
