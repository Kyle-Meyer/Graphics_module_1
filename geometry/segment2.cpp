#include "geometry/segment2.hpp"

#include "geometry/geometry.hpp"

namespace cg
{

LineSegment2::LineSegment2() : a{0.0f, 0.0f}, b{0.0f, 0.0f} {}

LineSegment2::LineSegment2(const Point2 &p1, const Point2 &p2) : a(p1), b(p2) {}

Segment2PointDistanceResult LineSegment2::distance(const Point2 &p) const
{
  /* APPROACH: Distance to LINE SEGMENT (finite), not infinite line
  * 
  * 1. Project the query point onto the infinite line containing the segment
  * 2. Check if this projection falls within the segment bounds [0,1]
  * 3. If projection is outside bounds, clamp to nearest endpoint
  * 4. This ensures we always find the closest point ON THE SEGMENT
  * 
  * For segment distance, we must clamp the projection parameter to [0,1], since this is not an infinite line.
  */
    
  // Get the segment vector from a to b
  Vector2 segmentVector = b - a;
  
  // Get the vector from segment start (a) to the query point (p)
  Vector2 pointVector = p - a;
  
  // Calculate the squared length of the segment
  float segmentLengthSq = segmentVector.dot(segmentVector);
  
  // Handle degenerate case where segment has zero length (point segment)
  if (segmentLengthSq <= 1e-6f) 
  {
      // Segment is just a point, so distance is simply point-to-point distance
      Point2 closestPoint = a;
      Vector2 diff = p - closestPoint;
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
  // This clamping is what makes this SEGMENT distance
  t = std::max(0.0f, std::min(1.0f, t));
  
  // Calculate the closest point using the clamped parameter
  // closestPoint = a + t * segmentVector
  Point2 closestPoint = a + (segmentVector * t);
  
  // Calculate final distance from query point to closest point on segment
  Vector2 diff = p - closestPoint;
  float dist = diff.norm();
  
  return {dist, closestPoint};
}

Segment2IntersectionResult LineSegment2::intersect(const LineSegment2 &segment) const
{
  // Direction vectors for both segments
  Vector2 d1 = b - a;        // This segment's direction
  Vector2 d2 = segment.b - segment.a;  // Other segment's direction
  
  // Vector from this segment's start to other segment's start
  Vector2 startDiff = a - segment.a;
  
  // Use cross product to check for parallel lines
  // Cross product in 2D: d1 × d2 = d1.x * d2.y - d1.y * d2.x
  float cross_d1_d2 = d1.cross(d2);
  
  // Check if segments are parallel (cross product is zero)
  if (fabs(cross_d1_d2) < 1e-6f) 
  {
      // Segments are parallel - return no intersection as specified
      return {false, Point2()};
  }
  
  // Calculate intersection parameters using cross products
  // For line intersection: P1 + t1*d1 = P2 + t2*d2
  // Solving: t1 = (startDiff × d2) / (d1 × d2)
  //         t2 = (startDiff × d1) / (d1 × d2)
  float t1 = startDiff.cross(d2) / cross_d1_d2;
  float t2 = startDiff.cross(d1) / cross_d1_d2;
  
  // Check if intersection point lies within both segments [0,1]
  if (t1 >= 0.0f && t1 <= 1.0f && t2 >= 0.0f && t2 <= 1.0f) 
  {
      // Calculate intersection point using vector addition
      Point2 intersectionPoint = a + (d1 * t1);
      return {true, intersectionPoint};
  }
  
  // No intersection within segment bounds
  return {false, Point2()};
}

Segment2ClipResult LineSegment2::clip_to_polygon(const std::vector<Point2> &poly) const
{
    // Defined Later...
    return {true, LineSegment2()};
}

Segment2ClipResult LineSegment2::clip_to_rectangle(const CRectangle &r) const
{
    // Defined Later...
    return {true, LineSegment2()};
}

} // namespace cg
