#include <cstdio>
#include <cstdint>
#include <vector>
#include <functional>
#include <queue>

struct Edge {
  int u, v;
  int cost;
  bool operator>(const Edge& other) const {
    return cost > other.cost;
  }
};

std::vector<std::vector<Edge>> adj;
std::vector<bool> vis;
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

void visit(int u) {
  vis[u] = true;
  for (const Edge& e : adj[u]) {
    if (!vis[e.v]) pq.push(e);
  }
}

int main() {
  int n_cases;
  scanf("%d", &n_cases);
  for (int case_n = 1; case_n <= n_cases; ++case_n) {
    int n, m;
    scanf("%d %d", &n, &m);
    adj.assign(n, std::vector<Edge>());
    vis.assign(n, false);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      adj[u].push_back({u, v, w});
      adj[v].push_back({v, u, w});
    }

    visit(0);
    int total = 0;
    while (!pq.empty()) {
      Edge e = pq.top(); pq.pop();
      if (vis[e.v]) continue;
      total += e.cost;
      visit(e.v);
    }
    bool success = true;
    for (const bool visited : vis) success &= visited;
    if (success) {
      printf("Case %d: %d\n", case_n, total);
    } else {
      printf("Case %d: Possums!\n", case_n);
    }
  }
}
