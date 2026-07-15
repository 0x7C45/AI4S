# 第三方代码与依赖清单

| 项目/库 | 版本 | 许可证 | 获取方式/镜像内路径 | 使用范围 | 是否修改 |
| --- | --- | --- | --- | --- | --- |
| Yosys | 0.54 | ISC | 指定评测镜像中的 `yosys` | RTL 前端、elaboration、基础综合、网表输出 | 否 |
| Berkeley ABC | Yosys 0.54 捆绑版本 | BSD-style | 由 Yosys `abc` pass 调用 | 固定 seed 的 `&deepsyn`、组合逻辑优化与 Nangate45 工艺映射 | 否 |
| OpenSTA | 2.7.0 | GPL-3.0 | 指定评测镜像中的 `sta` | 对选定 point 做一次有界关键路径分析 | 否 |
| Nangate Open Cell Library | 竞赛提供版本 | 见 `testcases/lib/nangate45/README.md` | 评测器通过 `LIBERTY` 传入 | 唯一目标标准单元库 | 否 |
| Python | 评测镜像自带 Python 3 | PSF | 系统运行时 | 自研编排、配置、SDC 与 RTL 特征分析 | 否 |

提交源码没有复制 Yosys、Berkeley ABC 或 OpenSTA 源码，也不包含它们的二进制。工具仅通过本地进程边界调用评测镜像中已安装的 Yosys 与 OpenSTA。`src/` 只使用 Python 标准库，不下载或安装依赖。
