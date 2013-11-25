#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef std::map<int, int> mii;
typedef std::vector<int> vi;

template<int NODES>
class MaxFlow
{
public:

  void run(mii* flow, int source, int sink)
  {
    flow_ = flow;
    source_ = source;
    sink_ = sink;
    maxFlow_ = 0;

    int amount;
    while ((amount = augment()) > 0)
      maxFlow_ += amount;
  }

  int flow()
  {
    return maxFlow_;
  }

private:

  int augment()
  {
    bool visited[NODES];
    int pred[NODES];
    std::queue<int> Q;
    bool stop;

    memset(visited, false, sizeof(bool)*NODES);
    memset(pred, -1, sizeof(int)*NODES);

    // Find augmenting path using BFS == Edmonds-Karp.
    visited[source_] = true;
    Q.push(source_);
    stop = false;
    while (!Q.empty() && !stop)
    {
      int u = Q.front();
      Q.pop();

      for (mii::const_iterator iter = flow_[u].begin();
           iter != flow_[u].end(); ++iter) {
        int v = (*iter).first;
        int cap = (*iter).second;
        if (!visited[v] && cap > 0) {
          pred[v] = u;
          visited[v] = true;
          Q.push(v);

          // Found augmenting path.
          if (v == sink_) {
            stop = true;
            break;
          }
        }
      }
    }

    if (pred[sink_] == -1)
      return 0;

    // Find out augmenting path capacity.
    int cap = std::numeric_limits<int>::max();
    for (int u = sink_; pred[u] != -1; u = pred[u])
      cap = std::min(cap, flow_[pred[u]][u]);

    // Update residual flow.
    for (int u = sink_; pred[u] != -1; u = pred[u])
    {
      flow_[pred[u]][u] -= cap;
      flow_[u][pred[u]] += cap;
    }

    return cap;
  }

  mii* flow_;
  int source_;
  int sink_;
  int maxFlow_;
};


int main() {
  int T;
  mii flow[200+2];
  MaxFlow<200+2> maxFlow;
  
  scanf("%d", &T);
  for (int caseN = 1; caseN <= T; caseN++) {
    int n, m;
    vi A, B;

    scanf("%d", &n);
    A.resize(n);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);

    scanf("%d", &m);
    B.resize(m);
    for (int i = 0; i < m; i++) scanf("%d", &B[i]);

    // Create flow graph

    #define A_NODE(u) ((u)+2)
    #define B_NODE(u) ((u)+2+n)

    // Clear flows
    for (int i = 0; i < n+m+2; i++)
      flow[i].clear();

    // Add edge from source to A nodes
    for (int i = 0; i < A.size(); ++i)
      flow[0][A_NODE(i)] = 1;

    // Add edge from B nodes to sink
    for (int i = 0; i < B.size(); ++i)
      flow[B_NODE(i)][1] = 1;
    
    // Add edges from numbers in A that divides numbers in B
    for (int i = 0; i < A.size(); ++i) {
      for (int j = 0; j < B.size(); ++j) {
          if (B[j] == 0) {
            flow[A_NODE(i)][B_NODE(j)] = 1;
          }
          else if (A[i] != 0 && (abs(B[j]) >= abs(A[i])) && (B[j] % A[i] == 0))
            flow[A_NODE(i)][B_NODE(j)] = 1;
      }
    }

    maxFlow.run(flow, 0, 1);
    printf("Case %d: %d\n", caseN, maxFlow.flow());
  }

  return 0;
}
