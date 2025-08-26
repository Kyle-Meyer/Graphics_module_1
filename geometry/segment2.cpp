#include "geometry/segment2.hpp"

#include "geometry/geometry.hpp"

namespace cg
{

LineSegment2::LineSegment2() : a{0.0f, 0.0f}, b{0.0f, 0.0f} {}

LineSegment2::LineSegment2(const Point2 &p1, const Point2 &p2) : a(p1), b(p2) {}

Segment2PointDistanceResult LineSegment2::distance(const Point2 &p) const
{
    // Student to define - Module 1
    return {0.0f, Point2()};
}

Segment2IntersectionResult LineSegment2::intersect(const LineSegment2 &segment) const
{
    // Student to define - Module 1
    return {true, Point2()};
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
