#include <cstdio>
#include <cmath>
#include <vector>

template<typename T>
T determinant(std::vector<std::vector<T>> a) {
  int m = a.size();
  // Forward elimination.
  for (int k = 0; k < m; ++k) {
    // Find pivot for column k.
    int i_max = k; T max = a[k][k];
    for (int i = k + 1; i < m; ++i) {
      if (a[i][k] > max) {
        i_max = i;
        max = a[i][k];
      }
    }
    // Swap row k and i_max;
    std::swap(a[k], a[i_max]);

    // Forward eliminiation.
    for (int i = k + 1; i < m; ++i) {
      for (int j = k + 1; j < m; ++j) {
        a[i][j] -= (a[k][j] * a[i][k]) / a[k][k];
      }
      a[i][k] = 0;
    }
  }
  T res = a[0][0];
  for (int k = 1; k < m; ++k) {
    res *= a[k][k];
  }
  return res;
}

// Uses Kirchhoff's theorem to calculate the number of spanning trees in a
// graph.
int main() {
  while (true) {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) break;
    if (n == 1) {
      printf("1\n");
      continue;
    }
    // Create laplace matrix.
    std::vector<std::vector<long double>> a;
    a.assign(n, std::vector<long double>(n, -1));
    while (--m >= 0) {
      int i, j;
      scanf("%d %d", &i, &j);
      a[i-1][j-1] = 0.0;
      a[j-1][i-1] = 0.0;
    }
    // Set a[i][i] to deg(i).
    for (int i = 0; i < n; ++i) {
      int deg = 0;
      for (int j = 0; j < n; ++j) {
        if (i != j && a[i][j] == -1) deg++;
      }
      a[i][i] = deg;
    }

    // Create q from a by removing row 0 and column 0.
    std::vector<std::vector<long double>> q;
    q.assign(n - 1, std::vector<long double>(n - 1));
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < n; ++j) {
        q[i-1][j-1] = a[i][j];
      }
    }
    printf("%lld\n", (long long int)roundl(determinant(q)));
  }
}
