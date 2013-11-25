#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

#include "stdio.h"

using namespace std;

static int pos[8];
static int curr[8];

static int solve(int depth) {
  if (depth == 8)
    return 0;

  int best = 1e9;
  for (int i = depth; i < 8; i++) {
    int newPos = curr[i];

    // check if position is valid.
    bool valid = true;
    for (int l = depth - 1; l >= 0; l--) {
        if (curr[l] == newPos + (depth - l) ||
        curr[l] == newPos - (depth - l))
        valid = false;
    }
    if (!valid)
      continue;

    swap(curr[depth], curr[i]);
    int cost = (pos[depth] - newPos) == 0 ? 0 : 1; 
    best = std::min(best, cost + solve(depth+1));
    swap(curr[depth], curr[i]);
  }

  return best;
}

int main() {
  for (int caseN = 1;; caseN++) {
    for (int i = 0; i < 8; i++) {
      if (scanf("%d", &pos[i]) != 1)
        return 0;
      pos[i]--;
      curr[i] = i;
    }

    printf("Case %d: %d\n", caseN, solve(0));
  }

  return 0;
}

