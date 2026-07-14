#!/usr/bin/env python3
"""仿真执行器 — Docker 容器内跑 cocotb + Verilator

per D-06: 镜像 verilator/verilator:v5.050 无 pip，需 apt bootstrap。
"""

import subprocess
import os
from dataclasses import dataclass
from pathlib import Path


@dataclass
class SimResult:
    passed: bool
    exit_code: int
    stdout: str
    stderr: str


# per D-20: single source of truth for the subprocess timeout. Both the Docker
# path and the local-make path must honor this so case2-5 (and the 5000-seq run)
# cannot hit a stale 600s ceiling on the local fallback while the Docker branch
# was bumped to 1200s during Task 2.
SIM_TIMEOUT_SECONDS = 1200


# Docker 命令模板（per D-06：镜像无 pip，需 bootstrap）
# per Phase 10 FIX5/6: 两层镜像策略
#   1. AI4S_A2_IMAGE 环境变量指向预装镜像（ai4s-a2:verilator-cocotb）→ 零 bootstrap
#   2. 默认 verilator/verilator:v5.050 → 走 PYTHONPATH pip 离线自举（依赖 wheelhouse）
# 评测机：docker load < ai4s-a2-image.tar.gz 后 export AI4S_A2_IMAGE=ai4s-a2:verilator-cocotb
# per SMOKE_TEST_REPORT §2：MSYS_NO_PATHCONV 防 Git Bash 路径转换

# 自定义预装镜像脚本：依赖已预装，跳过 bootstrap，直接仿真
_DOCKER_RUN_TEMPLATE_PREBUILT = """\
echo "=== [1/2] 确认工具链（预装镜像）==="
python3 -c "import cocotb, cocotbext.axi; print('cocotb', cocotb.__version__)"
echo "=== [2/2] 仿真 (SIM=verilator) ==="
cd {tb_dir}
make SIM=verilator MODULE={test_module} 2>&1
echo "=== MAKE_EXIT=$? ==="
"""

# 基础镜像脚本：需离线 bootstrap pip + 装依赖（依赖 wheelhouse）
_DOCKER_RUN_TEMPLATE = """\
echo "=== [1/4] 定位 pip wheel（离线自举）==="
PIP_WHEEL=$(ls /work/wheelhouse/pip-*.whl 2>/dev/null | head -1)
if [ -n "$PIP_WHEEL" ]; then
  # 直接通过 PYTHONPATH 运行 pip wheel（无需安装 pip 本身）
  export PYTHONPATH="$PIP_WHEEL:$PYTHONPATH"
  PIP_CMD="python3 -m pip"
else
  # fallback: 仍尝试 apt（开发机有网络时）
  apt-get update -qq >/dev/null 2>&1
  apt-get install -y -qq python3-pip >/dev/null 2>&1
  PIP_CMD="python3 -m pip"
fi
echo "=== [2/4] 离线装依赖 ==="
if [ -d /work/wheelhouse ]; then
  $PIP_CMD install --break-system-packages --no-index --find-links=/work/wheelhouse cocotb==2.0.1 cocotbext-axi==0.1.28 cocotb-bus==0.3.0 scapy==2.7.0 Jinja2==3.1.6 find_libpython 2>&1 | tail -2
else
  $PIP_CMD install --break-system-packages --quiet cocotb==2.0.1 cocotbext-axi==0.1.28 cocotb-bus==0.3.0 scapy==2.7.0 2>&1 | tail -2
fi
echo "=== [3/4] 确认工具链 ==="
python3 -c "import cocotb, cocotbext.axi; print('cocotb', cocotb.__version__)"
echo "=== [4/4] 仿真 (SIM=verilator) ==="
cd {tb_dir}
make SIM=verilator MODULE={test_module} 2>&1
echo "=== MAKE_EXIT=$? ==="
"""


def run(out_dir, seed=20260630, docker=True):
    """在 Docker 容器内执行仿真

    Args:
        out_dir: 产物目录（含 generated_tb/）
        seed: 固定种子（传给仿真环境）
        docker: True=Docker 容器执行，False=本机直接 make
    Returns:
        SimResult
    """
    out_path = Path(out_dir).resolve()
    tb_dir = out_path / "generated_tb"
    test_module = "generated_test"

    if not tb_dir.exists():
        return SimResult(passed=False, exit_code=-1, stdout="", stderr=f"generated_tb not found: {tb_dir}")

    if docker:
        return _run_docker(tb_dir, test_module, seed)
    else:
        return _run_local(tb_dir, test_module, seed)


def _run_docker(tb_dir, test_module, seed):
    """Docker 容器内执行（per D-06）"""
    tb_dir_abs = str(tb_dir).replace("\\", "/")
    # Windows E:/ → Docker 挂载用 //e/
    if tb_dir_abs[1:3] == ":/":
        drive = tb_dir_abs[0].lower()
        docker_mount = f"//{drive}{tb_dir_abs[2:]}"
    else:
        docker_mount = tb_dir_abs

    # 镜像选择（per Phase 10 FIX6）：优先 AI4S_A2_IMAGE 预装镜像，否则基础镜像
    custom_image = os.environ.get("AI4S_A2_IMAGE", "")
    if custom_image:
        image = custom_image
        template = _DOCKER_RUN_TEMPLATE_PREBUILT
    else:
        image = "verilator/verilator:v5.050"
        template = _DOCKER_RUN_TEMPLATE

    script = template.format(
        tb_dir="/work",
        test_module=test_module,
    )

    # wheelhouse 挂载（离线装依赖）— 向上搜索找到 wheelhouse 目录
    wh_path = None
    p = tb_dir.parent
    for _ in range(5):
        candidate = p / "wheelhouse"
        if candidate.exists():
            wh_path = candidate
            break
        p = p.parent
    wh_volumes = []
    if wh_path:
        wh_abs = str(wh_path.resolve()).replace("\\", "/")
        if wh_abs[1:3] == ":/":
            wh_docker = f"//{wh_abs[0].lower()}{wh_abs[2:]}"
        else:
            wh_docker = wh_abs
        wh_volumes = ["-v", f"{wh_docker}:/work/wheelhouse:ro"]

    cmd = [
        "docker", "run", "--rm",
        "--platform", "linux/amd64",
        "--entrypoint", "bash",
        "-v", f"{docker_mount}:/work",
    ] + wh_volumes + [
        "-w", "/work",
        "-e", f"SEED={seed}",
        image,
        "-c", script,
    ]

    env = os.environ.copy()
    env["MSYS_NO_PATHCONV"] = "1"  # 防 Git Bash 路径转换

    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=SIM_TIMEOUT_SECONDS, env=env,
        )
        # 判断成功：MAKE_EXIT=0（仿真 make 成功）
        passed = ("MAKE_EXIT=0" in result.stdout)
        return SimResult(
            passed=passed,
            exit_code=result.returncode,
            stdout=result.stdout,
            stderr=result.stderr,
        )
    except subprocess.TimeoutExpired:
        return SimResult(passed=False, exit_code=-1, stdout="",
                         stderr="Docker sim timeout (1200s)")
    except FileNotFoundError:
        return SimResult(passed=False, exit_code=-1, stdout="",
                         stderr="docker command not found")


def _run_local(tb_dir, test_module, seed):
    """本机直接 make（假设本机已装 verilator + cocotb）"""
    cmd = ["make", "SIM=verilator", f"MODULE={test_module}"]
    env = os.environ.copy()
    env["SEED"] = str(seed)
    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=SIM_TIMEOUT_SECONDS,
            cwd=str(tb_dir), env=env,
        )
        passed = result.returncode == 0
        return SimResult(
            passed=passed, exit_code=result.returncode,
            stdout=result.stdout, stderr=result.stderr,
        )
    except subprocess.TimeoutExpired:
        return SimResult(passed=False, exit_code=-1, stdout="", stderr="local sim timeout (1200s)")
