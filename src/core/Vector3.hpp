#pragma once

#ifndef ARDUINO
#include <iostream>
#endif

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector3() : x(0), y(0), z(0) {};
    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

    static const Vector3 zero();
    static const Vector3 unitX();
    static const Vector3 unitY();
    static const Vector3 unitZ();

    Vector3& operator=(const Vector3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    bool operator==(const Vector3& rhs) const {
        return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
    };
    bool operator!=(const Vector3& rhs) const {
        return ((x != rhs.x) || (y != rhs.y) || (z != rhs.z));
    }

    const Vector3& operator-() const {
        return Vector3(*this) *= -1;
    }

    Vector3& operator*=(const double rhs);
    const Vector3 operator*(const double rhs) const { return Vector3(*this) *= rhs; }
    Vector3& operator/=(const double rhs);
    const Vector3 operator/(const double rhs) const { return Vector3(*this) /= rhs; }
    
    Vector3& operator+=(const Vector3& rhs);
    const Vector3 operator+(const Vector3& rhs) const { return Vector3(*this) += rhs; }
    Vector3& operator-=(const Vector3& rhs);
    const Vector3 operator-(const Vector3& rhs) const { return Vector3(*this) -= rhs; }
    
    double norm() const;
    Vector3& normalize();
    const Vector3 normalized() const { return Vector3(*this).normalize(); }

    const double dot(const Vector3& rhs) const;
    const Vector3 cross(const Vector3& rhs) const;
    const double angle(const Vector3& rhs) const;

#ifndef ARDUINO
    friend std::ostream& operator<<(std::ostream& os, const Vector3& obj);
#endif
};