#include "Geometry.h"

Int Geometry::sign(const Float &t_difference) {
  return (std::abs(t_difference) < Global::eps()) ? EQUAL : (t_difference > 0) ? GREATER : LESS;
}

Bool Geometry::cmp(const Float &t_lhs, const Int &t_op, const Float &t_rhs) {
  return sign(t_rhs - t_lhs) == t_op;
}

Float Geometry::area(const Point &t_a, const Point &t_b, const Point &t_c) {
  return area2(t_a, t_b, t_c) / 2;
}

Float Geometry::area(const Polygon &t_polygon) {
  return area2(t_polygon) / 2;
}

Point Geometry::projectPointLine(const Point &t_a, const Point &t_b, const Point &t_c) {
  assert(!(t_a == t_b));
  return t_a + (t_b - t_a) * dot(t_b - t_a, t_c - t_a) / dot(t_b - t_a, t_b - t_a);
}

Point Geometry::reflectPointLine(const Point &t_a, const Point &t_b, const Point &t_c) {
  return 2 * projectPointLine(t_a, t_b, t_c) - t_c;
}

Point Geometry::projectPointSegment(const Point &t_a, const Point &t_b, const Point &t_c) {
  Float r = dot(t_b - t_a, t_b - t_a);

  if (cmp(r, EQUAL, 0)) {
    return t_a;
  }

  r = dot(t_c - t_a, t_b - t_a) / r;

  if (cmp(r, LESS, 0)) {
    return t_a;
  }

  if (cmp(r, GREATER, 1)) {
    return t_b;
  }

  return t_a + (t_b - t_a) * r;
}

Float Geometry::distancePointSegment(const Point &t_a, const Point &t_b, const Point &t_c) {
  return distance(t_c, projectPointSegment(t_a, t_b, t_c));
}

Point Geometry::computeLineIntersection(Point t_a, Point t_b, Point t_c, Point t_d) {
  assert(!linesParallel(t_a, t_b, t_c, t_d));
  t_b = t_b - t_a;
  t_d = t_c - t_d;
  t_c = t_c - t_a;
  assert(cmp(dot(t_b, t_b), GREATER, 0) and cmp(dot(t_d, t_d), GREATER, 0));
  return t_a + t_b * cross(t_c, t_d) / cross(t_b, t_d);
}

Point Geometry::computeSegmentIntersection(const Point &t_a, const Point &t_b, const Point &t_c,
                                           const Point &t_d) {
  assert(segmentsIntersect(t_a, t_b, t_c, t_d));
  return computeLineIntersection(t_a, t_b, t_c, t_d);
}

Point Geometry::computeCircleCenter(Point t_a, Point t_b, Point t_c) {
  t_b = (t_a + t_b) / 2;
  t_c = (t_a + t_c) / 2;
  return computeLineIntersection(t_b, t_b + rotateCW90(t_a - t_b), t_c, t_c + rotateCW90(t_a - t_c));
}

Float Geometry::circleCircleIntersectionAngle(const Float &t_r1, const Float &t_r2,
                                              const Float &t_d) {
  assert(isTriangle(t_r1, t_r2, t_d));
  return 2 * std::acos(((t_d * t_d + t_r2 * t_r2) - t_r1 * t_r1) / (2 * t_r2 * t_d));
}

Points Geometry::circleCircleIntersection(const Point &t_p, const Float &t_r1, const Point &t_q,
                                          const Float t_r2) {
  Float d = distance(t_p, t_q);

  if (cmp(d, GREATER, t_r1 + t_r2) || cmp(d + std::min(t_r1, t_r2), LESS, std::max(t_r1, t_r2))) {
    return Points();
  }

  Float x = (d * d - t_r2 * t_r2 + t_r1 * t_r1) / (2 * d);
  Float y = std::sqrt(t_r1 * t_r1 - x * x);
  Point v = (t_q - t_p) / d;
  Points ret;
  ret.push_back(t_p + v * x + rotateCCW90(v) * y);

  if (cmp(y, GREATER, 0)) {
    ret.push_back(t_p + v * x - rotateCCW90(v) * y);
  }

  return ret;
}
