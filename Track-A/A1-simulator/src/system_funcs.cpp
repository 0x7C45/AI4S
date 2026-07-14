#include "system_funcs.h"

#include <iostream>

void simulatorWarning(const std::string &message) {
    std::cerr << "simulator: " << message << '\n';
}
