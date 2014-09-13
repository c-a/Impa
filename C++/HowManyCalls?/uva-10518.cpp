#include <iostream>
#include <array>
#include <cstdint>

using Matrix = std::array<std::array<int, 3>, 3>;
Matrix Mul(const Matrix& m1, const Matrix& m2, int b) {
  Matrix m;
  for (int i = 0; i < m1.size(); ++i) {
    for (int j = 0; j < m2.size(); ++j) {
      int res = 0;
      for (int k = 0; k < m1.size(); ++k) {
        res += m1[i][k] * m2[k][j];
      }
      m[i][j] = res % b;
    }
  }
  return m;
}

int nCalls(uint64_t n, int b) {
  if (n == 0) return 1 % b;
  if (n == 1) return 1 % b;

  Matrix twoPower = {{
    {1, 1, 1},
    {1, 0, 0},
    {0, 0, 1}
  }};
  Matrix m = {{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  }};
  --n;
  for (; n; n >>= 1) {
    if (n & 0x1) m = Mul(m, twoPower, b);
    twoPower = Mul(twoPower, twoPower, b);
  }
  return (m[0][0] + m[0][1] + m[0][2]) % b;
}

int main() {
  for (int caseN = 1;; ++caseN) {
    uint64_t n;
    int b;
    std::cin >> n >> b;
    if (n == 0 && b == 0) break;
    std::cout << "Case " << caseN << ": " << n << " " << b << " "
              << nCalls(n, b) << "\n";
  }
}

