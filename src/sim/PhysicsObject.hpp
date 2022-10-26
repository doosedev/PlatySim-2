#pragma once

#include "../core/Vector3.hpp"
#include "../core/Quaternion.hpp"

class PhysicsObject
{
public:
    double mass;
    Vector3 centerOfMass;
    
    bool gravity;

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    Vector3 stepForce;

    Quaternion orientation;
    Vector3 angularVelocity;
    Vector3 angularAcceleration;

    Vector3 stepTorque;

    Vector3 moi;

    PhysicsObject() : mass(1), moi(1, 1, 1) {};

    void update(double dt);
    
    void applyForceCoM(Vector3 force);
    void applyTorque(Vector3 torque);

    void applyForceCoMLocal(Vector3 localForce);
    void applyTorqueLocal(Vector3 localTorque);

    void applyForce(Vector3 force, Vector3 dis);
    void applyForceLocal(Vector3 force, Vector3 dis);

    void applyGlobalForceLocal(Vector3 force, Vector3 dis);
};