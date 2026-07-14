# Phase 1 Summary: 骨架门禁 — RTL 解析 + cocotb/Verilator testbench 生成

**Phase:** A2-01-rtl-cocotb-verilator-testbench
**Status:** Complete
**Date:** 2026-07-14

## What Was Built

### 核心实现文件（8 个）
| 文件 | 功能 |
|---|---|
| `run.py` | 五参数入口（--rtl/--top/--out/--seed/--num-seq），完整流水线 parse→skeleton→simulate |
| `run.sh` | bash wrapper |
| `src/__init__.py` | 包标记 |
| `src/rtl_parser.py` | RTL 接口解析（正则）：真实模块名/端口/参数/时钟/复位/协议推断 |
| `src/skeleton_gen.py` | testbench 骨架生成（Jinja2）：渲染 + Makefile + verification_skeleton.json |
| `src/sim_runner.py` | 仿真执行器：Docker verilator/verilator:v5.050 容器内 make |
| `templates/cocotb_tb.py.j2` | cocotb testbench Jinja2 模板（cocotb 2.0 API） |
| `requirements.txt` | cocotb==2.0.1 等 5 包钉死版本 |

### 数据结构
- `DesignInfo`（dataclass）— RTL 解析结果：top_module/files/parameters/ports/clock/reset/inferred_protocols
- `SkeletonResult`（dataclass）— 骨架生成结果：testbench_path/makefile_path/skeleton_json_path
- `SimResult`（dataclass）— 仿真结果：passed/exit_code/stdout/stderr

## Goal Achievement

### ROADMAP Phase 1 五条 Success Criteria
1. ✅ run.py 五参数入口跑通（--rtl --top --out --seed --num-seq）
2. ✅ RTL 解析输出 design.json（端口/时钟/复位/参数/协议推断）
3. ✅ testbench 在 Verilator 后端编译（COMPILE_ARGS=-Wno-fatal）并仿真通过
4. ✅ DUT 端口正确连接 + 时钟/复位/驱动/监视/scoreboard/反压
5. ✅ case1 门禁五项不命中（全部验证通过）

### 门禁五项验证（CONSTRAINTS §7）
| 门禁项 | 实现 | 验证 |
|---|---|---|
| ① testbench 编译 | COMPILE_ARGS=-Wno-fatal | results.xml testcase PASS |
| ② DUT 端口连接 | AxiReadBus.from_prefix | s_axi/m_axi 端口匹配 |
| ③ 时钟/复位/握手 | Clock(unit=ns) + reset_dut | rst 高8拍低8拍 |
| ④ 驱动/监视/反压 | AxiMasterRead + set_pause_generator ×4 | 4 通道反压 |
| ⑤ scoreboard 比对 | assert read.data == data | 每事务 assert |

### CONTEXT.md 决策覆盖（D-01~D-10）
全部 10 项锁定决策已实现并验证。

## case1 端到端验收结果

```
python3 run.py --rtl testcases/.../case1/rtl --top case1 --out smoke_out/case1_gatecheck --seed 20260630 --num-seq 5000

[parse] OK — top_module=axi_adapter_rd, clock=clk, reset=rst, protocols=['AXI']
[skeleton] OK — testbench=generated_tb/generated_test.py
[simulate] OK — exit=0
```

- design.json: top=axi_adapter_rd（真实模块名，非 case1 别名）
- verification_skeleton.json: 完整 schema
- Docker 仿真 testcase run_generated_test PASS（sim_time=2004260ns）

## Deviations from Plan

无重大偏离。一个实现细节：
- rtl_parser 用正则解析而非 PyVerilog（CONTEXT.md Claude's Discretion 已授权）——正则更轻量可控，对 AXI 风格 Verilog 解析正确。

## Lessons Learned

1. **主机无依赖不影响交付**：jinja2/cocotb 装在主机用于开发期验证，交付在 Docker 容器（镜像自带 Python 3.12 + g++，只需 apt bootstrap pip）。
2. **cocotb 2.0 弃用警告非致命**：参考代码用 `units=`（旧），模板用 `unit=`（新），均能跑。Phase 3 收尾时清理。
3. **MSYS_NO_PATHCONV 关键**：Git Bash 会把 Docker 挂载路径 `/work` 转成 Windows 路径，必须用 `MSYS_NO_PATHCONV=1`。
4. **Verilator 参数化模块**：axi_adapter_rd 有参数（S=32/M=16），Verilator 用默认参数也能跑（测试用 AXI 协议握手，参数影响数据宽度但不阻断门禁）。

## What's Next (Phase 2)

Phase 2「覆盖率收集」需补：
- `src/constraint_gen.py` — 约束随机 5000 序列生成
- `src/coverage_gen.py` — 功能 bin 定义（4 类模板：FSM/数据通路/存储器/AXI）
- `src/coverage_collect.py` — Verilator coverage.dat LCOV 解析 + 功能覆盖汇总
- `src/report_gen.py` — 7 JSON 完整产出（coverage_result.json + coverage_bins.json + functional_coverage.json）
- RTL generate/if 死码静态分析（避免 case1 53% 天花板）
- coverage_result.json 综合公式 0.4/0.3/0.3
