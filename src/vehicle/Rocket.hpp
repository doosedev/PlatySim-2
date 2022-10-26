#include "../sim/AerodynamicObject.hpp"
#include "ThrustCurve.hpp"

class Rocket : public AerodynamicObject
{
public:
    bool launched;

    ThrustCurve thrustCurve;
    double launchedTime;
    double flightTime;

    Vector3 motorPosition;
    Vector3 motorNormal;

    Rocket() : launched(false) {};

    void launch();
    void update(double dt);
};