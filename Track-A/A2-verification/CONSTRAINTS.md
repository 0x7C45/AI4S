# A2 验证子题硬约束清单 (CONSTRAINTS.md)

> 适用范围：仅 A2（验证环境自动生成）。A1/A3 不受本文件约束。
> 维护者：A2 负责人。三方实现（mac-CC / win-CC / win-ZCode）一律遵守。
> 上游权威：`spec.md` / `scoring.md` / `testcases/`（官方 locked，不得修改）、`PLAN.md`、`EXECUTOR.md`。
> 冲突裁定：本文件与上游冲突时一律以上游 locked 文件为准，本文件仅汇总，不修订上游。发现冲突提 issue。

---

## 0. 一句话总览

每电路满分 10 = 骨架门禁 3 + 覆盖率 7；**门禁不过一切归零**。10 个电路合计 100 分。
现实保底 ≈ 7.9 × 10 ≈ 79 分（骨架 3 + 覆盖率 4.9）。

---

## 1. 技术路线（不可变）

- **路线锁定**：`cocotb + Verilator`。
- **Verilator 版本锁定 5.050**（具体号，非"5.x"）：`--coverage-line/-toggle` 在不同主版本间行为可能漂移，三方开发与评测环境必须统一此版本。来源 `ENVIRONMENT.md §4`；Docker 路线用官方镜像 `verilator/verilator:v5.050`。
- 覆盖率编译期插桩两标志：`--coverage-line` `--coverage-toggle`，仿真后解析 RTL 行/分支覆盖率（**branch 由 `--coverage-line` 自动产出**；Verilator 5.050 实测无 `--coverage-branch` 标志，原"三标志齐发"为误传）。
  > ✅ **congress 评审已裁决（2026-07-14）**：coverage 命令定标 `--coverage-line --coverage-toggle`（选项 A）。理由：`--coverage-line` 自动产 line+branch（Verilator 官方设计，branch 是 line coverage 结构化副产品）；functional(30%) 靠 cocotb bin，非 Verilator 标志。落地：①`COVERAGE_FLAGS` 参数化（Makefile 顶层变量，默认 A）；②解析器 schema-driven（字段从标志派生）；③coverage 文件头写 `verilator --version`+flags；④Phase1 末单端 C 烟雾测试验 fsm 格式四方一致；⑤functional bin 模板预置（FSM/数据通路/存储器/AXI 4 类，30% 权重杠杆）；⑥评分细则若发布且 branch 解读为真值表则切 B（零代码）。
- **已弃用（严禁在新增代码/文档/注释中出现，PITFALLS 中作为"已弃用"说明除外）**：
  - `iverilog`（仿真器）—— 原生不支持 RTL 行/分支覆盖率，无 `-cm` 等价物。
  - `VCS` / `URG`（仿真器/覆盖率工具）—— spec/scoring 不强制，评测器不锁工具。
  - `gcov` 直接作用于 RTL —— Verilator 路线下 gcov 测的是生成的 C++ 层，不能直接映射回 RTL 行/分支。

---

## 2. 运行入口（run.sh 五参数）

- 必须提供统一入口 `./run.sh`，或等价的 `python3 run.py`。
- **五参数**（缺一不可，命名固定）：

```bash
./run.sh \
  --rtl    benchmark/rtl          # RTL 文件或目录（单/多文件）
  --top    dut                    # 顶层模块名（逻辑 top）
  --out    submission_out/case_name  # 输出目录
  --seed   20260630               # 固定 seed（见 §3）
  --num-seq 5000                  # 约束随机序列数（见 §3）
```

- 必须完成完整流水线：RTL 解析 → testbench 骨架 → 约束随机序列 → 仿真 → 覆盖率收集 → 7 JSON 输出。
- 评测人员不应手动修改任何生成文件；`run.sh` 独自跑通即交活。

---

## 3. 可复现硬约束（seed / num-seq）

| 约束 | 固定值 | 违反后果 |
|---|---|---|
| `--seed` | **20260630**（与 5 个公开 case 一致） | 无可复现 seed 或输入序列 → **覆盖率上限 3 分**（不是 0，但封顶 3） |
| `--num-seq` | **5000**（约束随机序列数） | 评测以 5000 为基准，不得擅自改动 |
| seed 穿透 | `--seed` 必须穿透到 `random.Random(seed)` | 固定 seed + 相同 RTL → 一致或等价结果 |

- 约束随机生成器：`random.Random(seed)` + directed 边界值组合。
- 相同 seed + 相同 RTL 必须产生一致或等价结果（包括激励序列、覆盖率数值）。

---

## 4. 7-JSON 输出契约（顺序 + 自交）

- 输出目录：`<--out>/`（每电路独立结果目录），另需 `generated_tb/` 与 `generated_tests/` 两个目录。
- **7 个 JSON**（生成顺序，缺一即罚分）：

| # | 文件名 | 关键字段 |
|---|---|---|
| 1 | `design.json` | 顶层模块名、RTL 文件列表、时钟/复位信号、端口方向/宽度/类型/协议分组、推断接口协议（AXI/SRAM/valid-ready） |
| 2 | `verification_skeleton.json` | 时钟/复位生成方法、驱动列表、监视列表、DUT 输出、生成的 testbench 源码路径 |
| 3 | `constraints.json` | 固定 seed=20260630、固定总序列数 5000、随机变量列表、覆盖率反馈约束调整记录 |
| 4 | `coverage_bins.json` | Coverpoint 名称、Bin 定义、每个 bin 对应的协议场景/corner case、未覆盖 bin 的反馈记录 |
| 5 | `functional_coverage.json` | 已覆盖 bin 数、有效 bin 总数、功能覆盖百分比、每个 coverpoint 的 bin 命中次数与状态 |
| 6 | `coverage_result.json` | 行覆盖率、分支覆盖率、功能覆盖率、综合覆盖率 C（公式见 §5） |
| 7 | `report.json` | 各阶段成功/失败（解析/骨架/仿真/覆盖率收集）、关键文件路径、覆盖率汇总、可复现命令 |

- **产物自交**：`coverage_result.json` 由选手自交，评测器不锁工具重算（铁证：公开样例 case2 能加自定义字段，case4 公式与 scoring.md 不一致仍当官方示例）。

---

## 5. 覆盖率综合公式（系数锁定）

$$ C = 0.4 \times \text{行} + 0.3 \times \text{分支} + 0.3 \times \text{功能} $$

- 行 + 分支合计占综合分 70%，功能占 30%，三者均用百分比。
- 系数锁定在 `scoring.md`，`coverage_result.json` 必须写 **0.4 / 0.3 / 0.3**。
- **严禁抄公开样例的 0.42 / 0.28 / 0.30**（如在某公开示例见到，一律以 0.4 / 0.3 / 0.3 为准）。

功能覆盖率定义：

$$ \text{功能覆盖率} = \frac{\text{命中次数} > 0 \text{ 的 bin 数}}{\text{有效 bin 总数}} \times 100\% $$

- 一个 bin 被命中多次仅计为一次。
- bin 必须对应可解释的功能场景 / corner case / 协议状态 / 场景组合（详见 §8）。

---

## 6. 覆盖率档位阈值（每电路 7 分上限）

| 综合覆盖率 C | 得分 |
|---|---|
| **C ≥ 85%** | 7.0 分（满分） |
| 65% ≤ C < 85% | 4.9 分（保底档） |
| 45% ≤ C < 65% | 2.8 分 |
| C < 45% | 0 分 |

- 临界提醒：C = 84.99% 落 4.9 档而非 7.0，**临界案例需留余量**，目标冲 85% 以上。

---

## 7. 骨架门禁（3 分失败归零）

每电路 10 分 = 骨架门禁 3 分 + 覆盖率 7 分。**门禁不过，覆盖率不计，整电路 0 分。**

骨架 3 分细分：

| 子项 | 分值 |
|---|---|
| RTL 接口解析（端口方向/宽度/时钟/复位/参数/协议分组） | 0.8 |
| 时钟与复位生成 | 0.6 |
| 输入驱动与输出监视 | 0.8 |
| 自动比对框架（scoreboard） | 0.8 |

**门禁失败条件（任一命中即整电路 0 分，覆盖率不计）**：

1. Testbench 无法编译或仿真无法启动。
2. DUT 端口未连接 / 错连 / 宽度不匹配。
3. 时钟 / 复位 / 关键协议握手不可用。
4. 无有效驱动 / 监视，无法生成或采样事务。
5. 比对器未比对 DUT 行为，或静默忽略比对失败。

---

## 8. 功能 bin 采信标准

- bin 必须对应**可解释的功能场景 / corner case / 协议状态 / 场景组合**，不可凭空枚举。
- bin 必须有**真实事务触发证据**（仿真中真实采样到），**不能空 hit**。
- **禁止初始化时一次性 hit**：公开样例 case1 的 `backpressure`（4 bin）与 case4 的 `ready_valid_backpressure`（3 bin）均以 hits=1 边缘达标（与其他 coverpoint 数百~数千 hits 差 3~4 个数量级），当前判满分，但**隐藏评测可能收紧**（要求 hits 阈值 >1 或更细粒度协议覆盖即掉出），不可依赖此灰色地带。
- 违反：bin 无采样依据 / 不可解析 / 与定义不一致 → **功能覆盖率 = 0%**。

---

## 9. 接口与反压

- 骨架必须支持至少三类接口：**AXI4-Lite / AXI / AXI-like**、**SRAM-like**、**Streaming valid/ready**。
- valid/ready 接口**必须设 ready 反压**，否则骨架门禁"驱动监视"项失分。
- 多文件 RTL 必须保持正确编译顺序和 include 路径，否则 DUT 编译失败 → 覆盖率 = 0。

---

## 10. 覆盖率 scope（避免稀释）

- 覆盖率报告必须**对应当前 RTL 子树**，限定范围避免 wrapper 稀释。
- **反面教训（case1 行覆盖 53%）**：根因是**参数化死码**，**不是 wrapper 稀释**。`case1.v` L215 `always@*` 三分支互斥：
  - L243 `if(SEGMENT_COUNT==1)` 直通路径
  - L302 `else if(EXPAND)` 扩展路径
  - L434 `else` 即 SHRINK 路径（**唯一激活**）
  - 测试配置 `S_DATA=32 / M_DATA=16 → S_STRB=4 / M_STRB=2 → SEGMENT_COUNT=2、EXPAND=0`，使前两分支恒假未激活，`coverage_result.json` 实测 line 168/317=53.0%（149 行未覆盖，死码主体 L243-433 经行过滤后约 130-149 可执行行）。
  - `case1_cocotb_top.v` 是纯结构连线 wrapper（无 always / assign / Clock 生成），自身 LINE/BRANCH 全为 `--`，0 行贡献——**wrapper 不是 53% 的成因**。
  - 启示：测试前需对 RTL 做 `generate/if` 分支静态分析，只对可达分支采 bin，否则会复现 53% 天花板。
- **top_module 陷阱**：`design.json` 的 `top_module` / `name` 字段可能与 RTL 真实模块名不一致。
  - 公开 5 case 全部失配：均填 `caseN`（目录别名），真实模块名分别为 `axi_adapter_rd` / `axis_fifo_adapter` / `axi_vfifo_raw` / `axi_ram` / `axi_crossbar_addr`。
  - 必须自行解析 RTL 真实模块名，**不能直接信任 `design.json` 的 `top_module`**。区分"逻辑 top"与"仿真 top"。

---

## 11. 六条原创性红线（违反任一即取消资格 / 整电路 0 分）

| # | 红线 | 说明 |
|---|---|---|
| 1 | **禁抄袭** | 严禁复制赛题公开样例代码、第三方 IP 验证代码、其他队伍产物。公开数据集只读参考，不可照搬。 |
| 2 | **禁硬编码** | 禁止将激励向量、覆盖率 bin、报告内容直接写死，必须由框架根据 RTL 自动生成。 |
| 3 | **禁绕评测** | 禁止篡改 `run.sh` / `run.py` 入口、伪造仿真通过、伪造 scoreboard 比对结果。 |
| 4 | **禁预计算** | 禁止在评测前预先生成结果 JSON / 覆盖率报告，再在评测时直接输出。必须现场跑流水线。 |
| 5 | **禁针对性优化** | Phase 3 处理 10 个隐藏电路时，**禁止针对特定电路手工优化**激励 / bin / 比对逻辑。策略必须通用、可适配未知 RTL。 |
| 6 | **禁未披露依赖** | 所有第三方依赖（Z3 / PyVerilog / cocotb 等）必须在 `requirements.txt` 声明且**断网可装**：每包钉死精确版本 `==X.Y.Z`，对应 wheel/deb 必须随提交包提供（`submission/wheelhouse/`），评测机 `pip install --no-index --find-links=wheelhouse` 离线装。漏一个依赖 → 仿真失败 → 覆盖率 = 0（双重封杀）。 |

---

## 12. 评测环境约束

- **操作系统**：Linux x86_64。
- **Python**：3.10+ 推荐（本队自锁 3.12.x venv 隔离，`venv/` 不进提交包）。
- **断网评测**：所有第三方依赖须随提交包提供，`requirements.txt` 仅声明不够，需**离线可装**。
- **必交文件（硬约束，漏则断网构建 0 分）**：
  - `requirements.txt`：每包钉死精确版本 `==X.Y.Z`。
  - `wheelhouse/`（或等价离线包目录）：联网机预生成，`pip download -r requirements.txt -d submission/wheelhouse --python-version 3.12 --platform manylinux2014_x86_64 --only-binary=:all:`；评测机 `pip install --no-index --find-links=wheelhouse` 离线装。**禁现场 `pip install` / `apt-get`**（评测机无网络）。
  - `THIRD_PARTY.md`：列明每个第三方依赖的**版本 / 许可证类型 / 调用边界**（直接调用 / 间接依赖 / 仅工具链），供赛方合规审查。
  - 其他必交：`run.sh` / `run.py` / `src/` / `templates/cocotb_tb.py.j2` / `README.md`（离线安装与运行说明）。
- **动态产物不静态打包**：7 个 JSON + `generated_tb/` + `generated_tests/` 由 `run.sh` 在评测机为每 case 动态生成到 `<--out>/`，不随包静态打包，缺一即罚分。
- **评测对象**：10 个独立电路（**隐藏评测**），每电路单独计分，合计 100 分。
- 公开数据集 `testcases/A2_public_dataset/case1-5/` 仅作参考（目录结构 / 报告格式 / cocotb 覆盖率收集流程示范），**只读严禁修改，不参与计分**；隐藏评测使用相同 I/O 约定但 RTL 结构/参数/接口组合/corner case 不同，**不可照搬**。

---

## 13. 三方协同约束（mac-CC / win-CC / win-ZCode）

- **分支命名**：`exec/<instance>`（`exec/mac-cc`、`exec/win-cc`、`exec/win-zcode`）；从 master 拉工作分支，不直接在 master 开发。
- **产物隔离前缀**：`coverage_result.<instance>.json`、`dataset_result.<instance>.json`。
- **大文件**：仿真波形 / 编译产物等不进 repo，仅本地保留；repo 内只提交关键 JSON 产物 + 最终 `run.py` / `src/` 实现。
- **locked 文件**：`spec.md` / `scoring.md` / `testcases/` 严禁修改。
- **PLAN 修改流程**：对 `PLAN.md` 的分歧提 issue，不擅自改 PLAN。
- **commit 风格**：`A2: <描述> (<细节>)`，中文。
- **合并时机**：末段（评测前）合并，由 A2 负责人裁定；可取各方最优段（骨架 / 参考模型 / 覆盖率采集）拼接。
- **里程碑**：M1 骨架 / M2 参考模型+约束随机 / M3 覆盖率 / M4 反馈闭环；完成时在 issue 报进度。
- **三方 OS gap（核心风险）**：mac-CC 为 macOS arm64，win-CC 为 Windows（WSL2），win-ZCode 为 Windows（Docker linux/amd64）。其中 **win-ZCode 主运行环境 = Docker linux/amd64，与评测 OS 同构**，无跨平台漂移风险；mac-CC / win-CC 则需 Docker 复验。Verilator 覆盖率数值（行/分支/toggle）在不同 OS / 架构间可能漂移，跨平台一致性是核心风险。
- **开发与提交策略（覆盖率跨平台复验硬约束）**：
  - mac-CC 开发期用本机 native Verilator 5.050（brew）提速；**提交前必须在 Docker `verilator/verilator:v5.050`（linux/amd64）容器内复跑全部 case**，确认覆盖率与本地无漂移才提交。
  - win-CC 验证环境用 WSL2（原生 linux/amd64，最接近评测 OS）。
  - **win-ZCode 验证环境用 Docker linux/amd64（Windows + Docker Desktop），与评测 OS 完全同构，开发即交付环境**，覆盖率数字直接可用，无需额外平台复验。
  - 三方统一 `linux/amd64` 作为最终覆盖率仲裁平台；Docker 与服务器二选一，不强制 Docker 也不强制 VCS。
  - Fallback：Docker 不可用时回退 `venv3.12 + install.sh`（本机 Verilator 5.050 + 离线 wheelhouse），同样必须在 Linux x86_64 上复验。

---

## 14. 罚分项速查（缺失 / 无效处理）

| 情形 | 后果 |
|---|---|
| 仿真失败 / 挂起 / DUT 编译失败 | 覆盖率 = 0 |
| 缺少某类覆盖率 | 缺失项按 0% 计 |
| 功能 bin 无采样依据 / 不可解析 / 与定义不一致 | 功能覆盖率 = 0% |
| 无可复现 seed 或输入序列 | 覆盖率上限 3 分（封顶 3） |
| 覆盖率报告 / 附件不对应当前提交的 RTL | 覆盖率 = 0 |
| 门禁失败（见 §7 任一条） | 整电路 0 分（覆盖率不计） |
| 抄袭 / 硬编码 / 绕评测 / 预计算 / 针对性优化 / 未披露依赖 | 取消资格或整电路 0 分 |

---

## 15. 冲突裁定优先级（高 → 低）

1. `spec.md` / `scoring.md`（官方 locked，最高）
2. `testcases/` 公开数据集（官方 locked）
3. `PLAN.md`（A2 主计划）
4. `EXECUTOR.md`（三方执行规约）
5. `CONSTRAINTS.md`（本文件，仅汇总不修订上游）

> 本文件与上游冲突时以上游为准。`composite` 公式存在 spec 与公开样例不一致的已知风险点（见 PLAN.md），**一律以 `scoring.md` 的 0.4 / 0.3 / 0.3 为准**。
>
> **灰色待澄清（仿真器中立性）**：`scoring.md:74` 原文"VCS/URG 报告必须对应当前提交的 RTL；cocotb 和纯 Verilog testbench 均可"，是否隐含必须交 URG 附件存在歧义。注：用户提及的"TRACK_A.md A2 §7.3"该文件与章节均不存在，实为 PLAN.md §二"灰色地带（建议问赛方一句）"。从公开样例 case2 能加自定义字段、case4 公式与 scoring.md 不一致仍当官方示例推断，倾向不用 URG；本队走 **cocotb+Verilator** 路线，建议问赛方一句以消除最后不确定性。

---

## 16. 自检清单（提交前必过）

- [ ] `run.sh` 五参数齐全，独自跑通完整流水线，评测人员无需手改任何生成文件。
- [ ] 7 个 JSON 齐全且字段语义正确（顺序见 §4）。
- [ ] `--seed 20260630` 穿透到 `random.Random(seed)`，相同 seed 可复现。
- [ ] `--num-seq 5000`，不擅自改动。
- [ ] testbench 能编译能跑，DUT 端口正确连接，有驱动 / 监视 / scoreboard / **ready 反压**。
- [ ] 覆盖率报告对应当前 RTL 子树（避免 wrapper 稀释）。
- [ ] `coverage_result.json` 综合公式写 **0.4 / 0.3 / 0.3**（不是 0.42 / 0.28 / 0.30）。
- [ ] 功能 bin 有真实事务采样证据（不空 hit，不初始化一次性 hit）。
- [ ] 六条原创性红线全部不触犯。
- [ ] `requirements.txt` 每包钉死 `==X.Y.Z`；`wheelhouse/` 离线包齐全，评测机 `pip install --no-index` 可装，**禁现场 pip / apt**。
- [ ] `THIRD_PARTY.md` 齐全（版本 / 许可证 / 调用边界）。
- [ ] 三方在 Docker `verilator/verilator:v5.050`（linux/amd64）复跑全部 case，覆盖率与本地无漂移才提交。
- [ ] Verilator 版本统一锁定 5.050，三方与评测环境一致。

---

> 版本：v1.2
> 基于：`PLAN.md`（cocotb + Verilator, 2026-07-13）、`EXECUTOR.md` v1.0、`ENVIRONMENT.md`（Verilator 5.050 + Docker linux/amd64 复验）、`spec.md`、`scoring.md`、`testcases/`
> v1.2 变更：§8 一次性 hit 反例补全——原仅提 case4，修正为 case1（`backpressure` 4 bin）+ case4（`ready_valid_backpressure` 3 bin）双案例，并补 coverpoint 准确名称与 hits=1 边缘达标量级证据。其余与 v1.1 一致。
> v1.1 变更：补 Verilator 5.050 版本锁定；§10 case1 53% 根因精化（参数化死码 L215/L243/L302/L434，wrapper 0 贡献）；§12 新增必交文件硬约束（requirements.txt / wheelhouse / THIRD_PARTY.md，禁现场 pip/apt）；§13 新增三方 OS gap 与 Docker linux/amd64 跨平台复验；§15 补 VCS/URG 灰色待澄清；§16 自检清单同步。
> 最后更新：2026-07-13
