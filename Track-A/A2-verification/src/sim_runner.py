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


# Docker 命令模板（per D-06：镜像无 pip，需 bootstrap）
# per SMOKE_TEST_REPORT §2：MSYS_NO_PATHCONV 防 Git Bash 路径转换
_DOCKER_RUN_TEMPLATE = """\
set -e
echo "=== [1/3] bootstrap pip (镜像无 pip) ==="
apt-get update -qq >/dev/null 2>&1 && apt-get install -y -qq python3-pip >/dev/null 2>&1
python3 -m pip install --break-system-packages --quiet cocotb==2.0.1 cocotbext-axi==0.1.28 2>&1 | tail -1
echo "=== [2/3] 确认工具链 ==="
python3 -c "import cocotb, cocotbext.axi; print('cocotb', cocotb.__version__)"
echo "=== [3/3] 仿真 (SIM=verilator) ==="
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

    script = _DOCKER_RUN_TEMPLATE.format(
        tb_dir="/work",
        test_module=test_module,
    )

    cmd = [
        "docker", "run", "--rm",
        "--platform", "linux/amd64",
        "--entrypoint", "bash",
        "-v", f"{docker_mount}:/work",
        "-w", "/work",
        "-e", f"SEED={seed}",
        "verilator/verilator:v5.050",
        "-c", script,
    ]

    env = os.environ.copy()
    env["MSYS_NO_PATHCONV"] = "1"  # 防 Git Bash 路径转换

    try:
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=1200, env=env,
        )
        # 判断成功：make exit 0 且无 fatal error
        passed = (result.returncode == 0 and
                  "Error" not in result.stdout[-500:] and
                  "MAKE_EXIT=0" in result.stdout.replace(" ", ""))
        return SimResult(
            passed=passed,
            exit_code=result.returncode,
            stdout=result.stdout,
            stderr=result.stderr,
        )
    except subprocess.TimeoutExpired:
        return SimResult(passed=False, exit_code=-1, stdout="",
                         stderr="Docker sim timeout (600s)")
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
            cmd, capture_output=True, text=True, timeout=600,
            cwd=str(tb_dir), env=env,
        )
        passed = result.returncode == 0
        return SimResult(
            passed=passed, exit_code=result.returncode,
            stdout=result.stdout, stderr=result.stderr,
        )
    except subprocess.TimeoutExpired:
        return SimResult(passed=False, exit_code=-1, stdout="", stderr="local sim timeout")
