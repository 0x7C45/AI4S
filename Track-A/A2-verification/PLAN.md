# A2 验证环境自动生成 · 方案（PLAN）

> **更新于 2026-07-13**：路线从 `cocotb + iverilog + gcov` 切换为 **`cocotb + Verilator`**。
> ⚠️ 本文件取代 `TEAM_GUIDE.md` 中 A2 节的 iverilog 旧方案。TEAM_GUIDE 的 A2 节待后续精确更新。

---

## 一、目标

读取 RTL 设计，自动生成 cocotb testbench + 约束随机测试 + 覆盖率报告，产出 7 个 JSON + `generated_tb/` + `generated_tests/`。

入口：`./run.sh --rtl ... --top ... --out ... --seed x --num-seq 5000` 或 `python3 run.py`。

## 二、为什么 cocotb + Verilator（决策依据，原文核实）

### 问题：覆盖率是 A2 的大头
覆盖率分 = `C = 0.4×行 + 0.3×分支 + 0.3×功能`，**行/分支占 70%**。骨架门禁 3 分 + 覆盖率 7 分，门禁不过一切归零。

### iverilog 路线的真问题（工具能力，非规则）
- iverilog **原生不支持 RTL 行/分支覆盖率**（无 `-cm` 等价物，`$dumpvars` 只产波形）。
- 原计划 gcov/lcov **测的是 C++ 源码不是 RTL**，对行/分支覆盖无效 → 这 70% 拿不到。

### Verilator 是开源正解
- Verilator 原生支持：`--coverage-line --coverage-branch --coverage-toggle`，编译期插桩，仿真后产 RTL 覆盖率。
- CLAUDE.md 红线明确允许 Verilator。

### 规则确认（原文逐字核实，非推断）
- spec/scoring **不强制 VCS**：第 5 节环境约束只列 Linux/Python/Z3/PyVerilog，无仿真器要求。
- `coverage_result.json` **是选手自交**，评测器不锁工具重算。铁证：case2 加自定义字段 `all_modules_vcs_coverage`；case4 的 `composite.formula` (0.42/0.28/0.30) 与 scoring.md (0.4/0.3/0.3) 不一致仍当官方示例。
- 罚分项只有「仿真失败/缺项/无 seed/报告不对应 RTL」，**未用 VCS 不是罚分项**。

### 灰色地带（建议问赛方一句）
scoring.md:74「VCS/URG 报告必须对应 RTL」是否隐含必须交 URG 附件。从 case2 能加自定义字段看倾向不用，但可向赛方/助教确认以消除最后不确定性。

## 三、架构

```
run.py                — 入口脚本 (完整流水线: 解析→骨架→序列→仿真→覆盖→报告)
src/
  rtl_parser.py       — RTL 接口解析 (端口/时钟/复位/协议识别)
  skeleton_gen.py     — 验证骨架生成 (cocotb testbench Jinja2 模板)
  constraint_gen.py   — 约束随机测试生成
  coverage_gen.py     — 覆盖率 bin 定义
  sim_runner.py       — 仿真执行器 (cocotb-test + Verilator 后端)
  coverage_collect.py — 覆盖率收集 (Verilator --coverage 解析 + 功能覆盖)
  report_gen.py       — 7 个 JSON 报告生成
templates/
  cocotb_tb.py.j2     — cocotb testbench 模板
requirements.txt      — cocotb, cocotb-test, jinja2 等
```

## 四、覆盖率采集（核心，决定 7 分）

| 类型 | 权重 | 采集方式 |
|------|------|----------|
| 行覆盖 | 0.4 | Verilator `--coverage-line` 编译期插桩 → 仿真后解析 coverage 数据 |
| 分支覆盖 | 0.3 | Verilator `--coverage-branch` 同上 |
| 功能覆盖 | 0.3 | cocotb 测试代码 `coverage.hit(bin)` 采样，FunctionalCoverage 汇总 |

- **综合 C 值公式用 scoring.md 的 0.4/0.3/0.3**（别抄公开示例 case4 的 0.42/0.28/0.30）。
- 三类数字解析后填进 `coverage_result.json` 自交。

## 五、三阶段计划

### Phase 1：骨架门禁（3 分/电路）— 一切前提
- [ ] RTL 解析：端口方向/宽度/时钟/复位/参数
- [ ] 接口协议推断：AXI / SRAM / valid-ready
- [ ] cocotb+Verilator testbench 骨架：时钟/复位/驱动/监视/scoreboard
- [ ] run.py 入口跑通：RTL → testbench → 仿真 → 结果
- [ ] 通过 case1 骨架门禁（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）

### Phase 2：覆盖率收集（7 分/电路）
- [ ] 行/分支：Verilator `--coverage-line+branch` + 解析脚本
- [ ] 功能 bin：cocotb 采样（bin 必须有真实事务触发，**不能空 hit**）
- [ ] 约束随机：5000 序列，固定 seed（`random.Random(seed)` + directed 边界值）
- [ ] 目标：**C ≥ 65% 拿 4.9 分保底**，冲 85% 拿满 7 分

### Phase 3：通用化
- [ ] 处理 10 个隐藏电路（**不能硬编码/针对性优化**，README 红线禁止）
- [ ] 自适应接口驱动策略（AXI/SRAM/valid-ready 各类）

## 六、陷阱清单（执行者必看，审查者必查）

1. **公式**：`coverage_result.json` 写 0.4/0.3/0.3（scoring.md），别抄公开示例 0.42/0.28/0.30。
2. **top_module 不一致**：case1 design.json `top_module="case1"` 但实际模块 `axi_adapter_rd`，靠 wrapper 补。区分「逻辑 top」与「仿真 top」。
3. **bin 真实采样**：仅枚举随机值无采样证据的 bin 不计；别初始化时一次性 hit（case4 公开示例的 backpressure bin 这么做目前判满分，但隐藏评测可能收紧）。
4. **反压**：valid/ready 接口必须设 ready 反压，否则骨架门禁「驱动监视」项失分。
5. **seed 可复现**：无可复现 seed → 覆盖率上限 3 分。`--seed` 必须穿透到 `random.Random`。
6. **scope 限 RTL**：覆盖率报告必须对应当前 RTL 子树，限定范围避免 wrapper 稀释（case1 行覆盖被 wrapper 拉低到 53% 是反面教训）。
7. **Verilator 陷阱**：cocotb-test 配 Verilator 后端；`$fgets`/`$dumpvars` 兼容性需测；关注 Verilator 对部分 Verilog 写法的挑剔。

## 七、验收标准（执行者交活，负责人照此审）

- [ ] `run.sh` 独自跑完整流水线，评测人员无需手改任何生成文件
- [ ] 7 个 JSON 齐全且字段语义正确（design/skeleton/constraints/coverage_bins/functional_coverage/coverage_result/report）
- [ ] testbench 能编译能跑，DUT 端口正确连接，有驱动/监视/scoreboard/反压
- [ ] 固定 seed 可复现
- [ ] 覆盖率报告对应当前 RTL，综合公式 0.4/0.3/0.3
- [ ] case1 跑通：骨架门禁过 + 覆盖率有数（先不追求 85%）

## 八、关键参考

- 公开数据集：`Track-A/A2-verification/testcases/A2_public_dataset/case1-5/`
- case1/case4 的 JSON 格式 = 输出标准；`test_caseN_json_sequences.py` = 评测实际入口
- cocotb 文档：https://docs.cocotb.org/
- cocotb-test（Verilator 后端）：https://github.com/themperek/cocotb-test
- Verilator coverage：https://verilator.org/guide/latest/coverage.html
- 赛题规范：`Track-A/A2-verification/spec.md` + `scoring.md`

## 九、得分预期

- 骨架 3 分：**可控**（cocotb+Verilator+scoreboard 搞定门禁四项）。
- 覆盖率 7 分：行/分支（Verilator 自动采）更可控，功能覆盖（自设计 bin）更难。case4 公开示例 line 96.9 + branch 80.65 + functional 100 → C=92.96% → 满分 7.0。
- 10 电路现实保底：骨架 3 + 覆盖率 4.9 = 7.9 × 10 ≈ 79 分。
