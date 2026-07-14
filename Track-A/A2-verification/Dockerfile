# A2 验证环境 Docker 镜像 — 预装 cocotb + verilator（离线评测机可跑）
# per Phase 10 FIX6: verilator/verilator:v5.050 镜像无 pip/libpython，断网评测
# 不可靠（apt 镜像 502）。本 Dockerfile 一次性构建预装镜像，评测机只需
# docker load 即可，零运行时网络依赖。
#
# 构建（开发机有网络时）:
#   docker build --platform linux/amd64 -t ai4s-a2:verilator-cocotb -f Dockerfile .
#   docker save ai4s-a2:verilator-cocotb | gzip > ai4s-a2-image.tar.gz
#
# 评测机加载（离线）:
#   docker load < ai4s-a2-image.tar.gz
#   export AI4S_A2_IMAGE=ai4s-a2:verilator-cocotb
#   ./run.sh --rtl <dir> --top <module> --out <dir> --seed 20260630 --num-seq 5000
FROM --platform=linux/amd64 verilator/verilator:v5.050

# 换清华镜像（官方 archive.ubuntu.com 在评测期 502/EOF 频发）
RUN sed -i 's|http://archive.ubuntu.com/ubuntu|https://mirrors.tuna.tsinghua.edu.cn/ubuntu|g; s|http://security.ubuntu.com/ubuntu|https://mirrors.tuna.tsinghua.edu.cn/ubuntu|g' /etc/apt/sources.list.d/ubuntu.sources

# 装系统依赖：libpython3.12（cocotb find_libpython 需要）+ pip
RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends libpython3.12 python3-pip && \
    rm -rf /var/lib/apt/lists/*

# 预装 Python 依赖（与 requirements.txt 钉死版本对齐）
# --break-system-packages: Ubuntu 24.04 PEP 668 externally-managed 标记
RUN python3 -m pip install --no-cache-dir --break-system-packages \
        cocotb==2.0.1 \
        cocotb-test==0.2.6 \
        cocotbext-axi==0.1.28 \
        cocotb-bus==0.3.0 \
        scapy==2.7.0 \
        Jinja2==3.1.6 \
        PyVerilog==1.3.0 \
        find_libpython

# 验证：工具链可用
RUN python3 -c "import cocotb, cocotbext.axi, cocotb_bus, pygpi; print('cocotb', cocotb.__version__, 'pygpi OK')" && \
    verilator --version | head -1 && \
    python3 -c "import find_libpython; loc=find_libpython.find_libpython(); assert loc, 'libpython not found'; print('libpython at', loc)"
