#include <algorithm>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <cstring>

std::vector<int> a;

bool subsetSum(int j, int sum) {
  if (sum == 0)
    return true;
  if (sum < 0 || j < 0)
    return false;

  return subsetSum(j - 1, sum - a[j]) || subsetSum(j - 1, sum);
}

bool dividable(std::vector<int> m) {
  int sum, replace;

  // Check if we have an even sum
  sum = m[1] + 2*m[2] + 3*m[3] + 4*m[4] + 5*m[5] + 6*m[6] + 20*m[20] + 60*m[60];
  if (sum % 2 == 1)
    return false;

  // Replace 2 ones with 1 two
  replace = std::max(0, m[1] - 1) / 2;
  m[1] -= replace*2;
  m[2] += replace;

  // Replace 2 twos with 1 four
  replace = std::max(0, m[2] - 1) / 2;
  m[2] -= replace*2;
  m[4] += replace;

  // Replace 2 threes with 1 six
  replace = std::max(0, m[3] - 1) / 2;
  m[3] -= replace*2;
  m[6] += replace;

  // Replace 5 fours with 1 twenty
  replace = std::max(0, m[4] - 4) / 5;
  m[4] -= replace*5;
  m[20] += replace;

  // Replace 4 fives with 1 twenty
  replace = std::max(0, m[5] - 3) / 4;
  m[5] -= replace*4;
  m[20] += replace;

  // Replace 10 sixes with one sixty
  replace = std::max(0, m[6] - 9) / 10;
  m[6] -= replace*10;
  m[60] += replace;

  // replace 3 twenties with one sixty
  replace = std::max(0, m[20] - 2) / 3;
  m[20] -= replace*3;
  m[60] += replace;

  // Remove sixties
  int rm = std::max(0, 60*m[60] - (20*m[20] + 6*m[6]  + 5*m[5] + 4*m[4] + 3*m[3] + 2*m[2] + m[1])) / 60;
  if (rm % 2 == 1)
    rm--;
  m[60] -= rm;

  // Create vector of elements
  a.clear();
  for (int i = 1; i < m.size(); i++) {
      for (int j = 0; j < m[i]; j++)
        a.push_back(i);
  }

  sum = m[1] + 2*m[2] + 3*m[3] + 4*m[4] + 5*m[5] + 6*m[6] + 20*m[20] + 60*m[60];
  return subsetSum(a.size()-1, sum/2);
}

int main() {
  std::vector<int> m;
  m.assign(61, 0);

  for (int caseN = 1;; caseN++) {
    scanf("%d %d %d %d %d %d", &m[1], &m[2], &m[3], &m[4], &m[5], &m[6]);
    if (m[1] + m[2] + m[3] + m[4] + m[5] + m[6] == 0)
      break;

      printf("Collection #%d:\n", caseN);
      if (dividable(m))
        printf("Can be divided.\n\n");
      else
        printf("Can't be divided.\n\n");
  }
}
