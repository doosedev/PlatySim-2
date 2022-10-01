#pragma once

#ifndef ARDUINO
#include <iostream>
#endif

#include "EulerAngles.hpp"
#include "AxisAngle.hpp"

class Quaternion
{
public:
    double w;
    double x;
    double y;
    double z;

    Quaternion() : w(1), x(0), y(0), z(0) {};
    Quaternion(double _w, double _x, double _y, double _z) : w(_w), x(_x), y(_y), z(_z) {};

    static const Quaternion zero();
    static const Quaternion unitW(); // Same as zero()
    static const Quaternion unitX();
    static const Quaternion unitY();
    static const Quaternion unitZ();

    static const Quaternion fromVector(const Vector3& vec);
    static const Quaternion fromEuler(const EulerAngles& eul);
    static const Quaternion fromAxisAngle(const Vector3& axis, const double angle);
    static const Quaternion fromAxisAngle(const AxisAngle& aa);
    static const Quaternion fromRotationVector(const Vector3& rot);

    const Vector3 toVector() const;
    const EulerAngles toEuler() const;
    const AxisAngle toAxisAngle() const;
    const Vector3 toRotationVector() const;

    Quaternion& operator=(const Quaternion& rhs)
    {
        w = rhs.w;
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    Quaternion& operator*=(const double rhs);
    const Quaternion operator*(const double rhs) const { return Quaternion(*this) *= rhs; }
    Quaternion& operator/=(const double rhs);
    const Quaternion operator/(const double rhs) const { return Quaternion(*this) /= rhs; }
    
    Quaternion& operator+=(const Quaternion& rhs);
    const Quaternion operator+(const Quaternion& rhs) const { return Quaternion(*this) += rhs; }
    Quaternion& operator-=(const Quaternion& rhs);
    const Quaternion operator-(const Quaternion& rhs) const { return Quaternion(*this) -= rhs; }
    Quaternion& operator*=(const Quaternion& rhs);
    const Quaternion operator*(const Quaternion& rhs) const { return Quaternion(*this) *= rhs; }
    
    double norm() const;
    Quaternion& normalize();
    const Quaternion normalized() const { return Quaternion(*this).normalize(); }

    const Quaternion conj() const;

    const Vector3 rotate(const Vector3& rhs) const;

#ifndef ARDUINO
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& obj);
#endif
};