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
    return x * w.x + y * w.y + z * w.z;
}

Vector3 Vector3::cross(const Vector3 &w) const
{
    return Vector3(
      y * w.z - z * w.y,
      z * w.x - x * w.z,
      x * w.y - y * w.x
   );
}

float Vector3::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

float Vector3::norm_squared() const
{
    return x * x + y * y + z * z;
}

Vector3 &Vector3::normalize()
{
   float magnitude = norm();
   if (magnitude > 1e-6f) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
    return *this;
}

float Vector3::component(const Vector3 &w) const
{
   float w_magnitude = w.norm();
   if (w_magnitude == 0.0f) 
      return 0.0f;
   return dot(w) / w_magnitude;
}

Vector3 Vector3::projection(const Vector3 &w) const
{
    float w_norm_squared = w.norm_squared();
    if (w_norm_squared == 0.0f) 
      return Vector3();
    float scalar = dot(w) / w_norm_squared;
    return Vector3(w.x * scalar, w.y * scalar, w.z * scalar);
}

float Vector3::angle_between(const Vector3 &w) const
{
    float this_magnitude = norm();
    float w_magnitude = w.norm();
    
    if (this_magnitude == 0.0f || w_magnitude == 0.0f) return 0.0f;
    
    float cos_angle = dot(w) / (this_magnitude * w_magnitude);
    // Clamp to handle floating point errors
    cos_angle = fmax(-1.0f, fmin(1.0f, cos_angle));
    
    return acos(cos_angle);
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
    Vector3 n = normal;
    float n_magnitude = n.norm();
    if (n_magnitude != 0.0f) {
        n.x /= n_magnitude;
        n.y /= n_magnitude;
        n.z /= n_magnitude;
    }
    
    float dot_product = dot(n);
    return Vector3(
        x - 2.0f * dot_product * n.x,
        y - 2.0f * dot_product * n.y,
        z - 2.0f * dot_product * n.z
    );
}

Vector3 operator*(float s, const Vector3 &v) { return Vector3(v.x * s, v.y * s, v.z * s); }

} // namespace cg
