
#include <vector>
#include <queue>

#include <cstdio>
#include <cstring>

typedef std::vector<int> vi;
typedef std::queue<int> qi;

int bfs_tree_diameter(vi (&adj)[25], int u) {
  bool visited[25];
  vi badj[25];
  int leaf;
  qi q;

  // Create bfs tree
  memset(visited, false, 25*sizeof(bool));
  q.push(u);
  visited[u] = true;
  while (!q.empty()) {
    int v = q.front(); q.pop();

    for (vi::iterator i = adj[v].begin(); i != adj[v].end(); ++i) {
      int w = *i;
      if (visited[w])
        continue;

      // Add edge v <-> w
      badj[v].push_back(w);
      badj[w].push_back(v);

      q.push(w);
      visited[w] = true;
    }

    leaf = v;
  }

  // Do another bfs from leaf in the bfs tree to find diameter
  int diameter = -1;
  memset(visited, false, 25*sizeof(bool));
  q.push(leaf);
  visited[leaf] = true;
  q.push(-1);
  while (!q.empty()) {
    int v = q.front(); q.pop();
    if (v == -1) {
      diameter++;
      if (!q.empty())
        q.push(-1);
      continue;
    }

    for (vi::iterator i = badj[v].begin(); i != badj[v].end(); ++i) {
      int w = *i;
      if (visited[w])
        continue;

      q.push(w);
      visited[w] = true;
    }
  }

  return diameter;
}

int main() {
  int testCases;

  //scanf("%d", &testCases);
  for (int caseN = 1; caseN <= testCases; caseN++) {
    vi adj[25];
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
      int u, v;

      scanf("%d %d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    int minDiameter = 1e9;
    for (int u = 0; u < n; u++) {
      minDiameter = std::min(minDiameter, bfs_tree_diameter(adj, u));
    }

    printf("Case #%d:\n%d\n\n", caseN, minDiameter);
  }
  return 0;
}
