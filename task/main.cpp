#include <curves/curves.h>
#include <numbers>
#include <omp.h>
#include "CurveGenerator.h"
#include "CurveLogger.h"
#include "CLIParams.h"

int main(int argc, char* argv[]) {

    GeneratorParams params = parseArguments(argc, argv);

    std::vector<std::shared_ptr<curves::Curve>> curves;

    for (int i = 0; i < params.numCurves; ++i) {
        curves.push_back(
            std::move(CurveGenerator::createRandomCurve(
                params.minRadius, params.maxRadius,
                params.minStep, params.maxStep, params.allowNegativeStep,
                params.minEllipseRatio, params.maxEllipseRatio
            ))
        );
    }

    std::cout << "Generated curves and their points, first derivatives at t = PI/4:" << std::endl;
    double t = std::numbers::pi / 4;
    printCurvesTable(curves, t);
    std::cout << std::endl;

    std::vector<std::shared_ptr<curves::Circle>> circles;
    for (const auto& curve : curves) {
        if (std::shared_ptr<curves::Circle> circle = std::dynamic_pointer_cast<curves::Circle>(curve)) {
            circles.push_back(circle);
        }
    }

    std::cout << "Circles before sorting:" << std::endl;
    for (const auto& circle : circles) {
        std::cout << "Radius = " << circle->radius() << std::endl;
    }
    std::cout << std::endl;

    std::sort(circles.begin(), circles.end(), [](const std::shared_ptr<curves::Circle>& a, const std::shared_ptr<curves::Circle>& b) {
        return a->radius() < b->radius();
        });

    std::cout << "Circles after sorting:" << std::endl;
    for (const auto& circle : circles) {
        std::cout << "Radius = " << circle->radius() << std::endl;
    }
    std::cout << std::endl;

    double circlesRadiiTotalSum = 0;
    #pragma omp parallel for reduction(+:circlesRadiiTotalSum)
    for (int i = 0; i < circles.size(); ++i) {
        circlesRadiiTotalSum += circles[i]->radius();
    }
    std::cout << "Total sum of circles' radii (parallel) = " << circlesRadiiTotalSum << std::endl;



    return 0;
}