#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

typedef std::vector<int> vi;

struct BestEat {
  int burgers;
  int beer;

  BestEat(): burgers(0), beer(0) {}
  BestEat(int bu, int be): burgers(bu), beer(be) {}

  bool operator<(const BestEat& rhs) const {
    if (beer == rhs.beer)
      return burgers < rhs.burgers;

    return beer > rhs.beer;
  }

  const BestEat operator+(const BestEat& rhs) {
    return BestEat(burgers + rhs.burgers, beer + rhs.beer);
  }
};

int main() {
  int m, n, t;

  while (scanf("%d %d %d", &m, &n, &t)  == 3) {
    BestEat* be = new BestEat[t + 1];
    for (int i = 0; i <= t; i++) {
      be[i] = BestEat(0, i);
      if (i - m >= 0)
        be[i] = std::max(be[i], be[i - m] + BestEat(1, 0));
      if (i - n >= 0)
        be[i] = std::max(be[i], be[i - n] + BestEat(1, 0));
    }

    if (be[t].beer == 0)
      printf("%d\n", be[t].burgers);
    else
      printf("%d %d\n", be[t].burgers, be[t].beer);
  }

  return 0;
}

