#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

static bool play(int a, int b) {
  int small = std::min(a,b);
  int large = std::max(a,b);

  int mod = large % small;
  if (mod == 0)
    return true;

  if (large / small >= 2)
    return true;

  if (!play(mod, small))
    return true;

  return false;
}

int main() {
  while (true) {
    int a, b;

    scanf("%d %d", &a, &b);
    if (a == 0 && b == 0)
      break;

    if (play(a, b))
      printf("Stan wins\n");
    else
      printf("Ollie wins\n");
  }
  return 0;
}

