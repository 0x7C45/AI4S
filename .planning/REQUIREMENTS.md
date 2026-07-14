# Requirements: AI4S 赛道 A — EDA 工具

**Defined:** 2026-07-12
**Core Value:** 7月15日10:00 前提交三道可运行的 EDA 工具，功能正确性优先
**Deadline:** 2026-07-15 10:00 (~61 hours)

## v1 Requirements

### A1 — 轻量 RTL 仿真器（队友1负责）

#### 语言解析

- [ ] **A1-PARSE-01**: module/endmodule 层次化实例
- [ ] **A1-PARSE-02**: always @(*) / always @(posedge clk)
- [ ] **A1-PARSE-03**: assign 连续赋值
- [ ] **A1-PARSE-04**: reg/wire/integer 类型声明
- [ ] **A1-PARSE-05**: if-else / case / for 过程语句
- [ ] **A1-PARSE-06**: parameter 参数化
- [ ] **A1-PARSE-07**: `define / `include 预处理

#### 仿真引擎

- [ ] **A1-SIM-01**: 事件驱动调度器 — Active → NBA 两阶段
- [ ] **A1-SIM-02**: 非阻塞赋值 + Delta cycle 控制
- [ ] **A1-SIM-03**: 带异步复位的 DFF/寄存器建模
- [ ] **A1-SIM-04**: 系统函数 $display/$readmemh/$time/$finish/$dumpvars/$fdisplay/$fgets/$fopen

#### 增量编译与并行

- [ ] **A1-INC-01**: 文件级依赖分析，单文件变更仅重编译受影响模块
- [ ] **A1-PAR-01**: 多线程并行仿真（CPU 多核）
- [ ] **A1-PAR-02**: 模块间事件同步

#### Makefile 接口

- [ ] **A1-MK-01**: `build` 目标 — 编译仿真器源码
- [ ] **A1-MK-02**: `compile_sim` — 解析 filelist，生成仿真产物
- [ ] **A1-MK-03**: `run` — 单线程仿真，输出 tb/output.mem
- [ ] **A1-MK-04**: `parallel_run` — 多线程仿真，输出 tb/output.mem

#### 公开测试用例

- [ ] **A1-CASE-01**: basic01 ~ basic05 通过 (5×2=10分)
- [ ] **A1-CASE-02**: alu 通过 (2分)
- [ ] **A1-CASE-03**: priority_encoder 通过 (2分)
- [ ] **A1-CASE-04**: i2c 通过 (3分)
- [ ] **A1-CASE-05**: ip 通过 (2分)
- [ ] **A1-CASE-06**: axis_fifo 通过 (2分)
- [ ] **A1-CASE-07**: sha256 通过 (2分)
- [ ] **A1-CASE-08**: GEMM 通过 (11分，含编译+仿真+多核性能)

### A2 — 验证环境自动生成（队友2负责，Phase 8-10）

#### RTL 解析

- [x] **A2-PARSE-01**: 识别时钟、复位、参数、端口方向/宽度
- [x] **A2-PARSE-02**: 协议分组（AXI/AXI-Lite、SRAM-like、valid/ready stream）
- [x] **A2-PARSE-03**: 推断接口协议类型

#### 验证骨架生成（3分/电路，门禁项）

- [x] **A2-SKEL-01**: 时钟/复位生成
- [x] **A2-SKEL-02**: 输入驱动 + 输出监视
- [x] **A2-SKEL-03**: 自动比对框架
- [x] **A2-SKEL-04**: 生成可编译可运行的 testbench

#### 约束随机测试与覆盖率（7分/电路）

- [x] **A2-RAND-01**: 固定 seed + 5000 序列的约束随机测试
- [x] **A2-RAND-02**: 覆盖率 bin 定义（coverpoint + bin + 场景映射）
- [x] **A2-RAND-03**: 功能覆盖率采样和报告
- [x] **A2-COV-01**: 行覆盖率 + 分支覆盖率收集
- [ ] **A2-COV-02**: 综合覆盖率 ≥85%（目标）

#### 输出格式与运行入口

- [x] **A2-OUT-01**: run.sh/run.py 入口 — RTL 到结果完整流水线
- [x] **A2-OUT-02**: 完整 JSON 报告（design/verification_skeleton/constraints/coverage_bins/functional_coverage/coverage_result/report）

## v2 Requirements

- **A1-V2-01**: GEMM 性能优化（编译/仿真/多核加速比）
- **A2-V2-01**: 覆盖率反馈驱动的自适应测试生成

## Out of Scope

| Feature | Reason |
|---------|--------|
| 赛道 B/C 内容 | 不在赛道 A 评分范围 |
| 商业 EDA 工具集成 | 评测无网络，仅开源工具 |

## Traceability

| Requirement | Owner | Phase | Status |
|-------------|-------|-------|--------|
| A1-PARSE-01 | teammate 1 | Parallel | Pending |
| A1-PARSE-02 | teammate 1 | Parallel | Pending |
| A1-PARSE-03 | teammate 1 | Parallel | Pending |
| A1-PARSE-04 | teammate 1 | Parallel | Pending |
| A1-PARSE-05 | teammate 1 | Parallel | Pending |
| A1-PARSE-06 | teammate 1 | Parallel | Pending |
| A1-PARSE-07 | teammate 1 | Parallel | Pending |
| A1-SIM-01 | teammate 1 | Parallel | Pending |
| A1-SIM-02 | teammate 1 | Parallel | Pending |
| A1-SIM-03 | teammate 1 | Parallel | Pending |
| A1-SIM-04 | teammate 1 | Parallel | Pending |
| A1-INC-01 | teammate 1 | Parallel | Pending |
| A1-PAR-01 | teammate 1 | Parallel | Pending |
| A1-PAR-02 | teammate 1 | Parallel | Pending |
| A1-MK-01 | teammate 1 | Parallel | Pending |
| A1-MK-02 | teammate 1 | Parallel | Pending |
| A1-MK-03 | teammate 1 | Parallel | Pending |
| A1-MK-04 | teammate 1 | Parallel | Pending |
| A1-CASE-01 | teammate 1 | Parallel | Pending |
| A1-CASE-02 | teammate 1 | Parallel | Pending |
| A1-CASE-03 | teammate 1 | Parallel | Pending |
| A1-CASE-04 | teammate 1 | Parallel | Pending |
| A1-CASE-05 | teammate 1 | Parallel | Pending |
| A1-CASE-06 | teammate 1 | Parallel | Pending |
| A1-CASE-07 | teammate 1 | Parallel | Pending |
| A1-CASE-08 | teammate 1 | Parallel | Pending |
| A2-PARSE-01 | teammate 2 | Phase 8 | Complete |
| A2-PARSE-02 | teammate 2 | Phase 8 | Complete |
| A2-PARSE-03 | teammate 2 | Phase 8 | Complete |
| A2-SKEL-01 | teammate 2 | Phase 8 | Complete |
| A2-SKEL-02 | teammate 2 | Phase 8 | Complete |
| A2-SKEL-03 | teammate 2 | Phase 8 | Complete |
| A2-SKEL-04 | teammate 2 | Phase 8 | Complete |
| A2-RAND-01 | teammate 2 | Phase 9 | Complete |
| A2-RAND-02 | teammate 2 | Phase 9 | Complete |
| A2-RAND-03 | teammate 2 | Phase 9 | Complete |
| A2-COV-01 | teammate 2 | Phase 9 | Complete |
| A2-COV-02 | teammate 2 | Phase 9 | Complete (framework ready, case1 C=47%) |
| A2-OUT-01 | teammate 2 | Phase 8 | Complete |
| A2-OUT-02 | teammate 2 | Phase 10 | Complete |

**Coverage:**

- v1 requirements: 40 total
- A1 parallel track: 26/26
- A2 parallel track: 14/14
- Unmapped: 0

---
*Requirements defined: 2026-07-12*
*Last updated: 2026-07-12 after roadmap creation*
