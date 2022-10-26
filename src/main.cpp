/*=========================
         PlatySim2
  Written by Jordan Doose
       Happy flying!
=========================*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "vehicle/Rocket.hpp"

struct DataPoint
{
    double time;

    Vector3 pos;
    Vector3 vel;
    Vector3 accel;

    Quaternion ori;
    Vector3 angVel;
    Vector3 angAccel;
    
    double aoa;
    Vector3 drag;
    Vector3 lift;
};

double rocketDragCoefficient(double alpha)
{
    return 0.3;
}

double rocketLiftCoefficient(double alpha)
{
    return sin(alpha * 2);
}

DataPoint makeDataPoint(double time, AerodynamicObject obj)
{
    DataPoint ret;

    ret.time = time;

    ret.pos = obj.position;
    ret.vel = obj.velocity;
    ret.accel = obj.acceleration;

    ret.ori = obj.orientation;
    ret.angVel = obj.angularVelocity;
    ret.angAccel = obj.angularAcceleration;

    ret.aoa = obj.alpha;
    ret.drag = obj.dragForce;
    ret.lift = obj.liftForce;

    return ret;
}

void writeDataPoint(std::ofstream& os, DataPoint point)
{
    os << point.time << ",";
    os << point.pos.x << ",";
    os << point.pos.y << ",";
    os << point.pos.z << ",";
    os << point.vel.x << ",";
    os << point.vel.y << ",";
    os << point.vel.z << ",";
    os << point.accel.x << ",";
    os << point.accel.y << ",";
    os << point.accel.z << ",";
    os << point.ori.w << ",";
    os << point.ori.x << ",";
    os << point.ori.y << ",";
    os << point.ori.z << ",";
    os << point.angVel.x << ",";
    os << point.angVel.y << ",";
    os << point.angVel.z << ",";
    os << point.angAccel.x << ",";
    os << point.angAccel.y << ",";
    os << point.angAccel.z << ",";
    os << point.aoa << ",";
    os << point.drag.x << ",";
    os << point.drag.y << ",";
    os << point.drag.z << ",";
    os << point.lift.x << ",";
    os << point.lift.y << ",";
    os << point.lift.z << ",";
    os << std::endl;
}

int main()
{
    // simulation definition
    Rocket sampleRocket;

    sampleRocket.mass = 0.6;
    sampleRocket.centerOfMass = Vector3(0, 0, 0.2);
    sampleRocket.centerOfPressure = Vector3(0, 0, -0.6);
    sampleRocket.moi = Vector3(0.2, 0.2, 0.05);

    sampleRocket.motorPosition = Vector3(0, 0, -0.8);
    sampleRocket.motorNormal = Vector3::unitZ();

    sampleRocket.dragCoefficient = &rocketDragCoefficient;
    sampleRocket.liftCoefficient = &rocketLiftCoefficient;
    sampleRocket.dragArea = 0.06 * 0.06 * M_PI;
    sampleRocket.liftArea = sampleRocket.dragArea;

    sampleRocket.dampCoefficient = 0.005;

    sampleRocket.thrustCurve = {{0.0, 0.0}, {0.1, 50.0}, {0.5, 45.0}, {0.6, 15.0}, {2.0, 5.0}, {2.1, 0.0}};

    sampleRocket.globalWind = Vector3(3, 5, 0);
    sampleRocket.gravity = true;

    // simulation parameters
    double timestep = 0.01;
    int simSteps = 3000;
    int runSteps = 0;

    DataPoint simulation[simSteps + 1];

    std::cout << "Running simulation..." << std::endl;

    bool inFlight = false;

    for(int step = 0; step < simSteps; step++)
    {
        double totalElapsedTime = step * timestep;

        simulation[step] = makeDataPoint(totalElapsedTime, sampleRocket);

        if(!sampleRocket.launched && totalElapsedTime < 1.0)
        {
            sampleRocket.launch();
        }

        if(!inFlight && sampleRocket.position.z > 5)
        {
            inFlight = true;
        }

        if(inFlight && sampleRocket.position.z < 0)
        {
            break; // simulation complete
        }

        sampleRocket.update(timestep);

        std::cout << sampleRocket.flightTime << std::endl;

        runSteps++;
    }

    simulation[runSteps] = makeDataPoint(runSteps * timestep, sampleRocket);

    // output file
    std::cout << "Writing output..." << std::endl;

    std::ofstream output;
    output.open("sim.csv");

    output << "time,";
    output << "pos_x,pos_y,pos_z,";
    output << "vel_x,vel_y,vel_z,";
    output << "acc_x,acc_y,acc_z,";
    output << "ori_w,ori_x,ori_y,ori_z,";
    output << "angvel_x,angvel_y,angvel_z,";
    output << "angacc_x,angacc_y,angacc_z,";
    output << "alpha,";
    output << "drag_x,drag_y,drag_z,";
    output << "lift_x,lift_y,lift_z" << std::endl;

    for(int i = 0; i < runSteps + 1; i++)
    {
        writeDataPoint(output, simulation[i]);
    }

    output.close();

    std::cout << "Done!" << std::endl;

    return 0;
}