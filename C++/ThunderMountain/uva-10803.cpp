#include <cstdio>
#include <complex>
#include <vector>
#include <limits>

using Point = std::complex<double>;

int main() {
  int N;
  scanf("%d", &N);
  double D[101][101];
  for (int caseN = 1; caseN <= N; ++caseN) {
    int n;
    scanf("%d", &n);
    std::vector<Point> towns;
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      towns.push_back(Point(x, y));
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        double dist = std::abs(towns[i] - towns[j]);
        if ((dist > 10.0)) {
          dist = std::numeric_limits<double>::infinity();
        }
        D[i][j] = dist;
        D[j][i] = dist;
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
        }
      }
    }
    double max = -1;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        max = std::max(max, D[i][j]);
      }
    }
    printf("Case #%d:\n", caseN);
    if (max == std::numeric_limits<double>::infinity()) {
      printf("Send Kurdy\n\n");
    } else {
      printf("%.4f\n\n", max);
    }
  }
}

