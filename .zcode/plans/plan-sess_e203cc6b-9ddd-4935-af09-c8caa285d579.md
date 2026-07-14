# A2 纳入根规划 — Phase 8/9/10 重编号迁移

## 目标
将 A2 的 3 个 phase 从子目录 `Track-A/A2-verification/.planning/` 迁移到根 `.planning/`，分配 Phase 8/9/10 编号，使根成为唯一规划源。迁移后删除子目录 `.planning/`。

## 编号映射
| 子目录原编号 | 新根编号 | 名称 | 状态 |
|---|---|---|---|
| A2-01 | **Phase 8** | 骨架门禁 — RTL 解析 + testbench 生成 | ✅ Complete |
| A2-02 | **Phase 9** | 覆盖率收集 — 行/分支/功能 + 约束随机 | ✅ Complete |
| A2-03 | **Phase 10** | 通用化 + 离线打包 | 🔄 In Progress（Task1-3 done，无 SUMMARY） |

## 执行步骤

### Step 1: 创建根 phase 目录 + 复制文件（3 目录，8 文件）
```
.planning/phases/08-a2-skeleton-gate/{08-01-PLAN.md, 08-01-SUMMARY.md, 08-CONTEXT.md}
.planning/phases/09-a2-coverage-collection/{09-01-PLAN.md, 09-01-SUMMARY.md, 09-CONTEXT.md}
.planning/phases/10-a2-generalization-packaging/{10-01-PLAN.md, 10-CONTEXT.md}
```
文件名从 `01-01-PLAN.md`→`08-01-PLAN.md`（前缀改 phase 编号）。

### Step 2: 复制后逐文件改写内部引用（grep 替换）
每个 phase 文件内部的交叉引用需要全局替换，确保不与 A3 的 Phase 1-4 冲突：
- **frontmatter**: `phase: A2-01-...` → `phase: 08-a2-...`；`depends_on: ["A2-02"]` → `["09"]`
- **Phase 8 文件内**："Phase 1" → "Phase 8"，"Phase 2" → "Phase 9"，"Phase 3" → "Phase 10"
- **Phase 9 文件内**：同上映射（"Phase 2"→"Phase 9"，"Phase 1"→"Phase 8"，"Phase 3"→"Phase 10"）
- **Phase 10 文件内**：同上（"Phase 3"→"Phase 10"，"Phase 1/2"→"Phase 8/9"）
- **CONTEXT Source 行**：`Derived from ROADMAP Phase 2` → `Derived from ROADMAP Phase 9` 等
- **子目录路径**：保持 `Track-A/A2-verification/...` 不变（代码仍在子目录，只有 .planning 迁走）

### Step 3: 更新根 ROADMAP.md
- **删除** A2 当前的占位段（末尾 "Parallel Track: A2 Verification Auto-gen"，含需求 ID 列表但无 phase 号）
- **新增** Phase 8/9/10 三个完整 phase 段（仿现有 Phase 1-5 格式：Goal/Depends/Requirements/Success Criteria/Plans），内容来自子目录 ROADMAP
  - Phase 8: `Requirements: A2-PARSE-01~03, A2-SKEL-01~04, A2-OUT-01`；勾选 `[x]`
  - Phase 9: `Requirements: A2-RAND-01~03, A2-COV-01~02`；勾选 `[x]`
  - Phase 10: `Requirements: A2-OUT-02, A2-08, A2-09`；未勾选 `[ ]`
- **更新 Progress 表**：加 3 行（Phase 8 `1/1 Complete`，Phase 9 `1/1 Complete`，Phase 10 `0/1 In Progress`）
- **更新顶部 Parallel Tracks 说明**：A2 Track 改为 "Phases 8-10"

### Step 4: 更新根 STATE.md
对齐真实进度（frontmatter + body 双修）：
- `current_phase: 10`，`current_phase_name: A2 通用化 + 离线打包`
- `status: in_progress`，`stopped_at: "Phase 10 Task3 完成（wheelhouse），待 Task4 验收 + SUMMARY"`
- `progress: total_phases: 10, completed_phases: 3`（Phase 5 + Phase 8 + Phase 9），`percent: 30`
- body 的 Current Position 改为 Phase 10，Progress 条 `[███░░░░░░░] 30%`
- Performance Metrics 表加 Phase 8/9 行

### Step 5: 合并子目录 PROJECT.md 独有内容到根 PROJECT.md
子目录 PROJECT.md "Key Decisions" 表有 5 条 A2 独有决策（cocotb+Verilator 路线、Docker 主环境、镜像 tag、-Wno-fatal、综合公式 0.4/0.3/0.3）。追加到根 PROJECT.md Key Decisions 表末尾。

### Step 6: 更新根 REQUIREMENTS.md
A2 需求条目（A2-PARSE-01 等，根里已存在）的复选框改为勾选：
- Phase 8 覆盖的：A2-PARSE-01~03, A2-SKEL-01~04, A2-OUT-01 → `[x]`
- Phase 9 覆盖的：A2-RAND-01~03, A2-COV-01~02 → `[x]`
- Phase 10 覆盖的：A2-OUT-02 → `[ ]`（未完成）
- Traceability 表（第 191-204 行）Phase 列：`Pending` → `Phase 8/9/10`

### Step 7: 删除子目录 `.planning/`
```bash
git rm -r Track-A/A2-verification/.planning/
```
子目录 .planning 的 PROJECT/REQUIREMENTS/ROADMAP/STATE/config/phases 全删。子目录的代码、testcases、wheelhouse、smoke_out **不动**（这些是产出物，不是规划文档）。

## 不做的事
- **不动** `Track-A/A2-verification/` 下的代码、wheelhouse、smoke_out、README、run.py 等（只有 `.planning/` 迁走）
- **不动** Phase 1-7（A3/A1）的任何内容
- **不提交**（按 GSD 惯例，改完由你 review 后决定是否 commit；当前 working tree 还有未暂存的 sim_runner.py 和 merge 刚完成）

## 验证清单（执行后自查）
- [ ] `ls .planning/phases/` 含 08/09/10 三个目录
- [ ] `grep -r "A2-01\|A2-02\|A2-03" .planning/phases/08* .planning/phases/09* .planning/phases/10*` 无残留旧 ID
- [ ] `grep -rn "Phase 1\b" .planning/phases/08* .planning/phases/09* .planning/phases/10*` 无把 A2 phase 误指 A3 phase 的引用
- [ ] `ls Track-A/A2-verification/.planning/` 不存在
- [ ] 根 ROADMAP/STATE 进度数字一致（completed_phases: 3, percent: 30）
- [ ] REQUIREMENTS.md A2 复选框与 phase 完成状态一致

## 风险与缓解
| 风险 | 缓解 |
|---|---|
| phase 文件内部 "Phase 1/2/3" 替换误伤 | 用带边界的正则（`\bPhase 1\b`），替换后 grep 逐文件复核 |
| D-19~D-23 等 CONTEXT 决策丢失 | CONTEXT.md 整文件复制，只改编号引用，决策正文不动 |
| 子目录代码引用 .planning 路径 | 已确认代码（run.py/sim_runner 等）不读 .planning/，规划文档只是 GSD 元数据 |