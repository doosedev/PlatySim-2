#include "AerodynamicObject.hpp"

void AerodynamicObject::update(double dt)
{
    Vector3 relativeWind = globalWind - velocity;

    alpha = relativeWind.angle(orientation.rotate(-Vector3::unitZ()));

    dragForce = relativeWind.normalized() * dragCoefficient(alpha) * dragArea * airDensity * relativeWind.norm() * relativeWind.norm() * 0.5;
    
    Vector3 alphaAxis = orientation.rotate(Vector3::unitZ()).cross(relativeWind);
    Vector3 liftNorm = relativeWind.cross(alphaAxis).normalized();

    liftForce = liftNorm.normalized() * liftCoefficient(alpha) * liftArea * airDensity * relativeWind.norm() * relativeWind.norm() * 0.5;

    PhysicsObject::applyGlobalForceLocal(dragForce, centerOfPressure);
    PhysicsObject::applyGlobalForceLocal(liftForce, centerOfPressure);

    // hacky solution ik im sorry
    PhysicsObject::applyTorque(-PhysicsObject::angularVelocity * dampCoefficient);

    PhysicsObject::update(dt);
}
