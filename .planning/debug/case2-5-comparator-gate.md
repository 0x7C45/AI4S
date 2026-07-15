---
status: diagnosed
goal: find_root_cause_only
trigger: "case2-5 generated testbenches have 0 assert/comparison logic, failing official scoring.md §1 gate condition #5 (comparator must compare DUT behavior)."
created: 2026-07-15T04:36:00+08:00
updated: 2026-07-15T04:36:00+08:00
---

# Diagnosis: case2-5 comparator gate failure

## Root Cause (1-2 sentences)

The testbench template `cocotb_tb.py.j2` only emits a real comparison (`assert read.data == data`) in its AXI dual-bus branch (`s_axi` AND `m_axi`, case1 only); every other protocol path falls into the `{% else %}` "scoreboard 占位" branch that drives random inputs and samples only coverage — never sampling DUT outputs and never asserting. `skeleton_gen.py` then hardcodes the `verification_skeleton.json` scoreboard field to the static string `"assert read.data == expected_data"` for ALL cases regardless of which branch actually rendered, fabricating the gate-required comparator declaration. A secondary bug — `rtl_parser._parse_single_file` drops any port whose declaration is immediately preceded by a `/* ... */` block comment — silently removes `s_axis_tdata`/`m_axis_tdata` from case2's design.json, hiding the very output port a valid-ready golden model would compare against.

## Verified Claims

### 1. VERIFIED — non-AXI `{% else %}` branch has NO assert/comparison
`Track-A/A2-verification/templates/cocotb_tb.py.j2:196-224`. The branch body:
- L199-212: iterates `dir(dut)`, drives every input port with `rng.randrange(256)` and swallows output-port writes via the `except (AttributeError, ValueError, TypeError)` fallback.
- L215-220: only `coverage.hit(...)` calls keyed off `index % 2` / `index % 3` — no DUT output is read.
- L222: `await RisingEdge(dut.{{ design_info.clock }})`; L223: `test_count += 1`.
The literal self-label at L214 is `# scoreboard 占位：valid-ready 接口的基本数据比对（驱动后采样输出）` — "placeholder", and the "drive-then-sample-output" it describes is never implemented (no `getattr(dut, output).value` sampling anywhere in the branch). Zero `assert`/`raise`/comparison tokens.

### 2. VERIFIED — AXI dual-bus branch DOES have `assert read.data == data`
`cocotb_tb.py.j2:191-194`:
```
# 读 + scoreboard 比对（per 门禁五项第5项：scoreboard 实际比对，不静默）
read = await master.read(addr, length, size=size)
assert read.data == data, \
    "read %d addr=0x%x len=%d size=%s mismatch" % (index, addr, length, size)
```
This branch is gated by `{% if "AXI" in ... and _has_s_axi and _has_m_axi %}` (L161) — true only for case1. This is the reference pattern to adapt.

### 3. VERIFIED — skeleton_gen.py hardcodes the scoreboard field for all cases
`Track-A/A2-verification/src/skeleton_gen.py:151-154`:
```python
"scoreboard": {
    "model": "byte-addressed memory model on m_axi side",
    "compare": "assert read.data == expected_data after each transaction",
},
```
This dict is constructed unconditionally inside `generate()` and is identical for every design — it asserts an AXI-RAM comparison model even for case2 (valid-ready FIFO) and case3/case5 (no dual AXI bus). The gate checks `verification_skeleton.json`; this fabricated field makes a non-comparing testbench pass the spec's scoreboard-claim review until the actual testbench is read.

### 4. VERIFIED — case2 has usable output ports for a golden comparison
`Track-A/A2-verification/smoke_out/case2/design.json` lists output ports:
`s_axis_tready`, `m_axis_tkeep`, `m_axis_tvalid`, `m_axis_tlast`, `m_axis_tid`, `m_axis_tdest`, `m_axis_tuser`, `pause_ack`, `status_depth_commit`, `status_overflow`, `status_bad_frame`, `status_good_frame`.

NOTE (per claim 6): `m_axis_tdata` is MISSING from design.json even though the RTL declares it (`case2.v:117`). The data-bearing output port that a valid-ready shift-register golden model would compare against is `m_axis_tdata` — it exists in hardware but is invisible to the generator because of the parser bug. After fixing claim 6, the golden model for case2 is: drive `s_axis_tdata`/`s_axis_tvalid`, backpressure `m_axis_tready`, and assert `dut.m_axis_tdata.value == expected_byte` for each handshaked beat (the design is a width-1:1 axis_fifo_adapter, so the FIFO is a pure delay element and the golden model is a shift register / queue).

### 5. VERIFIED — case4 (AXI slave only, axi_ram) instantiates AxiMasterRead but never calls master.read()
`Track-A/A2-verification/smoke_out/case4/generated_test.py:106`:
```python
master = AxiMasterRead(AxiReadBus.from_prefix(dut, "s_axi"), dut.clk, dut.rst)
```
At L158 the driver is only awaited (`master.wait_idle()/wait()`). The main loop (L121-155) is the generic `{% else %}` branch: it `setimmediatevalue`s random bytes onto `s_axi_araddr`/`s_axi_arvalid`/etc. and never issues a structured transaction, so `master.read()` is never called and no readback data is compared. The master is an orphaned driver. Because case4's DUT is `axi_ram` (a slave memory), the fix is the case1 pattern adapted to slave-only: write expected data via `master` write path (or a second `AxiMasterWrite`) then `master.read()` + `assert read.data == data`.

### 6. VERIFIED — rtl_parser HAS a port-dropping bug (case2 missing m_axis_tdata)
Root cause is in `_parse_single_file` (`Track-A/A2-verification/src/rtl_parser.py:178-195`): it calls `_extract_port_section` then `port_section.split(",")` and matches each chunk against `_RE_PORT`. When a Verilog `/* ... */` block comment immediately precedes a port declaration (as in case2.v L102-105 / L114-117), the comma-split merges the multi-line comment text into the SAME chunk as the next port's `[WIDTH]` declaration, producing a chunk like:
```
/*\n * AXI input\n */\n    input  wire [S_DATA_WIDTH-1:
```
This chunk does not START with `input|output|inout`, so `_RE_PORT.match()` returns None. The port's NAME token (`s_axis_tdata`) is then orphaned into the FOLLOWING chunk (`0]  s_axis_tdata`) which also lacks a direction prefix and also fails to match. Both `s_axis_tdata` (L105) and `m_axis_tdata` (L117) are silently dropped. Reproduced empirically: parser output for case2.v matches `clk, rst, s_axis_tkeep, s_axis_tvalid, s_axis_tready, s_axis_tlast, s_axis_tid, s_axis_tdest, s_axis_tuser, m_axis_tkeep, m_axis_tvalid, m_axis_tready, m_axis_tlast, m_axis_tid, m_axis_tdest, m_axis_tuser, pause_ack, status_depth_commit, status_overflow, status_bad_frame, status_good_frame` — i.e. design.json exactly — but RTL has 23 ports not 21. The missing two are precisely the two `*_tdata` ports, both preceded by comments.

Knock-on effects beyond case2: any RTL using block comments before ports (standard Verilog style) loses those ports, breaking protocol inference, width detection, and output-port enumeration for the generic driver/golden-model logic.

## Missing Pieces (what the fix must add, per-protocol)

The fix is multi-layered. The planner must address all of the following:

1. **rtl_parser port-comment bug (blocker for everything else)** — strip `/* ... */` (and `//`) comments from the port section in `_extract_port_section` or `_parse_single_file` BEFORE `split(",")`. Until fixed, case2's `m_axis_tdata` is invisible and no golden model can compare against it. File: `Track-A/A2-verification/src/rtl_parser.py:178-195` (and/or `_extract_port_section` L202-241).

2. **valid-ready golden model (case2)** — in `cocotb_tb.py.j2`, add a new branch (between the AXI dual-bus branch and the `{% else %}`) gated on `"valid-ready" in design_info.inferred_protocols`. Drive `s_axis_tvalid`/`s_axis_tdata` with proper handshaking, backpressure `m_axis_tready`, and assert `dut.m_axis_tdata.value == expected` on each completed (`tvalid & tready`) output beat. Golden model = shift register / queue (axis_fifo_adapter at S_DATA_WIDTH==M_DATA_WIDTH==8 is a pure delay). Must also fix claim 6 first so `m_axis_tdata` is a known port.

3. **AXI slave-only golden (case4)** — add a branch gated on `_has_s_axi and not _has_m_axi` (or a sub-path of the existing `{% elif _has_s_axi %}` at template L133-138) that actually calls `master.read(addr, length)` against the slave RAM and asserts readback equals expected. Reuse the case1 RAM-comparison pattern, with expected data seeded by a parallel write or a known reset pattern. The orphaned `master` at case4 generated_test.py:106 must be wired into the main loop, replacing the generic `setimmediatevalue` block.

4. **Invariant checks for case3 / case5** — these DUTs are masters or address decoders (case3 `axi_vfifo_raw_rd` has `m_axi_*` master outputs; case5 `axi_crossbar_addr` is an address decoder). They cannot be driven the same way as slave DUTs. Add invariant-assertion logic: e.g. for case5, assert `m_select` / `m_wc_decerr` obey a decode-table reference for each address; for case3, assert pointer outputs (`rd_start_ptr_out`/`rd_finish_ptr_out`) monotonically advance and never cross invalidly. These are protocol-state invariants, not full golden models, but they satisfy gate #5 ("comparator compares DUT behavior") and are feasible without an upstream memory.

5. **skeleton_gen scoreboard de-fabrication** — replace the hardcoded dict at `skeleton_gen.py:151-154` with a value derived from the actual branch the template rendered (e.g. read a flag the template sets, or recompute from `design_info.inferred_protocols` + `has_axi_bus` results). For non-comparing designs the field should be honest (e.g. `"invariant checks"` or absent), not falsely claim an AXI-RAM comparison.

## Affected Files (exact paths + line ranges to change)

- `Track-A/A2-verification/src/rtl_parser.py:178-195` and `_extract_port_section` (L202-241) — strip comments before port split (claim 6 root cause).
- `Track-A/A2-verification/templates/cocotb_tb.py.j2:196-224` (`{% else %}` branch) — replace placeholder with protocol-specific comparator branches (valid-ready golden; invariant checks). New branches inserted ~L161-196 region.
- `Track-A/A2-verification/templates/cocotb_tb.py.j2:133-144` (`{% elif _has_s_axi %}` / AXI-slave-only) — wire the orphaned `master` into the main loop with `master.read()` + assert for case4.
- `Track-A/A2-verification/src/skeleton_gen.py:151-154` — de-hardcode scoreboard field (claim 3).
- (Regenerated, not hand-edited) `smoke_out/case{2,3,4,5}/generated_tb/generated_test.py` + `smoke_out/case2/design.json` (regain `m_axis_tdata`/`s_axis_tdata`).

## Specialist Hint
general (Python Jinja2 template + Python regex parser + cocotb testbench; no single strong language/framework signal beyond Python).
