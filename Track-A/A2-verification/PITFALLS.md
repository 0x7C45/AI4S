# A2 验证子题 · 陷阱清单（PITFALLS）

> 适用范围：A2 验证环境自动生成（cocotb + Verilator 路线）。
> 权威裁定优先级（高 → 低）：`spec.md` / `scoring.md`（官方 locked）> `testcases/`（locked 只读）> `PLAN.md` > `EXECUTOR.md` > `CONSTRAINTS.md`。
> 本文件仅汇总陷阱，不修订任何上游文件。所有 case 数字均逐字核实自 `testcases/A2_public_dataset/`。
> 撰写于 2026-07-13。

---

## 0. 阅读约定

- **路线锁定**：cocotb + Verilator（`--coverage-line --coverage-toggle`；**branch 由 `--coverage-line` 自动产出**，Verilator 5.050 实测无 `--coverage-branch` 标志），仿真器不强制 VCS。
  > ✅ **congress 评审已裁决（2026-07-14）**：coverage 命令定标 `--coverage-line --coverage-toggle`（选项 A）。理由：`--coverage-line` 自动产 line+branch（Verilator 官方设计，branch 是 line coverage 结构化副产品）；functional(30%) 靠 cocotb bin，非 Verilator 标志。落地：①`COVERAGE_FLAGS` 参数化（Makefile 顶层变量，默认 A）；②解析器 schema-driven（字段从标志派生）；③coverage 文件头写 `verilator --version`+flags；④Phase1 末单端 C 烟雾测试验 fsm 格式四方一致；⑤functional bin 模板预置（FSM/数据通路/存储器/AXI 4 类，30% 权重杠杆）；⑥评分细则若发布且 branch 解读为真值表则切 B（零代码）。
  > 已弃用路线（仅作历史说明，禁止出现在提交包里）：`iverilog + gcov`（iverilog 原生不支持 RTL 行/分支覆盖率，gcov 测的是 C++ 源码而非 RTL）、`VCS/URG`（公开样例所用，本队不走此路线）。
- **固定参数**：`--seed 20260630`、`--num-seq 5000`（本队锁定 5000；公开样例 case3 例外用 256，仅作参考，本队不沿用）。seed 或输入序列(num-seq) 不可复现 → 覆盖率上限 3 分（scoring.md §2）。注：RTL 是评测给定输入，选手不控制其复现性；RTL 报告不对应是另一条独立罚分（→ 覆盖率 0），勿与此 3 分上限混淆。
- **公式锁定**：综合覆盖率 `C = 0.4×行 + 0.3×分支 + 0.3×功能`（scoring.md §2 locked）。**严禁抄公开样例的 0.42/0.28/0.30**。
- **每陷阱结构**：症状（反例）→ 根因 → 正解 → 出处。

---

## 1. 陷阱 ① 公式系数抄公开样例（0.42/0.28/0.30）

### 症状（反例）
公开样例 5 个 case 的 `coverage_result.json` → `coverage.composite.formula` **完全一致**地写着：

```
"formula": "0.42 * line + 0.28 * branch + 0.30 * functional"
```

对应实测：
| case | line% | branch% | func% | composite（0.42/0.28/0.30）|
|------|-------|---------|-------|----------------------------|
| case1 | 53.0 | 48.33 | 100 | 65.79 |
| case4 | 96.9 | 80.65 | 100 | 93.28 |

选手若把样例的 `formula` 字段连同数字一起抄进自交的 `coverage_result.json`，自评分与官方口径错位。

### 根因
`scoring.md` §2（第 44–50 行）locked 公式为 `0.4×行 + 0.3×分支 + 0.3×功能`。公开样例使用旧系数 0.42/0.28/0.30 是「选手自交、评测器不锁工具重算」的铁证（case2 还能加自定义字段 `all_modules_vcs_coverage` 仍当官方示例），但**评测基准以 scoring.md 为准**。

对 case4 用两套系数复算：
- 0.42/0.28/0.30：`0.42×96.9 + 0.28×80.65 + 0.30×100 = 93.28`（与公开样例一致）
- **0.4/0.3/0.3**：`0.4×96.9 + 0.3×80.65 + 0.3×100 = 92.96`（scoring.md 口径）

两版差 0.32pp。case4 都落 ≥85% 满分档，影响为 0；但边界 case（C 接近 85/65/45 档线）会因 0.32pp **跨档**，单电路最多差 2.1 分（7.0 → 4.9），10 电路最多差 21 分。

### 正解
1. `coverage_result.json` 的 `composite.formula` 字段硬编码写 `"0.4 * line + 0.3 * branch + 0.3 * functional"`，`composite.percent` 用 0.4/0.3/0.3 复算后填入。
2. 综合分档以 **0.4/0.3/0.3** 的 C 值为准对档：`C≥85%→7.0` / `65%≤C<85%→4.9` / `45%≤C<65%→2.8` / `C<45%→0`。
3. 冲刺目标定在 85 / 65 / 45 整数，**不要**定在 84.99 / 64.99（边界值策略）。
4. 不读、不抄公开样例 `coverage_result.json` 的 `formula` 字段。

### 出处
`scoring.md` §2 公式；`PLAN.md` §二/§四/§六陷阱#1；`CONSTRAINTS.md` §5。

---

## 2. 陷阱 ② 功能 bin 预填（hits=1 边缘达标）

### 症状（反例）
**case1** `functional_coverage.json` 的 `backpressure` coverpoint 共 4 个 bin，每个 `hits=1`：

```
backpressure: source_rready_pause(1), downstream_arready_pause(1),
              downstream_rvalid_pause(1), combined_pause(1)
```

同期其他 coverpoint hits 量级：`read_length` 69–1782、`burst_size` 各 1250、`adapter_path` 4876–5000。backpressure 4 bin 与之差 **3–4 个数量级**。

**case4** `ready_valid_backpressure` coverpoint 共 3 个 bin，同样每个 `hits=1`：

```
ready_valid_backpressure: write_response_pause(1), read_data_pause(1), combined_pause(1)
```

同期 `operation_type` 1482–2011、`state_transitions` 2989–3493、`crosses_word_boundary` 4437。同样边缘达标。

### 根因
这是「刻意塞 1 次让 bin 判满分」而非协议自然覆盖。`scoring.md` §2（第 52–58 行）明确：**仅枚举随机值而无测试采样证据的 bin 不计 → 功能覆盖率直接 0%**。公开样例目前判满分，但隐藏评测极可能收紧（如要求 `hits ≥ N`、或要求 backpressure 持续多个周期、或细分 pause 时序）。一旦收紧，case1/case4 的 functional 会从 100% 暴跌，把 composite 从满分档（≥85%）拖到 4.9 档甚至 2.8 档。

### 正解
1. **bin 必须有真实事务触发**（`PLAN.md` §五 Phase2）：每个 bin 的 hits 量级应与该 coverpoint 自然命中频率相当，不能比同 case 其他 bin 差数量级。
2. backpressure 类 bin 在 5000 序列里以**自然概率**出现多次（例如每 N 笔强制插入一个反压周期，N 取 16/32/64 让 hits 落到 70–300 量级）。
3. 不要在测试启动时「初始化一次性 hit」凑数。
4. 对每个 bin 在 `coverage_bins.json` 里写明对应的协议场景/corner case，并在 `functional_coverage.json` 里记录真实命中次数（留采样证据）。

### 出处
`scoring.md` §2 第 52–58 行；`PLAN.md` §五 Phase2 + §六陷阱#3。

---

## 3. 陷阱 ③ 行覆盖被参数化死码拉低（case1 53% 真因）

### 症状（反例）
case1 `coverage_result.json`：`line 168/317 = 53.0%`（149 行未覆盖）、`branch 29/60 = 48.33%`。composite 仅 65.79，卡在 4.9 档底部。

### 根因 = 参数化死码（**不是 wrapper 稀释**）
`case1/rtl/case1.v` 第 **L215** `always @* begin`（用户提示「L216」是 always 体内首行 `state_next = STATE_IDLE`，行号差 1，语义一致）含三分支结构：

| 行号 | 分支 | 条件 | 状态 |
|------|------|------|------|
| L243 | `if (SEGMENT_COUNT == 1)` | 直通路径（约 58 行） | 恒假未激活 |
| L302 | `else if (EXPAND)` | 扩展路径（约 131 行） | 恒假未激活 |
| L434 | `else` | SHRINK 路径 | **激活** |

配置 `S_DATA=32 / M_DATA=16` → `EXPAND=0`、`SEGMENT_COUNT = S_STRB/M_STRB = 4/2 = 2`，故前两条分支恒假，**死码主体在 L243–433**（VCS `-cm` 行过滤后对应 130–149 可执行行，与 ~139 行一致）。

**case1_cocotb_top.v（124 行）是纯连线 wrapper**：全文为 `reg/wire` 声明 + 1 个 `axi_adapter_rd` 例化（L64–122），**无 always 块、无 assign、无 Clock 生成**（`clk/rst` 由 cocotb VPI 端驱动）。覆盖率 scope 为「RTL only / DUT 子树」，wrapper 自身的 LINE/BRANCH 全为 `--`，**0 行贡献**。所以 53% 不是被 wrapper 稀释，而是 DUT 内部有 ~139 行参数化死码永远跑不到。

### 正解（约束随机激活全部分支）
1. **测试前对 RTL 做 `generate/if` 分支静态分析**：解析 `always @*` / `generate-if` 里的参数化条件，识别哪些分支在当前 `configuration_under_test` 下恒假。
2. **只对可达分支采 bin**：对恒假分支不要浪费 bin 配额（功能 bin 也别指向死码路径）。
3. **约束随机需针对激活分支构造事务**：若隐藏电路用相同参数（S=32/M=16）盲目复用 case1 模板，会复现 53% 天花板；应在测试集中显式构造能触发各激活分支的事务组合（不同 burst size、不同地址对齐、不同反压时序）。
4. **参数化死码无法靠加测试解决**：若 RTL 配置使某分支恒假，行覆盖物理上限就是「扣除死码后的可达行」。这种情况应在 `report.json` 里记录「参数化死码行数 + 可达行覆盖率」，自评 C 值按可达行口径计算更接近评测口径。

### 出处
`case1/rtl/case1.v` L215/L243/L302/L434；`case1/coverage_result.json` line 168/317；`PLAN.md` §六陷阱#6（scope 稀释的反面教训，但本陷阱强调真因是死码非 wrapper）。

---

## 4. 陷阱 ④ 缺 report.json（公开样例反而没有）

### 症状（反例）
`testcases/A2_public_dataset/` 下 **5 个 case 全部没有 `report.json`**（取而代之是 `dataset_result.json`）：

```
case1/ case2/ case3/ case4/ case5/  →  均无 report.json
```

选手若照搬公开样例的目录结构（用 `dataset_result.json` 替代 `report.json`），评测视为缺项。

### 根因
`spec.md` §3（第 38–54 行）输出契约**明确要求 7 个 JSON**：

```
submission_out/case_name/
  design.json
  verification_skeleton.json
  constraints.json
  coverage_bins.json
  functional_coverage.json
  coverage_result.json
  report.json            ← 公开样例缺这一项
  generated_tb/
  generated_tests/
```

公开样例不齐全 ≠ 评测不查。罚分项包含「缺项」（`PLAN.md` §二规则确认：罚分项只有「仿真失败/缺项/无 seed/报告不对应 RTL」）。

### 正解
1. **严格按 `spec.md` §3 的 7 JSON 清单生成**，`report.json` 是必交项，不能用 `dataset_result.json` 顶替。
2. `report.json` 字段语义（`spec.md` §3 第 110–117 行）：各阶段成功/失败（解析、骨架生成、仿真、覆盖率收集）、关键输出文件路径、覆盖率汇总、**可复现命令**（`./run.sh --rtl ... --top ... --out ... --seed 20260630 --num-seq 5000`）。
3. `dataset_result.json` 是公开样例的额外产物，不在 spec 强制清单，可选择性地附带但不替代 `report.json`。
4. 7 JSON 生成顺序（`PLAN.md` §七）：`design → skeleton → constraints → coverage_bins → functional_coverage → coverage_result → report`，最后一步汇总前六步。

### 出处
`spec.md` §3 第 38–54 行；`PLAN.md` §二/§七；`CONSTRAINTS.md` §4。

---

## 5. 陷阱 ⑤ 模块名硬填 case 名（top_module 错位）

### 症状（反例）
5 个 case 的 `design.json` → `top_module` 字段**全部填 case 标签**，与 RTL 真实 module 名不一致：

| case | design.json `top_module` | RTL 真实 module |
|------|--------------------------|-----------------|
| case1 | `"case1"` | `axi_adapter_rd` |
| case2 | `"case2"` | `axis_fifo_adapter`（+依赖 `axis_fifo` / `axis_adapter`）|
| case3 | `"case3"` | `axi_vfifo_raw`（+依赖 `axi_vfifo_raw_wr/rd`）|
| case4 | `"case4"` | `axi_ram` |
| case5 | `"case5"` | `axi_crossbar_addr` |

**case4（用户点名反例）**：`design.json` 写 `top_module="case4"`，但 `Makefile` L9 `TOPLEVEL=axi_ram`、`case4_tb.py` L205 `dut='axi_ram'`、RTL L34 `module axi_ram#`。case1 同样中招（`top_module="case1"` vs `axi_adapter_rd`，靠 `case1_cocotb_top.v` wrapper 补）。

### 根因
生成器若把目录名/case 标签当模块名塞进 `design.json`，cocotb/Makefile 的 `TOPLEVEL` 与 `design.json` 字段错位 → DUT 例化失败 → **骨架门禁失败 → 整电路 0 分**（覆盖率不计）。case4 因为没 wrapper（直接 `TOPLEVEL=axi_ram`），错位会立刻暴露；case1 靠 wrapper 掩盖了一层，更具迷惑性。

### 正解
1. **生成器必须从 RTL `module XXX#` 行解析真实模块名**，不能填 case 标签或目录名。
2. 区分「逻辑 top」（`design.json` 报告的层次根 = RTL 顶层 module 名）与「仿真 top」（Makefile `TOPLEVEL` / cocotb `dut` 参数）—— 三者必须一致指向真实 module。
3. 多文件 RTL（case2/case3）需同时解析依赖模块（`axis_fifo` / `axis_adapter` / `axi_vfifo_raw_wr/rd`），在 `design.json` 的 `rtl_files` 字段按正确编译顺序列出。
4. 自检：生成 `design.json` 后断言 `top_module` 字段值在 RTL 源码 `module <name>` 出现过。

### 出处
`case1/design.json`、`case4/design.json`（实测）；`PLAN.md` §六陷阱#2；`spec.md` §3 design.json 字段要求。

---

## 6. 陷阱 ⑥ 硬编码/针对性优化（Phase3 通用化红线）

### 症状（反例）
对 case1–5 的具体接口宽度/参数/module 名写 `if/else` 分支，例如：

```python
# 反例（禁止）
if top_module == 'axi_adapter_rd':
    driver = AxiAdapterRdDriver(data_width=32)
elif top_module == 'axi_ram':
    driver = AxiRamDriver(...)
```

### 根因
`PLAN.md` §五 Phase3 明确：处理 10 个隐藏电路**不能硬编码/针对性优化**（引 README 红线禁止）。`spec.md` §6（第 154–163 行）声明：**公开数据集 case1–5 不代表隐藏评测范围**，隐藏评测使用相同 I/O 约定但 RTL 结构/参数/接口组合/corner case 不同。过拟合到公开 case → 隐藏电路 0 分。

### 正解
1. **驱动策略按协议族分类**（AXI / AXI-Lite / SRAM-like / valid-ready stream），不按 case 名或 module 名分类。
2. **接口参数从 `design.json` 的 `configuration_under_test` 动态读取**（ADDR/DATA/STRB/ID 等宽度），不写魔法数字。
3. **约束随机参数范围由 RTL 解析结果推导**（如 burst size 上限从 `max_burst` 参数读，不硬编码 16）。
4. 通用化验收：拿 case1–5 任一切走，框架仍能在其余 4 个 case 上跑通且覆盖率不退化；进一步用 `testcases/A2_public_dataset/functional_coverage.py`（`FunctionalCoverage` 类）里的协议模型对未见接口做泛化测试。

### 出处
`PLAN.md` §五 Phase3；`spec.md` §6；`CONSTRAINTS.md` §11 原创性红线。

---

## 7. 陷阱 ⑦ seed 不穿透（cocotb 内部 RNG ≠ constraints seed）

### 症状（反例）
`constraints.json` 声明 `seed=20260630`，但 cocotb 测试代码里用了未 seed 的 `random` 模块，或 cocotb 默认时钟抖动 RNG：

```python
# 反例（禁止）
import random
addr = random.randint(0, 0xFFFF)   # 用了进程全局 RNG，未 seed
```

### 根因
`scoring.md` §2（第 81 行）：**无可复现 seed 或输入序列 → 覆盖率上限 3 分**（不是 0，是硬上限）。`spec.md` §1/§5 可复现约束：相同 seed + 相同 RTL 必须产生一致或等价结果。cocotb 内部 RNG（`random.randrange`、时钟 jitter）与 `constraints.json` 声明的 seed 是两套独立源，不显式穿透就会导致每次跑结果不同。

公开样例统一用 `seed=20260630, sequence_count=5000`（case3 例外 `sequence_count=256`）。

### 正解
1. `--seed 20260630` 必须穿透到 `random.Random(seed)`，所有 directed 边界值与随机生成都基于此 RNG：

```python
# 正解
import random
SEED = 20260630   # 来自 --seed 参数，禁止魔法字面量散落
rng = random.Random(SEED)
addr = rng.randint(0, 0xFFFF)
```

2. cocotb 测试函数开头集中初始化 RNG，禁用 cocotb 默认时钟抖动（`clock.period` 用确定值，不带 jitter）。
3. 不得调用未 seed 的 `random` 模块函数；多线程/协程场景下每个生成器从主 RNG `rng.spawn()` 派生子 RNG，保证可复现。
4. `constraints.json` 完整记录 seed / 随机变量列表 / 范围 / 协议约束，作为复现证据。

### 出处
`scoring.md` §2 第 81 行；`PLAN.md` §五 Phase2 + §六陷阱#5；`spec.md` §1/§5；`CONSTRAINTS.md` §3。

---

## 8. 陷阱 ⑧ 三方 OS 不一致 → Verilator 覆盖率跨平台漂移

### 症状（反例）
三方开发机的 OS/架构不统一，其中 win-ZCode 主运行环境即评测同构环境：

| 实例 | OS / 架构 | Verilator 来源 |
|------|-----------|----------------|
| mac-CC | macOS arm64 | brew native（开发期提速）|
| win-CC | Windows + WSL2 | WSL2 linux/amd64（最接近评测 OS）|
| win-ZCode | Windows + Docker linux/amd64 | Docker `verilator/verilator:v5.050`（与评测 OS 同构，开发即交付）|
| 评测机 | Linux x86_64（`spec.md` §5 line 147）| 评测机自带 |

### 根因
Verilator `--coverage-line/-toggle` 在 macOS arm64 与 Linux x86_64 上的插桩/解析行为可能有细微差异（不同编译器版本、不同 libc、不同 `long/int` 对齐、`coverage.dat` 格式细节）→ **覆盖率跨平台漂移**。本地算出 `C=85.2%`（满分档），提交后评测 OS 跑出 `C=84.7%`（4.9 档）→ 单电路差 2.1 分 × 10 电路 = 最多 21 分漂移。这是「三方 OS gap」的核心风险：mac-CC 是 macOS arm64，win-CC 是 Windows（WSL2），win-ZCode 是 Windows（Docker linux/amd64，与评测 OS 同构），覆盖率跨平台一致性必须验证（win-ZCode 风险最低）。

### 正解（主推 Docker，三方统一 linux/amd64）
1. **运行环境主推 Docker**：`verilator/verilator:v5.050` 官方镜像，三方统一 `linux/amd64` 平台。
2. **mac-CC 开发策略**：开发期用本机 native Verilator（brew 5.050）提速；**提交前必须在 Docker `linux/amd64` 容器内复跑全部 case 验证覆盖率一致性，无漂移才提交**。
3. **win-CC 验证环境**：WSL2（原生 linux/amd64，最接近评测 OS），同样在提交前用 Docker 复验。
4. **win-ZCode 验证环境**：Docker linux/amd64（Windows + Docker Desktop），与评测 OS 完全同构，开发即交付环境，覆盖率数字直接可用，无需额外平台复验。
5. **复验比对口径**：三方在 Docker 内对 5 个公开 case 各跑 3 次，行/分支/功能覆盖率三组数字必须逐位一致（或差异 < 0.05pp 可接受），否则定位漂移源（多为 Verilator 版本或编译选项不一致）。
6. fallback：若 Docker 不可用，用 `venv3.12 + install.sh` 在 linux/amd64 服务器上复验，但优先 Docker。

### 出处
`spec.md` §5 line 147（评测 OS = Linux x86_64）；用户架构级决策；`ENVIRONMENT.md` §4。

---

## 9. 陷阱 ⑨ Verilator 版本漂移（--coverage 标志跨主版本差异）

### 症状（反例）
机器 A 装 Verilator 5.050，机器 B 装 Verilator 5.030（或更新版的 5.070），同一份 RTL + 同一 seed 跑出不同的行/分支覆盖数：

```
机器 A (5.050): line 168/317 = 53.0%
机器 B (5.030): line 171/317 = 53.9%   ← 漂移
```

### 根因
`--coverage-line` / `--coverage-toggle` 两个标志在不同主版本间行为可能漂移（**注：Verilator 5.050 实测无 `--coverage-branch` 标志；branch 由 `--coverage-line` 自动产出，5.050 实测 coverage.dat branch 83.3%**）：
- 行/分支判定口径（条件表达式如何拆分、`?:` 算几分支）；
- toggle 粒度（按 bit 还是按 bus）；
- `coverage.dat` 输出格式（字段名/层次结构）。

版本不锁 → 三方跑出不一致的覆盖率 → 末段合并时无法裁定哪一方数字「对」。`PLAN.md` §二/§四、`EXECUTOR.md` §3 指定两标志（`--coverage-line --coverage-toggle`），但未指定版本号，需本队自锁。

### 正解（锁具体号 5.050，非「5.x」）
1. **Verilator 版本锁定 5.050**（具体号，**不是**「5.x」或「latest」）。
2. 三方统一来源：
   - Docker：`verilator/verilator:v5.050` 官方镜像（首选）。
   - macOS：`brew install verilator` 后校验 `verilator --version` 输出含 `5.050`，否则 checkout `v5.050` 源码自编。
   - WSL2：同上锁 5.050。
3. **必交文件 `requirements.txt` 钉死依赖版本**（每包 `==X.Y.Z`），`THIRD_PARTY.md` 声明 Verilator 5.050 + 许可（LGPL-3.0）+ 调用边界（编译期插桩、仿真后解析 `coverage.dat`）。
4. 提交前 Docker 复验（见陷阱 ⑧）时，`verilator --version` 必须输出 5.050 才算有效复验。

### 出处
`PLAN.md` §二/§四（`--coverage-line --coverage-toggle`）；`ENVIRONMENT.md` §4；`CONSTRAINTS.md` §1。

---

## 10. 陷阱 ⑩ cocotb 2.0 时序 API（RisingEdge off-by-one / Clock unit=）

### 症状（反例）
- testbench 用 `await cocotb.triggers.RisingEdge(dut.clk)` 后立即读 `dut.some_signal.value`，读到的是**上一拍**的值（RTL `<=` 非阻塞赋值尚未提交到 VPI 可读层）→ scoreboard 错拍比对 → 误判失败或覆盖率漏采。
- `cocotb.clock.Clock(dut.clk, 10, units="ns")` 报错 `TypeError: __init__() got an unexpected keyword argument 'units'`。

### 根因
cocotb 2.0 相对 1.x 的 API/时序语义收紧（task3 实测 2026-07-13，macOS arm64 + Verilator 5.050）：
1. **非阻塞赋值可见时序**：Verilator VPI 后端在 `RisingEdge` 触发瞬间，RTL 内 `<=` 非阻塞赋值的新值尚未刷新到 VPI 读取层；必须等到时钟回落（`FallingEdge`）或下一拍 `RisingEdge` 才能读到本拍结果。1.x 下偶现宽容行为，2.0 收紧后 off-by-one 显现。
2. **Clock 构造签名变化**：cocotb 2.0 `Clock(signal, period, unit="ns")`（**单数 `unit`**），1.x 为 `units="ns"`（复数）。直接迁移会立刻 TypeError。

### 正解
1. **采样统一在 `FallingEdge`**：先 `await RisingEdge(dut.clk)` 推进一拍，再 `await FallingEdge(dut.clk)` 同步，然后读信号值——此时 RTL `<=` 已提交到 VPI 可读。
   ```python
   await cocotb.triggers.RisingEdge(dut.clk)
   await cocotb.triggers.FallingEdge(dut.clk)   # 等非阻塞赋值提交
   cur = dut.some_signal.value   # 本拍结果，无 off-by-one
   ```
2. **Clock 用 `unit=` 单数**：`cocotb.clock.Clock(dut.clk, 10, unit="ns")`。
3. scoreboard / 期望比对也要在相同时序点采样，否则参考模型与 DUT 错拍 → 门禁「比对器未比对 DUT 行为」误判失败 → 整电路 0 分。

### 出处
cocotb 2.0 release notes；task3（2026-07-13）macOS arm64 + Verilator 5.050 实测：`RisingEdge` 后直接读得旧值，`FallingEdge` 后读得新值；`units=` → `TypeError`，改 `unit=` 通过。

---

## 11. 速查表（10 陷阱一图流）

| # | 陷阱 | 反例关键数据 | 正解一句话 | 罚分上限 |
|---|------|--------------|------------|----------|
| ① | 公式抄样例 | 5 case 全用 0.42/0.28/0.30 | 锁 0.4/0.3/0.3 | 跨档最多 -21 分 |
| ② | bin 预填 hits=1 | case1 4 bin / case4 3 bin 各 hits=1 | 自然概率多次触发 | functional→0% |
| ③ | 参数化死码 | case1 line 168/317=53%（L243–433 死码）| 静态分析可达分支 | 行覆盖天花板 |
| ④ | 缺 report.json | 5 case 全无 report.json | 严格按 spec §3 7-JSON | 缺项罚分 |
| ⑤ | 模块名硬填 | 5 case top_module 全填 caseN | 从 `module XXX#` 解析 | 门禁失败→0 分 |
| ⑥ | 硬编码优化 | 按 module 名 if/else | 按协议族分类 | 隐藏电路 0 分 |
| ⑦ | seed 不穿透 | cocotb RNG ≠ constraints seed | `random.Random(20260630)` | 覆盖率上限 3 分 |
| ⑧ | OS 漂移 | macOS arm64 vs Linux x86_64 | Docker linux/amd64 复验 | 跨档漂移 |
| ⑨ | 版本漂移 | 5.050 vs 5.030 差异 | 锁 Verilator 5.050 | 三方不一致 |
| ⑩ | cocotb 2.0 时序 | RisingEdge 后读旧值；`units=` TypeError | `FallingEdge` 同步 + `unit=` 单数 | off-by-one / 门禁失败 |

---

## 12. 相关文件索引（均为绝对路径）

- 官方 locked（严禁修改）：
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/spec.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/scoring.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/testcases/`（整个目录只读）
- 本队方案：
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/PLAN.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/EXECUTOR.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/CONSTRAINTS.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/ENVIRONMENT.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/README.md`
  - `/Users/arco/Documents/project/AI4S/Track-A/A2-verification/PITFALLS.md`（本文件）
