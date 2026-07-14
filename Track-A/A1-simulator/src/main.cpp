#include "sim_engine.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace {

void printUsage() {
    std::cerr << "usage: simulator --compile -f FILELIST --top TOP -o SIM_EXE\n"
                 "       simulator [--sim PATH] [--threads N]\n"
                 "       simulator --run -f FILELIST --top TOP [--threads N]\n";
}

}  // namespace

int main(int argc, char *argv[]) {
    SimulationEngine engine;

    if (argc > 1 && std::string(argv[1]) == "--compile") {
        const char *filelist = nullptr;
        const char *top = nullptr;
        const char *output = nullptr;

        for (int i = 2; i + 1 < argc; i += 2) {
            const std::string option = argv[i];
            if (option == "-f") {
                filelist = argv[i + 1];
            } else if (option == "--top") {
                top = argv[i + 1];
            } else if (option == "-o") {
                output = argv[i + 1];
            } else {
                printUsage();
                return EXIT_FAILURE;
            }
        }

        if (filelist == nullptr || top == nullptr || output == nullptr) {
            printUsage();
            return EXIT_FAILURE;
        }

        return engine.compile(filelist, top, output);
    }

    if (argc > 1 && std::string(argv[1]) == "--run") {
        const char *filelist = nullptr;
        const char *top = nullptr;
        unsigned int threads = 1;

        for (int i = 2; i + 1 < argc; i += 2) {
            const std::string option = argv[i];
            if (option == "-f") {
                filelist = argv[i + 1];
            } else if (option == "--top") {
                top = argv[i + 1];
            } else if (option == "--threads") {
                try { threads = static_cast<unsigned int>(std::stoul(argv[i + 1])); }
                catch (...) { printUsage(); return EXIT_FAILURE; }
            } else {
                printUsage();
                return EXIT_FAILURE;
            }
        }

        if (filelist == nullptr || top == nullptr) {
            printUsage();
            return EXIT_FAILURE;
        }

        /* compile to in-memory, then run directly */
        int rc = engine.compile(filelist, top, "sim.out");
        if (rc != 0) return rc;
        return engine.run("", threads);
    }

    unsigned int threads = 1;
    std::string simPath;
    if (argc >= 3) {
        for (int i = 1; i + 1 < argc; i += 2) {
            std::string opt = argv[i];
            if (opt == "--threads") {
                try { threads = static_cast<unsigned int>(std::stoul(argv[i + 1])); }
                catch (...) { printUsage(); return EXIT_FAILURE; }
            } else if (opt == "--sim") {
                simPath = argv[i + 1];
            } else {
                printUsage();
                return EXIT_FAILURE;
            }
        }
    } else if (argc != 1) {
        printUsage();
        return EXIT_FAILURE;
    }

    return engine.run(simPath, threads);
}
