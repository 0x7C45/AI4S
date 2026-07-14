# Phase 9: 覆盖率收集 — 行/分支/功能 + 约束随机 - Context

**Gathered:** 2026-07-14
**Status:** Ready for planning
**Source:** Derived from ROADMAP Phase 9 + CONSTRAINTS §5/§8/§10 + SMOKE_TEST_REPORT Level 2 + Phase 8 SUMMARY

<domain>
## Phase Boundary

Phase 9 交付：在 Phase 8 骨架门禁基础上，补全覆盖率采集管道——约束随机 5000 序列生成、Verilator coverage.dat 解析（line/branch）、功能 bin 定义与采样（cocotb hit）、综合覆盖率 C 计算，产出完整 7 JSON（补 constraints/coverage_bins/functional_coverage/coverage_result）。

**Phase 9 不做**：10 隐藏电路通用化（Phase 10）、离线打包 wheelhouse（Phase 10）。

**验收**：case1 跑通后 coverage_result.json 含三类覆盖率 + 综合 C（公式 0.4/0.3/0.3），功能 bin 有真实事务采样证据。

</domain>

<decisions>
## Implementation Decisions (LOCKED)

### 覆盖率口径（烟雾测试 Level 2 已验证）
- **行覆盖率（权重 0.4）**：Verilator `--coverage-line` 插桩 → coverage.dat → `verilator_coverage -write-info` 转 LCOV .info → Python 解析 DA 行
- **分支覆盖率（权重 0.3）**：`--coverage-line` 自动产出（branch 是 line coverage 结构化副产品），LCOV BRDA 粒度
- **功能覆盖率（权重 0.3）**：cocotb `coverage.hit(bin)` 采样，FunctionalCoverage 汇总
- **口径锁定**：Verilator LCOV 口径，**不追求复现 VCS 标杆**（VCS branch 分母 60 vs Verilator 1419，本质不同）。选手自交 coverage_result.json，评测器不锁工具重算。

### 烟雾测试已确认的覆盖率数据（case1，Verilator 口径）
| 文件 | line | branch |
|---|---|---|
| case1.v（真实 RTL）| 262/437 = 59.95% | 1022/1419 = 72.02% |
| case1_cocotb_top.v（wrapper）| 36/42 = 85.71% | 316/402 = 78.61% |

### 覆盖率 scope 控制（CONSTRAINTS §10）
- 覆盖率解析**按文件过滤**：只算真实 RTL 子树（排除 wrapper / cocotb_top 稀释）
- wrapper 识别：文件名含 `cocotb_top` / `wrapper` / 纯连线无 always 块的文件

### 综合公式（CONSTRAINTS §5，LOCKED）
- `C = 0.4×行 + 0.3×分支 + 0.3×功能`
- coverage_result.json 必须写 **0.4 / 0.3 / 0.3**（严禁 0.42/0.28/0.30）
- 档位：C≥85%→7分 | 65-85%→4.9分 | 45-65%→2.8分 | <45%→0分

### 约束随机（CONSTRAINTS §3，LOCKED）
- seed=20260630 穿透 `random.Random(seed)`（Phase 8 已实现，Phase 9 补 constraints.json 产物）
- 序列数 5000（固定）
- directed 边界值 + 随机组合（Phase 8 testbench 已有 read_lengths/read_address 生成器，Phase 9 补 constraints.json 配置 + coverage 反馈约束调整记录）

### 功能 bin 采信标准（CONSTRAINTS §8，LOCKED）
- bin 必须对应**可解释的功能场景 / corner case / 协议状态**
- bin 必须有**真实事务触发证据**（仿真中真实采样到），**不能空 hit**
- **禁止初始化时一次性 hit**（公开样例 case1 backpressure bin hits=1 是灰色地带，隐藏评测可能收紧）

### 功能 bin 4 类模板（PLAN.md congress 裁决 ⑤）
1. **FSM**：状态机状态/弧覆盖
2. **数据通路**：位宽转换/边界值/对齐
3. **存储器**：读写/地址边界/并发
4. **AXI 协议**：通道握手/反压/burst 类型/边界

### RTL 死码静态分析（CONSTRAINTS §10，case1 53% 根因）
- case1 行覆盖 53%（VCS）/59.95%（Verilator）的根因是**参数化死码**：`SEGMENT_COUNT==1`/`EXPAND` 分支在测试配置（S=32/M=16）下恒假
- Phase 9 需对 RTL 做 `generate/if/parameter` 静态分析，识别不可达分支，覆盖率分母只计可达行
- **这是 C≥85% 的关键**：不做死码过滤则 case1 line 卡在 ~60%

### Claude's Discretion
- coverage.dat 解析用 verilator_coverage 转 LCOV 还是直接解析（倾向 LCOV，已验证）
- 功能 bin 的具体 coverpoint/bin 定义（参考公开样例 case1 的 5 coverpoint × 24 bin 结构，但通用化）
- 死码分析的实现方式（PyVerilog AST vs 正则模式匹配 `generate/if/parameter` 条件）

</decisions>

<canonical_refs>
## Canonical References

### Phase 8 产出（Phase 9 基础）
- `E:/AI4S/Track-A/A2-verification/run.py` — 五参数入口（Phase 9 补 coverage 阶段调用）
- `E:/AI4S/Track-A/A2-verification/src/rtl_parser.py` — DesignInfo（Phase 9 补死码分析）
- `E:/AI4S/Track-A/A2-verification/src/skeleton_gen.py` — testbench 生成（Phase 9 补 functional_coverage import）
- `E:/AI4S/Track-A/A2-verification/src/sim_runner.py` — Docker 仿真（Phase 9 补 coverage.dat 提取）

### 赛题规格
- `E:/AI4S/Track-A/A2-verification/spec.md` — §3 七个 JSON schema（constraints/coverage_bins/functional_coverage/coverage_result）
- `E:/AI4S/Track-A/A2-verification/CONSTRAINTS.md` — §5 公式、§8 bin 采信、§10 scope/死码
- `E:/AI4S/Track-A/A2-verification/smoke_out/SMOKE_TEST_REPORT.md` — §3 Level 2 覆盖率对照数据

### 公开样例（参考标杆，只读）
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/case1/coverage_result.json` — VCS 口径标杆（line 53/branch 48.33/func 100/composite 65.79，公式 0.42/0.28/0.30 禁抄）
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/case1/coverage_bins.json` — bin 定义参考
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/case1/functional_coverage.json` — 功能覆盖结果参考
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/case1/constraints.json` — 约束随机配置参考
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/functional_coverage.py` — FunctionalCoverage 类实现（直接复用）

</canonical_refs>

<specifics>
## Specific Ideas

- coverage.dat → LCOV .info 解析命令（烟雾测试已验证）：
  ```bash
  verilator_coverage -write-info /tmp/cov.info coverage.dat
  # 然后 Python 解析 SF:/DA:/BRDA: 行
  ```
- 功能 bin 参考结构（case1 公开样例，通用化时按协议自适应）：
  - read_length: 8 bins（1/2_to_3/4/5_to_15/16_to_31/32_to_63/64_to_127/128_to_256）
  - address_alignment: 4 bins（aligned_4/aligned_2/unaligned/near_4k）
  - burst_size: 4 bins（size_1/size_2/size_4/default_max）
  - adapter_path: 4 bins（位宽转换/合并/窄读/部分末拍）
  - backpressure: 4 bins（源/下游各通道反压）
- functional_coverage.py 的 FunctionalCoverage 类可直接复用（hit/write 方法已实现）
- Phase 8 Makefile 已含 `--coverage-line --coverage-toggle`（COMPILE_ARGS），coverage.dat 会自动生成

</specifics>

<deferred>
## Deferred Ideas

- 10 隐藏电路通用化 → Phase 10
- 离线打包 wheelhouse → Phase 10
- cocotb 2.0 弃用警告清理 → Phase 10
- 约束求解用 z3-solver（可选，Phase 10 评估）

</deferred>

---

*Phase: 02-coverage-collection*
*Context gathered: 2026-07-14 (derived from ROADMAP + smoke test Level 2 + Phase 8 SUMMARY)*
