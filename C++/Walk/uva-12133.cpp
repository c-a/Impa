#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <list>
#include <limits>
#include <queue>
#include <vector>
#include <iterator>

struct point {
  int x, y;
  point(int _x, int _y): x(_x), y(_y) {}
  point(const point& other) {
    x = other.x; y = other.y;
  }
  bool operator<(const point& other) const {
    if (x == other.x)
      return y < other.y;
    return x < other.x;
  }
};


struct Polygon {
  typedef std::vector<point> vp;

  vp points;

  void add_point(const point& p) {
    points.push_back(p);
  }

  size_t size() const {
    return points.size();
  }

  const point& operator[](size_t i) {
    return points[i];
  }

  bool inside(const point& pt) const {
    bool inside = false;
    int i, j;
    for (i = 0, j = (int)size() - 1; i < (int)size(); j = i++) {
      const point& pi = points[i];
      const point& pj = points[j];

      if ( ((pi.y > pt.y) != (pj.y > pt.y)) &&
          (pt.x < (pj.x-pi.x) * (pt.y-pi.y) / (pj.y-pi.y) + pi.x) ) {
        inside = !inside;
      }
    }
    return inside;
  }

  bool inside(const Polygon& p) const {
    for (vp::const_iterator i = p.points.begin(); i != p.points.end(); ++i) {
      if (!inside(*i))
        return false;
    }
    return true;
  }
};

struct Curve {
  int height;
  Polygon p;
  Curve* parent;
  point ll;

  Curve() : height(0), parent(0), ll(point(1e9, 1e9)) {}

  void add_point(const point& pt) {
    p.add_point(pt);
    if (pt < ll)
      ll = pt;
  }

  bool inside(const point& pt) const {
    return p.inside(pt);
  }

  bool operator<(const Curve& rhs) const {
    return ll < rhs.ll;
  }
};

struct Slope
{
  int up;
  int down;

  Slope(): up(0), down(0) {}

  Slope(int diff): up(0), down(0) {
    if (diff > 0)
      up = diff;
    else
      down = -diff;
  }

  Slope(int u, int d): up(u), down(d) {}

  const Slope operator+(const Slope& lhs) const {
    return Slope(up + lhs.up, down + lhs.down);
  }

  bool operator<(const Slope& lhs) const {
    return (up + down) < (lhs.up + lhs.down);
  }
};

int main()
{
  int nCases;

  scanf("%d", &nCases);
  while (nCases-- > 0) {
    int N;
    scanf("%d", &N);

    Curve* curves = new Curve[N+1]; 

    // Create an all compassing curve
    curves[N].add_point(point(-300001, -300001));
    curves[N].add_point(point(300001, -300001));
    curves[N].add_point(point(300001, 300001));
    curves[N].add_point(point(-300001, 300001));

    for (int i = 0; i < N; i++) {
      int H, P;
      scanf("%d %d", &H, &P);

      curves[i].height = H;
      for (int j = 0; j < P; j++) {
        int x, y;
        scanf("%d %d", &x, &y);
        curves[i].add_point(point(x, y));
      }
    }

    std::sort(curves, curves+N+1);

    int alice, bob;
    for (int i = 0; i < N+1; i++) {
      for (int j = i-1; j >= 0; j--) {
        if (curves[j].inside(curves[i].p[0])) {
          curves[i].parent = &curves[j];
          break;
        }
      }
      if (curves[i].inside(point(0,0))) alice = i;
      if (curves[i].inside(point(100000,0))) bob = i;
    }

    std::list<Curve*> a, b;

    for (Curve* c = &curves[alice]; c != NULL; c = c->parent)
      a.push_front(c);
    for (Curve* c = &curves[bob]; c != NULL; c = c->parent)
      b.push_front(c);

    std::list<Curve*>::const_iterator ai = a.begin(), bi = b.begin();
    for (; ai != a.end() && bi != b.end() && *ai == *bi; ++ai, ++bi);

    int asc = 0, des = 0;

    if (ai != a.end() && bi != b.end()) {
      int diff = (*bi)->height - (*ai)->height;
      if (diff > 0)
        asc += diff;
      else
        des -= diff;
    }

    if (ai != a.end()) {
      std::list<Curve*>::const_iterator aj = ai;
      for (++aj; aj != a.end(); ai = aj++) {
        int diff = (*ai)->height - (*aj)->height;
        if (diff > 0)
          asc += diff;
        else
          des -= diff;
      }
    }

    if (bi != b.end()) {
      std::list<Curve*>::const_iterator bj = bi;
      for (++bj; bj != b.end(); bi = bj++) {
        int diff = (*bj)->height - (*bi)->height;
        if (diff > 0)
          asc += diff;
        else
          des -= diff;
      }
    }

    printf("%d %d\n", asc, des);
  }

  return 0;
}
