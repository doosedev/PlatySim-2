#include "ThrustCurve.hpp"

#include <cmath>

double ThrustCurve::getThrustAt(double time)
{
    // check conditions
    if(time <= 0.0 || time >= burnTime)
    {
        return 0.0;
    }

    // get previous timestep
    int prevIndex = numPoints - 2;
    double prevTime = timePoints[prevIndex];

    while(prevTime > time)
    {
        prevIndex--;
        prevTime = timePoints[prevIndex];
    }

    double prevThrust = thrustPoints[prevIndex];

    // get next timestep
    int nextIndex = prevIndex + 1;
    double nextTime = timePoints[nextIndex];
    double nextThrust = thrustPoints[nextIndex];

    // interpolate
    double interpolation = (time - prevTime) / (nextTime - prevTime);
    return std::lerp(prevThrust, nextThrust, interpolation);
}