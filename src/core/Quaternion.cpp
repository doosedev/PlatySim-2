#include "Quaternion.hpp"

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <cmath>
#endif

const Quaternion Quaternion::zero()
{
    Quaternion ret(1., 0., 0., 0.);
    return ret;
}

const Quaternion Quaternion::unitW()
{
    Quaternion ret(1., 0., 0., 0.);
    return ret;
}

const Quaternion Quaternion::unitX()
{
    Quaternion ret(0., 1., 0., 0.);
    return ret;
}

const Quaternion Quaternion::unitY()
{
    Quaternion ret(0., 0., 1., 0.);
    return ret;
}

const Quaternion Quaternion::unitZ()
{
    Quaternion ret(0., 0., 0., 1.);
    return ret;
}

const Quaternion Quaternion::fromVector(const Vector3& vec)
{
    Quaternion ret(0., vec.x, vec.y, vec.z);
    return ret;
}

const Quaternion Quaternion::fromEuler(const double yaw, const double pitch, const double roll)
{
    double cy = cos(yaw / 2);
    double cp = cos(pitch / 2);
    double cr = cos(roll / 2);

    double sy = sin(yaw / 2);
    double sp = sin(pitch / 2);
    double sr = sin(roll / 2);

    Quaternion ret((cr * cp * cy) + (sr * sp * sy),
                   (sr * cp * cy) - (cr * sp * sy),
                   (cr * sp * cy) + (sr * cp * sy),
                   (cr * cp * sy) - (sr * sp * cy));
    return ret;
}

const Quaternion Quaternion::fromEuler(const EulerAngles& eul)
{
    return Quaternion::fromEuler(eul.yaw, eul.pitch, eul.roll);
}

const Quaternion Quaternion::fromAxisAngle(const Vector3& axis, const double angle)
{
    if(axis == Vector3::zero() || angle == 0)
    {
        return Quaternion::zero();
    }

    double sa = sin(angle / 2);
    double ca = cos(angle / 2);
    
    Quaternion ret(ca, axis.x * sa, axis.y * sa, axis.z * sa);
    return ret;
}

const Quaternion Quaternion::fromAxisAngle(const AxisAngle& aa)
{
    return Quaternion::fromAxisAngle(aa.axis, aa.angle);
}

const Quaternion Quaternion::fromRotationVector(const Vector3& rot)
{
    if(rot == Vector3::zero())
    {
        return Quaternion::zero();
    }

    return Quaternion::fromAxisAngle(rot.normalized(), rot.norm());
}

const Vector3 Quaternion::toVector() const
{
    Vector3 ret(x, y, z);
    return ret;
}

const EulerAngles Quaternion::toEuler() const
{
    double sinr_cosp = 2 * (w * x + y * z);
    double cosr_cosp = 1 - 2 * (x * x + y * y);

    double roll = atan2(sinr_cosp, cosr_cosp);

    double pitch;
    double sinp = 2 * (w * y - z * x);
    if(abs(sinp) >= 1)
    {
        pitch = copysign(M_PI, sinp);
    }
    else
    {
        pitch = asin(sinp);
    }

    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);

    double yaw = atan2(siny_cosp, cosy_cosp);

    EulerAngles ret(yaw, pitch, roll);
    return ret;
}

const AxisAngle Quaternion::toAxisAngle() const
{
    double angle = acos(w) * 2;

    if(angle == 0)
    {
        AxisAngle ret(Vector3::zero(), 0);
        return ret;
    }

    double sa = sin(angle / 2);

    AxisAngle ret(Vector3(x / sa, y / sa, z / sa), angle);
    return ret;
}

const Vector3 Quaternion::toRotationVector() const
{
    AxisAngle aa = toAxisAngle();
    return aa.axis * aa.angle;
}

Quaternion& Quaternion::operator*=(const double rhs)
{
    w *= rhs;
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Quaternion& Quaternion::operator/=(const double rhs)
{
    w /= rhs;
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& rhs)
{
    w += rhs.w;
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& rhs)
{
    w -= rhs.w;
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
    // the hamilton product
    double newW = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    double newX = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    double newY = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    double newZ = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;

    w = newW;
    x = newX;
    y = newY;
    z = newZ;

    return *this;
}

double Quaternion::norm() const
{
    return sqrt(w * w + x * x + y * y + z * z);
}

Quaternion& Quaternion::normalize()
{
    double mag = norm();
    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
    return *this;
}

const Quaternion Quaternion::conj() const
{
    Quaternion ret(w, -x, -y, -z);
    return ret;
}

const Vector3 Quaternion::rotate(const Vector3& vec) const
{
    // rotate a vector by this quaternion
    Quaternion vecQuat = Quaternion::fromVector(vec);
    Quaternion rotVecQuat = (*this) * vecQuat * conj();

    return rotVecQuat.toVector();
}

#ifndef ARDUINO
std::ostream& operator<<(std::ostream& os, const Quaternion& obj)
{
    os << "(" << obj.w << "," << obj.x << "," << obj.y << "," << obj.z << ")";
    return os;
}
#endif