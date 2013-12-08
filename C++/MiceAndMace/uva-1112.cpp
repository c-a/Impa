#include <cassert>
#include <cstdio>
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
    bool found;
    const Edge* edgeTo;
    T cost;
    bool visited;

    NodeData(): found(false), edgeTo(0), visited(false) {}
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

  std::list<Edge> get_path(int goal) {
    std::list<Edge> path;
    for (int cur = goal; D_[cur].edgeTo != 0; cur = D_[cur].edgeTo->from)
      path.push_front(*D_[cur].edgeTo);

    return path;
  }

  bool path_exists(int goal) {
    return D_[goal].found;
  }

  T get_cost(int goal) {
    return D_[goal].cost;
  }

private:
  int start_;
  std::vector<NodeData> D_;

  void compute(const Graph<T>& G) {
    typedef typename std::vector<Edge> vge;

    std::priority_queue< Elem, std::vector<Elem>, std::greater<Elem> > Q;

    D_[start_].found = true;
    Q.push(Elem(T(), start_));
    while (!Q.empty()) {
      Elem cur = Q.top();
      Q.pop();

      if (D_[cur.node].visited)
        continue;

      for (typename vge::const_iterator i = G.adj(cur.node).begin();
           i != G.adj(cur.node).end(); ++i) {
        const Edge& e = *i;

        if (D_[e.to].visited)
          continue;

        if (!D_[e.to].found || cur.cost + e.cost < D_[e.to].cost) {
          D_[e.to].found = true;
          D_[e.to].cost = cur.cost + e.cost;
          D_[e.to].edgeTo = &e;
          Q.push(Elem(D_[e.to].cost, e.to));
        }
      }

      D_[cur.node].visited = true;
    }
  }
};

int main() {
  int nCases;

  scanf("%d", &nCases);
  while (nCases--) {
    int N, E, T, M;

    scanf("%d %d %d %d", &N, &E, &T, &M);

    // Create the graph in reverse to compute shortest distance from exit
    // to all other nodes.
    Graph<int> G(N+1);
    for (int m = 0; m < M; m++) {
      int a, b, t;
      scanf("%d %d %d", &a, &b, &t);
      G.add_edge(b, a, t);
    }

    Dijkstra<int> di(G, E);
    int nMice = 0;
    for (int i = 1; i <= N; i++) {
      if (di.path_exists(i) && di.get_cost(i) <= T)
        nMice++;
    }

    printf("%d\n", nMice);
    if (nCases)
      printf("\n");
  }
  return 0;
}

