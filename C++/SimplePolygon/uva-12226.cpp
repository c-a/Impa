#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef int ftype;

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
};

struct Point {
  ftype x, y;
  int index;
  Point(): x(0), y(0) {}
  Point(ftype _x, ftype _y, int i = -1): x(_x), y(_y), index(i) {}
  bool operator<(const Point& other) const {
    if (x-other.x != 0) return x < other.x; else return y < other.y;
  }
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  const Point translate(const Vec& v) const {
    return Point(x + v.x, y + v.y);
  }
};
Vec::Vec(const Point& a, const Point& b) { // needs to be here since it uses point
  x = b.x-a.x; y = b.y-a.y;
}

// returns true if point r is to the left side of line pq
bool ccw(const Point& p, const Point& q, const Point& r) {
  return Vec(p,q).cross(Vec(p,r)) > 0;
}
// returns true if point r is on the line pq
bool collinear(const Point& p, const Point& q, const Point& r) {
  return Vec(p,q).cross(Vec(p,r)) == 0;
}

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

int main() {
  int c;
  cin >> c;
  while (--c >= 0) {
    int N;
    cin >> N;
    vector<Point> points;
    points.reserve(N);
    for (int n = 0; n < N; ++n) {
      int x, y;
      cin >> x >> y;
      points.emplace_back(x, y, points.size());
    }
    // Find leftmost point
    size_t p0 = 0;
    for (size_t i = 1; i < points.size(); ++i) {
      if (points[i].y < points[p0].y ||
          (points[i].y == points[p0].y && points[i].x < points[p0].x))
        p0 = i;
    }
    std::swap(points[0], points[p0]);
    std::sort(points.begin(), points.end(),
              CCWSort(points[0]));

    // Reverse order of collinear sequence at the end.
    int start = N - 1;
    while (start >= 1 && collinear(points[start - 1], points[start], points[0])) --start;
    for (int s = start, e = N - 1; s < e; ++s, --e) {
      std::swap(points[s], points[e]);
    }
    bool first = true;
    for (const auto& p : points) {
      if (!first) {
        std::cout << " ";
      }
      std::cout << p.index;
      first = false;
    }
    std::cout << "\n";
  }
}
