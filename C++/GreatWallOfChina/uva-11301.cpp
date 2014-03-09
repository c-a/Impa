#include <algorithm>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <stdexcept>
#include <stack>
#include <utility>
#include <vector>

template<typename FLOW, typename COST>
class FlowGraph
{
 public:
  using Flow = FLOW;
  using Cost = COST;

  class Edge
  {
   public:
    int from, to;
    Flow capacity, flow;
    Cost cost, red_cost;

    Edge(int f, int t, FLOW cap, COST c) :
      from(f), to(t), capacity(cap), flow(Flow()), cost(c), red_cost(c) {}

    int other(int u) const {
      if (u == from) return to;
      if (u == to) return from;
      throw std::runtime_error("Invalid node passed.");
    }

    Cost cost_to(int u) const {
      if (u == from) return -red_cost;
      if (u == to) return red_cost;
      throw std::runtime_error("Invalid node passed.");
    }

    void reduce_cost(Cost delta) {
      red_cost += delta;
    }

    bool active_to(int u) const {
      if (capacity_to(u) > Flow()) return true;
      return false;
    }

    Flow capacity_to(int u) const {
      if (u == from) return flow;
      if (u == to) return capacity - flow;
      throw std::runtime_error("Invalid node passed.");
    }

    void add_flow_to(int u, Flow delta) {
      if (u == from) flow -= delta;
      else if (u == to) flow += delta;
      else throw std::runtime_error("Invalid node passed.");
    }
  };

  int size() const {
    return adj_.size();
  }

  void reset(int n) {
    adj_.assign(n, std::vector<Edge*>());
    edges_.clear();
  }

  void add_edge(int from, int to, Flow cap, Cost cost) {
    edges_.emplace_back(from, to, cap, cost);
    Edge* edge = &edges_.back();

    adj_[from].push_back(edge);
    adj_[to].push_back(edge);
  }

  const std::vector<Edge*>& adj(int u) const {
    return adj_[u];
  }

  std::deque<Edge>& edges() {
    return edges_;
  }

 private:
  std::vector< std::vector<Edge*> > adj_;
  std::deque<Edge> edges_;
};

template<typename GRAPH>
class Dijkstra
{
private:
  using Graph = GRAPH;
  using Edge = typename Graph::Edge;
  using Cost = typename Graph::Cost;

  struct NodeData
  {
    Edge* edgeTo;
    Cost cost;
    bool visited;

    NodeData() : edgeTo(0), cost(Cost()), visited(false) {}
  };

  struct Elem
  {
    Cost cost;
    int node;

    Elem(const Cost& c, int n) : cost(c), node(n) {}

    bool operator>(const Elem& lhs) const {
      return cost > lhs.cost;
    }

    bool operator<(const Elem& lhs) const {
      return cost < lhs.cost;
    }
  };

public:

  void run(const Graph& G, int start) {
    compute(G, start);
  }

  std::list< std::pair<Edge*, int> > get_path(int goal) {
    std::list< std::pair<Edge*, int> > path;
    for (int cur = goal; D_[cur].edgeTo != 0; cur = D_[cur].edgeTo->other(cur))
      path.push_front(std::make_pair(D_[cur].edgeTo, cur));

    return path;
  }

  bool has_path(int goal) {
    return D_[goal].visited;
  }

  Cost get_cost(int goal) {
    return D_[goal].cost;
  }

private:
  void compute(const Graph& G, int start) {
    std::priority_queue< Elem, std::vector<Elem>, std::greater<Elem> > Q;

    D_.assign(G.size(), NodeData());
    Q.push(Elem(Cost(), start));
    while (!Q.empty()) {
      Elem cur = Q.top();
      Q.pop();

      if (D_[cur.node].visited)
        continue;

      for (auto i = G.adj(cur.node).begin(); i != G.adj(cur.node).end(); ++i) {
        Edge& e = **i;
        int to = e.other(cur.node);

        if (!e.active_to(to) || D_[to].visited)
          continue;

        if (D_[to].edgeTo == 0 ||
            cur.cost + e.cost_to(to) < D_[to].cost) {
          D_[to].cost = cur.cost + e.cost_to(to);
          D_[to].edgeTo = &e;
          Q.push(Elem(D_[to].cost, to));
        }
      }

      D_[cur.node].visited = true;
    }
  }

  std::vector<NodeData> D_;
};

template<typename FLOW, typename COST>
class MinCostFlow
{
 private:
  using Flow = FLOW;
  using Cost = COST;

 public:
  struct Result {
    Flow flow;
    Cost cost;
    Result() : flow(Flow()), cost(Cost()) {}
  };

  Result run(FlowGraph<Flow, Cost>& graph, int source, int sink) {
    res_ = Result();
    while (augment(graph, source, sink));
    for (const auto& e : graph.edges()) {
      res_.cost += e.cost*e.flow;
    }
    return res_;
  }

  Result result() {
    return res_;
  }

 private:
  bool augment(FlowGraph<Flow, Cost>& graph, int source, int sink) {
    dijkstra_.run(graph, source);
    if (!dijkstra_.has_path(sink))
      return false;

    // Calculate min capacity in augmenting path.
    auto path = dijkstra_.get_path(sink);
    Flow min = path.front().first->capacity_to(path.front().second);
    for (const auto& pair : dijkstra_.get_path(sink)) {
      min = std::min(min, pair.first->capacity_to(pair.second));
    }

    // Augment flow along path.
    for (const auto& pair : dijkstra_.get_path(sink)) {
      pair.first->add_flow_to(pair.second, min);
    }

    // Reduce costs.
    for (auto& e : graph.edges()) {
      e.reduce_cost(dijkstra_.get_cost(e.from) - dijkstra_.get_cost(e.to));
    }

    res_.flow += min;
    return true;
  }

  Result res_;
  Dijkstra< FlowGraph<Flow, Cost> > dijkstra_;
};

int main() {
  int n;
  FlowGraph<int, int> graph;
  MinCostFlow<int, int> mcf;
  while (std::cin >> n) {
    if (n == 0)
      break;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

#define IN_NODE(row, column) (((row)*n + column)*2)
#define OUT_NODE(row, column) (((row)*n + column)*2+1)
#define SOURCE_NODE 5*n*2
#define SINK_NODE 5*n*2+1

    graph.reset(5*n*2+2);
    for (int row = 0; row < 5; ++row) {
      std::string line;
      std::getline(std::cin, line);
      for (int col = 0; col < n; ++col) {
        int toll = line[col] == '@' ? 0 : line[col] - '0';
        graph.add_edge(IN_NODE(row, col), OUT_NODE(row, col), 1, toll);
        if (col > 0)
          graph.add_edge(OUT_NODE(row, col), IN_NODE(row, col-1), 1, 0);
        if (col < (n-1))
          graph.add_edge(OUT_NODE(row, col), IN_NODE(row, col+1), 1, 0);
        if (row > 0)
          graph.add_edge(OUT_NODE(row, col), IN_NODE(row-1, col), 1, 0);
        if (row < 4)
          graph.add_edge(OUT_NODE(row, col), IN_NODE(row+1, col), 1, 0);
      }

      if (line[0] == '@')
        graph.add_edge(SOURCE_NODE, IN_NODE(row, 0), 1, 0);
      graph.add_edge(OUT_NODE(row, n-1), SINK_NODE, 1, 0);
    }

    auto res = mcf.run(graph, SOURCE_NODE, SINK_NODE);
    std::cout << res.cost << std::endl;
  }
}
