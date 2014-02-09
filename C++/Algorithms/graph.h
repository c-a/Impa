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