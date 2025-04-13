#pragma once

#include <memory>
#include <random>
#include <ctime>
#include <curves/curves.h>

namespace CurveGenerator {

    double randomDouble(double min, double max) {
        static std::mt19937 generator(static_cast<unsigned>(time(0)));
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }
    int randomInt(int min, int max) {
        static std::mt19937 generator(static_cast<unsigned>(time(0)));
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    std::unique_ptr<curves::Curve> createRandomCurve(
        double minRadius, double maxRadius,
        double minStep, double maxStep, bool allowNegativeStep,
        double minEllipseRatio, double maxEllipseRatio
    ) {
        int type = randomInt(0, 2); // 0 = Circle, 1 = Ellipse, 2 = Helix

        switch (type) {
        case 0: // Circle
            return std::make_unique<curves::Circle>(randomDouble(minRadius, maxRadius));
        case 1: { // Ellipse
                double radiusX = randomDouble(minRadius, maxRadius);
                double ratio = randomDouble(minEllipseRatio, maxEllipseRatio);
                double radiusY = radiusX * ratio;
                return std::make_unique<curves::Ellipse>(radiusX, radiusY);
            }
        case 2: // Helix
        {
            double step;
            if (allowNegativeStep) {
                if (randomDouble(0, 1) < 0.5) {
                    step = randomDouble(minStep, maxStep);
                }
                else {
                    step = randomDouble(-maxStep, -minStep);
                }
            }
            else {
                step = randomDouble(minStep, maxStep);
            }
            return std::make_unique<curves::Helix>(
                randomDouble(minRadius, maxRadius),
                step
            );
        }
        default:
            return nullptr;
        }
    }

}