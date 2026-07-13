#ifndef A1_SIMULATOR_SIM_DATA_H
#define A1_SIMULATOR_SIM_DATA_H

#include "ast.h"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

struct SignalDef {
    std::string name;
    int width;
    uint64_t init_value;
    bool is_reg;
    bool is_signed;
};

struct ModuleDef {
    std::string name;
    std::map<std::string, uint64_t> params;
    std::vector<SignalDef> signals;
    std::vector<ASTNode *> items;
};

bool writeModuleDefs(const std::string &path, const std::vector<ModuleDef *> &modules);
bool readModuleDefs(const std::string &path, std::vector<ModuleDef *> &modules);

#endif
