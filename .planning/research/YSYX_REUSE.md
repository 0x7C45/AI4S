# YSYX Workbench 代码复用分析

**来源:** ~/ysyx-workbench/ 目录探索
**目的:** 为 A1 仿真器和 A2 验证生成找可复用代码

## 目录概览

| 目录 | 内容 | 语言 | 对 A1/A2 的价值 |
|------|------|------|-----------------|
| npc/ | RISC-V 处理器 RTL 设计 | Verilog | ★ A2 测试素材 |
| nemu/ | NJU EMUlator — CPU 模拟器 | C | ★★★ A1 仿真引擎参考 |
| verilator/ | Verilator 源码 | C++ | ★★★★ A1 解析器架构参考 |
| yosys-sta/ | Yosys + STA 工具 | Python/脚本 | ★ A3 可用 |
| c/ | C 项目 (minirvEMU, sEMU) | C | ★★ A1 可参考 |
| abstract-machine/ | AM 抽象层 | C | ★ 设备模型参考 |
| nvboard/ | 虚拟 FPGA 板 | C++ | ★ Verilator 集成参考 |
| oss-cad-suite/ | 开源 EDA 工具套件 | - | ★★ 工具链 |

## 对 A1 仿真器的复用建议

### 1. NEMU (CPU 模拟器) — 核心参考

NEMU 是一个完整的 CPU 模拟器，包含：
- **指令解码器** — 与 Verilog 解析类似的数据驱动模式
- **执行引擎** — 循环执行 + 状态更新模式
- **内存模型** — 地址空间管理
- **设备模拟** — 外设交互框架
- **调试器 (sdb.c)** — readline 交互 + 命令表模式
- **Difftest** — 参考模型比对框架

**可复用模式:**
```c
// NEMU 的命令表模式 (sdb.c) — 可用于仿真器命令接口
static struct {
  const char *name;
  const char *description;
  int (*handler)(char *);
} cmd_table[] = {
  {"help", "Display help", cmd_help},
  {"c", "Continue execution", cmd_c},
  {"q", "Exit", cmd_q},
};
```

### 2. Verilator 源码 — 解析器架构参考

Verilator 包含完整的 Verilog/SystemVerilog 解析器：
- `src/V3Parse*.cpp` — 语法分析器
- `src/V3Ast.h` — AST 节点定义
- `src/V3Active.cpp` — always 块处理
- `src/V3Simulate.h` — 仿真相关

**关键参考:**
- AST 节点类型定义（module, always, assign, reg, wire 等）
- 语法分析器的组织结构
- 层次化模块实例化的处理

### 3. NPC (处理器设计) — 测试素材

NPC 包含简单 RISC-V 处理器的 Verilog 设计：
```
vsrc/regfile.v  — 寄存器文件
vsrc/pc_reg.v   — PC 寄存器
vsrc/alu.v      — ALU
vsrc/rom.v      — ROM
vsrc/top.v      — 顶层模块
vsrc/seg.v      — 七段显示
```

**用途:** 可作为 A1 仿真器的额外测试用例（在 basic 之外）

## 对 A2 验证生成的复用建议

### 1. NPC RTL — 接口解析测试

NPC 的 Verilog 文件包含：
- 简单端口声明（input/output）
- always @(posedge clk) 时序逻辑
- parameter 参数化
- module 实例化

**用途:** 测试 RTL 接口解析器能否正确识别这些模式

### 2. cocotb 集成参考

NVBoard 与 Verilator 的集成模式可参考：
- Pin 映射 (`pins.h` — PinNode 结构)
- 信号访问 (`pin_peek`/`pin_poke` 函数)
- Makefile 集成 (`nvboard.mk`)

## 工具链

| 工具 | 路径 | 用途 |
|------|------|------|
| oss-cad-suite | ~/ysyx-workbench/oss-cad-suite/ | yosys, iverilog, verilator |
| yosys-sta | ~/ysyx-workbench/yosys-sta/ | Yosys + OpenSTA |

## 关键结论

1. **NEMU 的 C 代码**对 A1 最有价值 — 执行引擎、内存模型、调试器模式可直接参考
2. **Verilator 的解析器架构**是 A1 flex/bison 设计的最佳参考
3. **NPC 的 Verilog 文件**可作为额外测试用例
4. **NVBoard 的 Pin 映射**对 A2 的信号驱动有参考价值
5. **oss-cad-suite** 提供了完整的 EDA 工具链
