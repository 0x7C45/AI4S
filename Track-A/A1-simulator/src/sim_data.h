#ifndef A1_SIMULATOR_SIM_DATA_H
#define A1_SIMULATOR_SIM_DATA_H

#include <cstdint>
#include <string>

struct SimulationData {
    std::string top_module;
    std::uint64_t current_time = 0;
};

bool writeSimData(const std::string &path, const SimulationData &data);
bool readSimData(const std::string &path, SimulationData *data);

#endif  // A1_SIMULATOR_SIM_DATA_H
