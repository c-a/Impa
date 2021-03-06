#include <cassert>
#include <list>
#include <limits>
#include <queue>
#include <vector>

#include "graph.h"

template<typename T>
class TopologicalSort
{
public:
  typedef std::list<int>::const_iterator const_iterator;

  TopologicalSort(const Graph<T>& G):
    nextIndex_(0),
    index(new int[G.N()]),
    visited(new bool[G.N()]())
  {
    for (int i = 0; i < G.N(); i++) {
      if (visited[i])
        continue;

      dfs(G, i);
    }
  }

  int get_index(int u) const {
    return index[u];
  }

  const_iterator begin() const {
    return stack_.begin();
  }

  const_iterator end() const {
    return stack_.end();
  }

private:
  int nextIndex_;
  int* index;
  bool* visited;
  std::list<int> stack_;

  void dfs(const Graph<T>& G, int u) {
    visited[u] = true;

    for (auto i = G.adj(u).begin(); i != G.adj(u).end(); ++i) {
      const typename Graph<T>::Edge& e  = *i;
      if (visited[e.to])
        continue;

      dfs(G, e.to);
    }
    index[u] = nextIndex_++;
    stack_.push_front(u);
  }
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
  Dijkstra() = default;

  void run(const Graph<T>& G, int start) {
    D_.assign(G.N(), NodeData());
    start_ = start;
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

  std::list<Edge> get_path(int goal) {
    std::list<Edge> path;
    for (int cur = goal; D_[cur].edgesTo.size() > 0; cur = D_[cur].edgesTo[0]->from)
      path.push_front(*D_[cur].edgesTo[0]);

    return path;
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

    D_[start_].cost = 0;
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

    // Check if we have a negative cycle
    for (int node = 0; node < G.N(); node++) {
      NodeData& nd = D_[node];
      if (!nd.found)
        continue;

      for (auto i = G.adj(node).begin(); i != G.adj(node).end(); ++i) {
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
};

int main() {
  Graph<int> G(4);

  G.add_edge(0, 1, 4);
  assert(G.adj(0).size() == 1);
  assert(G.adj(0)[0].from == 0);
  assert(G.adj(0)[0].to == 1);
  assert(G.edges().size() == 1);

  G.add_edge(1, 2, 2);
  assert(G.adj(1).size() == 1);
  assert(G.adj(1)[0].from == 1);
  assert(G.adj(1)[0].to == 2);
  assert(G.edges().size() == 2);
  
  G.add_edge(2, 3, 6);
  assert(G.adj(2).size() == 1);
  assert(G.adj(2)[0].from == 2);
  assert(G.adj(2)[0].to == 3);
  assert(G.edges().size() == 3);

  Dijkstra<int> di;
  di.run(G, 0);

  assert(di.get_cost(0) == 0);
  assert(di.get_cost(1) == 4);
  assert(di.get_cost(2) == 6);
  assert(di.get_cost(3) == 12);

  std::list< Graph<int>::Edge > path = di.get_path(3);
  auto iter = path.begin();
  assert(iter != path.end());
  assert((*iter).from == 0);
  assert((*iter).to == 1);

  std::vector< Graph<int>::Edge > shortest_edges = di.get_shortest_edges(3);
}
