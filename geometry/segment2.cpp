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
    Segment2IntersectionResult result;
    result.intersects = false;
    result.intersect_point = Point2(0.0f, 0.0f);
    
    // Get the direction vectors for both segments
    Vector2 dir1 = b - a;  // Direction of current segment
    Vector2 dir2 = segment.b - segment.a;  // Direction of other segment
    
    // Calculate the cross product of the direction vectors
    float cross_product = dir1.x * dir2.y - dir1.y * dir2.x;
    
    // If cross product is zero (or very close to zero), lines are parallel
    const float EPSILON = 1e-10f;
    if (std::abs(cross_product) < EPSILON) {
        return result;  // Parallel lines - no intersection
    }
    
    // Calculate the vector from start of first segment to start of second segment
    Vector2 start_diff = segment.a - a;
    
    // Calculate parametric values for intersection point
    float t1 = (start_diff.x * dir2.y - start_diff.y * dir2.x) / cross_product;
    float t2 = (start_diff.x * dir1.y - start_diff.y * dir1.x) / cross_product;
    
    // Check if intersection point lies within both line segments
    if (t1 >= 0.0f && t1 <= 1.0f && t2 >= 0.0f && t2 <= 1.0f) {
        result.intersects = true;
        // Calculate intersection point using parametric equation
        result.intersect_point.x = a.x + t1 * dir1.x;
        result.intersect_point.y = a.y + t1 * dir1.y;
    }
    
    return result;
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
