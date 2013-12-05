#include <iostream>
#include <string>
#include <cstdio>

int main()
{

  while (true) {
    int n;

    bool* s1 = new bool[500*500];
    bool* s2 = new bool[500*500];

    bool* d1 = new bool[500*500];
    bool* d2 = new bool[500*500];

#define S1(i,j) (*(s1 + (i)*n + (j)))
#define S2(i,j) (*(s2 + (i)*n + (j)))

#define D1(i,j) (*(d1 + (i)*n + (j)))
#define D2(i,j) (*(d2 + (i)*n + (j)))

    if (!(std::cin >> n))
      break;

    for (int i = 0; i < n; i++) {
      std::string line;

      std::cin >> line;
      for (size_t j = 0; j < line.length(); j++) {
        D1(i,j) = S1(i,j) = line[j] == 'x' ? true : false;
        D2(i,j) = S2(i,j) = false;
      }
    }

    int squares = 0, diamonds = 0;
    for (int size = 2; size <= n; size++) {

      // Square
      for (int i = 0; i <= n - size; i++) {
        for (int j = 0; j <= n - size; j++) {
          S2(i,j) = S1(i,j) && S1(i+1,j) && S1(i,j+1) && S1(i+1,j+1);
          if (S2(i,j))
            squares++;
        }
      }

      bool* t;

      t = s1;
      s1 = s2;
      s2 = t;

      // Diamond
      if (size % 2 == 1) {
        int mid = size / 2;
        for (int i = mid; i <= n - (mid+1); i++) {
          for (int j = mid; j <= n - (mid+1); j++) {
            D2(i,j) = D1(i,j) && D1(i-1,j) && D1(i+1,j) && D1(i,j-1) && D1(i,j+1);
            if (D2(i,j))
              diamonds++;
          }
        }

        t = d1;
        d1 = d2;
        d2 = t;
      }
    }

    printf("%d\n", squares + diamonds);
  }

  return 0;
}
