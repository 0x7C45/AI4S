# A2 验证环境自动生成 — 需求规格

> 来源：spec.md（官方 locked）、scoring.md（官方 locked）、PLAN.md、CONSTRAINTS.md
> 权威：spec.md / scoring.md 为最高优先级，本文件仅汇总。

## 需求总览

| ID | 需求 | 优先级 | Phase |
|----|------|--------|-------|
| A2-01 | run.sh 五参数入口跑通完整流水线 | P0 | 1 |
| A2-02 | RTL 解析 — 端口/时钟/复位/参数/协议推断 | P0 | 1 |
| A2-03 | cocotb+Verilator testbench 骨架 — 门禁五项 | P0 | 1 |
| A2-04 | 约束随机 — seed=20260630 穿透，5000 序列 | P0 | 2 |
| A2-05 | 覆盖率采集 — 行/分支/功能三类 | P0 | 2 |
| A2-06 | 7 JSON 产物齐全且语义正确 | P0 | 2 |
| A2-07 | 综合公式 C = 0.4/0.3/0.3 | P0 | 2 |
| A2-08 | 10 隐藏电路通用化（禁硬编码） | P0 | 3 |
| A2-09 | 离线打包 — wheelhouse + requirements.txt | P0 | 3 |

## 详细需求

### A2-01: 运行入口（P0, Phase 1）
统一入口 `./run.sh --rtl <dir> --top <module> --out <dir> --seed 20260630 --num-seq 5000`，完成 RTL 解析 → testbench 骨架 → 约束随机序列 → 仿真 → 覆盖率收集 → 7 JSON 输出。评测人员不应手动修改生成文件。
- **验收**：run.sh 独自跑通，7 JSON + generated_tb/ + generated_tests/ 齐备。

### A2-02: RTL 接口解析（P0, Phase 1）
解析 RTL 模块接口：识别时钟、复位、参数、端口方向、端口宽度、协议分组。推断接口协议（AXI4-Lite/AXI/AXI-like、SRAM-like、Streaming valid/ready）。
- **关键陷阱**：design.json 的 top_module（目录别名 caseN）与 RTL 真实模块名不一致，必须自行解析真实模块名。
- **验收**：design.json 含顶层模块名、文件列表、时钟/复位、端口方向/宽度/类型/协议分组、推断协议。

### A2-03: testbench 骨架门禁（P0, Phase 1）
生成 cocotb+Verilator testbench：时钟/复位生成、输入驱动、输出监视、自动比对框架（scoreboard）、ready 反压。支持三类接口。
- **门禁失败条件**（任一命中 → 整电路 0 分）：①testbench 无法编译/仿真无法启动 ②DUT 端口未连接/错连/宽度不匹配 ③时钟/复位/协议握手不可用 ④无有效驱动/监视 ⑤scoreboard 未比对或静默忽略失败。
- **烟雾测试确认**：COMPILE_ARGS 必须含 `-Wno-fatal`（Verilator lint 致命）。
- **验收**：case1 跑通，门禁五项不命中。

### A2-04: 约束随机测试（P0, Phase 2）
固定 seed=20260630，固定序列数=5000，seed 穿透到 `random.Random(seed)` + directed 边界值。
- **硬约束**：无可复现 seed → 覆盖率上限 3 分；相同 seed + 相同 RTL → 一致或等价结果。
- **验收**：constraints.json 含 seed=20260630、序列数=5000、随机变量列表、覆盖率反馈约束调整记录。

### A2-05: 覆盖率采集（P0, Phase 2）
- **行覆盖率**（权重 0.4）：Verilator `--coverage-line` 插桩 → coverage.dat LCOV 解析
- **分支覆盖率**（权重 0.3）：`--coverage-line` 自动产出（branch 是 line coverage 结构化副产品）
- **功能覆盖率**（权重 0.3）：cocotb bin 真实事务采样，4 类模板（FSM/数据通路/存储器/AXI）
- **关键**：覆盖率 scope 必须对应当前 RTL 子树（排除 wrapper 稀释）；功能 bin 必须有真实事务采样证据，不空 hit、不初始化一次性 hit。
- **验收**：coverage_result.json 含三类覆盖率 + 综合 C。

### A2-06: 7 JSON 产物（P0, Phase 2）
1. design.json 2. verification_skeleton.json 3. constraints.json 4. coverage_bins.json 5. functional_coverage.json 6. coverage_result.json 7. report.json + generated_tb/ + generated_tests/
- **验收**：7 JSON 齐全且字段语义正确（见 spec.md §3 各文件 schema）。

### A2-07: 综合公式（P0, Phase 2）
`C = 0.4×行 + 0.3×分支 + 0.3×功能`。coverage_result.json 必须写 0.4/0.3/0.3（严禁抄公开样例 0.42/0.28/0.30）。
- **档位**：C≥85%→7分 | 65-85%→4.9分 | 45-65%→2.8分 | <45%→0分。

### A2-08: 10 隐藏电路通用化（P0, Phase 3）
框架对 10 个隐藏电路通用化，禁止硬编码/针对性优化。策略必须通用、可适配未知 RTL。
- **六条红线**：禁抄袭/禁硬编码/禁绕评测/禁预计算/禁针对性优化/禁未披露依赖。

### A2-09: 离线打包（P0, Phase 3）
- requirements.txt 每包钉死 ==X.Y.Z
- wheelhouse/ 离线包：`pip download --platform manylinux2014_x86_64 --python-version 3.12 --only-binary=:all:`；评测机 `pip install --no-index --find-links=wheelhouse`
- THIRD_PARTY.md：版本/许可/调用边界
- **镜像无 pip 注意**：wheelhouse 可能还需含 pip bootstrap 或改用 venv

## 锁版本表

| 组件 | 版本 |
|------|------|
| Python | 3.12.x |
| Verilator | 5.050（镜像 tag: verilator/verilator:v5.050）|
| cocotb | 2.0.1 |
| cocotb-test | 0.2.6 |
| cocotbext-axi | 0.1.28 |
| Jinja2 | 3.1.6 |
| PyVerilog | 1.3.0 |
| z3-solver | 4.16.0.0（可选）|

---
*Last updated: 2026-07-14*
