#include "geometry/plane.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Plane::Plane() : a(0.0f), b(0.0f), c(0.0f), d(0.0f) {}

Plane::Plane(const Point3 &p, const Vector3 &n) { set(p, n); }

Plane::Plane(const Point3 &p1, const Point3 &p2, const Point3 &p3)
{
  // Create two vectors from the three points
  Vector3 v1 = p2 - p1;  // Vector from p1 to p2
  Vector3 v2 = p3 - p1;  // Vector from p1 to p3
  
  // Cross product gives us the normal (right-hand rule with CCW ordering)
  Vector3 normal = v1.cross(v2);
  
  // Set the plane using the normal and the first point
  set(p1, normal);
}

void Plane::set(const Point3 &p, const Vector3 &n)
{
  // Set the plane coefficients (a, b, c) directly from the normal vector
  a = n.x;
  b = n.y;
  c = n.z;
  //solve for distance using 
  //a(x - x₀) + b(y - y₀) + c(z - z₀) = 0
  //ax + by + cz = d
  //d = N · P = 0
  //N = the normal
  //P = A point on the plane 
  d = n.dot(p);
}

void Plane::normalize()
{
  // Calculate the magnitude of the normal vector
  float magnitude = std::sqrt(a * a + b * b + c * c);
  
  // Avoid division by zero
  if (magnitude > 1e-6f)
  {
      float inv_magnitude = 1.0f / magnitude;
      a *= inv_magnitude;
      b *= inv_magnitude;
      c *= inv_magnitude;
      d *= inv_magnitude;
  }
}

float Plane::solve(const Point3 &p) const
{
  // - If result > 0: point is on positive side of plane (direction of normal)
  // - If result < 0: point is on negative side of plane (opposite to normal)
  // - If result = 0: point lies exactly on the plane
  // - If plane is normalized, this gives the signed distance to the plane
  return a * p.x + b * p.y + c * p.z - d;
}

Vector3 Plane::get_normal() const
{
  // The normal vector is simply (a, b, c) from the plane equation ax + by + cz + d = 0
  return Vector3(a, b, c);
}

} // namespace cg
