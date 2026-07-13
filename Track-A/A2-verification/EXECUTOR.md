# A2 执行器配置：三方独立竞赛

> 适用范围：仅 A2（验证环境自动生成）。A1/A3 不受影响。
> 关联文档：[PLAN.md](./PLAN.md)（cocotb + Verilator 路线）、spec.md、scoring.md
> 最后更新：2026-07-13

## 1. 模式

三路独立竞赛：mac 端 Claude Code、win 端 Claude Code、mac 端 Codex 三方按已定 [PLAN.md](./PLAN.md) 各自完整实现 A2 流水线，独立产出，末段取最优合并。

| 维度 | 说明 |
|---|---|
| 目标 | 冲分最大化，对冲单点实现风险 |
| 基线 | 三方统一以 PLAN.md（cocotb + Verilator）为实现规范 |
| 合并时机 | 末段（评测前），由 A2 负责人裁定 |
| 并行性 | 三套 agent 环境并行，互不阻塞 |

## 2. 三方环境

| 实例 | 平台 | 工具 | 角色 | 工作分支 |
|---|---|---|---|---|
| mac-CC | macOS | Claude Code | 独立实现 A2 全流水线；信息放送：定期把本机进度/发现/坑同步给 win-CC 与 mac-Codex | exec/mac-cc |
| win-CC | Windows | Claude Code | 独立实现 A2 全流水线；接收 mac-CC 信息放送，并反向同步本机进度/发现/坑（双向闭环） | exec/win-cc |
| mac-Codex | macOS | Codex CLI | 独立实现 A2 全流水线；接收 mac-CC 信息放送，并反向同步本机进度/发现/坑（双向闭环） | exec/mac-codex |

> 三方各自从 master 拉工作分支，不直接在 master 上开发；末段合并由负责人操作。

> **开发策略**（覆盖率跨平台一致性是核心风险：三方无人在评测 OS Linux x86_64 上原生跑过，必须 Docker 复验）：
> - **mac-CC / mac-Codex**：开发期用本机 native Verilator(brew 5.050) 提速；提交前必须在 Docker linux/amd64 容器内（`verilator/verilator:5.050` 官方镜像）复跑全部 case，覆盖率与产物无漂移才提交。
> - **win-CC**：WSL2（原生 linux/amd64，最接近评测 OS）开发与验证。
> - **fallback**：venv3.12 + install.sh。
>
> **双向同步**：mac-CC 负责「信息放送」（定期把本机进度/发现/坑同步出去）；win-CC 与 mac-Codex 必须接收，并**反向同步**自身进度/发现/坑回 mac-CC，形成双向闭环，避免信息单向下行导致重复踩坑。

## 3. 共同基线

三方必须遵守的统一约束（偏离需提 issue，不擅自改 PLAN）：

- **路线**：cocotb + Verilator，覆盖率用 `--coverage-line --coverage-toggle`（PLAN.md；**branch 由 `--coverage-line` 自动产出**，Verilator 5.050 无 `--coverage-branch` 标志）
  > ✅ **congress 评审已裁决（2026-07-14）**：coverage 命令定标 `--coverage-line --coverage-toggle`（选项 A）。理由：`--coverage-line` 自动产 line+branch（Verilator 官方设计，branch 是 line coverage 结构化副产品）；functional(30%) 靠 cocotb bin，非 Verilator 标志。落地：①`COVERAGE_FLAGS` 参数化（Makefile 顶层变量，默认 A）；②解析器 schema-driven（字段从标志派生）；③coverage 文件头写 `verilator --version`+flags；④Phase1 末单端 C 烟雾测试验 fsm 格式四方一致；⑤functional bin 模板预置（FSM/数据通路/存储器/AXI 4 类，30% 权重杠杆）；⑥评分细则若发布且 branch 解读为真值表则切 B（零代码）。
- **接口契约**：run.sh 五参数 + 七个 JSON 产物 schema（design/skeleton/constraints/bins/func_cov/result/report）（PLAN.md）
- **评测对象**：10 个独立电路，每电路单独计分（spec.md）
- **覆盖率公式**：C = 0.4×行 + 0.3×分支 + 0.3×功能，行/分支占 70%（PLAN.md）
- **产物自交**：coverage_result.json 由选手自交，评测器不锁工具重算（PLAN.md）

## 4. 产物隔离与合并

### 4.1 产物隔离
- 三方产物命名前缀隔离，避免覆盖：`coverage_result.<instance>.json`、`dataset_result.<instance>.json`
- 仿真波形、编译产物等大文件不进 repo，各自本地保留
- repo 内只提交关键 JSON 产物 + 最终 run.py/src 实现

### 4.2 末段合并
- 对比三方在 5 个公开 case（testcases/A2_public_dataset）上的覆盖率与产物质量
- 取最优组合：骨架/参考模型/覆盖率采集可分别取各方最优段拼接
- 合并到 master 由 A2 负责人裁定

## 5. 协调约定

- **locked**：spec.md / scoring.md / testcases/ 为赛题官方内容，三方不得修改
- **PLAN 修改**：对 PLAN.md 的分歧提 issue，不擅自改
- **公式风险**：composite 公式存在 spec 与公开样例不一致（见 PLAN.md 待澄清），以 scoring.md 为准
- **Phase3 通用化红线**：10 个隐藏电路结构/参数/接口组合各异，严禁硬编码或针对性优化（如针对特定 case 塞 bin hits、对特定 RTL 路径打补丁、把 case 标签当 module 名）；框架须对未见接口泛化，违反则隐藏评测失分（PLAN.md §五 Phase3 引 README 红线）
- **进度同步**：各方里程碑（M1 骨架 / M2 参考模型+约束随机 / M3 覆盖率 / M4 反馈闭环）完成时在 issue 报进度

## 6. 提交约定

- 工作分支命名：`exec/<instance>`（exec/mac-cc、exec/win-cc、exec/mac-codex）
- 末段合并到 master 由 A2 负责人操作
- commit message 风格：`A2: <描述> (<细节>)`，中文

---

> 版本：v1.0
> 基于：PLAN.md（cocotb + Verilator, 2026-07-13）、spec.md、scoring.md
> 最后更新：2026-07-13
