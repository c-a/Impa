#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <limits>

typedef double ftype;
static const ftype EPS = 1e-9;

struct Point;
struct Vec {
  ftype x, y;
  Vec(ftype _x, ftype _y): x(_x), y(_y) {}
  Vec(const Point& a, const Point& b); // definition after point
  const Vec scale(ftype s) const {
    return Vec(x*s, y*s);
  }
  ftype dot(const Vec& b) const{
    return x*b.x + y*b.y;
  }
  ftype cross(const Vec& b) {
    return x*b.y-y*b.x;
  }
  ftype norm_sq() const {
    return (x*x+y*y);
  }
  const Vec rotate(ftype theta) {
    ftype rad = theta * M_PI / 180;
    return Vec(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad));
  }
};
ftype angle(const Vec& a, const Vec& b) {
  return acos(a.dot(b) / sqrt(a.norm_sq()*b.norm_sq()));
}

struct Point {
  ftype x, y;
  Point(): x(0), y(0) {}
  Point(ftype _x, ftype _y): x(_x), y(_y) {}
  Point(const Point& other) {
    x = other.x; y = other.y;
  }
  bool operator<(const Point& other) const {
    if (fabs(x-other.x) > EPS) return x < other.x; else return y < other.y;
  }
  bool operator==(const Point& other) const {
    return (fabs(x-other.x) < EPS && fabs(y-other.y) < EPS);
  }
  const Point translate(const Vec& v) const {
    return Point(x + v.x, y + v.y);
  }
  const Point rotate(ftype theta) {
    ftype rad = theta * M_PI / 180;
    return Point(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad));
  }
};
Vec::Vec(const Point& a, const Point& b) { // needs to be here since it uses point
  x = b.x-a.x; y = b.y-a.y;
}

ftype dist(const Point& p1, const Point& p2) { // Euclidean distance
    return sqrt(Vec(p1, p2).norm_sq());
}
ftype angle(const Point& a, const Point& o, const Point& b) { // returns angle of aob in rad
  Vec oa(o, a), ob(o, b);
  return angle(oa, ob);
}
// returns true if point r is to the left side of line pq
bool ccw(const Point& p, const Point& q, const Point& r) {
  return Vec(p,q).cross(Vec(p,r)) > 0;
}
// returns true if point r is on the line pq
bool collinear(const Point& p, const Point& q, const Point& r) {
  return fabs(Vec(p,q).cross(Vec(p,r))) < EPS;
}

ftype distToLine(const Point& p, const Point& a, const Point& b, Point& c) {
  // formula: c = a + u * ab;
  Vec ap(a, p), ab(a, b);
  ftype u = ap.dot(ab) / ab.norm_sq();
  c = a.translate(ab.scale(u));
  return dist(p, c);
}

ftype pointLineDist(const Point& p, const Point& a, const Point& b) {
  Vec ab(a, b), ap(a, p);
  return abs(ab.cross(ap)) / sqrt(ab.norm_sq());
}

// returns the distance from p to the line segment ab defined by two points a and b. The closest point is stored in c.
ftype distToLineSegment(const Point& p, const Point& a, const Point& b, Point& c) {
  Vec ap(a, p), ab(a, b);
  ftype u = ap.dot(ab) / ab.norm_sq();
  if (u < 0.0) { // closer to a
    c = a; return dist(p, a); // Euclidean distance between p and a
  }
  else if (u > 1.0) { // closer to b
    c = b; return dist(p, b); // Euclidean distance between p and b
  }
  return distToLine(p, a, b, c);
}

struct Line {
  ftype a, b, c;
  Line(ftype _a, ftype _b, ftype _c): a(_a), b(_b), c(_c) {}
  Line(Point& p1, Point& p2) {
    if (fabs(p1.x-p2.x) < EPS) { // vertical line
      a = 1.0; b = 0.0; c = -p1.x; // default values
    } else {
      a = -(ftype)(p1.y-p2.y)/(p1.x-p2.x);
      b = 1.0; // IMPORTANT: we fix the value of b to 1.0
      c = -(ftype)(a*p1.x) - p1.y;
    }
  }
  bool parallel(const Line& l) const {
    return (fabs(a-l.a) < EPS) && (fabs(b-l.b) < EPS);
  }
  bool intersect(const Line& l, Point& p) const {
    if (parallel(l)) return false;
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
    if (fabs(b) > EPS) p.y = -(a*p.x + c); else p.y = -(l.a*p.x + l.c);
    return true;
  }
  bool operator==(const Line& other) const {
    return parallel(other) && (fabs(c-other.c) < EPS);
  }
};

class Polygon {
private:
  typedef std::vector<Point> vp;
  vp points_;

public:
  Polygon() {}
  Polygon(const vp& points): points_(points) {}

  void add_point(const Point& p) {
    points_.push_back(p);
  }
  size_t size() const {
    return points_.size();
  }
  const Point& operator[](size_t i) const {
    return points_[i];
  }
  const vp& get_points() const {
    return points_;
  }
  bool contains(const Point& pt) const {
    bool contains = false;
    int i, j;
    for (i = 0, j = (int)size() - 1; i < (int)size(); j = i++) {
      const Point& pi = points_[i];
      const Point& pj = points_[j];

      if ( ((pi.y > pt.y) != (pj.y > pt.y)) &&
          (pt.x < (pj.x-pi.x) * (pt.y-pi.y) / (pj.y-pi.y) + pi.x) ) {
        contains = !contains;
      }
    }
    return contains;
  }
  bool contains(const Polygon& p) const {
    for (vp::const_iterator i = p.points_.begin(); i != p.points_.end(); ++i) {
      if (!contains(*i))
        return false;
    }
    return true;
  }
};

class CCWSort {
public:
  CCWSort(const Point& o): origo(o) {}

  bool operator()(const Point& p1, const Point& p2) const {
    if (collinear(origo, p1, p2))
      return Vec(origo, p1).norm_sq() < Vec(origo, p2).norm_sq();
    return ccw(origo, p1, p2);
  }
private:
  Point origo;
};

Polygon
convexHull(const Polygon& pol) {
  if (pol.size() <= 3)
    return pol;

  std::vector<Point> points = pol.get_points();

  // Find leftmost point
  size_t p0 = 0;
  for (size_t i = 1; i < points.size(); ++i) {
    if (points[i].y < points[p0].y ||
        (points[i].y == points[p0].y && points[i].x < points[p0].x))
      p0 = i;
  }

  std::swap(points[0], points[p0]);
  std::sort(++points.begin(), points.end(), CCWSort(points[0]));

  std::vector<Point> hull(points.size());
  hull.resize(points.size());
  hull[0]= points[0];
  hull[1] = points[1];
  hull[2] = points[2];
  int hi = 3;
  for (size_t i = 3; i < points.size(); ++i) {
    const Point& p = points[i];
    for (; hi >= 2 && !ccw(hull[hi-2], hull[hi-1], p); hi--);
    hull[hi++] = p;
  }

  hull.resize(hi);
  return Polygon(hull);
}

int main() {
  Point p(1, 0);
  Line l(1, 0, 2);

  Polygon pol;
  pol.add_point(Point(-1, -1));
  pol.add_point(Point(1, -1));
  pol.add_point(Point(0, 0));
  pol.add_point(Point(1, 1));
  pol.add_point(Point(-1, 1));

  Polygon c = convexHull(pol);
  for (size_t i = 0; i < c.size(); ++i)
    printf("%f %f\n", c[i].x, c[i].y);
}
