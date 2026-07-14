# A3 GSD 执行指南：给第一次使用 GSD 的队友

> 本指南只指导验证、记录和提交前复验。**本指南本身不修改 A3 源码、测试、Makefile、配置或规划文件。**如果执行中发现必须修改 `Track-A/A3-synthesis/src/**`、`tests/**`、`Makefile`、`config.json`、`submission.yaml` 或其他实现文件，立即停止当前验证，重新走 `/gsd-discuss-phase` → `/gsd-plan-phase` → `/gsd-execute-phase`；不要在本指南流程中直接改文件。

## 0. 现状结论与优先级

当前全项目为 **3/10 phases，30%**。A3 的 Phase 1、Phase 2、Phase 3、Phase 4 **均为 incomplete，A3 当前是 0/4**。从当前时间窗口看，剩余工作约 **9.5-19 小时**；`STATE.md` 记录的截止窗口约 **16 小时**。执行顺序固定为：

**官方镜像/Phase1-2正确性 > LSV07/09/10初始化感知等价 > OpenSTA/PPA > clean package**。

先保证评测环境能运行并且正确性证据完整，再做 PPA 优化；没有官方镜像或没有等价证据时，不要把本机综合成功当作比赛通过。

## 1. 已确认证据与边界

### 1.1 当前证据

- A3 实现提交锚点：`87675ff`。
- 本机测试：`make -C Track-A/A3-synthesis test` 通过 **28 tests**。
- LSV01-LSV10 的 point 1 都有本机 Yosys + Nangate45 的 `synthesis observed_success` 记录。它们是本机观察，不是官方镜像验收。
- 本机已观察到 LSV01 point 1 生成 Nangate45 映射网表；这只说明本地流水线产出了网表，不等同于功能等价或竞赛通过。

### 1.2 等价矩阵：必须原样保持

| 电路 | 等价状态 | 等价样本数 | 解释 |
|---|---|---:|---|
| LSV01 | `pass` | 500 | 已记录的等价样本计数 |
| LSV02 | `pass` | 200 | 已记录的等价样本计数 |
| LSV03 | `pass` | 200 | 已记录的等价样本计数 |
| LSV04 | `pass` | 100 | 已记录的等价样本计数 |
| LSV05 | `pass` | 100 | 已记录的等价样本计数 |
| LSV06 | `pass` | 100 | 已记录的等价样本计数 |
| LSV07 | `not_verified` | `N/A` | gate-level X/uninitialized 阻塞初始化感知比较 |
| LSV08 | `pass` | 100 | 已记录的等价样本计数 |
| LSV09 | `not_verified` | `N/A` | gate-level X/uninitialized 阻塞初始化感知比较 |
| LSV10 | `not_verified` | `N/A` | gate-level X/uninitialized 阻塞初始化感知比较 |

**LSV07、LSV09、LSV10 的 `not_verified/N/A` 是 gate-level X/uninitialized 阻塞，不是 equivalence pass，也不是 synthesis defect。**只能在使用初始化感知、复位感知或四状态规则的验证器重新得到证据后，改变它们的状态。

### 1.3 未验证边界

- 本机没有 `OpenSTA`/`sta`。因此 PPA、area、timing、runtime、Pareto、hypervolume、auto-tuning 均未验证。
- `local evidence` 不得写成 `official pass`。
- 没有官方镜像运行记录时，状态应为 `blocked` 或 `not_verified`，不能猜测镜像名称、摘要、版本或比赛结果。
- 官方镜像统一用占位符 `<OFFICIAL_IMAGE>` 表示。实际执行前，必须由队友替换为竞赛实际提供的镜像名或本地镜像标签；本指南不提供不存在的镜像名称或摘要。

## 2. GSD 是什么，以及正确命令顺序

GSD 是把工作拆成可追踪阶段和计划的执行流程。第一次使用时只需要记住以下概念：

- **Phase**：一个有明确验收目标的阶段。A3 当前要处理 Phase 1-4。
- **Plan**：Phase 内可执行的任务清单，包含文件边界、命令和验收条件。
- **Wave**：可以并行执行的一组相互独立的 Plan；依赖关系未满足时不要提前并行。
- **SUMMARY**：Plan 完成后的结果记录，包含提交、证据、偏差和未完成项。
- **VERIFICATION**：验证记录，说明哪些证据真实通过，哪些只是观察、阻塞或未验证。

### 2.1 命令速查

| 命令 | 用途 | 输入 | 主要产物 |
|---|---|---|---|
| `/gsd-progress` | 查看当前 Phase、Plan、阻塞和下一步 | 当前仓库的 `.planning/` 状态 | 进度和推荐下一步 |
| `/gsd-discuss-phase` | 在执行前澄清目标、边界、证据和风险 | Phase 编号或名称 | Phase 上下文/讨论记录 |
| `/gsd-plan-phase` | 把已讨论的 Phase 写成可执行 Plan | Phase 上下文、代码库状态 | `PLAN.md`、任务和验收条件 |
| `/gsd-execute-phase` | 按 Wave 执行一个 Phase 的所有 Plan | 已审核的 `PLAN.md` | 代码/证据提交、`SUMMARY.md` |
| `/gsd-verify-work` | 对已执行功能做真实验收 | Phase 产物、运行环境 | UAT/验证结果和未决项 |
| `/gsd-code-review` | 审查该 Phase 改动的 bug、安全和质量风险 | Phase 的代码提交 | Review 结论和修复建议 |
| `/gsd-ship` | 在验证和 review 通过后准备交付/PR | 已验证的分支和提交 | 交付检查、PR 或发布准备结果 |

### 2.2 推荐标准命令链

按以下顺序执行；每一步都读取上一阶段的产物，不要跳过讨论或验收：

```text
/gsd-progress
/gsd-discuss-phase <PHASE>
/gsd-plan-phase <PHASE>
/gsd-execute-phase <PHASE>
/gsd-verify-work <PHASE>
/gsd-code-review <PHASE>
/gsd-ship
```

`<PHASE>` 替换成实际 Phase 编号或项目接受的 Phase 标识。若 `/gsd-verify-work` 或 `/gsd-code-review` 发现实现缺陷，不要直接在本指南中修源码；重新回到对应 Phase 的 discuss/plan/execute 工作流。

### 2.3 A3 Phase 1 缺口链

Phase 1 还没有官方镜像和 RTL/门级等价的完整证据时，按此顺序补缺口：

```text
/gsd-progress
/gsd-discuss-phase 1
/gsd-plan-phase 1
/gsd-execute-phase 1
/gsd-verify-work 1
/gsd-code-review 1
```

只有 Phase 1 的官方镜像版本、LSV01 综合、Nangate45/blackbox 检查和 LSV01 等价证据完整后，才进入 Phase 2。Phase 2、3、4 同样必须逐阶段验收，不要因本机 point 1 能运行而跳过。

## 3. 统一执行纪律

### 3.1 工作树和日志

每次验证先确认目录和工作树。验证命令必须保存日志；长命令用 `tee`，并保留真实退出码：

```bash
cd /workspace/AI4S
export A3="$PWD/Track-A/A3-synthesis"
export EVIDENCE="$PWD/evidence/a3"
mkdir -p "$EVIDENCE"
git status --short
set -o pipefail
```

如果不是在容器内执行，把 `cd /workspace/AI4S` 改成仓库实际绝对路径。不要把 `/tmp` 中的临时输出当作唯一证据；重要日志、命令、版本和结果应复制到队伍规定的证据目录或 SUMMARY/VERIFICATION 中。

### 3.2 固定失败记录字段

每一次 point、镜像、等价、STA 或打包失败，都记录一条，不要只写“失败”：

```text
phase: <1|2|3|4>
circuit: <LSV01-LSV10 或 N/A>
point: <整数或 N/A>
commit: <执行时的 git commit>
image: <OFFICIAL_IMAGE 的实际标签，若未使用则 local>
command: <完整命令>
exit_code: <整数>
status: <pass|observed_success|not_verified|fail|blocked>
log: <日志绝对路径>
evidence: <网表、报告、版本输出或失败片段路径>
next_action: <下一步；若阻塞写清需要谁提供什么>
```

日志命名建议为 `phase<N>-<circuit>-p<point>-<kind>.log`。命令示例：

```bash
set -o pipefail
if make -C "$A3" -j1 test 2>&1 | tee "$EVIDENCE/phase1-local-test.log"; then
  rc=0
else
  rc=$?
fi
printf 'exit_code: %s\n' "$rc" | tee -a "$EVIDENCE/phase1-local-test.log"
```

### 3.3 停止和回退规则

满足以下任一条件，停止扩展，不要用“先跑完再说”掩盖问题：

- 官方镜像缺失、版本无法确认、容器不能在 `network none` 下启动。
- 生成网表出现非法 cell、黑盒、未解析内部模块或非允许库实例。
- 综合失败、等价失败、关键日志缺失或退出码不为 0。
- LSV07/LSV09/LSV10 的 X/uninitialized 结果没有初始化感知规则支撑。
- OpenSTA/`sta` 不存在，或 STA 报告无法证明 `area/arrival/WNS/TNS`。

禁止使用 `git reset --hard`、`git checkout --`、`git clean -f` 等破坏性回退。需要撤销自有、明确的实现提交时，优先使用 `/gsd-undo`；在明确知道提交边界时才使用针对该提交的 `git revert <commit>`。不要回退队友提交，不要覆盖未提交工作。

## 4. Phase 1：本地基线、镜像和 LSV01 正确性

### 4.1 进入条件

- 已运行 `/gsd-progress`，确认当前 Phase 1 的 Plan 和依赖。
- 工作树状态已记录；没有未确认的队友改动。
- 已确认实现锚点为 `87675ff`，但不能把该提交本身当作官方验收。
- 已准备实际竞赛镜像标签。若镜像未提供或无法拉取/加载，Phase 1 立即 `blocked`，不升级 local evidence。

### 4.2 本地基线和 28 tests

```bash
cd /workspace/AI4S
export A3="$PWD/Track-A/A3-synthesis"
export EVIDENCE="$PWD/evidence/a3/phase1"
mkdir -p "$EVIDENCE"
git rev-parse HEAD | tee "$EVIDENCE/git-head.txt"
set -o pipefail
make -C "$A3" -j1 build 2>&1 | tee "$EVIDENCE/build.log"
make -C "$A3" -j1 test 2>&1 | tee "$EVIDENCE/test.log"
```

预期：构建成功，测试日志包含 **28 tests** 通过；这只是 local baseline。若测试失败，记录 `status: fail`，停止进入官方镜像和 point 扩展。

### 4.3 LSV01 point 1 本地综合

```bash
cd /workspace/AI4S
export A3="$PWD/Track-A/A3-synthesis"
export OUT="$PWD/evidence/a3/phase1/lsv01-p1"
mkdir -p "$OUT"
set -o pipefail
make -C "$A3" -j1 synth \
  RTL="$A3/testcases/public/LSV01_epfl_priority/rtl/design.v" \
  TOP=top \
  SDC="$A3/testcases/public/LSV01_epfl_priority/constraints.sdc" \
  LIBERTY="$A3/testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib" \
  CONFIG="$A3/config.json" \
  CIRCUIT=LSV01 \
  POINT=1 \
  OUT_DIR="$OUT" 2>&1 | tee "$OUT/synth.log"
test -s "$OUT/netlist.v"
```

预期产物：`netlist.v`、综合日志和工具诊断目录。状态只能写 `observed_success`，不能写 `official pass`。

### 4.4 官方镜像版本检查

先把下面变量中的字符串替换为竞赛实际镜像标签。不要凭空填写镜像名或 digest：

```bash
export OFFICIAL_IMAGE='<OFFICIAL_IMAGE>'
docker image inspect "$OFFICIAL_IMAGE" >/dev/null
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -e
    printf "image=%s\n" "$HOSTNAME"
    command -v yosys
    yosys -V
    command -v python3
    python3 --version
    command -v make
    make --version | head -1
  ' 2>&1 | tee "$EVIDENCE/official-image-versions.log"
```

预期：镜像存在，Yosys、Python、Make 版本可记录，且命令在无网络条件下完成。镜像不存在、工具版本不完整、容器需要网络或无法在 1 CPU/10 GiB 约束下运行时，记录 `status: blocked` 并停止；不能用本机结果替代官方镜像证据。

### 4.5 官方镜像内 LSV01、Nangate45 和 blackbox 检查

```bash
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -euo pipefail
    A3=/workspace/AI4S/Track-A/A3-synthesis
    OUT=/workspace/AI4S/evidence/a3/phase1/official-lsv01-p1
    mkdir -p "$OUT"
    make -C "$A3" -j1 synth \
      RTL="$A3/testcases/public/LSV01_epfl_priority/rtl/design.v" \
      TOP=top \
      SDC="$A3/testcases/public/LSV01_epfl_priority/constraints.sdc" \
      LIBERTY="$A3/testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib" \
      CONFIG="$A3/config.json" CIRCUIT=LSV01 POINT=1 OUT_DIR="$OUT" \
      2>&1 | tee "$OUT/synth.log"
    test -s "$OUT/netlist.v"
    if rg -n "blackbox|black_box|^[[:space:]]*\\$" "$OUT/netlist.v"; then
      echo "blackbox_or_unresolved_cell_found" >&2
      exit 21
    fi
    rg -n "AND2_X1|MUX2_X1|NAND2_X1|Nangate" "$OUT/netlist.v" | tee "$OUT/nangate45-cells.txt"
  ' 2>&1 | tee "$EVIDENCE/official-lsv01-p1.log"
```

验收证据必须同时包含：官方镜像版本、LSV01 point 1 退出码为 0、非空网表、允许的 Nangate45 cell 观察、无 blackbox/未解析 cell。缺任何一项都不能标为 `pass`。

### 4.6 LSV01 RTL/门级等价

优先使用竞赛实际提供的官方等价脚本/命令。命令、脚本路径和版本必须写入失败记录或证据记录；不能把未知命令写成事实。若使用 Yosys 等价模板，先在官方镜像中确认其适用于该电路和网表：

```bash
export EQUIV_RTL="$A3/testcases/public/LSV01_epfl_priority/rtl/design.v"
export EQUIV_GATE="$EVIDENCE/official-lsv01-p1/netlist.v"
export CELL_LIB="$A3/testcases/lib/nangate45/NangateOpenCellLibrary.v"
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -euo pipefail
    yosys -p "read_verilog /workspace/AI4S/Track-A/A3-synthesis/testcases/public/LSV01_epfl_priority/rtl/design.v; prep -top top; design -stash gold; read_verilog /workspace/AI4S/evidence/a3/phase1/official-lsv01-p1/netlist.v; read_verilog /workspace/AI4S/Track-A/A3-synthesis/testcases/lib/nangate45/NangateOpenCellLibrary.v; prep -top top; equiv_make gold top equiv; hierarchy -top equiv; equiv_simple; equiv_status -assert"'
  2>&1 | tee "$EVIDENCE/lsv01-equivalence.log"
```

如果官方等价器要求复位、时钟、黑盒模型或其他参数，按官方规则执行并记录完整命令。等价通过才允许 Phase 1 进入完成候选；失败、模型缺失或结果不确定时分别记 `fail` 或 `not_verified`，Phase 1 保持 incomplete。

### 4.7 Phase 1 产物、失败记录、停止/回退

预期产物：Phase 1 Plan/SUMMARY/VERIFICATION、local test 日志、官方镜像版本日志、LSV01 point 1 网表与日志、Nangate45/blackbox 检查、LSV01 等价报告。

失败记录至少包含固定字段 `phase, circuit, point, commit, image, command, exit_code, status, log, evidence, next_action`。官方镜像缺失时写 `image: <OFFICIAL_IMAGE>`, `status: blocked`，并写明需要竞赛实际镜像标签；不得升级为 `observed_success` 以外的 local 结论。若需要改实现，停止并重新走 GSD discuss/plan/execute。

## 5. Phase 2：循环综合、全部点和初始化感知等价

### 5.1 进入条件

- Phase 1 的官方镜像、LSV01 point 1、Nangate45/blackbox、LSV01 等价证据已保存。
- 已确认官方镜像允许的 CPU、内存和网络约束。
- 已确认 `config.json` 中每个电路的已配置 points；`$default` 只作为明确配置缺失时的回退，不能擅自扩展到超过 7 个 points。

### 5.2 LSV01-LSV10 循环综合 point 1 和已配置 points

以下命令在仓库根目录执行，使用官方镜像；它根据 `config.json` 读取每个电路的配置数量，并限制最多 7 个 point。日志和输出写在证据目录，不修改 A3 源码：

```bash
cd /workspace/AI4S
export OFFICIAL_IMAGE='<OFFICIAL_IMAGE>'
export EVIDENCE="$PWD/evidence/a3/phase2"
mkdir -p "$EVIDENCE"
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -uo pipefail
    A3=/workspace/AI4S/Track-A/A3-synthesis
    EVIDENCE=/workspace/AI4S/evidence/a3/phase2
    circuits="LSV01 LSV02 LSV03 LSV04 LSV05 LSV06 LSV07 LSV08 LSV09 LSV10"
    for circuit in $circuits; do
      case "$circuit" in
        LSV01) dir=LSV01_epfl_priority;;
        LSV02) dir=LSV02_epfl_cavlc;;
        LSV03) dir=LSV03_epfl_adder;;
        LSV04) dir=LSV04_itc99_b11;;
        LSV05) dir=LSV05_sog_axi_downsizer;;
        LSV06) dir=LSV06_sog_pfpu_f2i;;
        LSV07) dir=LSV07_sog_qdiv;;
        LSV08) dir=LSV08_sog_stage_mult;;
        LSV09) dir=LSV09_medium_sha256_wishbone;;
        LSV10) dir=LSV10_medium_vexriscv_small;;
      esac
      n=$(python3 - "$A3/config.json" "$circuit" <<'PY'
import json, sys
with open(sys.argv[1]) as f:
    data = json.load(f)
items = data.get(sys.argv[2], data.get("$default", []))
print(min(7, len(items)))
PY
)
      [ "$n" -ge 1 ] || { echo "$circuit has no configured point" >&2; continue; }
      for point in $(seq 1 "$n"); do
        out="$EVIDENCE/$circuit-p$point"
        mkdir -p "$out"
        cmd="make -C $A3 -j1 synth RTL=$A3/testcases/public/$dir/rtl/design.v TOP=top SDC=$A3/testcases/public/$dir/constraints.sdc LIBERTY=$A3/testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib CONFIG=$A3/config.json CIRCUIT=$circuit POINT=$point OUT_DIR=$out"
        start=$(date +%s)
        if eval "$cmd" 2>&1 | tee "$out/synth.log"; then
          rc=0; status=observed_success
        else
          rc=$?; status=fail
        fi
        end=$(date +%s)
        printf "circuit: %s\npoint: %s\ncommand: %s\nexit_code: %s\nruntime_wall_s: %s\nstatus: %s\nlog: %s\nevidence: %s/netlist.v\nnext_action: record and inspect before continuing\n---\n" "$circuit" "$point" "$cmd" "$rc" "$((end-start))" "$status" "$out/synth.log" "$out" | tee "$out/result.txt"
      done
    done
  ' 2>&1 | tee "$EVIDENCE/all-synthesis.log"
```

验收：每个尝试的 point 都有独立日志、退出码、wall time、网表存在性和状态。失败 point 必须保留记录；不能删除失败日志后宣称全部成功。`point 1/已配置 points` 是最低覆盖，不代表已经完成正确性。

### 5.3 非法 cell、黑盒和综合失败的扩展门禁

每个成功 point 在进入等价前检查网表：

```bash
cd /workspace/AI4S
export LIB="$PWD/Track-A/A3-synthesis/testcases/lib/nangate45/NangateOpenCellLibrary.v"
export NETLIST="$PWD/evidence/a3/phase2/LSV01-p1/netlist.v"
set -o pipefail
if rg -n "blackbox|black_box|^[[:space:]]*\\$" "$NETLIST"; then
  printf 'status: fail\nnext_action: stop point expansion and inspect unresolved cells\n'
  exit 21
fi
rg -n "_X[0-9]+|Nangate|AND2|NAND2|MUX2" "$NETLIST" | tee "$NETLIST.cells.log"
```

发现非法 cell、blackbox、未解析模块或综合失败时，立即停止该电路的后续 point 扩展；记录 `fail`，不要把失败转成 `not_verified`，也不要修改配置来掩盖失败。只有在根因已记录且 GSD 计划明确允许修复时，才重新进入 discuss/plan/execute。

### 5.4 等价和 LSV07/09/10 初始化感知规则

- LSV01-LSV06、LSV08：对每个成功 point 执行 RTL/门级等价或竞赛指定的功能验证，保存报告和命令；普通 `pass` 必须有可复现报告。
- LSV07、LSV09、LSV10：gate-level X/uninitialized 是已知阻塞。必须使用带 reset/initialization/valid protocol 的初始化感知验证，或官方允许的四状态比较规则。
- 如果验证器在未初始化状态上直接报 X mismatch，而没有初始化感知规则，则结果记 `not_verified`，不能记 `pass`，也不能据此判定 synthesis defect。
- 只有初始化感知验证明确通过，才可以把对应 point 标记为 `pass`；若 RTL/门级真实功能不等价，则记 `fail`。

每个 point 都记录：

```text
circuit: LSV07
point: 1
status: not_verified
log: evidence/a3/phase2/LSV07-p1/equivalence.log
evidence: gate-level X/uninitialized blocked comparison
next_action: run reset-aware or four-state equivalence in official image
```

### 5.5 Phase 2 产物、失败记录、停止/回退

预期产物：十个电路的 point 循环日志、每个 point 的网表和诊断目录、非法 cell/blackbox 检查、等价报告、LSV07/09/10 初始化感知验证报告，以及 Phase 2 SUMMARY/VERIFICATION。

下列任一情况发生时，停止扩展并记录：官方镜像不可用；非法 cell/blackbox；综合退出码非 0；等价失败；LSV07/09/10 没有初始化感知规则；日志或网表不完整。回退只能使用 `/gsd-undo` 或针对明确自有提交的 `git revert`，禁止 `reset --hard`、`checkout --`、`clean -f`。

## 6. Phase 3：OpenSTA、PPA、Pareto 和 auto-tuning

### 6.1 进入条件

- Phase 2 已有每个尝试 point 的综合和正确性状态。
- 已确认竞赛实际官方镜像内存在 `sta`/OpenSTA；本机没有 OpenSTA/`sta`，不能用本机命令伪造结果。
- 只对最多 7 个 point 做 PPA 评估；失败 point 仍保留 runtime/失败记录，但不作为正确 Pareto 点提交。

### 6.2 官方 OpenSTA 检查

```bash
cd /workspace/AI4S
export OFFICIAL_IMAGE='<OFFICIAL_IMAGE>'
export EVIDENCE="$PWD/evidence/a3/phase3"
mkdir -p "$EVIDENCE"
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -e
    command -v sta
    sta -version 2>&1 || true
  ' 2>&1 | tee "$EVIDENCE/opensta-version.log"
```

如果 `command -v sta` 失败，Phase 3 记为 `blocked`，停止本机 PPA 宣称；不能安装未经确认的替代包，也不能根据网表大小估算 area/timing。

### 6.3 每 point 的 OpenSTA TCL 和指标

每个正确网表建立一个独立目录，TCL 至少包含以下命令；将实际路径替换后在官方镜像执行：

```tcl
read_liberty /workspace/AI4S/Track-A/A3-synthesis/testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib
read_verilog /workspace/AI4S/evidence/a3/phase2/LSV01-p1/netlist.v
link_design top
read_sdc /workspace/AI4S/Track-A/A3-synthesis/testcases/public/LSV01_epfl_priority/constraints.sdc
report_design_area
report_checks -path_delay max -fields {slew cap input_pins} -digits 4
report_worst_slack -max
report_tns -max
```

执行并保留退出码：

```bash
export STA_TCL="$PWD/evidence/a3/phase3/LSV01-p1/run_sta.tcl"
export STA_LOG="$PWD/evidence/a3/phase3/LSV01-p1/opensta.log"
set -o pipefail
timeout 600 docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" sta /workspace/AI4S/evidence/a3/phase3/LSV01-p1/run_sta.tcl \
  2>&1 | tee "$STA_LOG"
```

每个 point 的 CSV/记录至少包含：`phase,circuit,point,runtime_s,area,arrival_ns,wns,tns,status,log,evidence`。按竞赛评分规则记录 `arrival_ns = max(0, -WNS)`；area 来自 OpenSTA/官方指定报告，不能用 cell 数量代替。runtime 是包含 `make synth` 的实际 wall time，失败 point 也要记录。

### 6.4 Pareto、hypervolume、auto-tuning 和 fallback

- 每个电路最多保留 7 个尝试 point；超过 7 个不得继续扩展。
- 只把功能正确、area/arrival/WNS/TNS 有报告的 point 放入 Pareto 集合。
- 被支配 point 可在确认日志已归档后从最终提交候选中剔除，但不要删除失败证据。
- 使用官方参考前沿和项目 `scoring.md` 中的定义计算 Pareto/hypervolume；记录参考文件、输入 CSV、脚本版本和输出。
- auto-tuning 必须记录候选配置、选择理由、fallback 触发条件、失败 point 和最终选中的 point。配置回退成功不等于该 point 的 PPA 通过，仍需重新综合、等价和 STA。
- 如果没有官方 OpenSTA、统一参考前沿或可复现的评分脚本，PPA/Pareto/hypervolume 状态保持 `not_verified`，不填估算数值。

### 6.5 Phase 3 产物、失败记录、停止/回退

预期产物：OpenSTA 版本日志、每个 point 的 `run_sta.tcl`、OpenSTA log、area/arrival/WNS/TNS 报告、runtime 表、失败 point 表、Pareto/hypervolume 输入输出、auto-tuning/fallback 记录，以及 Phase 3 SUMMARY/VERIFICATION。

OpenSTA 缺失、TCL 失败、link 失败、SDC 未加载、报告缺少关键指标、point 超过 7 个或结果无法复现时停止。不要手填 timing/PPA，不要把本机 Yosys 成功升级成官方 PPA pass。源代码需要调整时退出本阶段并重新走 GSD 规划流程。

## 7. Phase 4：打包、元数据和最终交付

### 7.1 进入条件

- Phase 1/2 的正确性证据已完成或明确记录 blocker。
- Phase 3 的官方 OpenSTA/PPA 证据已完成或明确记录 `not_verified/blocked`。
- 所有失败 point、未验证 point、初始化感知限制和官方镜像边界都已进入 SUMMARY/VERIFICATION。

### 7.2 文件、声明和红线检查

```bash
cd /workspace/AI4S
export A3="$PWD/Track-A/A3-synthesis"
export EVIDENCE="$PWD/evidence/a3/phase4"
mkdir -p "$EVIDENCE"
set -o pipefail
for f in Makefile submission.yaml config.json ORIGINALITY_DECLARATION.md README_SUBMISSION.md; do
  test -f "$A3/$f" || { echo "missing: $A3/$f"; exit 1; }
done
test -d "$A3/src"
rg -n "AI4S-Team|TODO|FIXME|placeholder|coming soon|not available" \
  "$A3/submission.yaml" "$A3/ORIGINALITY_DECLARATION.md" "$A3/README_SUBMISSION.md" \
  2>&1 | tee "$EVIDENCE/metadata-placeholder-scan.log" || true
rg -n "blackbox|black_box|precomputed|外部服务|network|worker|parallel" \
  "$A3" --glob '!testcases/docs/**' --glob '!testcases/figures/**' \
  2>&1 | tee "$EVIDENCE/redline-scan.log" || true
```

扫描结果必须人工分类：队名占位符、未完成声明、禁止项、预计算网表、外部服务和违规并行都必须在提交前处理或明确阻塞；不要用删除日志或忽略输出解决问题。

### 7.3 clean build/test 和归档复验

在临时副本做 clean 验证，避免破坏工作目录：

```bash
cd /workspace/AI4S
rm -rf /tmp/a3-clean-check
mkdir -p /tmp/a3-clean-check
# 仅复制 A3 交付目录到临时目录，不修改仓库中的 A3 文件
cp -a Track-A/A3-synthesis /tmp/a3-clean-check/A3-synthesis
cd /tmp/a3-clean-check/A3-synthesis
make clean 2>&1 | tee /tmp/a3-clean-check/clean.log
MAKEFLAGS=-j1 make -j1 build 2>&1 | tee /tmp/a3-clean-check/build.log
MAKEFLAGS=-j1 make -j1 test 2>&1 | tee /tmp/a3-clean-check/test.log
find . -maxdepth 2 -type f | sort | tee /tmp/a3-clean-check/file-list.txt
```

预期：临时 clean 副本能够 build/test；日志包含 28 tests 通过或明确记录为何官方环境不同。归档后必须从新目录重新解压再执行同样检查：

```bash
cd /workspace/AI4S
rm -f /tmp/a3-submission.tar.gz
# 归档前先确认提交范围和文件清单；不要把 .git、证据临时目录或秘密文件带入提交包
find Track-A/A3-synthesis -maxdepth 1 -type f -print | sort
 tar --exclude='Track-A/A3-synthesis/.git' \
      --exclude='Track-A/A3-synthesis/bin' \
      --exclude='Track-A/A3-synthesis/__pycache__' \
      -czf /tmp/a3-submission.tar.gz Track-A/A3-synthesis
rm -rf /tmp/a3-archive-check
mkdir -p /tmp/a3-archive-check
 tar -xzf /tmp/a3-submission.tar.gz -C /tmp/a3-archive-check
cd /tmp/a3-archive-check/Track-A/A3-synthesis
MAKEFLAGS=-j1 make -j1 build 2>&1 | tee /tmp/a3-archive-check/build.log
MAKEFLAGS=-j1 make -j1 test 2>&1 | tee /tmp/a3-archive-check/test.log
```

### 7.4 官方镜像复验、GSD 验收和交付

clean archive 通过后，再用竞赛实际镜像、固定资源约束复验入口和至少一个代表性 point；完整复验应覆盖 Phase 2 已选 points：

```bash
cd /workspace/AI4S
export OFFICIAL_IMAGE='<OFFICIAL_IMAGE>'
set -o pipefail
docker run --rm --network none --cpus 1 --memory 10g \
  -e MAKEFLAGS=-j1 \
  -v "$PWD":/workspace/AI4S -w /workspace/AI4S \
  "$OFFICIAL_IMAGE" bash -lc '
    set -e
    make -C /workspace/AI4S/Track-A/A3-synthesis -j1 build
    make -C /workspace/AI4S/Track-A/A3-synthesis -j1 test
  ' 2>&1 | tee evidence/a3/phase4/official-clean-recheck.log
```

确认所有阶段的 SUMMARY/VERIFICATION 后执行：

```text
/gsd-progress
/gsd-verify-work 4
/gsd-code-review 4
/gsd-ship
```

若 `verify` 或 review 发现源码、Makefile、配置或提交包需要修改，停止当前流程，回到 `/gsd-discuss-phase`、`/gsd-plan-phase`、`/gsd-execute-phase`，不要在交付检查阶段直接编辑。

### 7.5 Phase 4 产物、失败记录、停止/回退

预期产物：文件存在性和声明扫描、clean build/test 日志、解压归档复验日志、官方镜像复验日志、最终提交包文件清单、Phase 4 SUMMARY/VERIFICATION、verify/code-review/ship 结果。

缺文件、队名或声明仍是占位符、clean 副本不能 build/test、归档解压后缺依赖、官方镜像不能复验或有未解释失败 point 时，Phase 4 保持 incomplete/blocked。禁止用破坏性 Git 命令清理问题；使用 `/gsd-undo` 或针对明确自有提交的 `git revert`。

## 8. 最终命令清单与路径

提交前至少逐项执行并保存日志：

```bash
cd /workspace/AI4S

git status --short
git rev-parse HEAD

# 本机基线
make -C Track-A/A3-synthesis -j1 build
make -C Track-A/A3-synthesis -j1 test

# A3 入口和关键文件
ls -l Track-A/A3-synthesis/Makefile \
  Track-A/A3-synthesis/config.json \
  Track-A/A3-synthesis/submission.yaml \
  Track-A/A3-synthesis/ORIGINALITY_DECLARATION.md
find Track-A/A3-synthesis/src -type f -maxdepth 1 -print | sort

# 证据边界检查
rg -n "87675ff|28 tests|LSV01|LSV07|LSV09|LSV10|OpenSTA|not_verified|observed_success" \
  .planning/STATE.md .planning/quick Track-A/A3-synthesis

# 最终 GSD 验收链
/gsd-progress
/gsd-verify-work 4
/gsd-code-review 4
/gsd-ship
```

关键路径：

- A3 根目录：`Track-A/A3-synthesis/`
- 实现：`Track-A/A3-synthesis/src/`
- 测试：`Track-A/A3-synthesis/tests/`
- 配置：`Track-A/A3-synthesis/config.json`
- 入口：`Track-A/A3-synthesis/Makefile`
- 提交元数据：`Track-A/A3-synthesis/submission.yaml`
- 原创性声明：`Track-A/A3-synthesis/ORIGINALITY_DECLARATION.md`
- 公开电路：`Track-A/A3-synthesis/testcases/public/`
- Nangate45：`Track-A/A3-synthesis/testcases/lib/nangate45/`
- 证据建议目录：`evidence/a3/phase1/`、`evidence/a3/phase2/`、`evidence/a3/phase3/`、`evidence/a3/phase4/`

最后再次强调：本指南只创建并提交 `Track-A/A3-synthesis/A3_GSD_EXECUTION_GUIDE.md`。它不改 A3 源码、`tests/**`、Makefile、`config.json`、`submission.yaml` 或 `.planning/**`。任何实现性修改都必须停止，并重新走 GSD 的 discuss → plan → execute 流程。
