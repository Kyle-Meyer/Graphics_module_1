#include "geometry/plane.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Plane::Plane() : a(0.0f), b(0.0f), c(0.0f), d(0.0f) {}

Plane::Plane(const Point3 &p, const Vector3 &n) { set(p, n); }

Plane::Plane(const Point3 &p1, const Point3 &p2, const Point3 &p3)
{
  // Create two vectors in the plane using the three points
  Vector3 v1 = Vector3(p1, p2);  // Vector from p1 to p2
  Vector3 v2 = Vector3(p1, p3);  // Vector from p1 to p3
  
  // Counter-clockwise order: v1 × v2 gives outward-pointing normal
  Vector3 normal = v1.cross(v2);
  
  // Set the plane coefficients (a, b, c) from the normal vector
  a = normal.x;
  b = normal.y;
  c = normal.z;
  
  // Calculate d using the plane equation: ax + by + cz + d = 0
  // a*p1.x + b*p1.y + c*p1.z + d = 0, so d = -(a*p1.x + b*p1.y + c*p1.z)
  d = -(a * p1.x + b * p1.y + c * p1.z);
}

void Plane::set(const Point3 &p, const Vector3 &n)
{
  // Set the plane coefficients (a, b, c) directly from the normal vector
  a = n.x;
  b = n.y;
  c = n.z;
  
  // Calculate d using the plane equation: ax + by + cz + d = 0
  // Substitute the given point to solve for d
  // a*p.x + b*p.y + c*p.z + d = 0, so d = -(a*p.x + b*p.y + c*p.z)
  d = -(a * p.x + b * p.y + c * p.z);
}

void Plane::normalize()
{
  // Calculate the magnitude of the normal vector (a, b, c)
  float normal_magnitude = sqrt(a * a + b * b + c * c);
  
  // Avoid division by zero for degenerate planes
  if (normal_magnitude > 1e-6f) {
      // Divide all coefficients by the normal magnitude to make normal unit length
      a /= normal_magnitude;
      b /= normal_magnitude;
      c /= normal_magnitude;
      d /= normal_magnitude;
  }
}

float Plane::solve(const Point3 &p) const
{
  // - If result > 0: point is on positive side of plane (direction of normal)
  // - If result < 0: point is on negative side of plane (opposite to normal)
  // - If result = 0: point lies exactly on the plane
  // - If plane is normalized, this gives the signed distance to the plane
  return a * p.x + b * p.y + c * p.z + d;
}

Vector3 Plane::get_normal() const
{
  // The normal vector is simply (a, b, c) from the plane equation ax + by + cz + d = 0
  return Vector3(a, b, c);
}

} // namespace cg
