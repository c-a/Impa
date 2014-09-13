#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
#include <unordered_map>

using namespace std;

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
class SCC {
public:
  SCC(const Graph<T>& G):
    index_(0),
    data_(G.N())
  {
    compute(G);
  }

  const std::vector< std::vector<int> >& components() {
    return components_;
  }

private:
  struct VertexData {
    int index;
    int low;
    bool on_stack;

    VertexData() : index(-1), low(-1), on_stack(false) {}
  };

  void compute(const Graph<T>& G) {
    for (int u = 0; u < G.N(); ++u) {
      if (data_[u].index == -1)
        dfs(G, u);
    }
  }

  void dfs(const Graph<T>& G, int u) {
    auto& du = data_[u];
    du.low = du.index = index_++;
    du.on_stack = true;
    stack_.push(u);

    for (const auto& e : G.adj(u)) {
      int v = e.to;
      auto& dv = data_[v];
      if (dv.index == -1) {
        // Node `v` has not been visited, recurse on it.
        dfs(G, v);
        du.low = std::min(du.low, dv.low);
      }
      else if (dv.on_stack) {
        // Node `v` is on stack and thus in the current SCC.
        du.low = std::min(du.low, dv.index);
      }
    }

    if (du.low == du.index) {
      // Node `u` is root node, pop the stack and create SCC.
      std::vector<int> scc;
      int v;
      do {
        v = stack_.top(); stack_.pop();
        data_[v].on_stack = false;
        scc.push_back(v);
      } while (v != u);

      components_.push_back(std::move(scc));
    }
  }

  int index_;
  std::vector<VertexData> data_;
  std::stack<int> stack_;
  std::vector< std::vector<int> > components_;
};





Graph<bool> sccGraph(0);
vector<int> componentSize;
vector<int> reach;

int getReach(int n) {
  if (reach[n] != -1) return reach[n];
  reach[n] = componentSize[n];
  for (const auto& e : sccGraph.adj(n)) {
    reach[n] += getReach(e.to);
  }
  return reach[n];
}

int main() {
  int T;
  cin >> T;
  for (int caseN = 1; caseN <= T; ++caseN) {
    int N;
    cin >> N;
    Graph<bool> G(N);
    for (int i = 0; i < N; i++) {
      int from, to;
      cin >> from >> to;
      from--; to--;
      G.add_edge(from, to, false);
    }
    SCC<bool> scc(G);

    unordered_map<int, int> nodeToComponent;
    for (int i = 0; i < scc.components().size(); ++i) {
      for (const int node : scc.components()[i]) {
        nodeToComponent[node] = i;
      }
    }
    sccGraph = Graph<bool>(scc.components().size());
    componentSize.resize(scc.components().size());
    for (int i = 0; i < scc.components().size(); ++i) {
      componentSize[i] = scc.components()[i].size();
      for (const int node : scc.components()[i]) {
        for (const auto& e : G.adj(node)) {
          int component = nodeToComponent[e.to];
          if (component != i) {
            sccGraph.add_edge(i, component, false);
          }
        }
      }
    }

    reach.assign(sccGraph.N(), -1);
    int max = -1, best = -1;
    for (int i = sccGraph.N() - 1; i >= 0; --i) {
      int r = getReach(i);
      if (r >= max) {
        max = r;
        const auto& bestC = scc.components()[i];
        best = *std::min_element(bestC.begin(), bestC.end());
      }
    }
    cout << "Case " << caseN << ": " << best + 1 << "\n";
  }
}

