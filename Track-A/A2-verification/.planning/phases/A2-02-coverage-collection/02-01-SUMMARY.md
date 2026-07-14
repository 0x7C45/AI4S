# Phase 2 Summary: 覆盖率收集 — 行/分支/功能 + 约束随机

**Phase:** A2-02-coverage-collection
**Status:** Complete
**Date:** 2026-07-14

## What Was Built

### 新增模块（5 个）
| 文件 | 功能 |
|---|---|
| `src/constraint_gen.py` | 约束随机配置生成（AXI/SRAM/valid-ready 三类变量，seed=20260630, 5000 序列）|
| `src/coverage_gen.py` | 功能 bin 4 类模板（AXI/FSM/DATAPATH/MEMORY），按协议激活 |
| `src/coverage_collect.py` | LCOV coverage.dat 解析 + wrapper 过滤 + 功能覆盖汇总 |
| `src/report_gen.py` | coverage_result.json（综合公式 0.4/0.3/0.3）|
| `src/dead_code_analyzer.py` | RTL 参数化死码识别（SEGMENT_COUNT/EXPAND）|

### 更新模块（3 个）
| 文件 | 变更 |
|---|---|
| `templates/cocotb_tb.py.j2` | 补 FunctionalCoverage import + hit() 真实事务采样 + write() |
| `src/skeleton_gen.py` | 复制 functional_coverage.py + bin_dict 注入模板 |
| `run.py` | 阶段3 constraint+bins / 阶段5 coverage+report 全集成 |

## Goal Achievement

### ROADMAP Phase 2 五条 Success Criteria
1. ✅ 行/分支覆盖率：Verilator --coverage-line → coverage.dat → LCOV 解析（wrapper 过滤）
2. ✅ 功能 bin 真实事务采样（cocotb hit），4 类模板定义齐全
3. ✅ 约束随机 5000 序列，seed=20260630 穿透 random.Random
4. ✅ 7 JSON 齐全，coverage_result.json 公式 0.4/0.3/0.3
5. ⚠️ RTL 死码识别已实现（dead_code_analyzer），但 if/else 块边界识别需精化，Phase 2 保守不启用过滤

### case1 端到端验收（100 笔快速验证）
```
7 JSON 全部产出 ✓
formula: 0.4 * line + 0.3 * branch + 0.3 * functional ✓
line=51.95% branch=44.68% func=42.11% C=46.82%
功能 bin source=cocotb transaction sampling（真实采样）✓
```

## Deviations from Plan

1. **死码过滤暂不启用**：dead_code_analyzer 对 `if/else` 块边界识别不够精确（把 L243-679 整块标死，但 else 分支是激活的）。Phase 2 保守传 None 不过滤，确保覆盖率数字真实保守（52% 而非虚高 82%）。Phase 3 精化块匹配。
2. **5000 笔超时**：覆盖率插桩 + 5000 笔事务在 Docker 内超 10 分钟。调试用 100 笔验证管道正确性。评测时需优化（减少 cocotb 开销或提高 timeout）。

## Lessons Learned

1. **functional_coverage.json 位置**：testbench 在 generated_tb/ 下运行，coverage.write() 写到 cwd（generated_tb/）。run.py 需复制到 out_dir 根（spec 要求 7 JSON 在 --out 下）。
2. **LCOV BRDA 粒度**：Verilator branch 分母远大于 VCS（1739 vs 60），口径本质不同，选手自交即可。
3. **Docker verilator_coverage 解析**：coverage.dat → LCOV .info 需在容器内跑（主机无 verilator_coverage），MSYS_NO_PATHCONV 防 Git Bash 路径转换。

## What's Next (Phase 3)

- 死码分析精化（if/else 块匹配，启用过滤提升 line%）
- 5000 笔性能优化（timeout / cocotb 开销）
- 10 隐藏电路通用化
- 离线打包 wheelhouse + THIRD_PARTY.md
- Docker 复验全部 case
