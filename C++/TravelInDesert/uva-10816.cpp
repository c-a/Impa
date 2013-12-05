#include <algorithm>
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
struct Elem
{
  T cost;
  int node;

  Elem(const T& c, int n) : cost(c), node(n) {}

  bool operator>(const Elem<T>& lhs) const {
    return cost > lhs.cost;
  }

  bool operator<(const Elem<T>& lhs) const {
    return cost < lhs.cost;
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

  ShortestPath(const Graph<T>& G, int start): start_(start), D_(G.N()) {
    compute(G);
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
  int start_;
  std::vector< NodeData<T> > D_;

  void compute(const Graph<T>& G) {
    typedef typename std::vector<Edge> vge;

    std::priority_queue< Elem<T>, std::vector< Elem<T> >, std::greater< Elem<T> > > Q;

    D_[start_].totalcost = 0;
    Q.push(Elem<T>(0, start_));
    while (!Q.empty()) {
      Elem<T> cur = Q.top();
      Q.pop();

      if (D_[cur.node].visited)
        continue;

      for (typename vge::const_iterator i = G.adj(cur.node).begin();
           i != G.adj(cur.node).end(); ++i) {
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

struct Temperature
{
  int temp;

  Temperature(): temp(0) {};

  Temperature(int t): temp(t) {};

  Temperature operator+(const Temperature& rhs) const {
    return Temperature(std::max(temp, rhs.temp));
  }

  bool operator<(const Temperature& rhs) const {
    return temp < rhs.temp;
  }

  bool operator>(const Temperature& rhs) const {
    return temp > rhs.temp;
  }
};

int main()
{
  int N, E, S, T;

  for (int caseN = 1; scanf("%d %d %d %d", &N, &E, &S, &T) == 4; caseN++) {
    S--; T--;

    Graph<Temperature> tempGraph(N);
    std::vector<int> distances(E);

    // Read in all edges. Add edges to temperature graph and
    // store edge distances in the distances vector for later use.
    for (int i = 0; i < E; ++i) {
      int from, to;
      float length, temp;

      scanf("%d %d %f %f", &from, &to, &temp, &length);
      from--; to--;

      tempGraph.add_edge(i, from, to, temp*10.0 + 0.5);
      tempGraph.add_edge(i, to, from, temp*10.0 + 0.5);
      distances[i] = length*10.0 + 0.5;
    }

    // Find the path with minimal max temperature.
    ShortestPath<Temperature> tempSP(tempGraph, S);
    int maxTemp = tempSP.get_cost(T).temp;


    // Create distance graph with all edges which temperature is less than the max.
    Graph<int> distGraph(N);
    for (int ni = 0; ni < tempGraph.N(); ni++) {
      for (std::vector<Graph<Temperature>::Edge>::const_iterator ei = tempGraph.adj(ni).begin();
           ei != tempGraph.adj(ni).end(); ++ei) {
        const Graph<Temperature>::Edge& e = *ei;
        if (e.cost.temp <= maxTemp) {
          distGraph.add_edge(e.index, e.from, e.to, distances[e.index]);
        }
      }
    }


    // Find the shortest path.
    ShortestPath<int> distSP(distGraph, S);
    std::list<Graph<int>::Edge> distPath = distSP.get_path(T);

    // Print the shortest path.
    int length = 0;
    printf("%d", S+1);
    for (std::list<Graph<int>::Edge>::const_iterator i = distPath.begin(); i != distPath.end(); ++i) {
      printf(" %d", (*i).to+1);
      length += (*i).cost;
    }

    printf("\n%.1f %.1f\n", (double)length / 10, (double)maxTemp / 10);
  }

  return 0;
}
