#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct Point{
  int x, y;
  Point operator+(const Point& p) const {
    return {x + p.x, y + p.y};
  }
};

int main() {
  for (int caseN = 1;; ++caseN) {
    int N, M;
    cin >> N; if (N == 0) break;
    cin >> M;
    vector<string> names;
    cin.ignore(1e6, '\n');  
    for (int n = 0; n < N; ++n) {
      string name;
      std::getline(cin, name);
      names.push_back(name);
    }
    int D[22][22];
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) D[i][j] = 1e9;
      D[i][i] = 0;
    }
    for (int m = 0; m < M; ++m) {
      int i, j, k; cin >> i >> j >> k;
      --i, --j;
      D[i][j] = D[j][i] = k;
    }

    // Floyd-Warshall
    for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
        }
      }
    }

    int best = -1;
    int minSum;
    for (int i = 0; i < N; ++i) {
      int sum = 0;
      for (int j = 0; j < N; j++) sum += D[i][j];
      if (best == -1 || sum < minSum) {
        best = i; minSum = sum;
      }
    }
    cout << "Case #" << caseN << " : " << names[best] << "\n";
  }
}
