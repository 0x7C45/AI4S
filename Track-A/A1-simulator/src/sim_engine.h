#ifndef A1_SIMULATOR_SIM_ENGINE_H
#define A1_SIMULATOR_SIM_ENGINE_H

#include <string>
#include <vector>

struct ModuleDef;

class SimulationEngine {
public:
    int compile(const std::string &filelist, const std::string &top,
                const std::string &output);
    int run(const std::string &simPath, unsigned int threads);

    /* In-memory result from compile(), used when compile+run in same process */
    std::vector<ModuleDef *> compiledModules;
};

#endif
