#pragma once

struct EulerAngles
{
    double yaw;
    double pitch;
    double roll;

    EulerAngles() : yaw(0), pitch(0), roll(0) {}
    EulerAngles(double _yaw, double _pitch, double _roll) : yaw(_yaw), pitch(_pitch), roll(_roll) {};
};