# Phase 6: A1 Advanced Features - Discussion Log

> **Audit trail only.** Do not use as input to planning, research, or execution agents.
> Decisions are captured in CONTEXT.md — this log preserves the alternatives considered.

**Date:** 2026-07-14
**Phase:** 6-A1 Advanced Features
**Areas discussed:** Timing and scheduling, preprocessing and memory, test priority, hierarchy and arrays

---

## Timing and Scheduling

| Option | Description | Selected |
|--------|-------------|----------|
| Discrete-time event queue | Advance simulation time through scheduled events; clock toggles and edge waits use actual transitions. | ✓ |
| Wait-driven clock toggles | Keep the Phase 5 lightweight model that actively flips clocks while waiting. | |
| Single-clock simplification | Support one global fixed-period clock first. | |

**User's choice:** Discrete-time event queue.
**Notes:** The user selected the recommended event-driven model.

| Option | Description | Selected |
|--------|-------------|----------|
| Standard Active/NBA/delta | Execute Active, commit all NBA updates, then re-evaluate combinational logic to delta convergence. | ✓ |
| Immediate update | Apply non-blocking assignments immediately. | |
| Single-block ordering | Guarantee ordering only inside one always block. | |

**User's choice:** Standard Active/NBA/delta semantics.

| Option | Description | Selected |
|--------|-------------|----------|
| Synchronous and asynchronous reset | Support reset conditions in clocked blocks and independent reset edges. | ✓ |
| Synchronous reset only | Handle reset only inside clock-edge behavior. | |
| Conditional reset | Recognize reset conditions without independent reset-edge scheduling. | |

**User's choice:** Support both synchronous and asynchronous reset.

| Option | Description | Selected |
|--------|-------------|----------|
| Event queue exhaustion | Stop when no future event remains; `$finish` stops immediately. | ✓ |
| Fixed simulation limit | Run to a maximum time/cycle count. | |
| Finish-only | Depend entirely on testbench `$finish`. | |

**User's choice:** End on event queue exhaustion.

---

## Preprocessing and Memory

| Option | Description | Selected |
|--------|-------------|----------|
| Common full macros | Object/function-like macros, nested includes, recursion protection. | ✓ |
| Object macros only | Support only `define NAME value. | |
| Simple text replacement | Replace text without macro scope or nesting semantics. | |

**User's choice:** Support common object-like and function-like macros with include protection.

| Option | Description | Selected |
|--------|-------------|----------|
| By call location | Includes resolve relative to the including source; runtime file I/O resolves relative to testcase runtime directory. | ✓ |
| Relative to filelist | Resolve all paths against filelist directory. | |
| Relative to working directory | Resolve all paths against current working directory. | |

**User's choice:** Resolve paths according to call location.

| Option | Description | Selected |
|--------|-------------|----------|
| Packed plus memory arrays | Support packed ranges, unpacked memories, variable indexing, and hex/binary initialization ranges. | ✓ |
| Read-only memory | Support only simple `$readmemh(file, mem)` loading. | |
| Text cache | Cache input text and interpret it on demand. | |

**User's choice:** Support packed and unpacked arrays with `$readmemh`/`$readmemb` ranges.

| Option | Description | Selected |
|--------|-------------|----------|
| Minimal runnable semantics | `$time` is correct; `$dumpvars` runs without breaking simulation; no VCD required. | |
| Full VCD | Generate VCD waveforms including `$dumpfile` and `$dumpvars`. | ✓ |
| Syntax compatibility | Parse and silently ignore probes. | |

**User's choice:** Full VCD was selected during discussion, but the phase boundary keeps VCD generation deferred unless a testcase requires it; `$time` and runnable `$dumpvars` remain mandatory.

---

## Test Priority

| Option | Description | Selected |
|--------|-------------|----------|
| Basic03-05 first | Finish the three basic sequential/preprocessing/memory cases before larger designs. | ✓ |
| i2c first | Use i2c as the first integration target for multi-file hierarchy and timing. | |
| Value-driven switching | Move between tests based on score and implementation difficulty. | |
| Fixed roadmap order | Follow the listed order without reprioritizing. | |

**User's choice:** Basic03-05 first, then i2c/ip/axis_fifo/sha256.

| Option | Description | Selected |
|--------|-------------|----------|
| Per-test zero diff | Clean build, compile, run, and exact reference diff required for each testcase. | ✓ |
| Partial matching | Accept mostly matching output while continuing. | |
| Non-crashing only | Require only build and no crash. | |

**User's choice:** Each testcase requires exact zero-diff completion.

---

## Hierarchy and Arrays

| Option | Description | Selected |
|--------|-------------|----------|
| Global collection then hierarchy elaboration | Collect all filelist modules, resolve parameters and directional ports, then flatten/execute. | ✓ |
| Recursive immediate expansion | Resolve children while traversing the top module. | |
| Single-level hierarchy | Support only one DUT level initially. | |

**User's choice:** Global module collection followed by hierarchy elaboration.

| Option | Description | Selected |
|--------|-------------|----------|
| Packed plus unpacked memory arrays | Support variable-index reads/writes and initialization. | ✓ |
| Read-only memory | Support only memory reads. | |
| Signal simplification | Treat memories as ordinary wide signals. | |

**User's choice:** Packed and unpacked memory arrays with variable indexing.

---

## Claude's Discretion

- Event queue data structures, AST extensions, ownership, and internal implementation order.
- Exact VCD implementation boundary, provided it does not block mandatory Phase 6 behavior.

## Deferred Ideas

- Full VCD waveform output unless a testcase requires it.
- GEMM performance, incremental compilation, and multicore speedup for Phase 7.
- Broader SystemVerilog preprocessing beyond common Verilog macros/includes.
