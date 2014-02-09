#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <complex>

template<typename T>
struct DisjointSet
{
  T data;
  DisjointSet* parent;
  unsigned int rank;

  DisjointSet(T d): data(d), parent(0), rank(0) {};
};

template<typename T>
DisjointSet<T>*
setUnion(DisjointSet<T>* x, DisjointSet<T>* y) {
  DisjointSet<T> *xRoot, *yRoot;

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

template <typename T>
DisjointSet<T>*
setFind(DisjointSet<T>* x) {
  if (x->parent == 0)
    return x;

  return x->parent = setFind(x->parent);
}

typedef std::complex<double> point;

struct Edge
{
  int u, v;
  double dist;
  Edge(int u_, int v_, double dist_): u(u_), v(v_), dist(dist_) {};

  bool operator<(const Edge& other) const {
    return dist > other.dist;
  }
};

int main() {
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    int S, P;

    std::vector< DisjointSet<int> > outposts;
    std::vector<point> pos;

    scanf("%d %d", &S, &P);
    for (int p = 0; p < P; ++p) {
      int x, y;
      scanf ("%d %d", &x, &y);
      outposts.push_back(DisjointSet<int>(p));
      pos.push_back(std::complex<double>(x, y));
    }

    std::vector<Edge> edges;
    for (int i = 0; i < P; ++i) {
      for (int j = i + 1; j < P; ++j) {
        edges.push_back(Edge(i, j, std::abs(pos[i] - pos[j])));
      }
    }

    std::make_heap(edges.begin(), edges.end());
    int clusters = P;
    double maxEdge = 0.0;
    while (clusters > S) {
      std::pop_heap(edges.begin(), edges.end());
      Edge& e = edges.back();
      maxEdge = e.dist;
      if (setFind(&outposts[e.u]) != setFind(&outposts[e.v])) {
        setUnion(&outposts[e.u], &outposts[e.v]);
        clusters--;
      }

      edges.pop_back();
    }

    printf("%.2f\n", maxEdge);
  }

  return 0;
}
