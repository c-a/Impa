#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Point{
  int x, y;
  Point operator+(const Point& p) const {
    return {x + p.x, y + p.y};
  }
};

int main() {
  int height[500][500];
  int higher[500][500];
  int N;
  scanf("%d", &N);
  while (--N >= 0) {
    int h, w, d; scanf("%d %d %d", &h, &w, &d);
    vector<Point> points;
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        scanf("%d", &height[y][x]);
        higher[y][x] = -1;
        points.push_back({x, y});
      }
    }
    // Sort points in descending order of height.
    std::sort(points.begin(), points.end(),
      [&height](const Point& p1, const Point& p2) {
        return height[p1.y][p1.x] > height[p2.y][p2.x];
      });
    int summits = 0;
    for (int i = 0; i < points.size(); ++i) {
      const auto& sp = points[i];
      if (higher[sp.y][sp.x] != -1) continue;
      int sh = height[sp.y][sp.x];

      int curSummits = 0;
      bool summit = true;
      queue<Point> q; q.push(sp); higher[sp.y][sp.x] = i;
      while (!q.empty()) {
        static const vector<Point> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        const Point p = q.front(); q.pop();
        if (height[p.y][p.x] == sh) ++curSummits;
        for (const Point& dir : dirs) {
          Point np = p + dir;
          if (np.x < 0 || np.x >= w || np.y < 0 || np.y >= h) continue;
          if (height[np.y][np.x] + d <= sh) continue;
          if (higher[np.y][np.x] == i) continue;
          if (higher[np.y][np.x] != -1) {
            summit = false;
          } else {
            higher[np.y][np.x] = i;
            q.push(np);
          }
        }
      }
      if (summit) summits += curSummits;
    }
    printf("%d\n", summits);
  }
}
