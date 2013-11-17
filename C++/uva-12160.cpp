
#include <algorithm>
#include <queue>

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

using namespace std;


int
main(void)
{
  for (int c = 1; ; c++) {
    int L, U, R;
    scanf("%d %d %d", &L, &U, &R);
    if (L == 0 && U == 0 && R == 0)
      break;

    int buttons[10];
    for (int r = 0; r < R; r++) {
      scanf("%d", &buttons[r]);
    }

    bool visited[10000];
    memset(visited, false, sizeof(bool)*10000);

    int pushes = -1;

    std::queue<int> Q;
    Q.push(U); Q.push(-1);
    visited[U] = true;
    int level = 0;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      if (v == -1 && !Q.empty()) {
        level++;
        Q.push(-1);
        continue;
      }
      else if (v == L) {
        pushes = level;
        break;
      }

      for (int r = 0; r < R; r++) {
        int newSum = (v + 10000 - buttons[r]) % 10000;
        if (!visited[newSum]) {
          Q.push(newSum);
          visited[newSum] = true;
        }
      }
    }

    if (pushes != -1)
      printf("Case %d: %d\n", c, pushes);
    else
      printf("Case %d: Permanently Locked\n", c);
  }

  return 0;
}
