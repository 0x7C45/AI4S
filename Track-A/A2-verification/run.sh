#!/bin/bash
# A2 验证环境自动生成 — 统一入口 wrapper
# 转发五参数到 python3 run.py
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "${SCRIPT_DIR}/run.py" "$@"
