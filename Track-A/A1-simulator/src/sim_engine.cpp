#include "sim_engine.h"

#include "system_funcs.h"

int SimulationEngine::compile(const std::string &filelist, const std::string &top,
                              const std::string &output) const {
    (void)filelist;
    (void)top;
    (void)output;
    simulatorWarning("compile mode is not implemented yet");
    return 1;
}

int SimulationEngine::run(unsigned int threads) const {
    (void)threads;
    simulatorWarning("run mode is not implemented yet");
    return 1;
}
