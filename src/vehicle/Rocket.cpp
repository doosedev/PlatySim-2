#include "Rocket.hpp"

void Rocket::launch()
{
    launched = true;
}

void Rocket::update(double dt)
{
    if(launched)
    {
        flightTime += dt;

        double currentThrust = thrustCurve.getThrustAt(flightTime);

        AerodynamicObject::applyForceLocal(motorNormal * currentThrust, motorPosition);
        AerodynamicObject::update(dt);
    }
}