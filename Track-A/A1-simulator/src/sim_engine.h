#ifndef A1_SIMULATOR_SIM_ENGINE_H
#define A1_SIMULATOR_SIM_ENGINE_H

#include <string>

class SimulationEngine {
public:
    int compile(const std::string &filelist, const std::string &top,
                const std::string &output) const;
    int run(unsigned int threads) const;
};

#endif  // A1_SIMULATOR_SIM_ENGINE_H
