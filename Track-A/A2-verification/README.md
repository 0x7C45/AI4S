# A2 验证环境自动生成

> 一句话目标：读取 RTL 设计，自动生成 cocotb testbench + 约束随机测试 + 覆盖率报告，对 10 个独立电路各产出 7 个 JSON + `generated_tb/` + `generated_tests/`，按 `C = 0.4×行 + 0.3×分支 + 0.3×功能` 最大化覆盖率得分。
>
> 技术路线：**cocotb + Verilator**（覆盖率编译期插桩 `--coverage-line --coverage-toggle`；**branch 由 `--coverage-line` 自动产出**，Verilator 5.050 无 `--coverage-branch` 标志）。任何 iverilog / VCS / URG 描述均为过时残留，见文末「已弃用路线」。
>
> ✅ **congress 评审已裁决（2026-07-14）**：coverage 命令定标 `--coverage-line --coverage-toggle`（选项 A）。理由：`--coverage-line` 自动产 line+branch（Verilator 官方设计，branch 是 line coverage 结构化副产品）；functional(30%) 靠 cocotb bin，非 Verilator 标志。落地：①`COVERAGE_FLAGS` 参数化（Makefile 顶层变量，默认 A）；②解析器 schema-driven（字段从标志派生）；③coverage 文件头写 `verilator --version`+flags；④Phase1 末单端 C 烟雾测试验 fsm 格式四方一致；⑤functional bin 模板预置（FSM/数据通路/存储器/AXI 4 类，30% 权重杠杆）；⑥评分细则若发布且 branch 解读为真值表则切 B（零代码）。

---

## 1. 三方分工入口

三路独立竞赛，末段由 A2 负责人裁定合并。基线统一为 [PLAN.md](./PLAN.md)。

| 实例 | 平台 / 工具 | 角色 | 工作分支 |
|---|---|---|---|
| **mac-CC** | macOS / Claude Code | 独立实现 A2 全流水线；定期把本机进度/发现/坑同步给另外两方 | `exec/mac-cc` |
| **win-CC** | Windows / Claude Code | 独立实现 A2 全流水线 | `exec/win-cc` |
| **win-ZCode** | Windows / ZCode | 独立实现 A2 全流水线 | `exec/win-zcode` |

约定：
- 三方各自从 `master` 拉工作分支，**不直接在 `master` 上开发**。
- 产物命名前缀隔离：`coverage_result.<instance>.json`、`dataset_result.<instance>.json`；仿真波形 / 编译产物等大文件不进 repo，仅本地保留。
- 末段合并可取各方最优段（骨架 / 参考模型 / 覆盖率采集）拼接，由负责人操作合并到 `master`。
- 里程碑：**M1 骨架 → M2 参考模型+约束随机 → M3 覆盖率 → M4 反馈闭环**，完成时在 issue 报进度。
- commit 风格：`A2: <描述> (<细节>)`，中文。

---

## 2. 运行入口（run.sh 五参数）

统一入口必须提供 `./run.sh` 或等价的 `python3 run.py`，评测人员不应手动修改生成文件。

```bash
./run.sh \
  --rtl benchmark/rtl \
  --top dut \
  --out submission_out/case_name \
  --seed 20260630 \
  --num-seq 5000
```

| 参数 | 含义 | 默认 / 约定 |
|---|---|---|
| `--rtl` | RTL 源目录（单文件或多文件，需保持编译顺序与 include 路径） | 必填 |
| `--top` | 顶层模块名（可由参数给出或从 RTL 中识别） | 必填 |
| `--out` | 单电路结果目录 `submission_out/case_name/` | 必填 |
| `--seed` | 固定随机种子，**必须穿透到 `random.Random(seed)`**；公开 case 统一 `20260630` | `20260630` |
| `--num-seq` | 约束随机序列数，**固定 5000**，不得擅自改动 | `5000` |

> seed 硬约束：无可复现 seed 或输入序列 → 覆盖率上限仅 3 分；相同 seed + 相同 RTL 必须产生一致或等价结果。

---

## 3. 七个输出 JSON 契约（速查）

每个电路独立结果目录 `submission_out/case_name/` 下，按流水线顺序产出：

| # | 文件 | 一句话说明 |
|---|---|---|
| 1 | `design.json` | RTL 解析结果：顶层模块名、文件列表、时钟/复位信号、端口方向/宽度/类型/协议分组、推断接口协议（AXI / SRAM / valid-ready） |
| 2 | `verification_skeleton.json` | testbench 骨架元信息：时钟复位生成方法、驱动列表及负责接口、监视列表及采样时机、DUT 输出、生成的 testbench 源码路径 |
| 3 | `constraints.json` | 约束随机配置：固定 seed、固定总序列数 (5000)、随机变量列表、覆盖率反馈约束调整记录 |
| 4 | `coverage_bins.json` | 功能 bin 定义：Coverpoint 名、Bin 定义、每个 bin 对应的协议场景 / corner case、未覆盖 bin 反馈记录 |
| 5 | `functional_coverage.json` | 功能覆盖结果：已覆盖 bin 数、有效 bin 总数、功能覆盖百分比、每个 coverpoint 的 bin 命中次数与状态 |
| 6 | `coverage_result.json` | 三类覆盖率与综合：行覆盖率、分支覆盖率、功能覆盖率、按评分公式算的综合 C（**选手自交，评测器不重算**） |
| 7 | `report.json` | 流水线报告：各阶段（解析/骨架/仿真/覆盖率）成功失败、关键输出文件路径、覆盖率汇总、可复现命令 |

另需产出两个目录：`generated_tb/`（生成的 testbench 源码）与 `generated_tests/`（生成的约束随机测试序列）。

> bin 真实采样硬约束：功能 bin 必须有真实事务触发证据，**不能空 hit，不能初始化时一次性 hit**；仅枚举随机值而无采样证据的 bin 不计。

---

## 4. 评分契约速查

- **总分 100 = 10 个隐藏电路 × 每电路 10 分**；每电路 = 骨架门禁 3 分 + 覆盖率 7 分。
- **覆盖率综合公式（以 `scoring.md` 为准，锁定 0.4 / 0.3 / 0.3）**：

  ```
  C = 0.4 × 行覆盖率 + 0.3 × 分支覆盖率 + 0.3 × 功能覆盖率
  ```

  行 + 分支合计占综合分 70%，功能占 30%，三者均用百分比。**禁止抄公开样例 case4 的 `0.42 / 0.28 / 0.30`**（该样例 `composite.formula` 与 `scoring.md` 不一致，是已知风险点）。

- **档位阈值**：

  | C | 覆盖率得分 |
  |---|---|
  | `C ≥ 85%` | 7.0（满分） |
  | `65% ≤ C < 85%` | 4.9 |
  | `45% ≤ C < 65%` | 2.8 |
  | `C < 45%` | 0 |

  现实保底策略：10 电路稳定到 `C ≥ 65%` 档 ≈ `4.9 × 10 ≈ 49` 分（覆盖率）+ 骨架门禁通过 ≈ 总分 **79 分量级**。

- **门禁归零**：骨架是硬门禁，命中任一条（testbench 无法编译 / 仿真无法启动；DUT 端口未连接或错连或宽度不匹配；时钟 / 复位 / 关键协议握手不可用；无有效驱动 / 监视；比对器未比对或静默忽略失败）→ 该电路 **0 分，覆盖率不计**。

---

## 5. 快速上手

```bash
# 1. 切到自己的工作分支（勿直接用 master）
git checkout master && git pull
git checkout -b exec/mac-cc      # win-CC → exec/win-cc；win-ZCode → exec/win-zcode

# 2. 跑公开 case（只读，勿改 testcases/）
./run.sh \
  --rtl testcases/A2_public_dataset/case4/rtl \
  --top case4 \
  --out submission_out/case4 \
  --seed 20260630 \
  --num-seq 5000

# 3. 检查 7 个 JSON + generated_tb/ + generated_tests/ 是否齐备
ls submission_out/case4/

# 4. 核对 coverage_result.json 的 composite.formula 必须是 0.4/0.3/0.3
# 5. 核对 coverage_result.json 的报告范围对应当前 RTL 子树（不含 wrapper 稀释）
```

公开数据集 `testcases/A2_public_dataset/case1~case5`（只读，**严禁修改**）作参考标杆（VCS 测得）：

| case | 真实 RTL 模块 | line | branch | func | composite† | seq | 备注 |
|---|---|---|---|---|---|---|---|
| case1 | `axi_adapter_rd` | 53.0% | 48.33% | 100% | 65.79 | 5000 | 参数化死码拉低行覆盖，非 wrapper 稀释 |
| case2 | `axis_fifo_adapter` | 59.74% | 63.01% | 92.86% | 70.59 | 7403 cycles | 唯一非 cocotb（plain verilog vector），schema 需兼容 |
| case3 | `axi_vfifo_raw` | 93.48% | 87.61% | 100% | 93.79 | 256 | 三时钟域，激励效率高 |
| case4 | `axi_ram` | 96.90% | 80.65% | 100% | 93.28 | 5000 | line 最高，`$error` 校验分支结构性未覆盖 |
| case5 | `axi_crossbar_addr` | 87.68% | 88.37% | 100% | 91.57 | 5000 | — |

> † `composite` 源自公开样例各 case `coverage_result.json` 的 `coverage.composite.value`，按**公开样例系数** `0.42×line + 0.28×branch + 0.30×func` 算得（5 case 完全一致）。**本队锁定 `0.4 / 0.3 / 0.3`**（以 `scoring.md` 为准），`coverage_result.json` 必须写本队系数，禁抄样例 `0.42 / 0.28 / 0.30`，详见 [CONSTRAINTS.md](./CONSTRAINTS.md) §5。

> 公开 case 仅 5 个，隐藏评测 10 个，结构与参数不同，**不可照搬**。`design.json` 的 `top_module` 字段填的是目录别名 `caseN`，与 RTL 真实模块名不一致 — 需自行解析真实模块名，不能盲信 `design.json`。

---

## 6. 相关文档导航

| 文档 | 状态 | 位置 |
|---|---|---|
| **PLAN.md** | 已存在 | [./PLAN.md](./PLAN.md) — cocotb + Verilator 路线、决策依据、陷阱清单（第七节） |
| **EXECUTOR.md** | 已存在 | [./EXECUTOR.md](./EXECUTOR.md) — 三方分工、产物隔离、合并裁定、提交约定 |
| **CONSTRAINTS.md** | 已存在 | [./CONSTRAINTS.md](./CONSTRAINTS.md) — A2 硬约束汇总：run.sh 五参数、seed / num-seq 锁定、公式 `0.4 / 0.3 / 0.3`、门禁、原创性红线（仅汇总不修订上游） |
| **ENVIRONMENT.md** | 已存在 | [./ENVIRONMENT.md](./ENVIRONMENT.md) — 运行环境：Linux x86_64 + 断网、Docker 主推、Verilator 5.050 锁定、依赖离线打包、必交文件清单 |
| **PITFALLS** | 散落在官方文件 | `PLAN.md` 第七节陷阱清单 + 本文 §8；scoring.md 罚分项 |
| **spec.md** 🔒 | locked | [./spec.md](./spec.md) — 赛题官方，**三方不得修改** |
| **scoring.md** 🔒 | locked | [./scoring.md](./scoring.md) — 评分官方，**三方不得修改** |
| **testcases/** 🔒 | locked | [./testcases/](./testcases/) — 公开数据集，**只读严禁修改** |

> 对 `PLAN.md` 的分歧提 issue，**不擅自改 PLAN**。`spec.md / scoring.md / testcases/` 为赛题官方内容，三方一律不得修改。

---

## 7. 运行环境与必交文件

**评测 OS（权威）**：Linux x86_64 + 断网，依赖全打包（漏一个 = 0 分）。详见 [ENVIRONMENT.md](./ENVIRONMENT.md)。

**运行环境（本队策略）**：

| 角色 | 主推环境 | 说明 |
|---|---|---|
| 三方统一 | **Docker**：`verilator/verilator:v5.050`，`linux/amd64` | 与评测 OS 同构，作为覆盖率跨平台一致性基准；mac-CC 提交前**必须**在容器内复跑全部 case，无漂移才提交 |
| mac-CC | 开发期：本机 native Verilator（brew 5.050）提速 | macOS arm64 与 linux/amd64 行 / 分支覆盖可能漂移，提交前以 Docker 复验为准 |
| win-CC | WSL2（原生 linux/amd64） | 最接近评测 OS |
| win-ZCode | **Docker linux/amd64**（Windows + Docker Desktop） | 与评测 OS 完全同构，开发即交付环境，覆盖率数字直接可用，无需额外平台复验 |
| fallback | venv3.12 + `install.sh` | Docker 不可用时使用 |

> Verilator 版本**锁定 5.050**（`--coverage-line/-toggle` 在不同主版本间行为可能漂移）。`spec / scoring` 不强制 Docker 也不强制 VCS；本队走 cocotb + Verilator 路线。

**必交文件清单**（详见 [ENVIRONMENT.md](./ENVIRONMENT.md) §7、[CONSTRAINTS.md](./CONSTRAINTS.md) §11 红线#6）：

- `requirements.txt` — 每包钉死精确版本 `==X.Y.Z`（cocotb / cocotb-test / jinja2 / Z3 / PyVerilog 等）。
- `THIRD_PARTY.md` — 第三方依赖的**版本 / 许可证 / 调用边界**声明（用户决策必交）。
- `wheelhouse/` — 联网机用 `pip download --platform manylinux2014_x86_64 --only-binary=:all:` 预生成；评测机 `pip install --no-index --find-links=wheelhouse` 离线装。
- `run.sh` / `run.py` / `src/` / `templates/cocotb_tb.py.j2` / `README.md`（离线安装运行说明）。
- 7 个 JSON + `generated_tb/` + `generated_tests/` **不静态打包**，由 `run.sh` 在评测机动态生成到 `submission_out/<case>/`。

> 原创性红线#6「禁未披露依赖」：未在 `requirements.txt` 声明或断网不可装 → 取消资格 / 整电路 0 分；依赖缺失还会触发仿真失败 → 覆盖率 0（双重封杀）。

---

## 8. 红线与已弃用路线

**原创性红线（Phase 3 隐藏电路）**：处理 10 个隐藏电路时**禁止硬编码 / 针对性优化**，必须走通用化解析-生成-采集流水线。

**关键陷阱速记**：
- **公式系数**：`coverage_result.json` 必须写 `0.4 / 0.3 / 0.3`（`scoring.md`），绝不能抄公开样例 case4 的 `0.42 / 0.28 / 0.30`。
- **top_module**：`design.json` 的 `top_module`（目录别名 `caseN`）与 RTL 真实模块名不一致，需区分「逻辑 top」与「仿真 top」。
- **bin 采样**：仅枚举随机值无采样证据的 bin 不计；初始化时一次性 hit 公开样例判满分但隐藏评测可能收紧。
- **反压**：valid / ready 接口必须设 ready 反压，否则骨架门禁「驱动监视」项失分。
- **seed 穿透**：`--seed` 不穿透到 `random.Random(seed)` → 覆盖率上限仅 3 分。
- **覆盖率 scope**：覆盖率报告必须对应当前 RTL 子树，限定范围避免 wrapper 稀释。
- **Verilator 兼容**：`$fgets` / `$dumpvars` 兼容性需测；Verilator 对部分 Verilog 写法挑剔。

**已弃用路线（仅作历史说明，禁止在产物与文档主体中出现）**：
- `cocotb + iverilog + gcov`：iverilog 原生不支持 RTL 行 / 分支覆盖率，gcov 测的是 C++ 源码而非 RTL → 行 / 分支 70% 拿不到。`TEAM_GUIDE.md` A2 节仍残留此旧方案，以 `PLAN.md` 为准。
- VCS / URG：`spec / scoring` 不强制 VCS，未用 VCS 不是罚分项；公开 case 用 VCS 测得的数据仅作标杆参考，本路线采用 Verilator 原生覆盖率（`--coverage-line --coverage-toggle` + `verilator_coverage` 合并）。

---

## 9. 离线安装与运行（win-ZCode 提交包）

### 9.1 离线依赖安装（评测机断网）

`wheelhouse/` 目录预生成 manylinux2014_x86_64 wheel（cocotb/cocotbext-axi/jinja2/pyverilog 等 7 包），评测机断网时离线安装：

```bash
# 镜像 verilator/verilator:v5.050 无 pip，需先 bootstrap
apt-get update && apt-get install -y python3-pip python3-venv 2>/dev/null || true
python3 -m ensurepip 2>/dev/null || true

# 离线安装（不联网）
pip3 install --no-index --find-links=wheelhouse -r requirements.txt
```

### 9.2 运行（Docker linux/amd64）

```bash
# Docker 容器内执行完整流水线
./run.sh \
  --rtl benchmark/rtl \
  --top dut \
  --out submission_out/case_name \
  --seed 20260630 \
  --num-seq 5000
```

### 9.3 必交文件清单

- `run.sh` / `run.py` — 统一入口
- `src/` — 7 模块（rtl_parser/skeleton_gen/sim_runner/constraint_gen/coverage_gen/coverage_collect/report_gen/dead_code_analyzer）
- `templates/cocotb_tb.py.j2` — cocotb testbench 模板
- `requirements.txt` — 锁版本依赖
- `wheelhouse/` — 离线 wheel 包（manylinux2014_x86_64）
- `THIRD_PARTY.md` — 第三方依赖版本/许可/调用边界
- `README.md` — 本文件（离线安装运行说明）
