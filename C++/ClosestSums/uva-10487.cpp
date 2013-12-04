#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cstdio>

typedef std::vector<int> vi;

int main() {
  for (int caseN = 1;; caseN++) {
    int n, m;
    vi nums;

    scanf("%d", &n);
    if (n == 0)
      break;

    nums.resize(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &nums[i]);
    sort(nums.begin(), nums.end());

    printf("Case %d:\n", caseN);

    scanf("%d", &m);
    while (m-- > 0) {
      int val, best_diff, best, l, r;

      scanf("%d", &val);

      l = 0;
      r = n - 1;
      best_diff = 1e9;
      while (l < r) {
        int sum = nums[l] + nums[r];
        int diff = std::abs(val - sum);
        if (diff < best_diff) {
          best_diff = diff;
          best = sum;
        }
        if (sum < val)
          l++;
        else
          r--;
      }

      printf("Closest sum to %d is %d.\n", val, best);
    }
  }
}

