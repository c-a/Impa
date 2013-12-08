#include <cassert>
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

    for (typename std::vector<typename Graph<T>::Edge>::const_iterator i = G.adj(u).begin();
         i != G.adj(u).end(); ++i) {
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
    const Edge* edgeTo;
    T cost;
    bool visited;

    NodeData() : edgeTo(0), visited(false) {}
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

  T get_cost(int goal) {
    return D_[goal].cost;
  }

private:
  int start_;
  std::vector<NodeData> D_;

  void compute(const Graph<T>& G) {
    typedef typename std::vector<Edge> vge;

    std::priority_queue< Elem, std::vector<Elem>, std::greater<Elem> > Q;

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

        if (D_[e.to].edgeTo == 0 ||
            cur.cost + e.cost < D_[e.to].cost) {
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
  Graph<int> G(4);

  G.add_edge(0, 1, 4);
  assert(G.adj(0).size() == 1);
  assert(G.adj(0)[0].from == 0);
  assert(G.adj(0)[0].to == 1);

  G.add_edge(1, 2, 2);
  assert(G.adj(1).size() == 1);
  assert(G.adj(1)[0].from == 1);
  assert(G.adj(1)[0].to == 2);
  
  G.add_edge(2, 3, 6);
  assert(G.adj(2).size() == 1);
  assert(G.adj(2)[0].from == 2);
  assert(G.adj(2)[0].to == 3);

  Dijkstra<int> di(G, 0);

  assert(di.get_cost(0) == 0);
  assert(di.get_cost(1) == 4);
  assert(di.get_cost(2) == 6);
  assert(di.get_cost(3) == 12);

  std::list< Graph<int>::Edge > path = di.get_path(3);
  std::list< Graph<int>::Edge >::const_iterator iter = path.begin();
  assert(iter != path.end());
  assert((*iter).from == 0);
  assert((*iter).to == 1);
}
