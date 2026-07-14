#ifndef A1_SIMULATOR_SIM_DATA_H
#define A1_SIMULATOR_SIM_DATA_H

#include "ast.h"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

struct SignalDef {
    std::string name;
    int width = 1;
    uint64_t init_value = 0;
    bool is_reg = false;
    bool is_signed = false;
    std::string port_direction;
    uint32_t port_order = 0;
    bool is_port = false;
    bool has_initial_value = false;
    std::string init_expression;
    std::string source_file;
    uint32_t source_line = 0;
};

struct ParameterDef {
    std::string name;
    uint64_t value = 0;
    bool overridden = false;
    std::string source_file;
    uint32_t source_line = 0;
};

struct MemoryDef {
    std::string name;
    int address_msb = 0;
    int address_lsb = 0;
    int element_width = 1;
    bool is_signed = false;
    std::string source_file;
    uint32_t source_line = 0;
};

struct SourceDependency {
    std::string including_file;
    std::string included_file;
    uint32_t include_line = 0;
};

struct ModuleDef {
    std::string name;
    std::map<std::string, uint64_t> params;
    std::vector<ParameterDef> parameter_decls;
    std::vector<SignalDef> signals;
    std::vector<MemoryDef> memories;
    std::vector<SourceDependency> dependencies;
    std::string source_file;
    uint32_t source_line = 0;
    std::vector<ASTNode *> items;
};

bool writeModuleDefs(const std::string &path, const std::vector<ModuleDef *> &modules);
bool readModuleDefs(const std::string &path, std::vector<ModuleDef *> &modules);

#endif
