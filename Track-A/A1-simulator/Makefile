FILELIST ?= filelist.txt
TOP ?= tb
THREADS ?= 4
SIM_EXE ?= sim.out

CXX ?= g++
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra -pedantic

SRC_DIR := src
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

build: simulator

simulator: $(SIMULATOR_SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SIMULATOR_SOURCES) -lfl

$(SRC_DIR)/lexer.yy.c: $(SRC_DIR)/lexer.l $(SRC_DIR)/parser.tab.h
	flex -o $@ $<

$(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	bison -d -o $(SRC_DIR)/parser.tab.c $<

compile_sim: simulator
	./simulator --compile -f "$(FILELIST)" --top "$(TOP)" -o "$(SIM_EXE)"

run:
	./$(SIM_EXE)

parallel_run:
	./$(SIM_EXE) --threads "$(THREADS)"

clean:
	rm -f simulator $(SIM_EXE) $(SRC_DIR)/lexer.yy.c $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h tb/output.mem
