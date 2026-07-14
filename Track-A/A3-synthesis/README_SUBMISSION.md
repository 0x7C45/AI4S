# AdaptiveYosys A3 提交说明

本目录已经实现 A3 评测要求的离线综合入口。工具用 Python 标准库编排 Yosys/ABC，根据 `config.json` 选择面积、时序或平衡 point，并生成 Nangate45 门级网表。

## 构建

```bash
make -j1 build
```

成功后生成 `bin/synth_tool`。

## 运行一个公开电路

```bash
make -j1 synth \
  RTL=testcases/public/LSV01_epfl_priority/rtl/design.v \
  TOP=top \
  SDC=testcases/public/LSV01_epfl_priority/constraints.sdc \
  LIBERTY=testcases/lib/nangate45/NangateOpenCellLibrary_typical.lib \
  CONFIG=config.json \
  CIRCUIT=LSV01 \
  POINT=1 \
  OUT_DIR=/tmp/lsv01_p1
```

成功输出为 `/tmp/lsv01_p1/netlist.v`。诊断文件保存在 `/tmp/lsv01_p1/.synth_tool/`，包括生成的 Yosys 脚本、日志、RTL 特征和最终策略。

## 本地测试

```bash
make -j1 build
make -j1 test
```

测试覆盖配置回退、point 边界、SDC、RTL 特征、自适应策略、Yosys 脚本和完整 `make synth` 接口。模拟 Yosys 只验证编排链路；正式提交前必须在指定竞赛镜像中运行 LSV01-LSV10 的全部 point，并执行 RTL/门级等价与 OpenSTA PPA 检查。

## 提交前检查

1. 将 `submission.yaml` 和 `ORIGINALITY_DECLARATION.md` 中的 `AI4S-Team` 替换为正式队名。
2. 在指定镜像中记录 10 个公开电路每个 point 的正确性、area、arrival 和 runtime。
3. 删除失败或被支配的 point，减少运行时间扣分。
4. 把实测消融结果补充到 `ORIGINALITY_DECLARATION.md`。
5. 最终提交至少包含 `Makefile`、`submission.yaml`、`config.json`、两份声明和 `src/`。
