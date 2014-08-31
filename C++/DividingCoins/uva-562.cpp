#include <vector>
#include <string>
#include <iostream>

static const size_t kMaxSize = 101 * (500 * 101);
std::vector<int> coins;
std::vector<bool> dp;

int main() {
  int n;
  std::cin >> n;
  coins.resize(100);
  dp.resize(kMaxSize);
  while (--n >= 0) {
    int m;
    std::cin >> m;
    int sum = 0;
    for (int i = 0; i < m; ++i) {
      std::cin >> coins[i];
      sum += coins[i];
    }
    int half = sum / 2;
    #define DP(i, j) dp[((i)*(half+1) + j)]
    for (int j = 0; j <= half; ++j) DP(0, j) = false;
    for (int i = 0; i <= m; ++i) DP(i, 0) = true;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= half; ++j) {
        DP(i, j) = DP(i-1, j);
        int jIndex = j - coins[i-1];
        if (jIndex >= 0 && DP(i-1, jIndex)) {
          DP(i, j) = true;
        }
      }
    }

    int max = 0;
    for (int j = half; j >= 0; --j) {
      if (DP(m, j)) {
        max = j; break;
      }
    }
    std::cout << std::abs(sum - 2*max) << "\n"; 
  }
  return 0;
}

