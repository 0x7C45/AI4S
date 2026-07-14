# A2 验证环境自动生成 · 运行环境（ENVIRONMENT）

> 范围：仅 A2。本文只约束「硬约束 + 适用工具菜单」，**不替 mac-CC / mac-Codex / win-CC 三方定方案**；各机自选开发环境，统一以 §1 硬约束为最终交付门槛。
> 关联：[PLAN.md](./PLAN.md)（cocotb+Verilator 路线）、[EXECUTOR.md](./EXECUTOR.md)（三方分工）、[spec.md](./spec.md) / [scoring.md](./scoring.md)（官方 locked，禁改）。

---

## 1. 硬约束（三方都必须满足）

评测侧硬性要求（spec.md §5、scoring.md §三）：

- **评测 OS = Linux x86_64**，**断网**；容器 Docker 或服务器二选一，不强制。
- **依赖全打包随提交交**：`pip install` 联网装会失败；每个 wheel 必须 `linux/amd64 + Python 3.12` manylinux。必交 `requirements.txt`（钉死版本）+ `THIRD_PARTY.md`（版本/许可/调用边界）。
- **仿真器锁 Verilator 5.050**（PLAN.md 路线；官方未锁 VCS，A2 spec 把 VCS 列为「待澄清」）。覆盖率编译：`verilator --cc --build --coverage-line --coverage-toggle --top-module <top> <rtl>`；综合公式 = **0.4×行 + 0.3×分支 + 0.3×功能**（scoring.md locked；禁止抄公开样例 case4 的 0.42/0.28/0.30）。
  > ✅ **congress 评审已裁决（2026-07-14）**：coverage 命令定标 `--coverage-line --coverage-toggle`（选项 A）。理由：`--coverage-line` 自动产 line+branch（Verilator 官方设计，branch 是 line coverage 结构化副产品；5.050 实测 coverage.dat branch 83.3%）；functional(30%) 靠 cocotb bin，非 Verilator 标志。落地：①`COVERAGE_FLAGS` 参数化（Makefile 顶层变量，默认 A）；②解析器 schema-driven（字段从标志派生）；③coverage 文件头写 `verilator --version`+flags；④Phase1 末单端 C 烟雾测试验 fsm 格式四方一致；⑤functional bin 模板预置（FSM/数据通路/存储器/AXI 4 类，30% 权重杠杆）；⑥评分细则若发布且 branch 解读为真值表则切 B（零代码）。
- **提交前 Docker linux/amd64 复验是硬要求**（见 §5）：native 数字仅开发参考，不作交付依据。
- **提交包排除**：`testcases/`（官方 locked）、`vcs_coverage_*`（VCS 产物，本路线不用）、`.git/`、`venv/`、`__pycache__/`、波形 `*.fst/*.vcd`、`obj_dir/`。

> grader 脚本官方不提供 → 盲交付；任何「依赖缺失 / 仿真失败」直接 0 分。

---

## 2. 开发环境菜单（各机自选，不强制）

三套方案任选；每条标注 **coverage 数字效力**，决定是否需要 §5 复验。

### 2.1 macOS native（brew + 源码编译，mac-CC / mac-Codex）

```bash
# Verilator 5.050：brew 默认版本可能非 5.050，须源码锁版本
brew install verilator && verilator --version    # 若 != 5.050 走下面源码
git clone https://git.veripool.org/verilator && cd verilator && git checkout v5.050
autoconf && ./configure && make -j$(nproc) && sudo make install
verilator --version    # 必须 5.050
python3.12 -m venv venv && source venv/bin/activate
pip install -r requirements.txt
cocotb-config --makefiles    # 验证 cocotb Makefile 路径
```

- **coverage 数字效力：仅开发参考**（macOS arm64 与评测 Linux x86_64 架构不同，插桩数字可能漂移）；提交前必须在 §2.3 Docker linux/amd64 复跑全部 case。

### 2.2 Windows + WSL2（win-CC，三方中唯一原生 x86_64）

```bash
# WSL2 Ubuntu 22.04+ 内：apt verilator 只到 5.020，须源码编译到 5.050
sudo apt-get update
sudo apt-get install -y git autoconf flex bison libfl-dev make g++ \
                        python3.12 python3.12-venv python3.12-dev
git clone https://git.veripool.org/verilator && cd verilator && git checkout v5.050
autoconf && ./configure && make -j$(nproc) && sudo make install
verilator --version    # 必须 5.050
python3.12 -m venv venv && source venv/bin/activate
pip install -r requirements.txt
```

- **coverage 数字效力：可交付参考**（WSL2 原生 linux/amd64，与评测 OS 架构一致，漂移风险最低；但仍建议提交前过一次 §2.3 Docker 复验，与队友环境对齐）。

### 2.3 Docker linux/amd64（三方统一复验口径）

```bash
# verilator 官方按 release 自动打 tag，5.050 存在
docker pull --platform linux/amd64 verilator/verilator:5.050
docker run --rm --platform linux/amd64 verilator/verilator:5.050 verilator --version    # 必须 5.050
# 复验入口（挂载 A2-verification 到 /work）
docker run --rm -it --platform linux/amd64 \
    -v "$(pwd)/Track-A/A2-verification:/work" -w /work \
    verilator/verilator:5.050 bash
```

- **coverage 数字效力：可交付**（评测同构环境，权威基线）。镜像自带 Verilator 工具链但 Python 通常非 3.12，容器内补装：

```bash
# 容器内补装 Python 3.12 + 离线装依赖（开发期联网，仅复验用）
apt-get update && apt-get install -y software-properties-common
add-apt-repository -y ppa:deadsnakes/ppa && apt-get update
apt-get install -y python3.12 python3.12-venv python3.12-dev
python3.12 -m venv venv && source venv/bin/activate
pip install --no-index --find-links=offline_pkgs/ -r requirements.txt    # 见 §4
```

---

## 3. 锁版本表

| 组件 | 锁定版本 | 来源 / 备注 |
|------|---------|------------|
| 评测 OS | **Linux x86_64** | spec.md §5 唯一权威 |
| Python | **3.12.x** | 三方 venv 统一（spec 仅"推荐 3.10+"，本队自锁 3.12） |
| Verilator | **5.050** | `--coverage-line/-toggle` 行为在主版本间可能漂移；apt 5.020 不够，须源码或官方 Docker |
| cocotb | **2.0.1** | task3 实测：1.8.1 macOS arm64 无 wheel、源码构建失败；2.0.1 有 cp312 macosx arm64 wheel（本机可装）；评测机两版本都有 manylinux x86_64 wheel |
| cocotb-test | **0.2.6** | 配 Verilator 后端（`SIM=verilator`） |
| cocotbext-axi | **0.1.28** | 与 cocotb 2.0.1 实测全兼容（issue #119 已过期，详见 §5.3） |
| jinja2 | **3.1.6** | 渲染 `cocotb_tb.py.j2` 模板 |
| pyverilog | **1.3.0** | RTL 解析（spec.md §5 允许） |
| z3-solver | **4.16.0.0**（可选） | spec.md §5 / 02 手册；约束求解（可选，不装也能跑）；task3 网络未装上，PyPI 确认 arm64 wheel 存在 |
| Docker 镜像 | **verilator/verilator:5.050** | 官方按 release 自动打 tag，linux/amd64 |
| `--seed` | **20260630** | 5 公开 case 统一；scoring.md §2 可复现硬约束 |
| `--num-seq` | **5000** | spec.md；评测基准序列数 |

> smoke test：M1 骨架阶段在 cocotb 2.0.1 + Verilator 5.050 上跑通 case1，记录实际可装版本 → 回填本表 → 同步冻结到 `requirements.txt` + `THIRD_PARTY.md`。

---

## 4. 离线打包方案

### 4.1 在联网开发机生成 `offline_pkgs/`

```bash
# 预下载 linux/amd64 + Python 3.12 wheel（开发机即使是 mac arm64 也强制 linux/amd64）
mkdir -p Track-A/A2-verification/offline_pkgs
pip download -d Track-A/A2-verification/offline_pkgs/ \
    -r Track-A/A2-verification/requirements.txt \
    --platform manylinux2014_x86_64 --python-version 3.12 --only-binary=:all:
```

- `--platform manylinux2014_x86_64`：与评测 OS 严格对齐（pip download 平台标签用 manylinux2014_x86_64，与 THIRD_PARTY/CONSTRAINTS/README 口径统一；Docker run 的 `--platform linux/amd64` 是 Docker 平台语法，两套口径不冲突）。
- `--only-binary=:all:`：强制纯 wheel，避免评测机无编译环境时源码包失败。
- 若个别包无 manylinux wheel（极少见），需 vendored 源码 + README 注明编译前置条件。

### 4.2 评测机离线安装

```bash
# 评测机 / Docker 容器内：无网络，仅从 offline_pkgs 读 wheel
pip install --no-index --find-links=offline_pkgs/ -r requirements.txt
```

### 4.3 Verilator 二进制（非 pip 包）

- Docker 路线：`verilator/verilator:5.050` 官方镜像自带 5.050。
- fallback 路线（无 Docker）：README 注明 `verilator --version` 必须 = 5.050，附 §2.1/§2.2 源码编译命令；不假设赛方预装。

---

## 5. 风险与验证

### 5.1 提交前 Docker linux/amd64 复验（硬要求）

**任何 native 跑出的覆盖率，提交前必须在 Docker linux/amd64 复跑全部 case，逐 case 对比，确认无漂移才提交。**

- 跨平台风险：Verilator `--coverage-line/-toggle` 是编译期插桩、平台无关；但 **mac native 与 Linux 评测机数字一致性未验证**——这是 Docker 复验的存在理由。
- 漂移阈值（行/分支）：绝对差 > 0.5 个百分点 → **禁止提交**；seed 固定 20260630 + RTL 不变 → 覆盖率必须可复现；若 native 与 Docker 不一致，**以 Docker linux/amd64 为准**（评测同构）。

### 5.2 case4 公式复现标杆

公开样例 case4：**line 96.9 / branch 80.65 / func 100 → C = 92.96**（按 0.4/0.3/0.3 反算）。三方 Docker 复验若 case4 反算偏离 92.96，即环境异常（Verilator 版本/cocotb 配置/RTL scope 错位），必须排查。

### 5.3 已知灰色地带（接受风险推进）

- **VCS vs Verilator scoring 解释**：scoring.md「VCS/URG 报告必须对应 RTL」是否隐含必须交 URG 附件——A2 spec 列为「待澄清」。本队按 PLAN.md 走 Verilator，靠 case4 公式复现兜底；罚分项只有「仿真失败/缺项/无 seed/报告不对应 RTL」，未用 VCS 不是罚分项。
- **cocotbext-axi 是否评测预装 / cocotb 2.0 兼容**：02 手册 §7.4 未确认 → 一律走 §4 离线打包；**issue #119 已过期**：cocotb-bus 0.3.0 + cocotbext-axi 0.1.28 的 requires_dist 为 `cocotb>=1.6.0`（无 `<2.0` 上界），cocotb 2.0.1 + cocotbext-axi 0.1.28 实测全兼容（import/运行无报错）。
