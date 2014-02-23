#include <cassert>
#include <stack>

#include "graph.h"

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

int main() {
  Graph<int> G(3);

  G.add_edge(0, 1, 0);
  G.add_edge(1, 2, 0);
  G.add_edge(2, 1, 0);

  SCC<int> scc(G);
  const auto& comps = scc.components();
  assert(comps.size() == 2);
  int sum;
  for (const auto& comp : comps)
    sum += comp.size();
  assert(sum == 3);
}

