#include <cstdio>

using namespace std;


bool a[30];

int brute(int d, int length) {
  if (d == length) {
    for (int i = 2; i < length; i++) {
      if (a[i-2] == true && a[i-1] == true && a[i] == true)
        return 1;
    }
    return 0;
  }

  int sum;

  a[d] = true;
  sum = brute(d+1, length);
  a[d] = false;
  sum += brute(d+1, length);

  return sum;
}

int main() {
  int E[31][3], NC[31];

  E[0][0] = 0; E[0][1] = 0; E[0][2] = 0;
  E[1][0] = 1; E[1][1] = 1; E[1][2] = 0;
  E[2][0] = 2; E[2][1] = 1; E[2][2] = 1;
  NC[0] = 0; NC[1] = 2; NC[2] = 4;

  for (int i = 3; i <= 30; i++) {
    E[i][0] = E[i-1][0] + E[i-1][1] + E[i-1][2];
    E[i][1] = E[i-1][0];
    E[i][2] = E[i-1][1];

    NC[i] = 2*E[i-1][0] + 2*E[i-1][1] + E[i-1][2];
  }

  while (true) {
    int n;
    scanf("%d", &n);
    if (n == 0)
      break;
    printf("%d\n", (1 << n) - NC[n]);
  }

  return 0;
}

