# Phase 1: A3 Framework + RTL Frontend — Context

**Gathered:** 2026-07-12
**Status:** Ready for execution
**Source:** Discuss-phase (post-planning context capture)

<domain>
## Phase Boundary

构建 A3 RTL 逻辑综合工具的端到端 pipeline：从 Verilog 输入到 Nangate45 门级网表输出。包括 Makefile 接口、配置解析、Yosys 综合流程、LSV01 验证。

</domain>

<decisions>
## Implementation Decisions

### Yosys 调用方式
- **选择: CLI 脚本模式** — Python 生成 `.ys` 脚本文件，调用 `yosys -q -s script.ys`
- 理由: 最简单、调试方便、研究文档也是这个方案
- 不用 Python API（依赖复杂）或 C++ Plugin（时间不够）

### 综合流程架构
- **选择: 统一流程 + 可变 ABC 序列** — 所有电路用相同 Yosys 流程，只变 ABC 序列参数
- 流程: read_liberty → read_verilog → hierarchy → proc → opt → fsm → wreduce → peepopt → alumacc → share → memory_map → techmap → abc → dfflibmap → opt → write_verilog
- 不按电路类别分支（保持简单，61小时时限）

### SDC 约束处理
- **选择: Yosys `read_sdc`** — 直接使用 Yosys 内置 SDC 读取功能
- Yosys 0.54+ 原生支持，无需手动解析

### problem.yaml 元数据
- **选择: Python 解析** — 用 PyYAML 或正则提取 top_module、clock、reset 字段
- 当 `--top` 未提供时，从 problem.yaml 读取默认值
- 同样读取 clock/period 信息用于 SDC 约束验证

### 内置正确性自检
- **选择: 内置仿真验证** — 综合后自动用 Icarus Verilog 仿真，比对 golden trace
- 可提前发现问题，增加信心
- 如果仿真环境不可用（无 iverilog），优雅降级为仅输出 netlist

### 综合失败回退
- **选择: 自动回退** — 如果某个 point 综合失败，自动回退到 $default 配置重试
- 避免单个电路因配置问题导致整体失败

### Claude's Discretion
- Yosys 脚本的具体 pass 参数调优（研究文档已提供参考）
- 错误处理细节和日志格式
- netlist.v 的后处理和清理

</decisions>

<canonical_refs>
## Canonical References

**Downstream agents MUST read these before implementing.**

### 赛题规范
- `Track-A/A3-synthesis/spec.md` — 赛题完整规范（Makefile 接口、参数、交付物要求）
- `Track-A/A3-synthesis/scoring.md` — 评分细则（PPA Hypervolume、Runtime、Originality）

### 公开电路
- `Track-A/A3-synthesis/testcases/LSV01/` — 最简单电路，Phase 1 验证目标
- `Track-A/A3-synthesis/testcases/` — 全部 10 个公开电路目录

### 提交模板
- `Track-A/A3-synthesis/testcases/submission_template/` — Makefile、config.json、submission.yaml 模板

### 技术研究
- `.planning/research/A3_STRATEGY.md` — Yosys 合成流程、ABC 序列、PPA 优化策略、已知陷阱

### PDK 库
- Nangate45 Liberty 文件路径由评测系统通过 LIBERTY 参数传入

</canonical_refs>

<specifics>
## Specific Ideas

- 综合流程中 `abc` 命令必须包含 `map` 结尾（研究文档陷阱 #1）
- `dfflibmap` 必须在 `abc` 之后执行（研究文档陷阱 #2）
- 首个验证目标: LSV01 (epfl_priority)，1102 行 RTL，组合优先级电路
- config.json 初始配置: 每电路 1 个 point（balanced），后续扩展到 7 个
</specifics>

<deferred>
## Deferred Ideas

- 多 Point PPA 策略（Phase 3）
- 自动调参搜索（Phase 3）
- 隐藏电路适配（Phase 4）
- 自定义 Yosys pass（Phase 3 或后续）

</deferred>

---

*Phase: 01-a3-framework-rtl-frontend*
*Context gathered: 2026-07-12 via discuss-phase*
