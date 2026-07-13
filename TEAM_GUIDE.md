# 队友启动指南 — AI4S 赛道 A

## 竞赛概览

**竞赛**: Agentic4Systems 暑期学校 GPGPU 智能体加速设计竞赛 2026
**赛道**: A — EDA 软件（3 道子题，每题 100 分，取平均）
**截止**: 2026年7月15日 上午10:00

## 团队分工（更新于 7/13）

| 成员 | 负责 | 技术栈 | 目录 | 原因 |
|------|------|--------|------|------|
| **你 (负责人)** | **A1 RTL 仿真器** | C++ + flex/bison | `Track-A/A1-simulator/` | 代码复用最多(NEMU/Verilator)，需要深入理解 |
| 队友 | A3 逻辑综合 | Python + Yosys | `Track-A/A3-synthesis/` | Yosys 流程成熟，GSD 可直接辅助 |
| 队友2 | A2 验证生成 | Python + cocotb + iverilog | `Track-A/A2-verification/` | 不变 |

## 评分公式

```
赛道总分 = (A1分 + A2分 + A3分) / 3
```

---

# A3: RTL 逻辑综合工具（队友 — 你的新任务）

## 目标
构建基于 Yosys 的 RTL 逻辑综合工具，读取 Verilog + SDC + Nangate45 Liberty，输出合法门级网表。

## 技术方案: Python + Yosys CLI

### 核心思路
Python 脚本生成 Yosys `.ys` 脚本文件，调用 `yosys -q -s script.ys` 执行综合。

### 架构
```
Track-A/A3-synthesis/
  Makefile              — build/synth/clean 目标
  src/
    synth.py            — 核心综合脚本 (生成 .ys + 调用 yosys)
    config.py           — config.json 解析器
    problem_parser.py   — problem.yaml 解析 (top_module/clock/reset)
    verify.py           — 内置正确性自检 (iverilog 仿真)
  config.json           — per-circuit 优化配置
  bin/synth_tool        — build 生成的可执行文件
  submission.yaml       — 队伍信息
  ORIGINALITY_DECLARATION.md
  THIRD_PARTY.md
```

### Yosys 综合流程（统一，所有电路相同）

```yosys
read_liberty -lib {LIBERTY}
read_verilog {RTL}
read_sdc {SDC}
hierarchy -check -top {TOP}
proc
opt_expr; opt_clean; opt_merge
fsm
opt
wreduce; peepopt; alumacc; share
opt
memory_map
opt
techmap
opt
abc -liberty {LIBERTY} -script "{ABC_SCRIPT}"
dfflibmap -liberty {LIBERTY}
opt
setundef -zero
splitnets -driver
clean
write_verilog {OUT_DIR}/netlist.v
```

**关键陷阱（必须遵守）：**
1. abc 脚本必须以 `map` 结尾（否则输出不是映射后的网表）
2. `dfflibmap` 必须在 `abc` 之后（映射触发器到库单元）
3. 不要 `flatten` 时序电路（会破坏 FSM）

### 优先级

**Phase 1: 框架 + 基本综合 (正确性)**
- [ ] Makefile: `build` (创建 bin/synth_tool), `synth` (调用综合), `clean`
- [ ] config.py: 解析 config.json，per-circuit + `$default` 回退
- [ ] problem_parser.py: 从 problem.yaml 提取 top_module、clock、reset
- [ ] synth.py: 生成 Yosys .ys 脚本，调用 `yosys -q -s`
- [ ] 通过 LSV01 (最简单电路，1102 行组合逻辑)

**Phase 2: 全部 10 个公开电路正确**
- [ ] LSV01-LSV10 全部输出功能正确的 netlist
- [ ] 不同电路使用不同 ABC 序列（通过 config.json 驱动）
- [ ] 自动回退: point 失败时用 `$default` 重试

**Phase 3: 多 Point + PPA 优化**
- [ ] 每电路支持 1-7 个优化点
- [ ] 自动调参: 尝试多种 ABC 序列，选最优 PPA
- [ ] 内置仿真验证: iverilog 自检

### config.json 格式
```json
{
  "$default": [
    {"name": "balanced", "abc_script": "+strash; compress2rs; dch; map"}
  ],
  "LSV01": [
    {"name": "balanced", "abc_script": "+strash; compress2rs; dch; map"},
    {"name": "area", "abc_script": "+strash; resyn2rs; dch; map"},
    {"name": "timing", "abc_script": "+strash; if -K 6 -g -C 8; dch; map"}
  ]
}
```

### ABC 优化序列参考

| 序列 | 特点 | 用途 |
|------|------|------|
| `+strash; compress2rs; dch; map` | 平衡面积/延迟 | 默认 |
| `+strash; resyn2rs; dch; map` | 偏面积优化 | 面积敏感电路 |
| `+strash; if -K 6 -g -C 8; dch; map` | 偏延迟优化 | 时序敏感电路 |
| `+strash; compress2rs; compress2rs; dch; map` | 激进面积 | 两轮优化 |

### Makefile 模板
```makefile
FILELIST ?= filelist.txt
TOP ?= tb
THREADS ?= 4
SIM_EXE ?= sim.out

.PHONY: build synth clean

build:
	mkdir -p bin
	cp src/synth.py bin/synth_tool
	chmod +x bin/synth_tool

synth:
	python3 src/synth.py --rtl $(RTL) --top $(TOP) --sdc $(SDC) \
	  --liberty $(LIBERTY) --config $(CONFIG) --circuit $(CIRCUIT) \
	  --point $(POINT) --out-dir $(OUT_DIR)

clean:
	rm -rf bin/synth_tool __pycache__ src/__pycache__
```

### 测试流程
```bash
cd Track-A/A3-synthesis

# 构建
make build

# 综合 LSV01
make synth \
  RTL=testcases/LSV01/rtl/design.v \
  TOP=top \
  SDC=testcases/LSV01/constraints.sdc \
  LIBERTY=<Nangate45_lib_path> \
  CONFIG=config.json \
  CIRCUIT=LSV01 \
  POINT=1 \
  OUT_DIR=/tmp/lsv01_test

# 检查输出
cat /tmp/lsv01_test/netlist.v  # 应包含 Nangate45 标准单元
```

### 关键参考文件
- **赛题规范**: `Track-A/A3-synthesis/spec.md`
- **评分细则**: `Track-A/A3-synthesis/scoring.md`
- **公开电路**: `Track-A/A3-synthesis/testcases/LSV01-LSV10/`
- **提交模板**: `Track-A/A3-synthesis/testcases/submission_template/`
- **综合策略研究**: `.planning/research/A3_STRATEGY.md` (901行，ABC 序列、PPA 优化)
- **参考 Yosys 脚本**: `Track-A/A3-synthesis/testcases/scripts/run_yosys.py`
- **参考结果**: `Track-A/A3-synthesis/testcases/references/`

### 评分公式
```
PPA Hypervolume (90分) + Runtime (5分) + Originality (5分) = 100分/电路
20 个电路 (10 公开 + 10 隐藏) 平均 = 最终 A3 分
```

**PPA Hypervolume**: 你的点的 Pareto 前沿面积 / 参考前沿面积 × 90
**Runtime**: 参考综合时间 / 你的综合时间 × 5
**Originality**: 自研模块、算法贡献、消融证据 × 5

### 原创性加分方向
- 自适应策略选择（不同电路类别用不同流程）
- 自动调参搜索（不是预设固定序列）
- 电路分析启发式（根据 RTL 结构选择优化策略）

---

# A2: 验证环境自动生成（队友2 — 不变）

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

### 优先级

**Phase 1: 骨架门禁 (3分/电路)**
- [ ] RTL 解析: 识别端口方向/宽度/时钟/复位
- [ ] 接口协议推断: AXI / SRAM / valid-ready
- [ ] cocotb testbench 骨架生成: 时钟/复位/驱动/监视
- [ ] run.py 入口: RTL → testbench → 仿真 → 结果
- [ ] 通过 case1 骨架门禁

**Phase 2: 覆盖率收集 (7分/电路)**
- [ ] 行/分支覆盖率: gcov/lcov
- [ ] 功能覆盖 bin: cocotb 采样
- [ ] 约束随机测试: 5000 序列, 固定 seed
- [ ] 目标: C ≥ 85%

**Phase 3: 通用化**
- [ ] 处理 10 个隐藏电路 (不能硬编码)
- [ ] 自适应接口驱动策略

### 关键参考
- 公开数据集: `Track-A/A2-verification/testcases/A2_public_dataset/case1-5/`
- case1 的 JSON 格式就是输出标准
- cocotb 文档: https://docs.cocotb.org/

### 覆盖率公式
```
C = 0.4 × 行覆盖率 + 0.3 × 分支覆盖率 + 0.3 × 功能覆盖率
C ≥ 85% → 7分/电路 | 65-85% → 4.9分 | 45-65% → 2.8分 | <45% → 0分
```

---

# A1: 轻量 RTL 仿真器（你 — 负责人）

## 目标
构建事件驱动 Verilog RTL 仿真器，支持 Verilog-2001 核心子集。

## 技术方案: C++ + flex/bison

### 代码复用资源
- **NEMU** (`~/ysyx-workbench/nemu/`) — 执行引擎、内存模型、调试器模式
- **Verilator** (`~/ysyx-workbench/verilator/`) — AST 定义、解析器架构
- **NPC** (`~/ysyx-workbench/npc/`) — 额外测试用例

### 优先级

**Phase 1: 基础功能 (14分)**
- [ ] flex/bison 解析器: module, assign, always, reg/wire, if/case/for, parameter
- [ ] 组合逻辑仿真
- [ ] 系统函数: $fopen, $fscanf, $fdisplay, $fgets, $display, $finish
- [ ] 通过 basic01-05, alu, priority_encoder (各2分 = 14分)

**Phase 2: 高级特性 (8分)**
- [ ] 时序仿真: posedge clk, 非阻塞赋值
- [ ] DFF 建模 (异步复位)
- [ ] `define / `include, 多文件层次
- [ ] 通过 i2c(3分), ip(2分), axis_fifo(2分), sha256(2分)

**Phase 3: 性能优化 (11分)**
- [ ] GEMM 通过 (含编译/仿真/多核性能分)
- [ ] 增量编译 + 并行仿真

---

# GSD 辅助流程（队友专用）

## 快速开始

```bash
# 1. 进入项目目录
cd ~/Documents/github/AI4S

# 2. 创建 GSD 项目
/gsd-new-project
# 描述: "基于 Yosys 的 RTL 逻辑综合工具"
# 选择: YOLO 模式 + Coarse granularity

# 3. 规划 Phase 1
/gsd-plan-phase 1
# Claude 创建执行计划

# 4. 执行 Phase 1
/gsd-execute-phase 1
# Claude 写代码，你审查和测试

# 5. 后续 Phase
/gsd-plan-phase 2
/gsd-execute-phase 2
```

## 关键原则

1. **让 Claude 写代码** — 你负责描述需求、审查代码、运行测试
2. **先跑通再优化** — 功能正确 > 性能优化
3. **频繁测试** — 每完成一个任务就运行测试用例
4. **参考 `.planning/research/A3_STRATEGY.md`** — 901 行综合策略研究
5. **参考 `testcases/scripts/run_yosys.py`** — 官方参考 Yosys 脚本
6. **遇到问题及时沟通**

## 项目目录结构

```
~/Documents/github/AI4S/
├── Track-A/
│   ├── A1-simulator/     ← 你的工作目录 (A1)
│   ├── A2-verification/  ← 队友2 的工作目录 (A2)
│   └── A3-synthesis/     ← 队友的工作目录 (A3)
├── .planning/
│   ├── PROJECT.md        ← 项目上下文
│   ├── REQUIREMENTS.md   ← 69 条需求
│   ├── ROADMAP.md        ← 执行路线图
│   └── research/
│       ├── A3_STRATEGY.md  ← A3 综合策略 (901行)
│       └── YSYX_REUSE.md   ← 代码复用分析
├── TEAM_GUIDE.md         ← 本文件
└── .claude/CLAUDE.md     ← 项目指南
```

---

# 时间线建议（更新于 7/13）

| 时间 | 你 (A1) | 队友 (A3) | 队友2 (A2) |
|------|---------|----------|-----------|
| 7/13 上午 | flex/bison 解析器 + 基础仿真 | 框架 + LSV01 综合 | RTL 解析 + case1 骨架 |
| 7/13 下午 | basic01-05 + alu 通过 | 10 电路全部正确 | 覆盖率收集 |
| 7/13 晚 | 高级特性 (i2c, ip, sha256) | 多 Point + 自动调参 | 通用化 (隐藏电路) |
| 7/14 上午 | GEMM + 性能优化 | PPA 优化 | 覆盖率 ≥85% |
| 7/14 下午 | 并行仿真 + 增量编译 | 测试 + 修复 | 测试 + 修复 |
| 7/14 晚 | 测试 + 修复 | 提交准备 | 提交准备 |
| 7/15 10am | **提交** | **提交** | **提交** |
