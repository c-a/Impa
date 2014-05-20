#include <cstdio>
#include <queue>
#include <tuple>

uint32_t map[101][101];
bool wolfs[101][101];

int main() {
  while (true) {
    int w, h;
    scanf("%d %d", &w, &h);
    if (w == 0 && h == 0) break;

    for (int y = 0; y <= h; ++y) {
      for (int x = 0; x <= w; ++x) {
        map[y][x] = 0; wolfs[y][x] = false;
      }
    }
    int n;
    scanf("%d", &n);
    while (--n >= 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      wolfs[y][x] = true;
    }

    map[0][0] = 1;
    std::queue<std::tuple<int, int>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
      int x, y;
      std::tie(x, y) = q.front(); q.pop();
      if (x < w && !wolfs[y][x+1]) {
        if (map[y][x+1] == 0) q.emplace(x+1, y);
        map[y][x+1] += map[y][x];
      }
      if (y < h && !wolfs[y+1][x]) {
        if (map[y+1][x] == 0) q.emplace(x, y+1);
        map[y+1][x] += map[y][x];
      }
    }
    if (map[h][w] == 1) {
      printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
    } else if (map[h][w] > 1) {
      printf("There are %d paths from Little Red Riding Hood's house to her grandmother's house.\n",
        map[h][w]);
    } else {
      printf("There is no path.\n");
    }
  }
}
