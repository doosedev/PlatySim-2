#pragma once

#include "PhysicsObject.hpp"

class AerodynamicObject : public PhysicsObject
{
public:
    double (*dragCoefficient)(double);
    double (*liftCoefficient)(double);
    double dampCoefficient;

    double alpha;

    double dragArea;
    double liftArea;

    Vector3 centerOfPressure;

    Vector3 globalWind;
    double airDensity;

    Vector3 dragForce;
    Vector3 liftForce;

    AerodynamicObject() : PhysicsObject(), dampCoefficient(0), airDensity(1.225) {};

    void update(double dt);
};