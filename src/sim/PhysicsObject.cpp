#include "PhysicsObject.hpp"

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <cmath>
#endif

constexpr double EARTH_G = -9.80665;

void PhysicsObject::update(double dt)
{
    acceleration = stepForce / mass;   

    if(gravity)
    {
        acceleration += Vector3(0, 0, EARTH_G);
    }
    
    velocity += acceleration * dt;
    position += velocity * dt;

    angularAcceleration = Vector3(stepTorque.x / moi.x,
                                  stepTorque.y / moi.y,
                                  stepTorque.z / moi.z);
    angularVelocity += angularAcceleration * dt;
    orientation *= Quaternion::fromRotationVector(angularVelocity * dt);
    
    stepForce = Vector3::zero();
    stepTorque = Vector3::zero();
}

void PhysicsObject::applyForceCoM(Vector3 force)
{
    stepForce += force;
}

void PhysicsObject::applyTorque(Vector3 torque)
{
    stepTorque += torque;
}

void PhysicsObject::applyForceCoMLocal(Vector3 force)
{
    Vector3 inertialForce = orientation.rotate(force);
    applyForceCoM(inertialForce);
}

void PhysicsObject::applyTorqueLocal(Vector3 torque)
{
    Vector3 inertialTorque = orientation.rotate(torque);
    applyTorque(inertialTorque);
}

void PhysicsObject::applyForce(Vector3 force, Vector3 dis)
{
    Vector3 torque = (dis - centerOfMass).cross(force);
    applyForceCoM(force);
    applyTorque(torque);
}

void PhysicsObject::applyForceLocal(Vector3 force, Vector3 dis)
{
    Vector3 inertialForce = orientation.rotate(force);
    Vector3 inertialDis = orientation.rotate((dis - centerOfMass));
    applyForce(inertialForce, inertialDis);
}

void PhysicsObject::applyGlobalForceLocal(Vector3 force, Vector3 dis)
{
    Vector3 inertialDis = orientation.rotate((dis - centerOfMass));
    applyForce(force, inertialDis);
}