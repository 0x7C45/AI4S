---
quick_task: 260715-aqi-basic03
status: complete
completed: 2026-07-15
---

# Basic03 Recovery Summary

## Result

Basic03 passes the exact critical-path gate from its testcase directory:

- Build and parser regeneration: passed
- `compile_sim`: passed
- Fresh `tb/output.mem`: generated
- Timeout-bounded run: passed, `PASS cycles=32`
- Output lines: 33
- `diff -u tb/output_ref.mem tb/output.mem`: passed
- Output SHA-256: `02c9c7072a5686e3dd8991406c8164b743b0cdb384e3b6de2ab17a5d4512f3e8`

Basic01 smoke regression also passed with `PASS cycles=16` and exact diff.

## Commits

- `55bd389` — port generate-case elaboration, nested generated-cell flattening, edge-gated always execution, and bounded nonblocking assignment handling.
- `14732b0` — map indexed nested port expressions such as `a[i]`, `b[i]`, and `cell_y[i]`.
- `ad7968c` — canonicalize the parser's single-event `always` AST to the runtime-supported `@(posedge signal)` representation and regenerate parser artifacts.

## Scope

Only the basic03 parser/elaboration/runtime path was repaired. Basic04/basic05 and broader advanced cases remain separate work.
