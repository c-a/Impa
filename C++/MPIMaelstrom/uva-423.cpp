#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <limits>

#include <cstdlib>
#include <cstdio>
#include <cstring>

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

  void addEdge(int index, int from, int to, T cost) {
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

  std::list<Edge> shortest_path(int goal) {
    std::list<Edge> path;
    for (int cur = goal; D_[cur].edgeTo != 0; cur = D_[cur].edgeTo->from)
      path.push_front(*D_[cur].edgeTo);

    return path;
  }

  T getCost(int goal) {
    return D_[goal].totalcost;
  }

private:
  Graph<T> G_;
  int start_;
  std::vector< NodeData<T> > D_;

  void compute() {
    typedef typename std::vector<Edge> vge;

    std::priority_queue< Elem<T>, std::vector< Elem<T> >, std::greater< Elem<T> > > Q;

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
  int n;

  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  Graph<int> G(n);
  for (int i = 1; i < n; i++) {
    std::string line;
    const char* s;

    getline(std::cin, line);
    s = line.c_str();
    for (int j = 0; j < i; j++) {
      if (*s == 'x')
        s++;
      else {
        int expense = strtol(s, (char**)&s, 10);
        G.addEdge(0, i, j, expense);
        G.addEdge(0, j, i, expense);
      }

      // Skip whitespace
      while (*s == ' ') s++;
    }
  }

  // Compute shortest paths
  ShortestPath<int> sp(G, 0);

  int max = 0;
  for (int i = 1; i < n; i++)
    max = std::max(max, sp.getCost(i));

  printf("%d\n", max);

  return 0;
}

