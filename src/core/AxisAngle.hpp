#pragma once

#include "Vector3.hpp"

struct AxisAngle
{
    Vector3 axis;
    double angle;

    AxisAngle() : axis(0, 0, 0), angle(0) {}
    AxisAngle(double x, double y, double z, double _angle) : axis(x, y, z), angle(_angle) {};
    AxisAngle(const Vector3& _axis, double _angle) : axis(_axis), angle(_angle) {};
};