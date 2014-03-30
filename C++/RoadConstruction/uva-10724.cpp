
#include <complex>
#include <cstdint>
#include <cstring>
#include <vector>

#define eps 1e-8

int main() {
  bool B[50][50];
  double D[50][50];
  while (true) {
    int N, M;
    scanf("%d %d", &N, &M);
    if (N == 0 && M == 0) break;

    std::vector<std::complex<double>> No;
    for (int n = 0; n < N; ++n) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      No.emplace_back(x, y);
    }

    for (int i = 0; i < 50; ++i) {
      for (int j = 0; j < 50; ++j) {
        D[i][j] = 1e99;
        B[i][j] = false;
      }
      D[i][i] = 0.0;
      B[i][i] = true;
    }

    for (int m = 0; m < M; ++m) {
      int u, v;
      if (scanf("%d %d", &u, &v) != 2)
        break;
      --u; --v;
      B[u][v] = B[v][u] = true;
      D[u][v] = D[v][u] = std::abs(No[v] - No[u]);
    }

    for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
        }
      }
    }

    double C_max = 0.0;
    std::pair<int, int> max_road;
    for (int u = 0; u < N; ++u) {
      for (int v = u + 1; v < N; ++v) {
        if (B[u][v]) continue;

        double C = 0.0;
        double dist = std::abs(No[u] - No[v]);
        for (int i = 0; i < N; ++i) {
          for (int j = i + 1; j < N; ++j) {
            double t = D[i][j];
            t = std::min(t, D[i][u] + dist + D[v][j]);
            t = std::min(t, D[i][v] + dist + D[u][j]);
            C += D[i][j] - t;
          }
        }
        if (C > C_max+eps ||
          (fabs(C-C_max) < eps &&
            dist < std::abs(No[max_road.first] - No[max_road.second])-eps)) {
          C_max = C;
          max_road = std::make_pair(u, v);
        }
      }
    }

    if (C_max > 1.0+eps)
      printf("%d %d\n", max_road.first+1, max_road.second+1);
    else
      printf("No road required\n");
  } 
}
