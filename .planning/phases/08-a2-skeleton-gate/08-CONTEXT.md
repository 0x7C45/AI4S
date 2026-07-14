# Phase 8: 骨架门禁 — RTL 解析 + cocotb/Verilator testbench 生成 - Context

**Gathered:** 2026-07-14
**Status:** Ready for planning
**Source:** Derived from PLAN.md + CONSTRAINTS.md + spec.md + SMOKE_TEST_REPORT.md (pre-locked decisions, skip discuss-phase)

<domain>
## Phase Boundary

Phase 8 交付：一个 `run.py` 五参数入口，能读取 RTL → 解析接口 → 生成 cocotb+Verilator testbench 骨架 → 在 Docker linux/amd64 + Verilator 5.050 下编译仿真通过 → 产出 design.json + verification_skeleton.json。

**Phase 8 不做**：覆盖率采集（Phase 9）、约束随机 5000 序列（Phase 9）、功能 bin（Phase 9）、10 隐藏电路通用化（Phase 10）、离线打包（Phase 10）。

**门禁验收**（case1）：testbench 能编译、能跑、DUT 端口连对、有时钟/复位/驱动/监视/scoreboard/反压。门禁五项任一命中 → 整电路 0 分。

</domain>

<decisions>
## Implementation Decisions (LOCKED — 烟雾测试已验证)

### 架构（来自 PLAN.md §三）
- **入口**：`run.py`（完整流水线：解析→骨架→序列→仿真→覆盖→报告）
- **源码结构**：
  - `src/rtl_parser.py` — RTL 接口解析（端口/时钟/复位/协议识别）
  - `src/skeleton_gen.py` — 验证骨架生成（cocotb testbench Jinja2 模板）
  - `templates/cocotb_tb.py.j2` — cocotb testbench 模板
- **Phase 8 只实现**：rtl_parser + skeleton_gen + run.py 骨架（解析→生成 testbench→调 cocotb 仿真）。constraint_gen/coverage_gen/sim_runner/coverage_collect/report_gen 在 Phase 9 补。

### 技术栈（LOCKED，烟雾测试已验证）
- **cocotb 2.0.1** + **cocotb-test 0.2.6**（Verilator 后端）
- **cocotbext-axi 0.1.28**（AXI 驱动，实测与 cocotb 2.0.1 兼容）
- **Jinja2 3.1.6**（testbench 模板渲染）
- **PyVerilog 1.3.0**（RTL 解析）
- **Verilator 5.050**（仿真器，镜像 `verilator/verilator:v5.050`）

### 运行环境（LOCKED — win-ZCode 主路线）
- **Docker linux/amd64**（Windows + Docker Desktop），与评测 OS 同构
- 镜像 `verilator/verilator:v5.050`：Ubuntu 24.04 + Python 3.12.3 + g++ 13.3 自带
- **镜像无 pip**：run.sh/Dockerfile 必须含 `apt-get install python3-pip` bootstrap

### 烟雾测试确认的关键约束（SMOKE_TEST_REPORT.md）
1. **COMPILE_ARGS 必须含 `-Wno-fatal`**：Verilator 默认 lint 致命，case1 RTL 有 34 个 WIDTHEXPAND/WIDTHTRUNC/CASEINCOMPLETE warning。不传则编译失败。
2. **cocotb 2.0 API 适配**：生成 testbench 必须用 `unit=`（非 `units=`）、`Immediate()`、`cancel()`（非 `kill()`）。
3. **Makefile 默认 `SIM=vcs`**：生成的 Makefile 必须默认 `SIM=verilator`。
4. **产物隔离**：run.py 用 `--out` 隔离产物，不能写 testcases（locked）。

### RTL 解析决策（来自 CONSTRAINTS.md §10）
- **top_module 陷阱**：design.json 的 top_module（目录别名 caseN）与 RTL 真实模块名不一致。必须自行解析真实模块名（如 case1 → axi_adapter_rd），不能盲信 design.json。
- **协议推断**：三类接口 AXI4-Lite/AXI/AXI-like、SRAM-like、Streaming valid/ready。

### testbench 骨架门禁五项（CONSTRAINTS.md §7，任一命中=0分）
1. testbench 能编译、仿真能启动（COMPILE_ARGS 含 -Wno-fatal）
2. DUT 端口正确连接（宽度匹配、不错连）
3. 时钟/复位/协议握手可用
4. 有有效驱动/监视（valid/ready 接口必须设 ready 反压）
5. scoreboard 实际比对（不静默忽略失败）

### Claude's Discretion
- rtl_parser 用 PyVerilog 还是正则解析（PyVerilog 对 cocotb-style Verilog 可能有问题，可降级正则）
- testbench 模板的具体 Jinja2 结构（driver/monitor 怎么组织）
- AXI 驱动用 cocotbext-axi 的 AxiMasterBus 还是手写（倾向 cocotbext-axi，烟雾测试已验证）
- 仿真调度：直接 make 还是 cocotb-test Python API

</decisions>

<canonical_refs>
## Canonical References

**Downstream agents MUST read these before planning or implementing.**

### 赛题规格（官方 locked）
- `Track-A/A2-verification/spec.md` — 赛题说明（输入输出格式、7 JSON schema、运行入口）
- `Track-A/A2-verification/scoring.md` — 评分（综合公式 0.4/0.3/0.3、门禁、档位）

### 技术方案（团队 locked）
- `Track-A/A2-verification/PLAN.md` — cocotb+Verilator 路线、架构、三阶段、陷阱清单
- `Track-A/A2-verification/CONSTRAINTS.md` — 硬约束 16 节（门禁、公式、seed、scope）
- `Track-A/A2-verification/ENVIRONMENT.md` — 运行环境、锁版本表、Docker 命令
- `Track-A/A2-verification/PITFALLS.md` — 10 类陷阱（cocotb 2.0 时序、Verilator lint、scope）

### 环境背书（烟雾测试）
- `Track-A/A2-verification/smoke_out/SMOKE_TEST_REPORT.md` — 环境验证结论 + 5 项实现待办

### 公开样例（参考标杆，只读严禁修改）
- `Track-A/A2-verification/testcases/A2_public_dataset/case1/` — case1 完整样例（RTL/wrapper/testbench/JSON）
- `Track-A/A2-verification/testcases/A2_public_dataset/functional_coverage.py` — 功能覆盖采样（cocotb bin）

**注意：代码实现在 E 盘 `E:/AI4S/Track-A/A2-verification/`，规划在本地 C 盘 `.planning/`。实现时操作 E 盘文件。**

</canonical_refs>

<specifics>
## Specific Ideas

- case1 烟雾测试通过的最小命令（planner 可参考作为门禁验收基准）：
  ```bash
  # 容器内，case1 目录
  COMPILE_ARGS='-Wno-fatal' make SIM=verilator MODULE=test_case1_json_sequences TESTCASE=run_json_sequences
  ```
- case1 真实模块 `axi_adapter_rd`，wrapper `case1_cocotb_top`（硬编码参数 ADDR=16/S=32/M=16）
- cocotbext-axi 用法参考 `test_case1_json_sequences.py`：`AxiMasterRead(AxiReadBus.from_prefix(dut, "s_axi"))` + `AxiRamRead(AxiReadBus.from_prefix(dut, "m_axi"))`
- RTL 解析参考：verilog-axi 系列模块端口命名规律（`s_axi_*` / `m_axi_*` 前缀，clk/rst 全小写）

</specifics>

<deferred>
## Deferred Ideas

- 覆盖率采集（line/branch/functional）→ Phase 9
- 约束随机 5000 序列 → Phase 9
- RTL generate/if 死码静态分析 → Phase 9
- 10 隐藏电路通用化 → Phase 10
- 离线打包（wheelhouse） → Phase 10
- cocotbext-axi 弃用警告清理（非致命，Phase 10 收尾时处理）

</deferred>

---

*Phase: 01-rtl-cocotb-verilator-testbench*
*Context gathered: 2026-07-14 (derived from PLAN.md + smoke test, skip discuss-phase)*
