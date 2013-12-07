#include <bitset>
#include <cstdio>
#include <cstring>
#include <utility>

typedef std::pair<int, int> ii;

static int gcd(int a, int b) {
  while (b != 0) {
    int t = a % b;
    a = b;
    b = t;
  }

  return a;
}

static std::bitset<1000001> nums;

static ii
calc(int N) {

  nums.reset();

  int primTriples = 0;
  for (int n = 1;; n++) {
    int m = n + 1;
    if (n*n + m*m > N)
      break;

    for (;; m++) {
      if (m*m + n*n > N)
        break;

      if (((m - n) & 0x1) != 1 || gcd(n, m) != 1)
        continue;

      primTriples++;

      for (int k = 1;; k++) {
        int c = k*(m*m + n*n);
        if (c > N)
          break;

        int a = k*(m*m - n*n);
        int b = k*(2*m*n);

        nums[a] = nums[b] = nums[c] = true;
      }
    }
  }

  int notInTriple = 0;
  for (int i = 1; i <= N; i++)
    if (!nums[i]) notInTriple++;

  return std::make_pair(primTriples, notInTriple) ;
}

int main()
{
  int N;

  while (scanf("%d", &N) == 1) {
    ii res = calc(N);
    printf("%d %d\n", res.first, res.second);
  }

  return 0;
}
