#include "Vector3.hpp"

#ifdef ARDUINO
#include "Arduino.h"
#else
#include <cmath>
#endif

const Vector3 Vector3::zero()
{
    Vector3 ret(0., 0., 0.);
    return ret;
}

const Vector3 Vector3::unitX()
{
    Vector3 ret(1., 0., 0.);
    return ret;
}

const Vector3 Vector3::unitY()
{
    Vector3 ret(0., 1., 0.);
    return ret;
}

const Vector3 Vector3::unitZ()
{
    Vector3 ret(0., 0., 1.);
    return ret;
}

Vector3& Vector3::operator*=(const double rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3& Vector3::operator/=(const double rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

double Vector3::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::normalize()
{
    double mag = norm();

    if(mag == 0)
    {
        return *this;
    }

    x /= mag;
    y /= mag;
    z /= mag;
    return *this;
}

const double Vector3::dot(const Vector3& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

const Vector3 Vector3::cross(const Vector3& rhs) const
{
    return Vector3(y * rhs.z - z * rhs.y,
                   z * rhs.x - x * rhs.z,
                   x * rhs.y - y * rhs.x);
}

const double Vector3::angle(const Vector3& rhs) const
{
    return acos(dot(rhs) / (norm() * rhs.norm()));
}

#ifndef ARDUINO
std::ostream& operator<<(std::ostream& os, const Vector3& obj)
{
    os << "(" << obj.x << "," << obj.y << "," << obj.z << ")";
    return os;
}
#endif