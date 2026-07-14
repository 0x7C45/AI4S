# Auto-generated Makefile — win-ZCode A2 验证环境自动生成
# DUT: axis_fifo_adapter
TOPLEVEL_LANG = verilog

# per D-05: 默认 verilator（非 vcs）
SIM ?= verilator
WAVES ?= 0

COCOTB_HDL_TIMEUNIT = 1ns
COCOTB_HDL_TIMEPRECISION = 1ps

TOPLEVEL = axis_fifo_adapter
MODULE = generated_test

# per D-03: -Wno-fatal 必须（Verilator lint 致命，RTL 有 width warning）
COMPILE_ARGS = -Wno-fatal --coverage-line --coverage-toggle

CASE_ROOT = $(abspath .)

VERILOG_SOURCES += $(CASE_ROOT)/rtl/case2.v
VERILOG_SOURCES += $(CASE_ROOT)/rtl/case2_1.v
VERILOG_SOURCES += $(CASE_ROOT)/rtl/case2_2.v

include $(shell cocotb-config --makefiles)/Makefile.sim
