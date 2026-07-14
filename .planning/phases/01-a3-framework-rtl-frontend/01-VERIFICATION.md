# Phase 1 Verification Record

## Evidence Boundary

Only commit `87675ff` and the canonical command result are used in this record. No file under `Track-A/A3-synthesis` was modified by this synchronization.

## Automated Local Evidence

| ID | Verification | Command/evidence | Status |
|---|---|---|---|
| L1 | Source implementation snapshot | Commit `87675ff` (`feat(A3): add adaptive synthesis submission`) | pass |
| L2 | Canonical local test suite | `make -C Track-A/A3-synthesis test` (equivalent to `cd Track-A/A3-synthesis && make test`) | pass: 28 tests |
| L3 | Local real LSV01 point 1 synthesis | A3 Makefile `synth` entry; output `/tmp/a3-lsv01-p1/netlist.v` | observed locally |
| L4 | Local mapped-netlist cell observation | `/tmp/a3-lsv01-p1/netlist.v` contains Nangate45 cells including `AND2_X1`, `MUX2_X1`, and `NAND2_X1` | observed locally |

L1-L4 are local evidence only. The LSV01 synthesis and Nangate45 observations are not evidence of official-image execution, RTL/gate functional equivalence, or final competition correctness. No OpenSTA result is available on this machine, so PPA and runtime are not verified.

## Human-Needed Validation Matrix

| ID | Required validation | Status | Why human_needed |
|---|---|---|---|
| H1 | Official-image synthesis | human_needed | No evidence shows a run in the pinned official evaluation image. |
| H2 | RTL/gate equivalence for LSV01 | human_needed | No evidence shows an RTL-versus-gate functional equivalence result. |
| H3 | Official/evaluator-relevant mapped-netlist acceptance | pending | Local Nangate45 cells were observed, but black-box, unauthorized-cell, and evaluator-image acceptance checks remain unproven. |

## Phase Status

Phase 1 remains incomplete. Local implementation, 28-test, real LSV01 point 1 synthesis, and Nangate45 mapped-netlist observations are recorded, but official-image synthesis and RTL/gate equivalence remain human-needed; evaluator-relevant mapped-netlist acceptance is pending.

Phases 2, 3, and 4 remain incomplete and are not advanced by this record.

## Dated Reconciliation: 2026-07-14

The following independent reconciliation section is appended without changing the preceding evidence.

| Circuit | synthesis_observed | equivalence_status | samples | note |
|---|---|---|---:|---|
| LSV01 | point1: observed_success | pass | 500 | local randomized RTL/gate equivalence passed |
| LSV02 | point1: observed_success | pass | 200 | local randomized RTL/gate equivalence passed |
| LSV03 | point1: observed_success | pass | 200 | local randomized RTL/gate equivalence passed |
| LSV04 | point1: observed_success | pass | 100 | local randomized RTL/gate equivalence passed |
| LSV05 | point1: observed_success | pass | 100 | local randomized RTL/gate equivalence passed |
| LSV06 | point1: observed_success | pass | 100 | local randomized RTL/gate equivalence passed |
| LSV07 | point1: observed_success | not_verified | N/A | verifier blocked by gate-level X/uninitialized state |
| LSV08 | point1: observed_success | pass | 100 | local randomized RTL/gate equivalence passed |
| LSV09 | point1: observed_success | not_verified | N/A | verifier blocked by gate-level X/uninitialized state |
| LSV10 | point1: observed_success | not_verified | N/A | verifier blocked by gate-level X/uninitialized state |

`not_verified` for LSV07/09/10 is neither pass nor a synthesis-defect determination. Dedicated initialization handling and the official testbench are required. All ten point 1 synthesis observations are local Yosys plus Nangate45 Liberty generated-netlist observations. `make -C Track-A/A3-synthesis test` passed 28 tests. OpenSTA/`sta` is unavailable locally, so PPA, area, timing, and runtime remain unverified. Official-image execution, full ten-circuit/all-point equivalence, auto-tuning/Pareto, final clean package/metadata/originality, and Phase 1-4 completion remain pending.

`STATE.md` unchanged because unresolved merge conflict; existing user content preserved. No safe conflict-external append-only location was proven.
