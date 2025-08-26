#include "geometry/vector2.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(const Point2 &p) : x(p.x), y(p.y) {}

Vector2::Vector2(float ix, float iy) : x(ix), y(iy) {}

Vector2::Vector2(const Point2 &from, const Point2 &to) : x(to.x - from.x), y(to.y - from.y) {}

Vector2::Vector2(const Vector2 &w) : x(w.x), y(w.y) {}

Vector2 &Vector2::operator=(const Vector2 &w)
{
    x = w.x;
    y = w.y;
    return *this;
}

void Vector2::set(float ix, float iy)
{
    x = ix;
    y = iy;
}

void Vector2::set(const Point2 &p)
{
    x = p.x;
    y = p.y;
}

void Vector2::set(const Point2 &from, const Point2 &to)
{
    x = to.x - from.x;
    y = to.y - from.y;
}

Vector2 Vector2::operator+(const Vector2 &w) const { return Vector2(x + w.x, y + w.y); }

Vector2 &Vector2::operator+=(const Vector2 &w)
{
    x += w.x;
    y += w.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &w) const { return Vector2(x - w.x, y - w.y); }

Vector2 &Vector2::operator-=(const Vector2 &w)
{
    x -= w.x;
    y -= w.y;
    return *this;
}

Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

Vector2 &Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

bool Vector2::operator==(const Vector2 &w) const { return (x == w.x && y == w.y); }

float Vector2::dot(const Vector2 &w) const
{
    return x * w.x + y * w.y;
}

float Vector2::cross(const Vector2 &w) const
{
    return x * w.y - y * w.x;;
}

Vector2 Vector2::get_perpendicular(bool clockwise) const
{
    return Vector2(-y, x);
}

float Vector2::norm() const
{
    //I could be cheeky here
    //https://en.wikipedia.org/wiki/Fast_inverse_square_root
    //and invoke one of my favorite graphics hacks of all time 
    //but lets not cause any headaches 
    return std::sqrt(x * x + y * y);
}

float Vector2::norm_squared() const
{
    // Student to define - Module 1
    return x * x + y * y ;
}

Vector2 &Vector2::normalize()
{
    float length = norm();
    //generouse check to make sure we dont do a div by 0
    if (length > 1e-6f) {
        float invLength = 1.0f / length;
        x *= invLength;
        y *= invLength;
    }
    return *this;
}

float Vector2::component(const Vector2 &w) const
{
    // Student to define - Module 1
    //
    float wLength = w.norm();
    if (wLength > 1e-6f) 
        return dot(w) / wLength;
    return 0.0f;
}

Vector2 Vector2::projection(const Vector2 &w) const
{
    // Student to define - Module 1
    return Vector2();
}

float Vector2::angle_between(const Vector2 &w) const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector2 Vector2::reflect(const Vector2 &normal) const
{
    // Student to define - Module 1
    return Vector2();
}

Vector2 operator*(float s, const Vector2 &v) { return Vector2(v.x * s, v.y * s); }

} // namespace cg
