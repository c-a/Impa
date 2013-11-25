#include <vector>
#include <utility>

#include "stdio.h"

using namespace std;

typedef unsigned long long ul;
typedef pair<ul,ul> ulp;
typedef vector<ulp> vulp;

static vulp
findFractions(int k) {
  vulp fractions;

  for (ul x = k+1; x*x <= k*(x+x); x++) {
    ul y = k*x / (x-k);
    if (x*y == k*(x+y))
      fractions.push_back(make_pair(y, x));
  }

  return fractions;
}

int main() {
  int k;

  while (scanf("%d", &k) == 1) {
    vulp fractions = findFractions(k);
    printf("%lu\n", fractions.size());
    for (vulp::iterator i = fractions.begin(); i != fractions.end(); ++i) {
      ulp& f = *i;
      printf("1/%d = 1/%llu + 1/%llu\n", k, f.first, f.second);
    }
  }
}

