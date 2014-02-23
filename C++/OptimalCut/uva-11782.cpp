#include <algorithm>
#include <cstdio>
#include <vector>

std::vector<int> weights;
std::vector<int> dp;
int H, K;

void read_weights(int n, int depth) {
  scanf("%d", &weights[n]);
  if (depth == H)
    return;

  read_weights(n*2+1, depth+1);
  read_weights(n*2+2, depth+1);
}

int opt_cut(int n, int depth, int k) {
  if (dp[n*K+(k-1)] != 1e9)
    return dp[n*K+(k-1)];

  int max = weights[n];
  if (depth < H) {
    for (int l = 1; (k-l) >= 1; ++l) {
      max = std::max(max,
          opt_cut(n*2+1, depth+1, l) + opt_cut(n*2+2, depth+1, k-l));
    }
  }

  return dp[n*K+(k-1)] = max;
}

int main() {
  while (true) {
    scanf("%d", &H);
    if (H == -1)
      break;
    scanf("%d", &K);

    int n_nodes = (1 << (H+1)) - 1;

    weights.resize(n_nodes);
    read_weights(0, 0);

    dp.assign(K*n_nodes, 1e9);
    printf("%d\n", opt_cut(0, 0, K));
  }
  return 0;
}

