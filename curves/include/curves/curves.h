#pragma once

#include <iostream>

#ifdef _WIN32
#ifdef CURVES_BUILD_DLL
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif
#else
#define CURVES_API
#endif

namespace curves {

    class CURVES_API Point3D {
    public:
        Point3D(double _x, double _y, double _z = 0)
            : x(_x), y(_y), z(_z)
        {
        }

        double x{ 0 };
        double y{ 0 };
        double z{ 0 };
    };

    class CURVES_API Vector3D {
    public:
        Vector3D(double _x, double _y, double _z = 0)
            : x(_x), y(_y), z(_z)
        {
        }

        double x{ 0 };
        double y{ 0 };
        double z{ 0 };
    };

    // console output
    std::ostream& operator<<(std::ostream& out, const Point3D& point);
    std::ostream& operator<<(std::ostream& out, const Vector3D& vector);

    class CURVES_API Curve {
    public:
        virtual Vector3D firstDerivative(double t) const = 0;
        virtual Point3D point3D(double t) const = 0;

        virtual ~Curve() = default;
    };

    class CURVES_API Circle : public Curve {
    public:
        explicit Circle(double radius);
        Vector3D firstDerivative(double t = 0) const override;
        Point3D point3D(double t = 0) const override;

        double radius() const { return _radius; }

    private:
        double _radius{ 1 };
    };

    class CURVES_API Ellipse : public Curve {
    public:
        Ellipse(double radiusX, double radiusY);

        Vector3D firstDerivative(double t = 0) const override;
        Point3D point3D(double t = 0) const override;

        double radiusX() const { return _radiusX; }
        double radiusY() const { return _radiusY; }

    private:
        double _radiusX{ 1 };
        double _radiusY{ 1 };
    };

    class CURVES_API Helix : public Curve {
    public:
        Helix(double radius, double step);

        Vector3D firstDerivative(double t = 0) const override;
        Point3D point3D(double t = 0) const override;

        double radius() const { return _radius; }
        double step() const { return _step; }
    private:
        double _radius{ 1 };
        double _step{ 1 };
    };

}