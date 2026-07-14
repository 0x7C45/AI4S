# A2 验证环境自动生成 — 项目构想（win-ZCode GSD 输入）

## 一句话目标

构建一个自动验证环境生成框架：读取 RTL 设计，自动生成 cocotb testbench + 约束随机测试 + 覆盖率报告，对 10 个隐藏电路各产出 7 个 JSON + `generated_tb/` + `generated_tests/`，按 `C = 0.4×行 + 0.3×分支 + 0.3×功能` 最大化覆盖率得分。

这是赛题 A2（赛道 A 第 2 题）。满分 100 = 10 电路 × 10 分（骨架门禁 3 + 覆盖率 7）。

## 技术路线（已锁定，不可变）

- **cocotb 2.0.1 + Verilator 5.050**（已弃用 iverilog+gcov、VCS+URG）
- 覆盖率编译期插桩：`--coverage-line --coverage-toggle`（branch 由 `--coverage-line` 自动产出，无 `--coverage-branch` 标志）
- 功能覆盖靠 cocotb `coverage.hit(bin)` 采样
- 运行环境：**Docker linux/amd64**（win-ZCode 主路线，与评测 OS 同构）

## 运行环境（烟雾测试已验证可用）

- 容器：`verilator/verilator:v5.050`（注意 tag 带 v 前缀，文档误写 :5.050）
- Ubuntu 24.04 + Python 3.12.3 + g++ 13.3（镜像自带）
- **镜像无 pip**：需 `apt-get install python3-pip` bootstrap 后装 cocotb
- cocotb 2.0.1 + cocotbext-axi 0.1.28 实测可装可用
- case1 烟雾测试通过：编译（需 `-Wno-fatal`）+ 仿真（5000 笔 exit 0）+ 覆盖率插桩 + coverage.dat 解析全通

## 输入输出契约

**入口**（五参数缺一不可）：
```bash
./run.sh --rtl <dir> --top <module> --out <dir> --seed 20260630 --num-seq 5000
```

**每电路产出**（7 JSON + 2 目录）：
1. `design.json` — RTL 解析：顶层模块、文件列表、时钟/复位、端口/协议
2. `verification_skeleton.json` — testbench 骨架：时钟/复位/驱动/监视/scoreboard
3. `constraints.json` — 约束随机：seed=20260630、序列数=5000、变量列表
4. `coverage_bins.json` — 功能 bin 定义：coverpoint/bin/场景
5. `functional_coverage.json` — 功能覆盖结果：bin 命中/百分比
6. `coverage_result.json` — 三类覆盖率 + 综合 C（公式 0.4/0.3/0.3）
7. `report.json` — 流水线报告：各阶段成功失败、文件路径、可复现命令
+ `generated_tb/`（生成的 testbench 源码）+ `generated_tests/`（约束随机测试序列）

## 评分（满分 100）

- 综合 `C = 0.4×行覆盖率 + 0.3×分支覆盖率 + 0.3×功能覆盖率`
- 档位：C≥85% → 7分 | 65-85% → 4.9分 | 45-65% → 2.8分 | <45% → 0分
- 门禁不过（testbench 编译失败/端口错连/无驱动监视/scoreboard 静默）→ 整电路 0 分

## 关键硬约束

1. `--seed 20260630` 必须穿透到 `random.Random(seed)`（否则覆盖率上限 3 分）
2. `--num-seq 5000` 锁定
3. 综合公式 coverage_result.json 必须写 **0.4/0.3/0.3**（严禁抄公开样例的 0.42/0.28/0.30）
4. 功能 bin 必须有真实事务采样证据，不能空 hit、不能初始化一次性 hit
5. valid/ready 接口必须设 ready 反压
6. 覆盖率 scope 必须对应当前 RTL 子树，避免 wrapper 稀释
7. 支持三类接口：AXI4-Lite/AXI、SRAM-like、Streaming valid/ready
8. 六条原创性红线：禁抄袭/禁硬编码/禁绕评测/禁预计算/禁针对性优化/禁未披露依赖
9. 评测 OS = Linux x86_64 断网，依赖全打包（wheelhouse 离线装）

## 已有资产（输入文档）

- `spec.md` / `scoring.md` — 赛题官方（locked，不得修改）
- `PLAN.md` — cocotb+Verilator 路线 + 三阶段计划 + 陷阱清单
- `CONSTRAINTS.md` — 硬约束汇总（16 节）
- `ENVIRONMENT.md` — 运行环境 + 锁版本表 + 离线打包方案
- `EXECUTOR.md` — win-ZCode 角色（三方竞赛之一）
- `PITFALLS.md` — 10 类陷阱
- `THIRD_PARTY.md` — 第三方依赖版本/许可
- `testcases/A2_public_dataset/case1-5/` — 5 个公开样例（VCS 实测标杆，只读）
- `smoke_out/SMOKE_TEST_REPORT.md` — win-ZCode 环境烟雾测试报告

## 三阶段计划（来自 PLAN.md）

### Phase 1：骨架门禁（每电路 3 分基础）
- RTL 接口解析：端口方向/宽度/时钟/复位/参数/协议推断（AXI/SRAM/valid-ready）
- cocotb+Verilator testbench 骨架生成（Jinja2 模板）：时钟/复位/驱动/监视/scoreboard/反压
- run.py 入口跑通：RTL → testbench → 仿真 → 结果
- 通过 case1 骨架门禁（能编译、能跑、DUT 端口连对、有反压、有 scoreboard）

### Phase 2：覆盖率收集（每电路 7 分）
- 行/分支覆盖率：Verilator `--coverage-line` + coverage.dat LCOV 解析
- 功能覆盖 bin：cocotb 采样（FSM/数据通路/存储器/AXI 4 类模板）
- 约束随机：5000 序列，固定 seed（`random.Random(seed)` + directed 边界值）
- RTL 静态分析：`generate/if` 死码识别，只对可达分支采 bin
- 目标 C ≥ 65% 拿 4.9 分保底，冲 85% 拿满 7 分

### Phase 3：通用化（10 隐藏电路）
- 处理 10 个隐藏电路（禁硬编码/针对性优化，必须通用化）
- 自适应接口驱动策略（AXI/SRAM/valid-ready 各类自动识别）
- 离线打包（wheelhouse + requirements.txt + THIRD_PARTY.md）
- Docker linux/amd64 复验全部 case

## 技术栈

- Python 3.12（入口 run.py / src/ 七模块 / cocotb testbench / 覆盖率后处理）
- cocotb 2.0.1 + cocotb-test 0.2.6（Verilator 后端）
- cocotbext-axi 0.1.28（AXI 驱动）
- Jinja2 3.1.6（testbench 模板渲染）
- PyVerilog 1.3.0（RTL 解析）
- z3-solver 4.16.0.0（约束求解，可选）
- Verilator 5.050（仿真器 + 覆盖率插桩）

## 现状

- 文档完备（PLAN/CONSTRAINTS/ENVIRONMENT/EXECUTOR/PITFALLS/THIRD_PARTY）
- 零实现代码（无 run.py / src/ / templates/ / requirements.txt）
- 环境已验证（Docker + Verilator 5.050 + cocotb 烟雾测试通过）
- 工作分支：`exec/win-zcode`（已建，文档改动已提交）
