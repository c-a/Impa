#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <complex>

struct DisjointSet
{
  DisjointSet* parent;
  unsigned int rank;

  DisjointSet(): parent(0), rank(0) {};
};

DisjointSet*
setFind(DisjointSet* x) {
  if (x->parent == 0)
    return x;

  return x->parent = setFind(x->parent);
}

DisjointSet*
setUnion(DisjointSet* x, DisjointSet* y) {
  DisjointSet *xRoot, *yRoot;

  xRoot = setFind(x);
  yRoot = setFind(y);
  if (xRoot == yRoot)
    return xRoot;

  if (xRoot->rank < yRoot->rank) {
    xRoot->parent = yRoot;
    return yRoot;
  }
  else if (yRoot->rank < xRoot->rank) {
    yRoot->parent = xRoot;
    return xRoot;
  }
  else {
    yRoot->parent = xRoot;
    xRoot->rank++;
    return xRoot;
  }
}

struct Edge
{
  int u, v;
  int c;
  Edge(int u_, int v_, int c_): u(u_), v(v_), c(c_) {};

  bool operator<(const Edge& other) const {
    return c < other.c;
  }
};

int main() {
  int N;
  scanf("%d", &N);
  for (int caseN = 1; caseN <= N; ++caseN) {

    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<DisjointSet> cross(n);
    std::vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
      int u, v, c;
      scanf ("%d %d %d", &u, &v, &c);
      edges.push_back(Edge(u, v, c));
    }

    std::make_heap(edges.begin(), edges.end());
    int clusters = n;
    int minRoad = 1e7;
    while (clusters > 1) {
      std::pop_heap(edges.begin(), edges.end());
      Edge& e = edges.back();
      minRoad = e.c;
      if (setFind(&cross[e.u]) != setFind(&cross[e.v])) {
        setUnion(&cross[e.u], &cross[e.v]);
        clusters--;
      }

      edges.pop_back();
    }

    printf("Case #%d: %d\n", caseN, minRoad);
  }

  return 0;
}
