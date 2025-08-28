#include "geometry/segment3.hpp"

#include "geometry/geometry.hpp"

namespace cg
{

LineSegment3::LineSegment3(const Point3 &p1, const Point3 &p2) : a(p1), b(p2) {}

Segment3PointDistanceResult LineSegment3::distance(const Point3 &p) const
{
  /* APPROACH: Distance to LINE SEGMENT (finite), not infinite line
   * 
   * 1. Project the query point onto the infinite line containing the segment
   * 2. Check if this projection falls within the segment bounds [0,1]
   * 3. If projection is outside bounds, clamp to nearest endpoint
   * 4. This ensures we always find the closest point ON THE SEGMENT
   * 
   * For segment distance, we must clamp the projection parameter to [0,1], again because this is a finite line.
   */
  
  // Get the segment vector from a to b
  Vector3 segmentVector = Vector3(a, b);  // Using Vector3(from, to) constructor
  
  // Get the vector from segment start (a) to the query point (p)
  Vector3 pointVector = Vector3(a, p);    // Using Vector3(from, to) constructor
  
  // Calculate the squared length of the segment using norm_squared()
  float segmentLengthSq = segmentVector.norm_squared();
  
  // Handle degenerate case where segment has zero length (point segment)
  if (segmentLengthSq <= 1e-6f) 
  {
      // Segment is just a point, so distance is simply point-to-point distance
      Point3 closestPoint = a;
      Vector3 diff = Vector3(closestPoint, p);
      float dist = diff.norm();
      return {dist, closestPoint};
  }
  
  // Project pointVector onto segmentVector using dot product
  // t represents the parametric position along the segment (0 = point a, 1 = point b)
  float t = pointVector.dot(segmentVector) / segmentLengthSq;
  
  // Clamp t to [0, 1] to ensure closest point lies within the segment
  // - If t < 0: closest point is at segment start (point a)
  // - If t > 1: closest point is at segment end (point b)  
  // - If 0 ≤ t ≤ 1: closest point is the projection on the segment
  // This clamping is what makes this SEGMENT distance, not infinite line distance
  t = std::max(0.0f, std::min(1.0f, t));
  
  // Calculate the closest point using the clamped parameter
  // closestPoint = a + t * segmentVector
  Vector3 scaledSegment = segmentVector * t;
  Point3 closestPoint = Point3(a.x + scaledSegment.x, a.y + scaledSegment.y, a.z + scaledSegment.z);
  
  // Calculate final distance from query point to closest point on segment
  Vector3 diff = Vector3(closestPoint, p);
  float dist = diff.norm();
  
  return {dist, closestPoint};
}

} // namespace cg
