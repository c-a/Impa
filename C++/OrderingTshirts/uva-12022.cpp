
#include <cstdint>
#include <iostream>

int64_t comb(int n, int k) {
  int64_t res = 1;
  for (int i = 0; i < k; i++)
    res *= (n - i);
  for (int i = 0; i < k; i++)
    res /= (k - i);
  return res;
}

int64_t arrangements(int n) {
  if (n == 0)
    return 1;

  int64_t res = 0;
  for (int i = 1; i <= n; ++i) {
    res += comb(n, i) * arrangements(n-i);
  }
  return res;
}

int main() {
  int N;
  std::cin >> N;
  while (--N >= 0) {
    int64_t n;
    std::cin >> n;
    std::cout << arrangements(n) << "\n";
  }
}
