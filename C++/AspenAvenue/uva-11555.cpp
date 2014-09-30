#include <algorithm>
#include <cstdio>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

double dist[1001][1001];
vector<int> trees;
double delta;
int w2;

double MinDist(int i, int j) {
  if (i < 0 || j < 0) return 0.0;
  double& d = dist[i][j];
  if (d != -1) return d;
  d = 1e9;
  int tree = i + j - 1;
  if (i >= 1) {
    double yi = std::abs(trees[tree] - delta * (i - 1));
    d = yi + MinDist(i - 1, j);
  }
  if (j >= 1) {
    double yj = std::abs(trees[tree] - delta * (j - 1));
    d = std::min(d, sqrt(w2 + yj*yj) + MinDist(i, j - 1));
  }
  return d;
}

int main() {
  int N;
  while (scanf("%d", &N) == 1) {
    if (N == 0) break;
    int L, W;
    scanf("%d %d", &L, &W);
    trees.resize(N);
    for (int i = 0; i < N; ++i) {
      int p; scanf("%d", &p);
      trees[i] = p;
    }
    std::sort(trees.begin(), trees.end());

    int rows = N / 2;
    delta = static_cast<double>(L) / (rows - 1);
    w2 = W*W;
    for (int i = 0; i <= rows; ++i) {
      for (int j = 0; j <= rows; ++j) dist[i][j] = -1;
    }
    dist[0][0] = 0.0;
    printf("%.10f\n", MinDist(rows, rows));
  }
}
