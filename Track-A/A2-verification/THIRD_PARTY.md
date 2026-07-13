# THIRD_PARTY.md — A2 验证子题第三方依赖披露

> 本文件满足官方 `spec.md §5`「允许 Z3 / PyVerilog 等开源库（必须声明依赖）」「若有额外依赖需提供 requirements.txt」的披露要求，并满足项目级断网评测约束（所有第三方依赖须随提交包提供，评测机无网络）。
>
> 关联文档：[ENVIRONMENT.md](./ENVIRONMENT.md) §2 / §3 / §4 / §5（运行时与依赖清单权威；实际章节为 §1 硬约束 / §2 开发环境菜单 / §3 锁版本表 / §4 离线打包 / §5 风险与验证）、[CONSTRAINTS.md](./CONSTRAINTS.md) §11 红线 #6（禁未披露依赖）、[PLAN.md](./PLAN.md) §三（技术栈）。
>
> 冲突裁定优先级：`spec.md` / `scoring.md` / `testcases/`（官方 locked，最高）> 本队 `PLAN.md` > `EXECUTOR.md` > `CONSTRAINTS.md` > `ENVIRONMENT.md` > 本文件。

---

## 1. 依赖总览

| # | 依赖 | 类别 | 版本（锁定） | 许可证 | 是否打包进提交包 | 调用边界（一句话） |
|---|------|------|--------------|--------|------------------|--------------------|
| 1 | **Python** | 运行时语言 | **3.12.x**（本队自锁；官方仅推荐 3.10+） | PSF-2.0 | 否（评测机自带） | 整个流水线实现语言 |
| 2 | **cocotb** | Python 包 | **==1.8.1** | MIT | 是（离线 wheel） | 验证框架主体，驱动 RTL 仿真、采样功能覆盖 bin |
| 3 | **cocotb-test** | Python 包 | `==X.Y.Z`（M1 锁定，见 §5） | MIT | 是（离线 wheel） | cocotb 的 Python 测试入口，配 Verilator 后端（`SIM=verilator`） |
| 4 | **cocotbext-axi** | Python 包 | `==X.Y.Z`（M1 锁定，防 issue #119） | MIT | 是（离线 wheel） | AXI4 / AXI4-Lite / AXI-Stream 接口驱动与监视 |
| 5 | **Jinja2** | Python 包 | `==X.Y.Z`（M1 锁定） | BSD-3-Clause | 是（离线 wheel） | 渲染 `templates/cocotb_tb.py.j2`，生成 testbench 骨架与 7-JSON |
| 6 | **PyVerilog** | Python 包 | `==X.Y.Z`（M1 锁定） | MIT | 是（离线 wheel） | RTL 解析（`spec.md §5` 明确允许的开源库） |
| 7 | **Z3** (`z3-solver`) | Python 包 | **>=4.12**（下限锁） | MIT | 是（离线 wheel） | 约束随机求解（`spec.md §5` 明确允许的开源库） |
| 8 | **Verilator** | 系统二进制 | **5.050**（硬锁，见 §5） | LGPL-3.0 或 Artistic-2.0（双许可） | 否（评测机自带；若赛方不提供，README 注明须 = 5.050） | 仿真器 + 覆盖率插桩 |

> **版本号说明**：
> - 已硬锁（来自本队两轮调查确认）：`cocotb==1.8.1`、`z3-solver>=4.12`、`Verilator==5.050`、`Python==3.12`。
> - 标注 `X.Y.Z` 的包：依 `ENVIRONMENT.md §5` / `CONSTRAINTS.md §11` 红线 #6，须在 `requirements.txt` 钉死精确版本 `==X.Y.Z`；具体号在 M1 骨架阶段于 Verilator 5.050 容器内复验后填入并冻结，三方（mac-CC / win-CC / mac-Codex）对齐。
> - `cocotbext-axi` 锁版本须规避上游 issue #119（与 cocotb / Python 版本兼容性相关），M1 选版时显式回归。

---

## 2. 逐项详情

### 2.1 Python 3.12（运行时）

- **版本**：3.12.x（本队 `ENVIRONMENT.md §3` 自锁；官方 `spec.md §5` 仅「推荐 3.10+」）。venv 隔离，目录名 `venv/` **不进提交包**。
- **许可证**：Python Software Foundation License 2.0（PSF-2.0，宽松，商用友好）。
- **调用边界**：整个 A2 流水线的实现语言；入口 `run.py` / `run.sh`、`src/` 七模块、cocotb testbench、覆盖率后处理脚本均为 Python。
- **打包**：不打包。评测机自带 Python 3.12（由赛方提供或 README 注明前置条件）。`requirements.txt` 锁定 `--python-version 3.12` 拉取 wheel。

### 2.2 cocotb 1.8.1（验证框架主体）

- **版本**：**==1.8.1**（本队两轮调查锁定）。
- **许可证**：MIT。
- **锁版本理由**：
  - cocotb 1.8.1 与 Verilator 5.050 经官方手册核对兼容；若升 cocotb 2.0 须 Verilator ≥ 5.036 且须同步锁 cocotbext-axi 防 issue #119，本队不承担此升级风险，故停在最稳的 1.8.1。
  - cocotb 主版本升级会改变 VPI 接口与 `coverage` API 语义，威胁跨平台覆盖率一致性。
- **调用边界**：
  - 验证框架主体，将 Python 测试代码经 VPI/FLI 驱动 Verilator 编译后的 RTL。
  - 在生成的 testbench 中以固定 `--seed 20260630`、`--num-seq 5000` 驱动约束随机事务；`seed` 必须穿透到 `random.Random(seed)`，否则该电路覆盖率上限 3 分（scoring.md §2）。
  - 功能覆盖率由 cocotb 测试代码内对**真实事务**采样（综合公式中功能权重 0.3）；禁止空 hit、禁止初始化期一次性 hit（公开样例 case1/case4 的 backpressure bin `hits=1` 边缘达标是脆弱性来源，隐藏评测可能收紧）。
- **打包**：是，随提交包离线 wheel 提供（目录名见 §4）。

### 2.3 cocotb-test（cocotb 的 Python 测试入口）

- **版本**：`==X.Y.Z`，M1 锁定（须与 cocotb 1.8.1 兼容）。
- **许可证**：MIT。
- **调用边界**：cocotb 的 pytest 风格入口，在本项目中**配 Verilator 后端**（`SIM=verilator`），由 `src/sim_runner` 调用以编译并启动仿真。
- **打包**：是，随提交包离线 wheel 提供。

### 2.4 cocotbext-axi（AXI 接口驱动）

- **版本**：`==X.Y.Z`，M1 锁定。**选版时必须显式回归 issue #119**（上游已知兼容性问题，与 cocotb / Python 版本耦合），确认在 cocotb 1.8.1 + Python 3.12 下无回归才冻结。
- **许可证**：MIT。
- **调用边界**（依 `ENVIRONMENT.md §5` 说明）：
  - 负责 `spec.md §2` 三类接口中的**前两类 + AXI-Stream 子集**：AXI4-Lite / AXI / AXI-like、AXI-Stream。
  - **SRAM-like 与通用 valid/ready Streaming 由本队自实现驱动覆盖**，不依赖此库。
  - valid/ready 接口必须设 `ready` 反压，否则骨架门禁「驱动监视」项失分（scoring.md §1）。
- **披露说明**：此库未在 `PLAN.md §三` 具名，但属实现层必要依赖；`ENVIRONMENT.md §5` 已将其纳入 `requirements.txt` 清单。本文件与之保持一致。
- **打包**：是，随提交包离线 wheel 提供。

### 2.5 Jinja2（模板引擎）

- **版本**：`==X.Y.Z`，M1 锁定。
- **许可证**：BSD-3-Clause。
- **调用边界**：渲染 `templates/cocotb_tb.py.j2`，由 `src/skeleton_gen` 调用，生成 testbench 骨架与 7 个 JSON 产物中的 `verification_skeleton.json`（7-JSON 顺序：design → skeleton → constraints → coverage_bins → functional_coverage → coverage_result → report）。
- **打包**：是，随提交包离线 wheel 提供。

### 2.6 PyVerilog（RTL 解析）

- **版本**：`==X.Y.Z`，M1 锁定。
- **许可证**：MIT。
- **调用边界**：`spec.md §5` 明确允许的开源库。由 `src/rtl_parser` 调用，解析 RTL 接口（端口方向/宽度/时钟/复位/参数/接口协议分组），输出 `design.json`。多文件 RTL 须保持正确编译顺序与 include 路径，否则触发骨架门禁失败（编译失败 → 整电路 0 分）。
- **打包**：是，随提交包离线 wheel 提供。

### 2.7 Z3（`z3-solver`，约束求解）

- **版本**：**>=4.12**（下限锁，本队两轮调查确认）。
- **许可证**：MIT。
- **调用边界**：`spec.md §5` 明确允许的开源库。由 `src/constraint_gen` 调用，生成约束随机测试策略（固定 seed=20260630、固定总序列数 5000、随机变量列表），输出 `constraints.json`，并支持覆盖率反馈驱动的约束调整。
- **打包**：是，随提交包离线 wheel 提供。注意 z3-solver 含原生扩展，须确保 `manylinux2014_x86_64`（或 `linux/amd64`）wheel 可用（见 §4）；若无预编译 wheel，须 vendored 源码 + README 注明编译前置条件。

### 2.8 Verilator 5.050（仿真器 + 覆盖率插桩，系统二进制）

- **版本**：**5.050**（硬锁，具体号而非「5.x」）。
- **许可证**：LGPL-3.0 或 Artistic-2.0（双许可，使用者可选其一）。
- **调用边界**（依 `ENVIRONMENT.md §4`）：
  - 仿真器：编译 RTL（`verilator --cc --build ...`），由 cocotb 经 VPI 驱动。
  - 覆盖率插桩：编译期三标志齐发 `--coverage-line --coverage-branch --coverage-toggle`；仿真后由 `verilator_coverage` 合并 `coverage.dat`，交 `src/coverage_collect` 解析为行/分支覆盖率。
  - 综合覆盖率公式以 `scoring.md` 为准：**C = 0.4×行 + 0.3×分支 + 0.3×功能**（严禁抄公开样例 case4 的 0.42/0.28/0.30）。
- **覆盖率口径注记（case1 line=53% 根因）**：公开样例 case1 行覆盖 53%（168/317）经本队查清为 **RTL 参数化死码**，非 Verilator 依赖问题、也非 wrapper 稀释——`case1.v` L215 `always @*` 三分支（L243 `if(SEGMENT_COUNT==1)` 直通 / L302 `else if(EXPAND)` 扩展 / L434 `else` SHRINK 激活），配置 `S_DATA=32 / M_DATA=16` 使前两分支恒假，L243–L433 约 139–149 可执行行成死码；`case1_cocotb_top.v` 为纯结构连线（无 `always`/`assign`/Clock 生成），LINE/BRANCH 全为 `--`，0 行贡献。故 Verilator 覆盖率口径可信，本队按现状使用，不切换工具链。
- **打包**：**否**，作为系统二进制由评测机自带。若赛方不提供，须在 README 注明 `verilator --version` 必须输出 5.050。本队不把 Verilator 二进制打入离线 wheel 目录。
- **版本锁理由**：见 §5.2。

---

## 3. 依赖与 7-JSON 产物的映射（调用边界速查）

| 依赖 | 主要驱动的阶段 / 产物 |
|------|----------------------|
| PyVerilog + Z3 | RTL 解析 → `design.json`；约束随机 → `constraints.json` |
| Jinja2 | testbench 骨架生成 → `verification_skeleton.json`、`generated_tb/` |
| cocotbext-axi + cocotb | 驱动事务、采样功能 bin → `coverage_bins.json`、`functional_coverage.json`、`generated_tests/` |
| cocotb-test + Verilator | 仿真执行 + 行/分支覆盖率插桩 → `coverage_result.json`（行/分支来自 Verilator，功能来自 cocotb） |
| （本队自研）`src/report_gen` | 汇总 → `report.json` |

> 7 个 JSON 产物 + `generated_tb/` + `generated_tests/` **不静态打包**进提交包，由 `run.sh` 在评测机为每个 case 动态生成到 `submission_out/<case_name>/`。

---

## 4. 打包与离线安装策略（断网评测）

依 `ENVIRONMENT.md §4`（离线打包方案）/ `§5`（风险与验证）：评测机**无网络**，`requirements.txt` 仅声明依赖不够，所有 Python 包必须随提交包提供且离线可装。

> **目录命名说明**：本队离线 wheel 目录在 `ENVIRONMENT.md §4`（§4.1 / §4.2）写作 `offline_pkgs/`，在 `CONSTRAINTS.md §11` 红线 #6 / `§12` / `README.md` §7 写作 `submission/wheelhouse/`，二者**同义**。以 `ENVIRONMENT.md §4`（离线打包专节）为命名权威，提交包实际目录用 `offline_pkgs/`；本文件下文统称「离线 wheel 目录」。

```bash
# 中文注释：在联网开发机上生成离线 wheel，供评测机离线安装（目录名以 ENVIRONMENT.md §4 为准）
mkdir -p offline_pkgs   # 或 submission/wheelhouse，二者等价
pip download -r requirements.txt -d offline_pkgs/ \
    --python-version 3.12 \
    --platform manylinux2014_x86_64 \
    --only-binary=:all:

# 评测机离线安装命令（写入 run.sh 前置或 README）
pip install --no-index --find-links=offline_pkgs/ -r requirements.txt
```

- `--platform manylinux2014_x86_64 --only-binary=:all:`：锁 Linux x86_64（评测 OS），与三方开发机架构解耦（mac-CC / mac-Codex 为 macOS arm64，win-CC 为 Windows，均非评测 OS）。
- 若存在必须源码编译的依赖（如 z3-solver 在个别平台无预编译 wheel），需一并 vendored 进离线 wheel 目录，并在 README 注明编译前置条件。
- **Verilator 二进制不打入离线 wheel 目录**，由评测机自带。

---

## 5. 版本锁定策略与复验要求

### 5.1 为何钉死精确版本

- `CONSTRAINTS.md §11` 红线 #6「禁未披露依赖」：所有第三方依赖须在 `requirements.txt` 声明且断网可装，违反 → 取消资格 / 整电路 0 分；依赖缺失还会导致仿真失败 → 覆盖率 = 0（双重封杀）。**漏一个 = 0 分。**
- 三方开发机架构各异（macOS arm64 / Windows / Linux），依赖随机升级会引入跨平台行为漂移，威胁覆盖率一致性（覆盖率跨平台一致性是 A2 命脉，见 `ENVIRONMENT.md §1`）。

### 5.2 Verilator 为何硬锁 5.050；cocotb 为何停在 1.8.1

- **Verilator 5.050**：`--coverage-line / --coverage-branch / --coverage-toggle` 三标志的插桩与 `coverage.dat` 输出格式在不同主版本间可能漂移；锁定具体号而非「5.x」，保证三方复跑与评测机产出同一口径的行/分支覆盖率。Ubuntu 24.04 apt 仅到 5.020，**须源码 `git checkout v5.050` 自编**或用官方 Docker 镜像 `verilator/verilator:5.050`。
- **cocotb 1.8.1**：与 Verilator 5.050 官方手册核对兼容；升 cocotb 2.0 须 Verilator ≥ 5.036 且须锁 cocotbext-axi 防 issue #119。停在 1.8.1 是兼容性与覆盖率口径稳定性的折中。
- 安装方式（`ENVIRONMENT.md §3 / §4`）：mac 可 `brew install verilator`（若版本不符则源码自编）；win-CC 用 WSL2（原生 linux/amd64，最接近评测 OS）；提交前必须在 Docker `verilator/verilator:5.050`（`--platform linux/amd64`）容器内复跑全部 case 验证覆盖率一致性，无漂移才提交。

### 5.3 Python 包版本复验流程（M1 阶段）

1. 选定起始稳定版本写入 `requirements.txt`（`==X.Y.Z`）；cocotb 已锁 1.8.1、z3-solver 下限 4.12。
2. 对 cocotbext-axi 候选版本显式回归 issue #119，确认 cocotb 1.8.1 + Python 3.12 下无回归。
3. 在 Verilator 5.050 容器内跑通 case1 骨架门禁（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）。
4. 跑 5 个公开 case 验证覆盖率与三方一致。
5. 冻结版本，三方对齐，回填本文件 §1 占位，后续不得擅改。

---

## 6. 许可证合规说明

| 许可证 | 涉及依赖 | 合规要点 |
|--------|----------|----------|
| MIT | cocotb、cocotb-test、cocotbext-axi、PyVerilog、Z3 | 宽松，保留版权声明即可。本队分发提交包时随包保留各 wheel 自带 LICENSE。 |
| BSD-3-Clause | Jinja2 | 宽松，保留版权声明。 |
| PSF-2.0 | Python | 宽松，商用友好。 |
| LGPL-3.0 / Artistic-2.0（双许可） | Verilator | **作为系统二进制由评测机自带，本队不分发 Verilator 二进制**，仅调用其 CLI；如需分发须遵 LGPL 动态链接例外或 Artistic 条款。 |

> 本提交包为竞赛用途，不商用闭源分发；所有依赖许可证均兼容。离线 wheel 目录内随包保留各 wheel 自带许可证元数据。

---

## 7. 已弃用路线（仅作说明，不作为依赖）

> 下列工具/路线**已弃用**，不在依赖清单内；实现层（源码/配置/commit message/JSON 字段）不得将 iverilog / gcov / VCS / URG 作为实际依赖或硬编码路线，文档层（本文件 §9 待澄清项 / `PITFALLS.md` 弃用说明）的技术对比除外。

- **iverilog**：原 `cocotb + iverilog + gcov` 方案已于 2026-07-13 切换为 `cocotb + Verilator`（`PLAN.md` line 3、`CONSTRAINTS.md §1` 技术路线不可变）。弃用根因：iverilog 原生不支持 RTL 行/分支覆盖率，gcov/lcov 测的是 C++ 源码而非 RTL，行/分支 70% 权重拿不到。
- **gcov / lcov**：Verilator 路线下改用 `--coverage-line/--coverage-branch/--coverage-toggle` + `verilator_coverage` 合并 `coverage.dat`；gcov 仅在调试 C++ 层时可选，**不作为评分口径**。
- **VCS / URG**：`spec.md §5` 不强制 VCS，罚分项只有「仿真失败 / 缺项 / 无 seed / 报告不对应 RTL」，**未用 VCS 不是罚分项**。本队走 cocotb + Verilator 路线；`scoring.md:74` 的 VCS/URG 措辞属官方对仿真器中立的描述，非强制。

---

## 8. 与项目其它文件的同步关系

| 文件 | 关系 | 同步要求 |
|------|------|----------|
| `requirements.txt` | 本文件 §1 表的工程落地 | 每个包钉死 `==X.Y.Z`，与本文件版本列、`ENVIRONMENT.md §3`（锁版本表）三处一致；版本冻结后同步回填本文件 §1 占位 |
| `ENVIRONMENT.md` §2 / §3 / §4 / §5 | 本文件的权威上游 | Python/Verilator 版本、离线 wheel 打包命令以 `ENVIRONMENT.md` 为准（实际章节 §1–§5，无 §6/§8） |
| `CONSTRAINTS.md` §11 红线 #6 | 本文件披露义务的来源 | 「禁未披露依赖」→ 本文件必须列全且与 `requirements.txt` 一致 |
| `README.md`（提交包内） | 评测机离线安装运行说明 | 须写明 `verilator --version` 必须 = 5.050、`pip install --no-index --find-links=offline_pkgs` 命令 |

---

## 9. 待澄清 / 复验项

1. **`requirements.txt` 剩余精确版本号**：cocotb-test / cocotbext-axi / Jinja2 / PyVerilog 的 `X.Y.Z` 在 M1 骨架阶段于 Verilator 5.050 容器内复验后填入并冻结，回填本文件 §1 占位。cocotb（1.8.1）、z3-solver（>=4.12）、Verilator（5.050）、Python（3.12）已锁，不列入待澄清。
2. **cocotbext-axi issue #119 回归**：M1 选版时显式回归，确认 cocotb 1.8.1 + Python 3.12 下无 #119 症状才冻结版本。
3. **z3-solver 原生扩展 wheel 可用性**：确认 `manylinux2014_x86_64` 平台有预编译 wheel；若无则 vendored 源码进离线 wheel 目录。
4. **Verilator 是否赛方提供**：若评测机不自带 Verilator 5.050，需在 README 注明前置条件。此为覆盖率一致性的关键风险——三方开发机均非评测 OS（Linux x86_64），必须 Docker `linux/amd64` 复验（`ENVIRONMENT.md §5`）。
5. **`scoring.md:74` VCS/URG 措辞（灰色地带）**：原文「VCS/URG 报告必须对应当前提交的 RTL；cocotb 和纯 Verilog testbench 均可」。本队倾向「仅强调报告须对应 RTL、testbench 形式可选」，走 cocotb + Verilator 路线；建议向赛方/助教确认以消除最后不确定性（见 `PLAN.md §二` 灰色地带）。
6. **cocotbext-axi 与 `PLAN.md` 同步**：此库未在 `PLAN.md §三` 具名，后续同步 `PLAN.md` requirements 描述，避免后人误以为可删。
