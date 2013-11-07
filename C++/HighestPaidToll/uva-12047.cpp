#include <vector>
#include <list>
#include <queue>
#include <iterator>
#include <algorithm>

#include "stdio.h"

using namespace std;

template<typename T>
class Graph
{
public:

  struct Edge
  {
    int index;
    int from, to;
    T weight;

    Edge(int i, int f, int t, T& w): index(i), from(f), to(t), weight(w) {}
  };

  Graph(int N): adj_(N) {}

  void addEdge(int index, int from, int to, T weight) {
    adj_[from].push_back(Edge(index, from, to, weight));
  }

  int N() const {
    return adj_.size();
  }
  
  const vector<Edge>& adj(int n) const {
    return adj_[n];
  }

  vector< vector<Edge> > adj_;
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
  T totalWeight;
  bool visited;

  NodeData() : edgeTo(0), visited(false) {}
};

template<typename T>
void
shortest_path(Graph<T> G, vector<NodeData<T> >& D, int start, int goal)
{
  priority_queue< Elem<T>, vector< Elem<T> >, greater< Elem<T> > > Q;

  for (typename std::vector<NodeData<T> >::iterator iter = D.begin();
       iter != D.end(); ++iter) {
    (*iter).totalWeight = 1e9;
  }

  D[start].totalWeight = 0;
  Q.push(Elem<T>(0, start));
  while (!Q.empty()) {
    Elem<T> cur = Q.top();
    Q.pop();

    if (D[cur.node].visited)
      continue;

    for (typename vector<typename Graph<T>::Edge>::const_iterator i = G.adj(cur.node).begin();
         i != G.adj(cur.node).end(); ++i) {
      const typename Graph<T>::Edge& e = *i;

      if (D[e.to].visited)
        continue;

      if (D[e.to].edgeTo == 0 ||
          cur.cost + e.weight < D[e.to].totalWeight) {
        D[e.to].totalWeight = cur.cost + e.weight;
        D[e.to].edgeTo = &e;
        Q.push(Elem<T>(D[e.to].totalWeight, e.to));
      }
    }

    D[cur.node].visited = true;
  }
}

struct Edge
{
  int from, to, cost;

  Edge(int f, int t, int c): from(f), to(t), cost(c) {};

  bool operator<(const Edge& rhs) const {
    return this->cost > rhs.cost;
  }

};

int main(int argc, char* argv[]) {
  int T;

  scanf("%d", &T);
  while (T-- > 0) {
    int N, M, s, t, p;

    scanf("%d %d %d %d %d", &N, &M, &s, &t, &p);

    Graph<int> Gf(N);
    Graph<int> Gb(N);
    vector<Edge> edges;

    for (int m = 0; m < M; m++) {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      Gf.addEdge(m, u-1, v-1, c);
      Gb.addEdge(m, v-1, u-1, c);
      edges.push_back(Edge(u-1, v-1, c));
    }

    vector<NodeData<int> > Df(N), Db(N);
    shortest_path(Gf, Df, s-1, t-1);
    shortest_path(Gb, Db, t-1, s-1);

    int max = -1;
    for (std::vector<Edge>::const_iterator iter = edges.begin();
         iter != edges.end(); ++iter) {
      const Edge& e = *iter;
      if ((Df[e.from].totalWeight + e.cost + Db[e.to].totalWeight) <= p) {
        max = std::max(max, e.cost);
      }
    }

    printf("%d\n", max);
  }
}

