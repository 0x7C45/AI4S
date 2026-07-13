# 队友启动指南 — AI4S 赛道 A

## 竞赛概览

**竞赛**: Agentic4Systems 暑期学校 GPGPU 智能体加速设计竞赛 2026
**赛道**: A — EDA 软件（3 道子题，每题 100 分，取平均）
**截止**: 2026年7月15日 上午10:00

## 团队分工

| 成员 | 负责 | 技术栈 | 目录 |
|------|------|--------|------|
| 你 (负责人) | A3 逻辑综合 | Python + Yosys | `Track-A/A3-synthesis/` |
| 队友1 | A1 RTL 仿真器 | C++ + flex/bison | `Track-A/A1-simulator/` |
| 队友2 | A2 验证生成 | Python + cocotb + iverilog | `Track-A/A2-verification/` |

## 评分公式

```
赛道总分 = (A1分 + A2分 + A3分) / 3
```

---

# A1: 轻量 RTL 仿真器（队友1）

## 目标
构建事件驱动 Verilog RTL 仿真器，支持 Verilog-2001 核心子集。

## 技术方案: C++ + flex/bison

### 架构
```
src/
  lexer.l          — flex 词法分析器
  parser.y         — bison 语法分析器
  ast.h/cpp        — AST 节点定义
  sim_engine.h/cpp — 事件驱动仿真引擎
  netlist.h/cpp    — 网表数据结构
  system_funcs.h/cpp — $display/$readmemh 等系统函数
  main.cpp         — 入口
Makefile           — build/compile_sim/run/parallel_run
```

### 优先级（按得分效率）

**Phase 1: 基础功能 (14分)**
- [ ] flex/bison 解析器: module, assign, always, reg/wire, if/case/for, parameter
- [ ] 组合逻辑仿真 (assign + always @(*))
- [ ] 系统函数: $fopen, $fscanf, $fdisplay, $fgets, $display, $finish
- [ ] Makefile: build, compile_sim, run
- [ ] 通过 basic01-05, alu, priority_encoder (各2分 = 14分)

**Phase 2: 高级特性 (8分)**
- [ ] 时序仿真: always @(posedge clk), 非阻塞赋值 `<=`
- [ ] DFF 建模 (带异步复位)
- [ ] `define / `include 预处理
- [ ] 多文件 module 层次化
- [ ] 通过 i2c(3分), ip(2分), axis_fifo(2分), sha256(2分)

**Phase 3: 性能优化 (11分)**
- [ ] GEMM 测试用例通过
- [ ] 增量编译 (文件级依赖)
- [ ] 多线程并行仿真 (parallel_run)
- [ ] 性能调优

### 测试流程
```bash
cd Track-A/A1-simulator/testcases/sim_public/benchmark/basic01
make build
make compile_sim FILELIST=filelist.txt TOP=tb
make run
diff -u tb/output_ref.mem tb/output.mem  # 应该无差异
```

### 关键参考
- Verilator 源码: `~/ysyx-workbench/verilator/` (解析器架构参考)
- NEMU 源码: `~/ysyx-workbench/nemu/` (CPU 模拟器参考)

### 评分细节
- F1 (语言解析): 每 case 1 分 — 解析器能读取并构建数据结构
- F2 (功能正确): 每 case 1-2 分 — output.mem 与 output_ref.mem 完全一致
- P1 (编译性能): 仅 GEMM — 与基线比较编译时间
- P2 (仿真性能): 仅 GEMM — 与基线比较单核仿真时间
- P3 (多核加速): 仅 GEMM — 4 核 vs 单核加速比

---

# A2: 验证环境自动生成（队友2）

## 目标
读取 RTL 设计，自动生成 cocotb testbench + 约束随机测试 + 覆盖率报告。

## 技术方案: cocotb + iverilog + gcov

### 架构
```
run.py             — 入口脚本 (完整流水线)
src/
  rtl_parser.py    — RTL 接口解析 (端口/时钟/复位/协议识别)
  skeleton_gen.py  — 验证骨架生成 (cocotb testbench 模板)
  constraint_gen.py — 约束随机测试生成
  coverage_gen.py  — 覆盖率 bin 定义
  sim_runner.py    — 仿真执行器 (调用 iverilog + cocotb)
  coverage_collect.py — 覆盖率收集 (gcov + 功能覆盖)
  report_gen.py    — JSON 报告生成
templates/
  cocotb_tb.py.j2  — cocotb testbench Jinja2 模板
requirements.txt   — cocotb, jinja2 等依赖
```

### 优先级（按得分效率）

**Phase 1: 骨架门禁 (3分/电路)**
- [ ] RTL 解析: 识别端口方向/宽度/时钟/复位
- [ ] 接口协议推断: AXI / SRAM / valid-ready
- [ ] cocotb testbench 骨架生成: 时钟/复位/驱动/监视
- [ ] run.py 入口: RTL → testbench → 仿真 → 结果
- [ ] 通过 case1 骨架门禁 (testbench 能编译运行)

**Phase 2: 覆盖率收集 (7分/电路)**
- [ ] 行覆盖率: gcov/lcov 收集
- [ ] 分支覆盖率: gcov/lcov 收集
- [ ] 功能覆盖 bin: cocotb 采样
- [ ] 约束随机测试: 5000 序列, 固定 seed
- [ ] 覆盖率反馈: 根据未覆盖 bin 调整测试策略
- [ ] 目标: C ≥ 85% (综合覆盖率)

**Phase 3: 通用化 (10 电路)**
- [ ] 处理 10 个隐藏电路 (不能硬编码)
- [ ] 自适应: 根据接口类型选择驱动策略
- [ ] 错误处理: 仿真失败时优雅降级

### 输出格式
```
submission_out/
  case_name/
    design.json              — 接口解析结果
    verification_skeleton.json — 验证骨架
    constraints.json         — 约束随机配置
    coverage_bins.json       — 功能覆盖 bin
    functional_coverage.json — 覆盖率采样
    coverage_result.json     — 覆盖率汇总
    report.json              — 顶层报告
    generated_tb/            — 生成的 testbench
    generated_tests/         — 生成的测试
```

### 测试流程
```bash
cd Track-A/A2-verification/testcases/A2_public_dataset
python3 run.py --rtl case1/rtl --top case1 --out out/case1 --seed 42 --num-seq 5000
# 检查 out/case1/ 下的 JSON 文件
```

### 关键参考
- 公开数据集: `Track-A/A2-verification/testcases/A2_public_dataset/case1-5/`
- case1 的 JSON 格式就是输出标准
- cocotb 文档: https://docs.cocotb.org/

### 覆盖率公式
```
C = 0.4 × 行覆盖率 + 0.3 × 分支覆盖率 + 0.3 × 功能覆盖率

C ≥ 85% → 7分/电路
65% ≤ C < 85% → 4.9分/电路
45% ≤ C < 65% → 2.8分/电路
C < 45% → 0分
```

### 骨架门禁失败条件（任意一条 = 整电路 0 分）
- Testbench 无法编译或仿真无法启动
- DUT 端口未连接、错连或宽度不匹配
- 时钟、复位或关键协议握手不可用
- 无有效驱动/监视
- 比对器未比对 DUT 行为

---

# GSD 辅助流程（两位队友通用）

## 快速开始

```bash
# 1. 进入项目目录
cd ~/Documents/github/AI4S

# 2. 创建 GSD 项目
/gsd-new-project
# 描述你的题目，选择 YOLO 模式 + Coarse granularity

# 3. 规划 Phase 1
/gsd-plan-phase 1
# Claude 会创建详细的执行计划

# 4. 执行 Phase 1
/gsd-execute-phase 1
# Claude 写代码，你审查和测试

# 5. 继续后续 Phase
/gsd-plan-phase 2
/gsd-execute-phase 2
```

## 关键原则

1. **让 Claude 写代码** — 你们负责描述需求、审查代码、运行测试
2. **先跑通再优化** — 功能正确 > 性能优化
3. **频繁测试** — 每完成一个任务就运行测试用例
4. **参考公开数据集** — 输入输出格式都在 testcases/ 里
5. **遇到问题及时沟通** — 在群里问，不要卡太久

## 项目目录结构

```
~/Documents/github/AI4S/
├── Track-A/
│   ├── A1-simulator/     ← 队友1 的工作目录
│   ├── A2-verification/  ← 队友2 的工作目录
│   └── A3-synthesis/     ← 你的工作目录
├── .planning/            ← GSD 项目管理文件
└── TEAM_GUIDE.md         ← 本文件
```

---

# 时间线建议

| 时间 | 队友1 (A1) | 队友2 (A2) | 你 (A3) |
|------|-----------|-----------|---------|
| 7/12 晚 | 项目搭建 + 基础解析器 | 项目搭建 + RTL 解析 | 框架 + 基本综合流程 |
| 7/13 上午 | basic01-05 通过 | case1 骨架通过 | LSV01 正确 |
| 7/13 下午 | 高级特性 (i2c, ip) | 覆盖率收集 | 10 电路全部正确 |
| 7/13 晚 | GEMM 性能优化 | 通用化 (隐藏电路) | 多 Point + 自动调参 |
| 7/14 上午 | 并行仿真 | 覆盖率 ≥85% | PPA 优化 |
| 7/14 下午 | 测试 + 修复 | 测试 + 修复 | 测试 + 修复 |
| 7/14 晚 | 提交准备 | 提交准备 | 提交准备 |
| 7/15 10am | **提交** | **提交** | **提交** |
