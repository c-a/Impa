#include <cassert>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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

ftype angle(const Point& a, const Point& o, const Point& b) { // returns angle of aob in rad
  Vec oa(o, a), ob(o, b);
  return angle(oa, ob);
}

int smallestN(double r1, double r2, double r3) {
  double radianEPS = 1e-7;
  for (int n = 3; n <= 1000; ++n) {
    double segmentAngle = M_PI / n;
    double rem1 = remainder(r1, segmentAngle);
    double rem2 = remainder(r2, segmentAngle);
    double rem3 = remainder(r3, segmentAngle);
    if (fabs(rem1) < radianEPS && fabs(rem2) < radianEPS
      && fabs(rem3) < radianEPS) return n;
  }
  return -1;
}

bool readPoint(Point& p) {
  std::string line;
  std::getline(std::cin, line);
  if (line == "END") return false;
  std::stringstream sstream(line);
  sstream >> p.x >> p.y;
  return true;
}

int main() {
  std::string line;
  while (true) {
    Point a, b, c;
    if (!readPoint(a)) break;
    if (!readPoint(b)) break;
    if (!readPoint(c)) break;

    double av = angle(b, a, c);
    double bv = angle(a, b, c);
    double cv = angle(a, c, b);
    int res = smallestN(av, bv, cv);
    if (res == -1) assert(false);
    std::cout << res << "\n";
  }
}
