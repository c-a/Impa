#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

static long long bin[201][11];

static void
calc_bin()
{
  for (int i = 0; i < 201; i++) {
    bin[i][0] = 1;

    for (int j = 1; j < std::min(i, 11); j++)
      bin[i][j] = bin[i-1][j-1] + bin[i-1][j];

    if (i < 11)
      bin[i][i] = 1;
  }
}

static int D;
static int M;
static int mods[20];

long long dp[20][11][20];

static long long searchm(int pos, int left, int sum);

static long long search(int pos, int left, int sum) {
  if (left == 0)
    return sum == 0;
  else if (pos >= D)
    return 0;

  long long res = 0;
  for (int i = 0; i <= std::min(left, mods[pos]); ++i) {
    res += bin[mods[pos]][i] * searchm(pos + 1, left - i, (sum + i*pos) % D);
  }

  return res;
}

static long long searchm(int pos, int left, int sum) {
  if (dp[pos][left][sum] == -1)
    dp[pos][left][sum] = search(pos, left, sum);

  return dp[pos][left][sum];
}

int main() {
  calc_bin();

  for (int setN = 1;; ++setN) {
    int N, Q;
    int numbers[200];

    scanf("%d %d", &N, &Q);
    if (N == 0 && Q == 0)
      break;

    for (int i = 0; i < N; i++)
      scanf("%d", &numbers[i]);

    printf("SET %d:\n", setN);
    for (int queryN = 1; queryN <= Q; ++queryN) {
      scanf("%d %d", &D, &M);
      memset(mods, 0, D*sizeof(int));
      for (int i = 0; i < N; ++i)
        mods[(numbers[i] % D + D) % D]++;

      for (int i = 0; i < 20*11*20; ++i)
        *((long long*)dp + i) = -1;

      printf("QUERY %d: %lld\n", queryN, searchm(0, M, 0));
    }
  }

  return 0;
}
