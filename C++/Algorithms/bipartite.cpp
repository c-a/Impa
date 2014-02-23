#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
#include <vector>

using vi = std::vector<int>;

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
  int run(const std::vector<vi>& adj, int left_nodes) {
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

    return min_cover_.size();
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

void add_edge(std::vector<vi>& adj, int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

bool check_match(const std::vector<vi>& adj, const vi& match) {
  // Check that all matches are mutual and that the edges exist in the original graph.
  for (int i = 0; i < match.size(); ++i) {
    if (match[i] == -1)
      continue;
      
    if (i != match[match[i]]) {
      printf("Vertex '%d' is matched with vertex '%d' "
             "but vertex '%d' is matched with vertex '%d'.\n",
             i, match[i], match[i], match[match[i]]);
      return false;
    }
    if (std::find(adj[i].begin(), adj[i].end(), match[i]) == adj[i].end()) {
      printf("No edge between vertex '%d' and '%d' in original graph.\n", i, match[i]);
      return false;
    }
  }
  return true;
}

bool check_cover(const std::vector<vi>& adj, vi cover) {
  // Sort cover to be able to binary search on it.
  std::sort(cover.begin(), cover.end());

  // Check that all edges in the graph are covered by a vertex in `cover`.
  for (int u = 0; u < adj.size(); ++u) {
    // If `u` is in cover all it's edges are covered.
    if (std::binary_search(cover.begin(), cover.end(), u))
      continue;

    for (auto v : adj[u]) {
      if (!std::binary_search(cover.begin(), cover.end(), v)) {
        printf("Edge between vertex '%d' and '%d' is not covered.\n", u, v);
        return false;
      }
    }
  }
  return true;
}

int main() {
  std::vector<vi> adj;

  adj.assign(4, vi());
  add_edge(adj, 0, 2);
  add_edge(adj, 0, 3);
  add_edge(adj, 1, 3);

  BipartiteMatching bm;
  assert(bm.run(adj, 2) == 2);
  assert(check_match(adj, bm.match()));
  
  BipartiteVertexCover bvc;
  assert(bvc.run(adj, 2) == 2);
  assert(check_cover(adj, bvc.min_cover()));
}

