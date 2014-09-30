#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int Maximum1DSum(int A[100], int N) {
  int maxSum = -1e9;
  int sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += A[i];
    maxSum = std::max(maxSum, sum);
    if (sum < 0) sum = 0;
  }
  return maxSum;
}

int Maximum2DSum(int A[100][100], int N) {
  int rowSums[100];
  int maxSum = -1e9;
  for (int l = 0; l < N; ++l) {
    for (int i = 0; i < N; ++i) rowSums[i] = 0;
    for (int r = l; r < N; ++r) {
      for (int i = 0; i < N; ++i) rowSums[i] += A[i][r];
      maxSum = std::max(maxSum, Maximum1DSum(rowSums, N));
    }
  }
  return maxSum;
}

int main() {
  int N;
  int A[100][100];
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &A[i][j]);
    }
  }
  printf("%d\n", Maximum2DSum(A, N));
}
