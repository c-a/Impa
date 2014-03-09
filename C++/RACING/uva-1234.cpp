#include <algorithm>
#include <vector>

template<typename T>
struct DisjointSet
{
  T data;
  DisjointSet* parent;
  unsigned int rank;

  DisjointSet(T d): data(d), parent(0), rank(0) {};
  DisjointSet(): parent(0), rank(0) {};
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

struct Road {
  int u, v;
  int cost;
  bool selected = false;

  Road(int u_, int v_, int c_) : u(u_), v(v_), cost(c_) {}
  bool operator<(const Road& other) const {
    return cost > other.cost;
  }
};

int main() {
  int c;
  scanf("%d", &c);
  while (--c >= 0) {
    int N, M;
    scanf("%d %d", &N, &M);
    std::vector<DisjointSet<int>> sets(N);
    std::vector<Road> roads;
    for (int m = 0; m < M; ++m) {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      --u; --v;
      roads.emplace_back(u, v, c);
    }

    // Run kruskal.
    std::sort(roads.begin(), roads.end());
    int clusters = N;
    for (int i = 0; clusters > 1 && i < roads.size(); ++i) {
      Road& r = roads[i];
      if (setFind(&sets[r.u]) != setFind(&sets[r.v])) {
        r.selected = true;
        setUnion(&sets[r.u], &sets[r.v]);
        clusters--;
      }
    }

    int total_cost = 0;
    for (const auto& r : roads) {
      if (!r.selected)
        total_cost += r.cost;
    }
    printf("%d\n", total_cost);
  }
}
