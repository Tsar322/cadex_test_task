#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

struct GeneratorParams {
    int numCurves = 15;
    double minRadius = 0.5;
    double maxRadius = 10.0;
    double minStep = 0.1;
    double maxStep = 3.0;
    double minEllipseRatio = 0.3;
    double maxEllipseRatio = 2.0;
    bool allowNegativeStep = false;
};

inline void printHelp() {
    std::cout << "Options:\n"
        << "  -n NUM       Number of curves (default: 15)\n"
        << "  --min-r VAL  Minimum radius (default: 0.5)\n"
        << "  --max-r VAL  Maximum radius (default: 10.0)\n"
        << "  --min-s VAL  Minimum step (default: 0.1)\n"
        << "  --max-s VAL  Maximum step (default: 3.0)\n"
        << "  --min-er VAL Minimum ellipse ratio (default: 0.3)\n"
        << "  --max-er VAL Maximum ellipse ratio (default: 2.0)\n"
        << "  -h, --help   Show this help message\n"
        << "  --allow-neg-s  Allow negative helix step values\n"
        << std::endl;
}

inline void validateParams(const GeneratorParams& params) {
    if (params.minRadius <= 0 || params.maxRadius <= 0 || params.minStep <= 0) {
        throw std::invalid_argument("All size parameters must be positive");
    }
    if (params.minRadius > params.maxRadius) {
        throw std::invalid_argument("min radius cannot be greater than max radius");
    }
    if (params.minStep > params.maxStep) {
        throw std::invalid_argument("min step cannot be greater than max step");
    }
    if (params.minEllipseRatio > params.maxEllipseRatio) {
        throw std::invalid_argument("min ellipse ratio cannot be greater than max ratio");
    }
}

inline GeneratorParams parseArguments(int argc, char* argv[]) {
    GeneratorParams params;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp();
            exit(0);
        }
        else if (arg == "-n" && i + 1 < argc) {
            params.numCurves = std::stoi(argv[++i]);
        }
        else if (arg == "--min-r" && i + 1 < argc) {
            params.minRadius = std::stod(argv[++i]);
        }
        else if (arg == "--max-r" && i + 1 < argc) {
            params.maxRadius = std::stod(argv[++i]);
        }
        else if (arg == "--min-s" && i + 1 < argc) {
            params.minStep = std::stod(argv[++i]);
        }
        else if (arg == "--max-s" && i + 1 < argc) {
            params.maxStep = std::stod(argv[++i]);
        }
        else if (arg == "--min-er" && i + 1 < argc) {
            params.minEllipseRatio = std::stod(argv[++i]);
        }
        else if (arg == "--max-er" && i + 1 < argc) {
            params.maxEllipseRatio = std::stod(argv[++i]);
        }
        else if (arg == "--allow-neg-s") {
            params.allowNegativeStep = true;
        }
        else {
            throw std::invalid_argument("Unknown option: " + arg);
        }
    }

    validateParams(params);
    return params;
}