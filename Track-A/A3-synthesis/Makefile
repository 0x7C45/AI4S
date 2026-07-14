SHELL := /bin/bash

TOOL := bin/synth_tool
RTL ?=
TOP ?=
SDC ?=
LIBERTY ?=
CONFIG ?= config.json
CIRCUIT ?=
POINT ?= 1
OUT_DIR ?= output

.PHONY: build synth clean test

build:
	rm -rf bin
	mkdir -p bin
	cp src/*.py bin/
	cp bin/synth.py "$(TOOL)"
	chmod +x "$(TOOL)"
	test -x "$(TOOL)"

synth:
	test -x "$(TOOL)"
	test -n "$(RTL)"
	test -n "$(TOP)"
	test -n "$(SDC)"
	test -n "$(LIBERTY)"
	test -r "$(CONFIG)"
	test -n "$(CIRCUIT)"
	test "$(POINT)" -ge 1
	mkdir -p "$(OUT_DIR)"
	"$(TOOL)" \
	  --rtl "$(RTL)" \
	  --top "$(TOP)" \
	  --sdc "$(SDC)" \
	  --liberty "$(LIBERTY)" \
	  --config "$(CONFIG)" \
	  --circuit "$(CIRCUIT)" \
	  --point "$(POINT)" \
	  --output "$(OUT_DIR)/netlist.v"
	test -s "$(OUT_DIR)/netlist.v"

test: build
	PYTHONPATH=src python3 -m unittest discover -s tests -v

clean:
	rm -rf bin build output .synth_tool __pycache__ src/__pycache__ tests/__pycache__
