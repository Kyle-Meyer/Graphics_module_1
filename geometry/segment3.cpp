#include "geometry/segment3.hpp"

#include "geometry/geometry.hpp"

namespace cg
{

LineSegment3::LineSegment3(const Point3 &p1, const Point3 &p2) : a(p1), b(p2) {}

Segment3PointDistanceResult LineSegment3::distance(const Point3 &p) const
{
    // Student to define - Module 1
    return {0.0f, Point3()};
}

} // namespace cg
