# AI4S — Agentic4Systems 暑期学校 GPGPU 竞赛 2026

## 赛道 A：EDA 软件

三人为一队，完成三道 EDA 工具赛题：

| 子题 | 目标 | 负责人 | 技术栈 |
|------|------|--------|--------|
| **A1** | 轻量 RTL 仿真器 | 队长 | C++ + flex/bison |
| **A2** | 验证环境自动生成 | 队友2 | Python + cocotb + Verilator |
| **A3** | RTL 逻辑综合工具 | 队友 | Python + Yosys |

**评分**: A1 + A2 + A3 各 100 分，取平均 = 赛道总分

## 目录结构

```
Track-A/
  A1-simulator/      ← A1：事件驱动 Verilog RTL 仿真器
  A2-verification/   ← A2：自动验证环境生成
  A3-synthesis/      ← A3：RTL 逻辑综合工具
.planning/           ← 项目管理文件（需求、路线图、计划）
TEAM_GUIDE.md        ← 队友启动指南
```

## 快速开始

```bash
# 查看赛题规范
cat Track-A/A1-simulator/spec.md
cat Track-A/A2-verification/spec.md
cat Track-A/A3-synthesis/spec.md

# 查看评分细则
cat Track-A/A1-simulator/scoring.md
cat Track-A/A2-verification/scoring.md
cat Track-A/A3-synthesis/scoring.md

# 查看公开测试用例
ls Track-A/A1-simulator/testcases/sim_public/benchmark/
ls Track-A/A2-verification/testcases/A2_public_dataset/
ls Track-A/A3-synthesis/testcases/
```

## 截止时间

**2026年7月15日 上午10:00**

## 环境要求

- Linux x86_64
- GCC/G++ 13.3.0
- Python 3.10+
- Yosys 0.64+
- Icarus Verilog 10.3+
- Verilator 5.x（A2 覆盖率采集：`--coverage-line+branch`）
- cocotb (pip install cocotb)
- cocotb-test（A2 Verilator 后端）
- flex/bison

## GSD 工具

项目使用 [GSD (Get Stuff Done)](https://github.com/open-gsd/gsd-core) 工具辅助开发：

```bash
# 查看项目进度
/gsd-progress

# 规划和执行阶段
/gsd-plan-phase N
/gsd-execute-phase N

# 快速任务
/gsd-quick "任务描述"
```
