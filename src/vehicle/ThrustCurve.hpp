#pragma once

#include <initializer_list>

class ThrustCurve
{
public:
    double timePoints[100];
    double thrustPoints[100];
    int numPoints;
    double burnTime;

    ThrustCurve() {};
    ThrustCurve(std::initializer_list<std::initializer_list<double>> list) :  numPoints(list.size())
    {
        int index = 0;
        for(auto point : list)
        {
            auto pointList = point.begin();

            double pointTime = pointList[0];
            double pointThrust = pointList[1];

            timePoints[index] = pointTime;
            thrustPoints[index] = pointThrust;

            index++;
        }

        // set final burn time
        burnTime = timePoints[index - 1];
    }

    double getThrustAt(double time);
};