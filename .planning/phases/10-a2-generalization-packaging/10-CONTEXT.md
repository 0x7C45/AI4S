# Phase 10: 通用化 + 离线打包 - Context

**Gathered:** 2026-07-14
**Status:** Ready for planning
**Source:** Derived from ROADMAP Phase 10 + CONSTRAINTS §11/§12 + Phase 8/9 SUMMARY + SMOKE_TEST_REPORT

<domain>
## Phase Boundary

Phase 10 交付：将 Phase 8/9 的 case1 验证管道通用化到 10 个隐藏电路，补全离线打包（wheelhouse + THIRD_PARTY.md + README），死码过滤精化，5000 笔性能优化，Docker 复验。最终产出可提交的 run.sh 独自跑通的完整包。

**Phase 10 不做**：新增覆盖率采集逻辑（Phase 9 已完成）、新增 testbench 骨架（Phase 8 已完成）。

**验收**：run.sh 对 5 公开 case 各自跑通完整流水线，7 JSON 齐全，覆盖率有数。

</domain>

<decisions>
## Implementation Decisions (LOCKED)

### 通用化（CONSTRAINTS §11 红线 #5）
- 框架对 10 个隐藏电路**禁硬编码 / 禁针对性优化**
- 策略必须通用：rtl_parser 按端口模式自动推断协议，coverage_gen 按协议选 bin 模板，testbench 按接口自适应驱动
- 公开 case（case1-5）作为通用化测试基准，**不可照搬**

### 死码过滤精化（Phase 9 遗留）
- Phase 9 dead_code_analyzer 对 if/else 块边界识别不精确（把 else 激活分支也标死）
- Phase 10 精化：只标记 `if (PARAM)` 到对应 `else` 之间的行为死码，`else` 块保留为可达
- 或保守方案：死码过滤改为可选（默认关闭），覆盖率分母含全部行（保守真实）

### 5000 笔性能优化（Phase 9 遗留）
- Phase 9 case1 5000 笔 + 覆盖率插桩超 10 分钟 timeout
- 优化方向：①Docker 容器 timeout 提到 1200s ②cocotb log 降噪（WARNING 级）③减少 RisingEdge 等待
- 评测机可能有更高性能，5000 笔必须能跑完（CONSTRAINTS §3 硬约束 sequence_count=5000）

### 离线打包（CONSTRAINTS §12，硬约束）
- `requirements.txt`：每包钉死 ==X.Y.Z（Phase 8 已建）
- `wheelhouse/`：`pip download --platform manylinux2014_x86_64 --python-version 3.12 --only-binary=:all:` 预生成
  - 评测机 `pip install --no-index --find-links=wheelhouse`
  - **镜像无 pip 注意**：wheelhouse 可能还需含 pip bootstrap 或 run.sh 改用 venv
- `THIRD_PARTY.md`：版本/许可/调用边界（已存在，Phase 10 确认完整性）
- `README.md`：离线安装运行说明

### Docker 复验（CONSTRAINTS §13）
- win-ZCode 主环境即 Docker linux/amd64，与评测同构
- 复跑 5 公开 case，确认覆盖率可复现（seed 20260630 + 相同 RTL → 一致结果）

### 六条原创性红线（CONSTRAINTS §11）
1. 禁抄袭 2. 禁硬编码 3. 禁绕评测 4. 禁预计算 5. 禁针对性优化 6. 禁未披露依赖
- Phase 10 重点检查 #2/#5：框架不可含 case1-5 的特定 RTL 路径/参数/bin 硬编码

### Claude's Discretion
- 死码过滤最终策略（精化块匹配 or 可选关闭）
- wheelhouse 生成方式（主机 pip download 还是 Docker 内生成）
- README 的具体安装步骤结构

</decisions>

<canonical_refs>
## Canonical References

### Phase 8/9 产出（Phase 10 基础）
- `E:/AI4S/Track-A/A2-verification/run.py` — 完整流水线（Phase 10 优化 timeout）
- `E:/AI4S/Track-A/A2-verification/src/sim_runner.py` — Docker 仿真（Phase 10 调 timeout）
- `E:/AI4S/Track-A/A2-verification/src/dead_code_analyzer.py` — 死码分析（Phase 10 精化）
- `E:/AI4S/Track-A/A2-verification/src/rtl_parser.py` — 通用化基础
- `E:/AI4S/Track-A/A2-verification/src/coverage_gen.py` — 4 类 bin 模板

### 赛题规格
- `E:/AI4S/Track-A/A2-verification/CONSTRAINTS.md` — §11 红线、§12 离线打包、§13 三方协同
- `E:/AI4S/Track-A/A2-verification/ENVIRONMENT.md` — §4 离线打包方案、§5 Docker 复验
- `E:/AI4S/Track-A/A2-verification/THIRD_PARTY.md` — 第三方依赖（Phase 10 确认完整）

### 公开数据集（通用化测试基准）
- `E:/AI4S/Track-A/A2-verification/testcases/A2_public_dataset/case1-5/` — 5 个公开 case

</canonical_refs>

<deferred>
## Deferred Ideas

- 无（Phase 10 是最后阶段）

</deferred>

---

*Phase: 03-generalization-packaging*
*Context gathered: 2026-07-14*
