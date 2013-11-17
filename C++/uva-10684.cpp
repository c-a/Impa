#include <algorithm>
#include <map>
#include <vector>
#include <limits>

#include <stdio.h>
#include <math.h>

using namespace std;

int
main(void)
{
  while (true) {
    int N;
    int max;

    scanf("%d", &N);
    if (N == 0)
      break;

    int prevStreak = 0;
    max = std::numeric_limits<int>::min();
    for (int n = 0; n < N; n++) {
      int v;
      scanf("%d", &v);
      int streak = std::max(0, prevStreak) + v;
      max = std::max(max, streak);
      prevStreak = streak;
    }

    if (max > 0)
      printf("The maximum winning streak is %d.\n", max);
    else
      printf("Losing streak.\n");
  }

  return 0;
}
