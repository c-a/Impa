#include "stdio.h"

bool win(int curr, int n) {

  if (2*curr >= n || 9*curr >= n)
    return true;

  if (!win(2*curr, n) || !win(9*curr, n))
    return true;

  return false;
}

int main() {
  int n;

  while (scanf("%d", &n) == 1) {
    if (win(1, n))
      printf("Stan wins.\n");
    else
      printf("Ollie wins.\n");
  }
}

