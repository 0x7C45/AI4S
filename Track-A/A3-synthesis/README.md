# A3 AdaptiveYosys 逻辑综合工具

本目录包含 A3 提交源码和公开题复现实验。工具在官方离线镜像中调用 Yosys 0.54、其内置 Berkeley ABC 与 OpenSTA 2.7.0，根据 `config.json` 为每个电路选择 1–7 个综合 point，并输出 Nangate45 门级网表。

## 提交内容

- `Makefile`：唯一构建和综合入口
- `submission.yaml`：工具元数据
- `config.json`：公开电路和隐藏电路默认 point 配置
- `ORIGINALITY_DECLARATION.md`：原创模块、消融和 LLM 使用声明
- `THIRD_PARTY.md`：Yosys/ABC 调用边界与许可证
- `src/`：完整 Python 标准库实现

## 构建

```bash
make -j1 build
```

构建后生成 `bin/synth_tool`，不访问网络，也不下载依赖。

## 综合一个 point

```bash
make -j1 synth \
  RTL=/case/rtl/design.v \
  TOP=top \
  SDC=/case/constraints.sdc \
  LIBERTY=/pdk/NangateOpenCellLibrary_typical.lib \
  CONFIG=/submission/config.json \
  CIRCUIT=LSV01 \
  POINT=1 \
  OUT_DIR=/output
```

成功时生成 `/output/netlist.v`。每个 point 独立运行，工具遵守 1 CPU、1 线程、10 GiB 内存和无网络约束。

## 测试

```bash
make -j1 test
```

测试覆盖配置选择、隐藏电路 `$default` 回退、SDC 解析、自适应策略、ABC 脚本、gate sizing、高扇出缓冲、OpenSTA 关键路径 sizing、改写失败回退和 Makefile 端到端接口。所有映射后改写都会由 Yosys 重新解析和检查，失败时自动恢复未改写网表。官方镜像中的公开 61 点复现实验可运行：

```bash
python3 experiments/run_submission_baseline.py --output /tmp/a3-official-baseline
```

按赛题手册中的固定 nadir 和二维最小化超体积公式重算公开代理分（不替代隐藏正确性仿真）：

```bash
python3 experiments/score_submission.py /tmp/a3-official-baseline/results.csv
```

隐藏回退七点选择可由候选结果完整重算。当前默认组合额外包含高强度 `amap` 候选，相关配置保存在 `experiments/configs/config.amap-*.json`：

```bash
python3 experiments/run_submission_baseline.py --config experiments/configs/config.default-current.json --output /tmp/a3-default-current
python3 experiments/run_submission_baseline.py --config experiments/configs/config.default-alternatives.json --output /tmp/a3-default-alternatives
python3 experiments/run_submission_baseline.py --config experiments/configs/config.default-sizing.json --output /tmp/a3-default-sizing
python3 experiments/run_submission_baseline.py --config experiments/configs/config.buffer-threshold.json --output /tmp/a3-buffer-threshold
python3 experiments/run_submission_baseline.py --config experiments/configs/config.buffer-amap.json --output /tmp/a3-buffer-amap
python3 experiments/select_default_points.py \
  --candidate experiments/configs/config.default-current.json /tmp/a3-default-current/results.csv \
  --candidate experiments/configs/config.default-alternatives.json /tmp/a3-default-alternatives/results.csv \
  --candidate experiments/configs/config.default-sizing.json /tmp/a3-default-sizing/results.csv \
  --candidate experiments/configs/config.buffer-threshold.json /tmp/a3-buffer-threshold/results.csv \
  --candidate experiments/configs/config.buffer-amap.json /tmp/a3-buffer-amap/results.csv
```

## 清理与打包

```bash
make clean
```

在本目录运行以下 allowlist 命令，zip 根目录不会再包一层文件夹，并且不会包含 `bin/`、公开赛题包、缓存或大型日志：

```bash
rm -f AdaptiveYosys-A3.zip
zip -r AdaptiveYosys-A3.zip \
  Makefile submission.yaml config.json ORIGINALITY_DECLARATION.md \
  THIRD_PARTY.md README.md src experiments tests \
  -x '*/__pycache__/*' '*.pyc' '*.log'
```

详细实测证据见 `ORIGINALITY_DECLARATION.md`。
