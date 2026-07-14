#!/bin/bash
# A2 验证环境自动生成 — 统一入口
# 用法: ./run.sh --rtl <dir> --top <module> --out <dir> --seed 20260630 --num-seq 5000
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# ── 离线依赖安装（per D-22：评测机断网，从 wheelhouse 离线装）──
if [ -d "wheelhouse" ] && ! python3 -c "import cocotb" 2>/dev/null; then
    echo "[setup] 离线安装依赖（wheelhouse/）..."
    pip3 install --no-index --find-links=wheelhouse -r requirements.txt 2>/dev/null \
        || python3 -m pip install --no-index --find-links=wheelhouse -r requirements.txt
fi

# ── 执行完整流水线 ──
exec python3 "${SCRIPT_DIR}/run.py" "$@"
