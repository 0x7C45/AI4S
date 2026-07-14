# Phase 6: A1 Advanced Features - Discussion Log

**Date:** 2026-07-15
**Phase:** 06-a1-advanced-features

## Scope decision
- Replanned the phase for the remaining critical path: basic03, basic04, basic05 first.
- Phase 5 regression remains mandatory: basic01, basic02, alu, priority_encoder.
- i2c, ip, axis_fifo, sha256 and performance work are deferred.

## Locked decisions
- Use the minimum discrete-time semantics needed by the target cases: posedge clock, edge wait, #delay, basic NBA commit, and combinational propagation after NBA.
- Implement only the system-task subset required by the targets: `$time`, `$readmemh` with a minimal `$readmemb` entry point, existing file I/O tasks, `$finish`, and non-crashing `$dumpvars`.
- Require clean build, compile_sim, argument-free run, and exact diff for each target case.
- Preserve Phase 5 zero-diff behavior.

## Deferred
- Full Active/NBA/delta generality, asynchronous reset, complete VCD output, broad hierarchy generalization, remaining advanced cases, incremental compilation, GEMM, and multicore performance.
