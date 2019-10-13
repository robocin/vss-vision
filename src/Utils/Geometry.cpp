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


int Geometry::cmp(float a, float b) {
    if (fabs(a-b) < EPS) return 0;
    else if (a < b) return -1;
    return 1;
}

Geometry::PT Geometry::rotateCCW90(Geometry::PT p) { return Geometry::PT(-p.y,p.x); }
Geometry::PT Geometry::rotateCW90(Geometry::PT p)  { return Geometry::PT(p.y,-p.x); }
Geometry::PT Geometry::rotateCCW(Geometry::PT p, float t) {
    return Geometry::PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

Geometry::PT Geometry::projPtLine(Geometry::PT a, Geometry::PT b, Geometry::PT c) {
    b = b - a; c = c - a;
    return a + b * (c*b) / (b*b);
}

Geometry::PT Geometry::projPtSeg(Geometry::PT a, Geometry::PT b, Geometry::PT c) {
    b = b - a; c = c - a;
    float r = b * b;
    if (cmp(r) == 0) return a;
    r = c * b / r;
    if (r < 0) return a;
    if (r > 1) return a+b;
    return a + b * r;
}

float Geometry::distPtSeg(Geometry::PT a, Geometry::PT b, Geometry::PT c) {
    return !(c - projPtSeg(a, b, c));
}

float Geometry::distPtPlane(float x, float y, float z, float a, float b, float c, float d) {
    return fabs(a*x + b*y + c*z - d) / sqrt(a*a + b*b + c*c);
}

bool Geometry::parallel(Geometry::PT a, Geometry::PT b, Geometry::PT c, Geometry::PT d) {
    return cmp((b-a) % (c-d)) == 0;
}

bool Geometry::collinear(Geometry::PT a, Geometry::PT b, Geometry::PT c, Geometry::PT d) {
    return parallel(a, b, c, d)
        && cmp((a-b) % (a-c)) == 0
        && cmp((c-d) % (c-a)) == 0;
}

bool Geometry::segInter(Geometry::PT a, Geometry::PT b, Geometry::PT c, Geometry::PT d) {
    if (collinear(a, b, c, d)) {
        if (cmp(!(a-c)) == 0 || cmp(!(a-d)) == 0 ||
            cmp(!(b-c)) == 0 || cmp(!(b-d)) == 0) return true;

        if ((c-a) * (c-b) > 0 && (d-a) * (d-b) > 0 && (c-b) * (d-b) > 0)
            return false;

        return true;
    }

    if (((d-a) % (b-a)) * ((c-a) % (b-a)) > 0) return false;
    if (((a-c) % (d-c)) * ((b-c) % (d-c)) > 0) return false;

    return true;
}

Geometry::PT Geometry::lineLine(Geometry::PT a, Geometry::PT b, Geometry::PT c, Geometry::PT d) {
    b = b - a; d = c - d; c = c - a;
    return a + b * (c % d) / (b % d);
}

Geometry::PT Geometry::circleCenter(Geometry::PT a, Geometry::PT b, Geometry::PT c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return lineLine(b, b + rotateCW90(a-b), c, c + rotateCW90(a-c));
}

bool Geometry::PointInPolygon(const std::vector<Geometry::PT> &p, Geometry::PT q) {
    bool c = 0;
    for (unsigned int i = 0; i < p.size(); i++) {
        int j = (i+1)%p.size();
        if (((p[i].y <= q.y && q.y < p[j].y) ||
            (p[j].y <= q.y && q.y < p[i].y)) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)) {
            c = !c;
        }
    }
    return c;
}

bool Geometry::PointOnPolygon(const std::vector<Geometry::PT> &p, Geometry::PT q) {
    for (unsigned int i = 0; i < p.size(); i++){
        if ( (!(projPtSeg(p[i], p[(i+1) % p.size()], q) - q)) < EPS){
            return true;
        }
    }
    return false;
}

std::vector<Geometry::PT> Geometry::circleLine(Geometry::PT a, Geometry::PT b, Geometry::PT c, float r) {
    std::vector<Geometry::PT> ret;
    b = b-a;
    a = a-c;
    float A = b*b;
    float B = a*b;
    float C = a*a - r*r;
    float D = B*B - A*C;
    if (D < -EPS) return ret;
    ret.push_back(c + a + b*(-B + sqrt(D + EPS)) / A);
    if (D > EPS)
        ret.push_back(c + a + b*(-B - sqrt(D)) / A);
    return ret;
}

std::vector<Geometry::PT> Geometry::circleCircle(Geometry::PT a, Geometry::PT b, float r, float R) {
    std::vector<Geometry::PT> ret;
    float d = !(a-b);
    if (d > r + R || d + std::min(r, R) < std::max(r, R)) return ret;
    float x = (d*d - R*R + r*r) / (2*d);
    float y = sqrt(r*r - x*x);
    Geometry::PT v = (b - a)/d;
    ret.push_back(a + v*x + rotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a + v*x - rotateCCW90(v)*y);
    return ret;
}

float Geometry::signedArea(const std::vector<Geometry::PT> &p) {
    float area = 0;
    for(unsigned int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i] % p[j];
    }
    return area / 2.0;
}

float Geometry::area(const std::vector<Geometry::PT> &p) {
    return fabs(signedArea(p));
}

Geometry::PT Geometry::centroid(const std::vector<Geometry::PT> &p) {
    Geometry::PT c(0,0);
    float scale = 6.0 * signedArea(p);
    for (unsigned int i = 0; i < p.size(); i++){
        int j = (i+1) % p.size();
        c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale;
}

bool Geometry::isSimple(const std::vector<Geometry::PT> &p) {
    for (unsigned int i = 0; i < p.size(); i++) {
        for (unsigned int k = i+1; k < p.size(); k++) {
            int j = (i+1) % p.size();
            int l = (k+1) % p.size();
            if (((int) i) == l || j == ((int) k)) continue;
            if (segInter(p[i], p[j], p[k], p[l]))
            return false;
        }
    }
    return true;
}

bool Geometry::circle2PtsRad(Geometry::PT p1, Geometry::PT p2, float r, Geometry::PT &c) {
    float d2 = !(p1 - p2);
    d2 *= d2;
    float det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    float h = sqrt(det);
    c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    return true;
}

bool Geometry::areClockwise(Geometry::PT p1, Geometry::PT p2) {
    return (-p1.x*p2.y + p1.y*p2.x) > 0;
}

bool Geometry::isWithinRadius(Geometry::PT p1, float sectorRadius) {
    float sectorRadiusSquared = sectorRadius*sectorRadius;
    return p1.x*p1.x + p1.y*p1.y <= sectorRadiusSquared;
}

bool Geometry::isPointInsideSector(Geometry::PT p1, Geometry::PT center, Geometry::PT sectorStart, Geometry::PT sectorEnd, float sectorRadius) {
    Geometry::PT relPoint(p1.x-center.x, p1.y-center.y);
    return !areClockwise(sectorStart, relPoint) && areClockwise(sectorEnd, relPoint) && isWithinRadius(relPoint, sectorRadius);
}

bool Geometry::isRangeInsideSector(Geometry::PT p1, Geometry::PT center, Geometry::PT sectorStart, Geometry::PT sectorEnd, float sectorRadius, float rangeRadius) {
    return isPointInsideSector(Geometry::PT(p1.x,p1.y-rangeRadius), center, sectorStart, sectorEnd, sectorRadius)
            || isPointInsideSector(Geometry::PT(p1.x,p1.y), center, sectorStart, sectorEnd, sectorRadius)
            || isPointInsideSector(Geometry::PT(p1.x,p1.y+rangeRadius), center, sectorStart, sectorEnd, sectorRadius);
}

uint8_t Geometry::whichQuadrant(Geometry::PT p1) {
    if(p1.x > 0){
        if(p1.y > 0)
            return 0;
        else
            return 1;
    }
    else {
        if(p1.y < 0)
            return 2;
        else
            return 3;
    }
}
