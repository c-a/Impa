#include <algorithm>
#include <map>
#include <vector>
#include <limits>

#include <stdio.h>
#include <math.h>

using namespace std;

static int
max_segment_tree_build(int tree[], int counts[], int node, int l, int r)
{
  if (l == r)
    tree[node] = counts[l];
  else {

    int middle = l + (r - l) / 2;

    int lm = max_segment_tree_build(tree, counts, 2*node+1, l, middle);
    int rm = max_segment_tree_build(tree, counts, 2*node+2, middle+1, r);

    tree[node] = std::max(lm, rm);
  }

  return tree[node];
}

int
max_segment_tree_get(int tree[], int node, int l, int r, int sl, int sr)
{
  if (sl <= l && sr >= r)
    return tree[node];

  int middle = l + (r - l) / 2;
  if (sr <= middle)
    return max_segment_tree_get(tree, 2*node+1, l, middle, sl, sr);
  else if (sl > middle)
    return max_segment_tree_get(tree, 2*node+2, middle+1, r, sl, sr);
  else
    return std::max(max_segment_tree_get(tree, 2*node+1, l, middle, sl, sr),
                    max_segment_tree_get(tree, 2*node+2, middle+1, r, sl, sr));
}

int
main(void)
{
  while (true) {
    int N, Q;
    int starts[100000];
    int counts[100000];
    int toCount[100000];
    int mstree[2<<17];

    scanf("%d", &N);
    if (N == 0)
      break;

    scanf("%d", &Q);

    int start = 0;
    int count = 0;
    int cntIdx = 0;
    int prev = std::numeric_limits<int>::min();
    for (int n = 0; n < N; n++) {
      int a;
      scanf("%d", &a);

      if (prev == std::numeric_limits<int>::min())
        prev = a;
      else if (a != prev) {
        counts[cntIdx++] = count;
        count = 0;
        prev = a;
        start = n;
      }

      count++;
      toCount[n] = cntIdx;
      starts[n] = start;
    }
    if (count > 0) {
      counts[cntIdx++] = count;
    }

    max_segment_tree_build (mstree, counts, 0, 0, cntIdx-1);

    for (int q = 0; q < Q; q++) {
      int i, j;

      scanf("%d %d", &i, &j);
      i--; j--;

      int max;
      if (starts[i] == starts[j])
        max = j - i + 1;
      else {
        int lc = counts[toCount[i]] - (i - starts[i]);
        int rc = j - starts[j] + 1;
        max = std::max(lc, rc);

        int sl = toCount[starts[i] + counts[toCount[i]]];
        int sr = toCount[starts[j]] - 1;
        if (sl <= sr)
          max = std::max(max, max_segment_tree_get(mstree, 0, 0, cntIdx-1, sl, sr));
      }

      printf("%d\n", max);
    }
  }

  return 0;
}
