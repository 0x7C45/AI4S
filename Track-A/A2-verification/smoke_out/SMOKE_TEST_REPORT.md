# A2 win-ZCode 烟雾测试报告

> 日期：2026-07-14
> 执行者：win-ZCode（ZCode on Windows + Docker linux/amd64）
> 目的：验证 win-ZCode 主运行环境（Docker linux/amd64 + Verilator 5.050）下，case1 公开样例可编译、可仿真、覆盖率管道可用。
> 范围：环境验证，**非 win-ZCode 自身实现**（用公开样例现成 cocotb 测试）。

---

## 1. 环境（已验证可用）

| 组件 | 版本 | 来源 |
|---|---|---|
| 宿主 | Windows + Docker Desktop | win-ZCode 主路线（ENVIRONMENT.md §2.3）|
| 容器 OS | Ubuntu 24.04.4 LTS | `verilator/verilator:v5.050` 镜像 |
| 架构 | linux/amd64（与评测 OS 同构）| `--platform linux/amd64` |
| Verilator | **5.050** 2026-07-01 rev v5.050 | 镜像自带 |
| Python | 3.12.3 | 镜像自带（满足 spec 3.10+ 与本队 3.12 锁定）|
| cocotb | 2.0.1 | `pip install`（镜像无 pip，需 `apt-get install python3-pip` bootstrap）|
| cocotbext-axi | 0.1.28 | `pip install` |
| g++ / make / git | 13.3.0 / 有 / 有 | 镜像自带 |

### ⚠️ 文档勘误（待全局修正）

A2 全部文档（ENVIRONMENT.md §2.3/§2.4、CONSTRAINTS.md §13、PITFALLS.md、README §7）写的镜像 tag `verilator/verilator:5.050` **不存在**，正确 tag 是 `verilator/verilator:v5.050`（带 `v` 前缀）。

### ⚠️ 镜像无 pip

`verilator/verilator:v5.050` 是极简运行镜像，**无 pip**。每次容器需 `apt-get update && apt-get install -y python3-pip` bootstrap 后才能装 cocotb。实现阶段 run.sh/Dockerfile 必须包含此步骤。

---

## 2. Level 1：编译 + 仿真通过 ✅

**命令**（容器内，case1 目录）：
```bash
CASE1_CONSTRAINT_JSON=constraints.json \
FUNCTIONAL_COVERAGE_OUTPUT=functional_coverage.json \
COMPILE_ARGS='-Wno-fatal' \
  make SIM=verilator MODULE=test_case1_json_sequences TESTCASE=run_json_sequences
```

**结果**：
- `MAKE_EXIT=0` ✅
- 仿真正常 `$finish` 退出，**无 assert 失败**（5000 笔读全过）
- functional_coverage.json：status=passed，**24/24 bins，100%**

### ⚠️ 关键避坑（实现阶段必须处理）

1. **`-Wno-fatal` 必传**：Verilator 默认把 lint warning 当 error。case1 RTL 有 34 个 WIDTHEXPAND/WIDTHTRUNC/CASEINCOMPLETE（上游 verilog-axi 既有写法），不传 `-Wno-fatal` 编译直接失败。**win-ZCode 的 run.py 生成的 COMPILE_ARGS 必须含 `-Wno-fatal`**。
2. **`case1_tb.py` 不能用**：它访问 `s_axi_wdata`/`write_if` 等 case1（纯读模块）不存在的信号。必须用 `test_case1_json_sequences.py`（评测入口）。
3. **Makefile 默认 `SIM=vcs`**：必须 `SIM=verilator` 覆盖。
4. **functional_coverage.py 依赖**：test 脚本 `sys.path.insert` 上溯一级 import，挂载点必须是 `A2_public_dataset/`，工作目录进 `case1/`。
5. **产物隔离**：直接跑会覆盖 testcases（locked）。实现阶段 run.py 必须用 `--out` 隔离，烟雾测试时已改用复制到 `/tmp/ws` + 输出到独立 `/out` 目录。

### cocotb 2.0 弃用警告（非致命，但实现阶段要处理）

cocotbext-axi 0.1.28 对 cocotb 2.0 API 有大量 DeprecationWarning：
- `units=` → `unit=`（Clock 构造）
- `handle.setimmediatevalue()` → `handle.set(Immediate(...))`
- `task.kill()` → `task.cancel()`
- `signal.value_change` 替代 `Edge(reset_signal)`
- `event.data` 字段将移除

这些不阻断仿真，但 PITFALLS 陷阱⑩已预警。实现阶段生成的 testbench 要适配 cocotb 2.0 API。

---

## 3. Level 2：覆盖率插桩 + 解析 ✅

**命令**（在 Level 1 基础上加覆盖率标志）：
```bash
COMPILE_ARGS='-Wno-fatal --coverage-line --coverage-toggle' \
SIM_ARGS='+verilator+coverage+file+/out/coverage.dat' \
  make SIM=verilator MODULE=test_case1_json_sequences TESTCASE=run_json_sequences
```

**结果**：
- coverage.dat 生成（252KB）✅
- LCOV 格式，用 `verilator_coverage -write-info` 转 info 后 Python 解析

### 覆盖率数据（Verilator 口径）

| 文件 | line 命中/总 | line% | branch 命中/总 | branch% |
|---|---|---|---|---|
| case1.v（真实 RTL）| 262/437 | 59.95% | 1022/1419 | 72.02% |
| case1_cocotb_top.v（wrapper）| 36/42 | 85.71% | 316/402 | 78.61% |
| **合计** | **298/479** | **62.21%** | **1338/1821** | **73.48%** |

### 与 VCS 标杆对照（⚠️ 口径不可直接比较）

| 指标 | VCS 标杆 | Verilator（仅 case1.v） | 差异根因 |
|---|---|---|---|
| line | 168/317 = 53.0% | 262/437 = 59.95% | 分母不同：VCS 只算可执行行 317，Verilator LCOV DA 行 437（含声明/注释行粒度不同）|
| branch | 29/60 = 48.33% | 1022/1419 = 72.02% | **分母差异巨大**：VCS 只算 RTL 层 if/case 分支 60 个；Verilator 把每个 condition 拆成 LCOV BRDA 粒度 1419 个 |
| functional | 24/24 = 100% | 24/24 = 100% | 一致（cocotb 采样，与仿真器无关）|

**核心结论**：VCS 与 Verilator 的 branch 覆盖率**分母口径本质不同**，百分比不可直接比较。Verilator 的 branch 是 line coverage 的结构化副产品（LCOV BRDA 粒度），VCS 的 branch 是 RTL 逻辑分支。这正是 PLAN.md "congress 评审裁决"选择 `--coverage-line`（自动产 line+branch）的口径。

### ⚠️ 实现阶段的关键风险

1. **scope 控制**：VCS 标杆 53% 是含 wrapper 的 `case1_cocotb_top` 层级。CONSTRAINTS.md §10 要求"避免 wrapper 稀释"。win-ZCode 的覆盖率解析必须能**按文件过滤**（只算真实 RTL，排除 wrapper）。
2. **口径不可复现 VCS 标杆**：不要期望 Verilator 跑出 53%/48.33%。评测按"选手自交"（PLAN.md 已确认评测器不锁工具重算），win-ZCode 用 Verilator 口径自交即可，但 coverage_result.json 必须注明 simulator=Verilator + 口径说明。
3. **case1 53% 的真实根因**（CONSTRAINTS.md §10）：参数化死码——`SEGMENT_COUNT==1`/`EXPAND` 分支在测试配置（S=32/M=16）下恒假未激活，约 130-149 行死码。这不是 wrapper 稀释，是 RTL 参数配置导致。实现阶段需对 RTL 做 `generate/if` 静态分析，只对可达分支采 bin。

---

## 4. 通过判定

| 检查项 | 结果 |
|---|---|
| Docker linux/amd64 环境可用 | ✅ |
| Verilator 5.050 镜像正确（tag `v5.050`）| ✅ |
| Python 3.12 + cocotb 2.0.1 + cocotbext-axi 0.1.28 可装可用 | ✅ |
| case1 编译通过（需 `-Wno-fatal`）| ✅ |
| case1 仿真通过（5000 笔，exit 0）| ✅ |
| functional coverage 24/24 = 100% | ✅ |
| Verilator 覆盖率插桩 + coverage.dat 生成 + 解析 | ✅ |
| 覆盖率管道端到端通（compile→sim→dat→parse）| ✅ |

**结论：win-ZCode 主运行环境（Docker linux/amd64 + Verilator 5.050）完全可用，cocotb + 覆盖率管道端到端打通。可以进入实现阶段。**

---

## 5. 实现阶段待办（环境背书衍生）

- [ ] run.py 生成的 COMPILE_ARGS 必须含 `-Wno-fatal`（否则 Verilator lint 致命）
- [ ] run.sh/Dockerfile 必须含 `apt-get install python3-pip` bootstrap（镜像无 pip）
- [ ] 生成的 testbench 适配 cocotb 2.0 API（`unit=` 非 `units=`，`Immediate()` 等）
- [ ] 覆盖率解析按文件过滤（排除 wrapper，只算真实 RTL 子树）
- [ ] coverage_result.json 注明 simulator=Verilator + 口径，公式用 0.4/0.3/0.3
- [ ] RTL 静态分析：`generate/if` 死码识别，只对可达分支采 bin
- [ ] 文档全局修正：`verilator/verilator:5.050` → `:v5.050`
- [ ] 离线打包：镜像无 pip 意味着 `wheelhouse/` 还需含 pip 本身或改用 venv bootstrap
