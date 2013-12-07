#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <limits>
#include <queue>
#include <vector>

template<typename T>
class Graph
{
public:

  struct Edge
  {
    int index;
    int from, to;
    T cost;

    Edge(int i, int f, int t, T& w): index(i), from(f), to(t), cost(w) {}
  };

  Graph(int N): adj_(N) {}

  void add_edge(int index, int from, int to, T cost) {
    adj_[from].push_back(Edge(index, from, to, cost));
  }

  int N() const {
    return adj_.size();
  }
  
  const std::vector<Edge>& adj(int n) const {
    return adj_[n];
  }

private:
  std::vector< std::vector<Edge> > adj_;
};

template<typename T>
class BellmanFord
{
private:
  typedef typename Graph<T>::Edge Edge;

  struct NodeData
  {
    bool found;
    T cost;
    const Edge* edgeTo;

    NodeData() : found(false), edgeTo(0) {}
  };

public:

  BellmanFord(const Graph<T>& G, int start):
    start_(start),
    D_(G.N()),
    has_negative_cycle_(false)
  {
    compute(G);
  }

  std::list<Edge> get_path(int goal) {
    std::list<Edge> path;
    for (int cur = goal; D_[cur].edgeTo != 0; cur = D_[cur].edgeTo->from)
      path.push_front(*D_[cur].edgeTo);

    return path;
  }

  T get_cost(int goal) {
    return D_[goal].cost;
  }

  bool has_negative_cycle() {
    return has_negative_cycle_;
  }

private:
  typedef typename std::vector<Edge> vge;

  int start_;
  std::vector<NodeData> D_;
  bool has_negative_cycle_;

  void compute(const Graph<T>& G) {

    D_[start_].cost = 0;
    D_[start_].found = true;

    for (int pass = 0; pass < G.N() - 1; pass++) {
      for (int node = 0; node < G.N(); node++)
        relax(G, node);
    }

    // Check if we have a negative cycle
    for (int node = 0; node < G.N(); node++) {
      NodeData& nd = D_[node];
      if (!nd.found)
        continue;

      for (typename vge::const_iterator i = G.adj(node).begin(); i != G.adj(node).end(); ++i) {
        const Edge& e = *i;

        if (nd.cost + e.cost < D_[e.to].cost) {
          has_negative_cycle_ = true;
          return;
        }
      }
    }
  }

  void relax(const Graph<T>& G, int node) {

    NodeData& nd = D_[node];

    if (!nd.found)
      return;

    for (typename vge::const_iterator i = G.adj(node).begin(); i != G.adj(node).end(); ++i) {
      const Edge& e = *i;

      if (!D_[e.to].found ||
          nd.cost + e.cost < D_[e.to].cost) {
        D_[e.to].cost = D_[node].cost + e.cost;
        D_[e.to].found = true;
        D_[e.to].edgeTo = &e;
      }
    }
  }
};

int main()
{
  int nCases;

  scanf("%d", &nCases);
  while (nCases-- > 0) {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph<int> G(n+1);

    // Read wormholes
    for (int i = 0; i < m; i++) {
      int x, y, t;
      scanf("%d %d %d", &x, &y, &t);
      G.add_edge(0, x, y, t);
    }

    // Add zero cost edges from node n to all other nodes
    for (int i = 0; i < n; i++)
      G.add_edge(0, n, i, 0);

    BellmanFord<int> bf(G, n);

    if (bf.has_negative_cycle())
      printf("possible\n");
    else
      printf("not possible\n");
  }

  return 0;
}
