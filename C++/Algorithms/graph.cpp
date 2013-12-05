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

  std::vector< std::vector<Edge> > adj_;
};

template<typename T>
struct Elem
{
  T cost;
  int node;

  Elem(const T& c, int n) : cost(c), node(n) {}

  bool operator>(const Elem<T>& lhs) const {
    return this->cost > lhs.cost;
  }

  bool operator<(const Elem<T>& lhs) const {
    return this->cost < lhs.cost;
  }

};

template<typename T>
struct NodeData
{
  const typename Graph<T>::Edge* edgeTo;
  T totalcost;
  bool visited;

  NodeData() : edgeTo(0), visited(false) {}
};

template<typename T>
class ShortestPath
{
private:
    typedef typename Graph<T>::Edge Edge;

public:

  ShortestPath(const Graph<T>& G, int start): G_(G), start_(start), D_(G.N()) {
    compute();
  }

  std::list<Edge> get_path(int goal) {
    std::list<Edge> path;
    for (int cur = goal; D_[cur].edgeTo != 0; cur = D_[cur].edgeTo->from)
      path.push_front(*D_[cur].edgeTo);

    return path;
  }

  T get_cost(int goal) {
    return D_[goal].totalcost;
  }

private:
  Graph<T> G_;
  int start_;
  std::vector< NodeData<T> > D_;

  void compute() {
    typedef typename std::vector<Edge> vge;

    std::priority_queue< Elem<T>, std::vector< Elem<T> >, std::greater< Elem<T> > > Q;

    D_[start_].totalcost = 0;
    Q.push(Elem<T>(0, start_));
    while (!Q.empty()) {
      Elem<T> cur = Q.top();
      Q.pop();

      if (D_[cur.node].visited)
        continue;

      for (typename vge::const_iterator i = G_.adj(cur.node).begin();
           i != G_.adj(cur.node).end(); ++i) {
        const Edge& e = *i;

        if (D_[e.to].visited)
          continue;

        if (D_[e.to].edgeTo == 0 ||
            cur.cost + e.cost < D_[e.to].totalcost) {
          D_[e.to].totalcost = cur.cost + e.cost;
          D_[e.to].edgeTo = &e;
          Q.push(Elem<T>(D_[e.to].totalcost, e.to));
        }
      }

      D_[cur.node].visited = true;
    }
  }
};

int main() {
  Graph<int> G(4);

  G.add_edge(0, 0, 1, 4);
  assert(G.adj(0).size() == 1);
  assert(G.adj(0)[0].from == 0);
  assert(G.adj(0)[0].to == 1);

  G.add_edge(1, 1, 2, 2);
  assert(G.adj(1).size() == 1);
  assert(G.adj(1)[0].from == 1);
  assert(G.adj(1)[0].to == 2);
  
  G.add_edge(2, 2, 3, 6);
  assert(G.adj(2).size() == 1);
  assert(G.adj(2)[0].from == 2);
  assert(G.adj(2)[0].to == 3);

  ShortestPath<int> sp(G, 0);

  assert(sp.get_cost(0) == 0);
  assert(sp.get_cost(1) == 4);
  assert(sp.get_cost(2) == 6);
  assert(sp.get_cost(3) == 12);

  std::list< Graph<int>::Edge > path = sp.get_path(3);
  std::list< Graph<int>::Edge >::const_iterator iter = path.begin();
  assert(iter != path.end());
  assert((*iter).from == 0);
  assert((*iter).to == 1);
}
