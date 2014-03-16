#include <algorithm>
#include <iostream>
#include <queue>
#include <list>
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

int main() {
  static const int MAX_NODES = 'z' - 'a' + 1;
  Graph<int> G(MAX_NODES);
  Dijkstra<int> di;
  int edge_sum = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line != "deadend") {
      int u = line.front() - 'a';
      int v = line.back() - 'a';
      G.add_edge(u, v, line.size());
      G.add_edge(v, u, line.size());
      edge_sum += line.size();
      continue;
    }

    // Get the nodes with odd degree.
    std::vector<int> odd_nodes;
    for (int u = 0; u < G.N(); ++u) {
      if (G.adj(u).size() % 2 != 0)
        odd_nodes.push_back(u);
    }
    int cost = edge_sum;
    if (odd_nodes.size() == 2) {
      di.run(G, odd_nodes[0]);
      cost += di.get_cost(odd_nodes[1]);
    }
    std::cout << cost << std::endl;

    G.clear();
    edge_sum = 0;
  }
}
