#include "sim_data.h"

#include <fstream>

bool writeSimData(const std::string &path, const SimulationData &data) {
    std::ofstream output(path);
    if (!output) {
        return false;
    }

    output << data.top_module << '\n' << data.current_time << '\n';
    return static_cast<bool>(output);
}

bool readSimData(const std::string &path, SimulationData *data) {
    if (data == nullptr) {
        return false;
    }

    std::ifstream input(path);
    return static_cast<bool>(input >> data->top_module >> data->current_time);
}
