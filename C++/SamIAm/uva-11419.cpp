#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

typedef std::vector<int> vi;

class BipartiteMatching {
 public:
  int run(const std::vector<vi>& adj, int left_nodes) {
    match_.assign(adj.size(), -1);
    int matching = 0;
    for (int u = 0; u < left_nodes; ++u) {
      visited.assign(left_nodes, false);
      matching += augment(adj, u);
    }

    for (int v = left_nodes; v < adj.size(); ++v) {
      if (match_[v] != -1)
        match_[match_[v]] = v;
    }
    return matching;
  }

  int augment(const std::vector<vi>& adj, int u) {
    if (visited[u]) return 0;
    visited[u] = true;
    for (auto v = adj[u].begin(); v != adj[u].end(); ++v) {
      if (match_[*v] == -1 || augment(adj, match_[*v])) {
        match_[*v] = u;
        return 1;
      }
    }
    return 0;
  }

  const vi& match() {
    return match_;
  }

 private:
  std::vector<bool> visited;
  vi match_;
};

class BipartiteVertexCover {
 public:
  void run(const std::vector<vi>& adj, int left_nodes) {
    min_cover_.clear();

    bm.run(adj, left_nodes);
    const vi& match = bm.match();

    visited.assign(adj.size(), false);
    layers[0].clear();
    // Find all vertices which are not matched.
    for (int u = 0; u < adj.size(); ++u) {
      if (adj[u].size() == 0) {
        visited[u] = true;
        continue;
      }
      if (match[u] == -1) {
        layers[0].push_back(u);
        visited[u] = true;
      }
    }

    for (int level = 0; level == 0 || !layers[level % 2].empty(); ++level) {
      vi* layer = &layers[level % 2];
      vi* new_layer = &layers[(level+1) % 2];

      new_layer->clear();
      // Even, follow not matched edges.
      if (level % 2 == 0) {
        for (auto u = layer->begin(); u != layer->end(); ++u) {
          for (auto i = adj[*u].begin(); i != adj[*u].end(); ++i) {
            if (*i != match[*u] && !visited[*i]) {
              new_layer->push_back(*i);
              visited[*i] = true;
            }
          }
        } 
        if (new_layer->empty()) {
          auto not_visited = std::find(visited.begin(), visited.end(), false);
          if (not_visited != visited.end()) {
            int u = not_visited - visited.begin();
            new_layer->push_back(u);
            visited[u] = true;
          }
        }
      }
      // Odd, follow matched edges.
      else {
        min_cover_.insert(min_cover_.end(), layer->begin(), layer->end());
        for (auto u = layer->begin(); u != layer->end(); ++u) {
          if (match[*u] != -1 && !visited[match[*u]]) {
            new_layer->push_back(match[*u]);
            visited[match[*u]] = true;
          }
        }
      }
    }
  }

  const vi& min_cover() const {
    return min_cover_;
  }

 private:
  vi min_cover_;
  BipartiteMatching bm;
  std::vector<bool> visited;
  vi layers[2];
};

static std::string
toString(int node, int R) {
  std::stringstream ss;
  if (node == -1)
    ss << "-1";
  else if (node < R)
    ss << "r" << node+1;
  else
    ss << "c" << (node+1-R);

   return ss.str();
}

int main() {
  static const size_t MAX_NODES = 1000*1000;

  std::vector<vi> adj(MAX_NODES);
  BipartiteVertexCover bvc;

  while (true) {
    int R, C, N;
    scanf("%d %d %d", &R, &C, &N);
    if (R == 0 && C == 0 && N == 0)
      break;

    #define R_NODE(r) (((r)-1))
    #define C_NODE(c) (((c)-1)+R)

    // Clear adjacency lists
    adj.assign(R+C, vi());

    // Add edges between rows and columns representing enemies. 
    for (int n = 0; n < N; ++n) {
      int r, c;
      scanf("%d %d", &r, &c);
      adj[R_NODE(r)].push_back(C_NODE(c));
      adj[C_NODE(c)].push_back(R_NODE(r));
    }

    // Find minimum vertex cover, e.g. choose a minimum of horizontal and vertical nodes
    // so that all edges (enemies) are covered.
    bvc.run(adj, R);
    vi min_cover = bvc.min_cover();

    printf("%d", (int)min_cover.size());
    std::sort(min_cover.begin(), min_cover.end());
    for (auto i = min_cover.begin(); i < min_cover.end(); ++i) {
      printf(" %s", toString(*i, R).c_str());
    }
    printf("\n");
  }
  return 0;
}
