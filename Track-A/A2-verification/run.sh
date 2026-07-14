#!/bin/bash
# A2 验证环境自动生成 — 统一入口
# 用法: ./run.sh --rtl <dir> --top <module> --out <dir> --seed 20260630 --num-seq 5000
#
# Docker 镜像优先级（per Phase 10 FIX6）:
#   1. AI4S_A2_IMAGE 环境变量（评测机 docker load 后 export）
#   2. 本地 ai4s-a2:verilator-cocotb 镜像（自动检测）
#   3. verilator/verilator:v5.050 基础镜像（需 wheelhouse 离线自举）
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── Docker 镜像自动选择 ──
if [ -z "${AI4S_A2_IMAGE:-}" ]; then
    if docker image inspect ai4s-a2:verilator-cocotb >/dev/null 2>&1; then
        export AI4S_A2_IMAGE=ai4s-a2:verilator-cocotb
        echo "[setup] 使用预装镜像 ai4s-a2:verilator-cocotb（零 bootstrap）"
    else
        echo "[setup] 未找到预装镜像，使用 verilator/verilator:v5.050（走 wheelhouse 离线自举）"
        echo "       评测机推荐: docker load < ai4s-a2-image.tar.gz && export AI4S_A2_IMAGE=ai4s-a2:verilator-cocotb"
    fi
fi

# ── 离线依赖安装（per D-22：评测机断网，从 wheelhouse 离线装）──
# 仅在主机本地跑（非 Docker）时需要；Docker 仿真在容器内装。
# 容错：评测机可能无 python3（Windows）或仅 Docker，此步失败不阻断——
# Docker 路径自给自足（容器内 PYTHONPATH pip 离线装）。
PYTHON_BIN=""
for cand in python3 python; do
    if command -v "$cand" >/dev/null 2>&1; then PYTHON_BIN="$cand"; break; fi
done
if [ -n "$PYTHON_BIN" ] && [ -d "wheelhouse" ] && ! "$PYTHON_BIN" -c "import cocotb" 2>/dev/null; then
    echo "[setup] 离线安装依赖（wheelhouse/）..."
    "$PYTHON_BIN" -m pip install --no-index --find-links=wheelhouse -r requirements.txt 2>/dev/null \
        || echo "[setup] 主机离线装失败（非致命，Docker 路径自给自足）"
fi

# ── 执行完整流水线 ──
# python3 优先（Linux 评测机），fallback python（Windows 开发机）
RUN_PYTHON="${PYTHON_BIN:-python3}"
exec "$RUN_PYTHON" "${SCRIPT_DIR}/run.py" "$@"
