#include <algorithm>
#include <functional>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cstdio>

typedef std::vector<int> vi;

int main() {
  while (true) {
    int n, m, head, knight, coins;
    vi heads, knights;

    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0)
      break;

    heads.resize(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &heads[i]);
    sort(heads.begin(), heads.end());

    knights.resize(m);
    for (int i = 0; i < m; i++)
      scanf("%d", &knights[i]);
    sort(knights.begin(), knights.end());

    head = 0;
    knight = 0;
    coins = 0;
    while (head < n) {
      while (knight < m && knights[knight] < heads[head]) knight++;
      if (knight >= m) {
        coins = -1;
        break;
      }
      coins += knights[knight];
      head++;
      knight++;
    }

    if (coins == -1)
      printf("Loowater is doomed!\n");
    else
      printf("%d\n", coins);
  }
}

