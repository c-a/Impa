#include <algorithm>
#include <queue>
#include <set>
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
class Dijkstra
{
private:
  typedef typename Graph<T>::Edge Edge;

  struct NodeData
  {
    std::vector<const Edge*> edgesTo;
    T cost;
    bool visited;

    NodeData() : visited(false) {}
  };

  struct Elem
  {
    T cost;
    int node;

    Elem(const T& c, int n) : cost(c), node(n) {}

    bool operator>(const Elem& lhs) const {
      return cost > lhs.cost;
    }

    bool operator<(const Elem& lhs) const {
      return cost < lhs.cost;
    }
  };

public:

  Dijkstra(const Graph<T>& G, int start): start_(start), D_(G.N()) {
    compute(G);
  }

  std::vector<Edge> get_shortest_edges(int goal) {
    std::vector<Edge> edges;
    std::vector<bool> seen(D_.size(), false);
    std::queue<int> Q;
    Q.push(goal);
    seen[goal] = true;
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      for (const Edge* edge : D_[u].edgesTo) {
        edges.push_back(*edge);
        if (!seen[edge->from])
          Q.push(edge->from);
      }
    }
    return edges;
  }

  T get_cost(int goal) {
    return D_[goal].cost;
  }

  bool has_path(int goal) {
    return D_[goal].visited;
  }

private:
  int start_;
  std::vector<NodeData> D_;

  void compute(const Graph<T>& G) {
    std::priority_queue< Elem, std::vector<Elem>, std::greater<Elem> > Q;

    Q.push(Elem(T(), start_));
    while (!Q.empty()) {
      Elem cur = Q.top();
      Q.pop();

      if (D_[cur.node].visited)
        continue;

      for (auto i = G.adj(cur.node).begin(); i != G.adj(cur.node).end(); ++i) {
        const Edge& e = *i;

        if (D_[e.to].visited)
          continue;

        if (D_[e.to].edgesTo.size() == 0 ||
            cur.cost + e.cost < D_[e.to].cost) {
          D_[e.to].cost = cur.cost + e.cost;
          D_[e.to].edgesTo.clear();
          Q.push(Elem(D_[e.to].cost, e.to));
        }
        if (D_[e.to].edgesTo.size() == 0 ||
            cur.cost + e.cost <= D_[e.to].cost) {
            D_[e.to].edgesTo.push_back(&e);
        }
      }

      D_[cur.node].visited = true;
    }
  }
};

int main() {
  while (true) {
    int N, M;
    scanf("%d %d", &N, &M);
    if (N == 0 && M == 0)
      break;

    int S, D;
    scanf("%d %d", &S, &D);

    Graph<int> G(N);
    for (int m = 0; m < M; ++m) {
      int u, v, p;
      scanf("%d %d %d", &u, &v, &p);
      G.add_edge(u, v, p);
    }

    Dijkstra<int> di(G, S);
    std::set<int> short_edges;
    for (const auto& e : di.get_shortest_edges(D))
      short_edges.insert(e.index);

    Graph<int> G2(N);
    for (int u = 0; u < N; ++u) {
      for (const auto& e : G.adj(u)) {
        if (short_edges.find(e.index) == short_edges.end())
          G2.add_edge(e.from, e.to, e.cost);
      }
    }

    Dijkstra<int> di2(G2, S);
    int res = di2.has_path(D) ? di2.get_cost(D) : -1;
    printf("%d\n", res);
  }
}
