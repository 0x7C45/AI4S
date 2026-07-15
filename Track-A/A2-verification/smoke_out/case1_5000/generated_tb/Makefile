# Auto-generated Makefile — win-ZCode A2 验证环境自动生成
# DUT: axi_adapter_rd
TOPLEVEL_LANG = verilog

# per D-05: 默认 verilator（非 vcs）
SIM ?= verilator
WAVES ?= 0

COCOTB_HDL_TIMEUNIT = 1ns
COCOTB_HDL_TIMEPRECISION = 1ps

TOPLEVEL = axi_adapter_rd
MODULE = generated_test

# per D-03: -Wno-fatal 必须（Verilator lint 致命，RTL 有 width warning）
COMPILE_ARGS = -Wno-fatal --coverage-line --coverage-toggle

CASE_ROOT = $(abspath .)

VERILOG_SOURCES += $(CASE_ROOT)/rtl/case1.v

include $(shell cocotb-config --makefiles)/Makefile.sim
