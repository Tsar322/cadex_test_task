#include <curves/curves.h>
#include <numbers>
#include <stdexcept>
#include <cmath>

namespace curves {


    std::ostream& operator<<(std::ostream& out, const Point3D& point) {
        return out << '(' << point.x << ", " << point.y << ", " << point.z << ')';
    }
    std::ostream& operator<<(std::ostream& out, const Vector3D& vector) {
        return out << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')';
    }

    Circle::Circle(double radius)
        : _radius(radius)
    {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

    Point3D Circle::point3D(double t) const {
        return Point3D(
            _radius * std::cos(t),
            _radius * std::sin(t),
            0
        );
    }

    Vector3D Circle::firstDerivative(double t) const {
        return Vector3D(
            -_radius * std::sin(t),
            _radius * std::cos(t),
            0
        );
    }

    Ellipse::Ellipse(double radiusX, double radiusY)
        : _radiusX(radiusX), _radiusY(radiusY)
    {
        if (radiusX <= 0 || radiusY <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

    Point3D Ellipse::point3D(double t) const {
        const double& a = _radiusX;
        const double& b = _radiusY;

        double x = a * std::cos(t);
        double y = b * std::sin(t);
        return Point3D(x, y, 0);
    }

    Vector3D Ellipse::firstDerivative(double t) const {
        const double& a = _radiusX;
        const double& b = _radiusY;

        double x = -a * std::sin(t);
        double y = b * std::cos(t);
        return Vector3D(x, y, 0);
    }

    Helix::Helix(double radius, double step)
        : _radius(radius), _step(step)
    {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
        if (step == 0) {
            throw std::invalid_argument("Helix step must not be zero");
        }
    }

    Point3D Helix::point3D(double t) const {
        return Point3D(
            _radius * std::cos(t),
            _radius * std::sin(t),
            _step * (t / std::numbers::pi * 2)
        );
    }

    Vector3D Helix::firstDerivative(double t) const {
        return Vector3D(
            -_radius * std::sin(t),
            _radius * std::cos(t),
            _step / (2 * std::numbers::pi)
        );
    }
}