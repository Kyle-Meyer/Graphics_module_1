#include "geometry/vector3.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(const Point3 &p) : x(p.x), y(p.y), z(p.z) {}

Vector3::Vector3(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}

Vector3::Vector3(const Point3 &from, const Point3 &to) :
    x(to.x - from.x), y(to.y - from.y), z(to.z - from.z)
{
}

Vector3::Vector3(const Vector3 &w) : x(w.x), y(w.y), z(w.z) {}

Vector3 &Vector3::operator=(const Vector3 &w)
{
    x = w.x;
    y = w.y;
    z = w.z;
    return *this;
}

void Vector3::set(float ix, float iy, float iz)
{
    x = ix;
    y = iy;
    z = iz;
}

void Vector3::set(const Point3 &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

void Vector3::set(const Point3 &from, const Point3 &to)
{
    x = to.x - from.x;
    y = to.y - from.y;
    z = to.z - from.z;
}

Vector3 Vector3::operator+(const Vector3 &w) const { return Vector3(x + w.x, y + w.y, z + w.z); }

Vector3 &Vector3::operator+=(const Vector3 &w)
{
    x += w.x;
    y += w.y;
    z += w.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &w) const { return Vector3(x - w.x, y - w.y, z - w.z); }

Vector3 &Vector3::operator-=(const Vector3 &w)
{
    x -= w.x;
    y -= w.y;
    z -= w.z;
    return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 &Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

bool Vector3::operator==(const Vector3 &w) const { return (x == w.x && y == w.y && z == w.z); }

float Vector3::dot(const Vector3 &w) const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector3 Vector3::cross(const Vector3 &w) const
{
    // Student to define - Module 1
    return Vector3();
}

float Vector3::norm() const
{
    // Student to define - Module 1
    return 0.0f;
}

float Vector3::norm_squared() const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector3 &Vector3::normalize()
{
    // Student to define - Module 1
    return *this;
}

float Vector3::component(const Vector3 &w) const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector3 Vector3::projection(const Vector3 &w) const
{
    // Student to define - Module 1
    return Vector3();
}

float Vector3::angle_between(const Vector3 &w) const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
    // Student to define - Module 1
    return Vector3();
}

Vector3 operator*(float s, const Vector3 &v) { return Vector3(v.x * s, v.y * s, v.z * s); }

} // namespace cg
