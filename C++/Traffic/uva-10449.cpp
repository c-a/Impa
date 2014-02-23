#include <algorithm>
#include <cstdio>
#include <list>
#include <queue>
#include <stack>
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

  Graph(int N): adj_(N), edgeIndex_(0) {}

  int add_edge(int from, int to, T cost) {
    adj_[from].push_back(Edge(edgeIndex_++, from, to, cost));
    return edgeIndex_;
  }

  int N() const {
    return adj_.size();
  }
  
  const std::vector<Edge>& adj(int n) const {
    return adj_[n];
  }

  std::vector<Edge> edges() const {
  	std::vector<Edge> edges;
  	auto back_insert_iter = std::back_insert_iterator< std::vector<Edge> >(edges);
  	for (int n = 0; n < N(); n++) {
  		std::copy(adj_[n].begin(), adj_[n].end(), back_insert_iter);
  	}
  	return edges;
  }

  void clear() {
    for (int i = 0; i < N(); i++)
      adj_[i].clear();
    edgeIndex_ = 0;
  }

private:
  std::vector< std::vector<Edge> > adj_;
  int edgeIndex_;
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

  bool has_path(int goal) {
    return D_[goal].found;
  }

  T get_cost(int goal) {
    return D_[goal].cost;
  }

  bool has_negative_cycle() {
    return has_negative_cycle_;
  }

private:
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

    // Run N-1 passes more where we set the new distance
    // to -1e9 if the distance to the node could still be reduced.
    // This way all nodes which are reachable from, a negative cycle that is
    // reachable from the source, will have their distance set to -1e9.
    for (int pass = 0; pass < G.N() - 1; pass++) {
      for (int node = 0; node < G.N(); node++)
        relax2(G, node);
    }
  }

  void relax(const Graph<T>& G, int node) {

    NodeData& nd = D_[node];

    if (!nd.found)
      return;

    for (auto i = G.adj(node).begin(); i != G.adj(node).end(); ++i) {
      const Edge& e = *i;

      if (!D_[e.to].found ||
          nd.cost + e.cost < D_[e.to].cost) {
        D_[e.to].cost = D_[node].cost + e.cost;
        D_[e.to].found = true;
        D_[e.to].edgeTo = &e;
      }
    }
  }
  void relax2(const Graph<T>& G, int node) {

    NodeData& nd = D_[node];

    if (!nd.found)
      return;

    for (auto i = G.adj(node).begin(); i != G.adj(node).end(); ++i) {
      const Edge& e = *i;

      if (!D_[e.to].found ||
          nd.cost + e.cost < D_[e.to].cost) {
        D_[e.to].cost = -1e9;
        D_[e.to].found = true;
        D_[e.to].edgeTo = &e;
      }
    }
  }
};

int main() {
  int N;

  for (int setN = 1; scanf("%d", &N) == 1; ++setN) {
    std::vector<int> busyness(N);
    for (int n = 0; n < N; ++n)
      scanf("%d", &busyness[n]);

    Graph<int> G(N);

    int R;
    scanf("%d", &R);
    for (int r = 0; r < R; ++r) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u; --v;
      int cost = busyness[v] - busyness[u];
      cost = cost*cost*cost;
      G.add_edge(u, v, cost);
    }

    int Q;
    scanf("%d", &Q);

    BellmanFord<int> bf(G, 0);
    printf("Set #%d\n", setN);
    for (int q = 0; q < Q; ++q) {
      int u;
      scanf("%d", &u);
      --u;
      if (u >= N || !bf.has_path(u) || bf.get_cost(u) < 3)
        printf("?\n");
      else
        printf("%d\n", bf.get_cost(u));
    }
  }
  return 0;
}
