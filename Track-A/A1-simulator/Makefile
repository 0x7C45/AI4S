FILELIST ?= filelist.txt
TOP ?= tb
THREADS ?= 4
SIM_EXE ?= sim.out

# Directory containing this Makefile (the A1-simulator source tree)
SIM_DIR := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
SIMULATOR := $(SIM_DIR)/simulator

CXX ?= g++
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra -pedantic

SRC_DIR := $(SIM_DIR)/src

SIMULATOR_SOURCES := \
	$(SRC_DIR)/lexer.yy.c \
	$(SRC_DIR)/parser.tab.c \
	$(SRC_DIR)/ast.cpp \
	$(SRC_DIR)/eval_expr.cpp \
	$(SRC_DIR)/sim_engine.cpp \
	$(SRC_DIR)/system_funcs.cpp \
	$(SRC_DIR)/sim_data.cpp \
	$(SRC_DIR)/main.cpp

.PHONY: build compile_sim run parallel_run clean

build: $(SIMULATOR)

$(SIMULATOR): $(SIMULATOR_SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SIMULATOR_SOURCES) -lfl

$(SRC_DIR)/lexer.yy.c: $(SRC_DIR)/lexer.l $(SRC_DIR)/parser.tab.h
	flex -o $@ $<

$(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	bison -d -o $(SRC_DIR)/parser.tab.c $<

# compile_sim: parse RTL, produce sim.out binary
compile_sim: $(SIMULATOR)
	"$(SIMULATOR)" --compile -f "$(FILELIST)" --top "$(TOP)" -o "$(SIM_EXE)"

# run: compile and run in-memory
run: $(SIMULATOR)
	"$(SIMULATOR)" --run -f "$(FILELIST)" --top "$(TOP)"

# parallel_run: compile and run with multi-threading
parallel_run: $(SIMULATOR)
	"$(SIMULATOR)" --run -f "$(FILELIST)" --top "$(TOP)" --threads "$(THREADS)"

clean:
	rm -f $(SIMULATOR) $(SIM_EXE) $(SRC_DIR)/lexer.yy.c $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h
