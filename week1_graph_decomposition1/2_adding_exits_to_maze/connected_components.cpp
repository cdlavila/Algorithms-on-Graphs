#include <iostream>
#include <vector>

using std::vector;
using std::pair;

// Function to know if a vertex already was visited
bool visited(pair<bool, vector<unsigned int>> &v) {
    return v.first;
}

// Function to explore a vertex
int explore(pair<bool, vector<unsigned int>> &v, vector<pair<bool, vector<unsigned int>>> &adj) {
    v.first = true;
    // for (v, w) E E
    unsigned int length = v.second.size();
    for (size_t i = 0; i < length; i++){
        if (!visited(adj[v.second[i]])) {
            explore(adj[v.second[i]], adj);
        }
    }
    return 0;
}

// In fact, this function is a DFS(G) implementation
unsigned int number_of_components(vector<pair<bool, vector<unsigned int>>> &adj) {
  unsigned int cc = 0;
  // for v E V
  unsigned int length = adj.size();
  for (size_t i = 0; i < length; i++) {
      if (!visited(adj[i])) {
          explore(adj[i], adj);
          cc++;
      }
  }
  return cc;
}

// Main function
int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<pair<bool, vector<unsigned int>>> adj(n, pair<bool, vector<unsigned int>>());
  for (size_t i = 0; i < m; i++) {
      unsigned int x, y;
      std::cin >> x >> y;
      adj[x - 1].first = false;
      adj[x - 1].second.push_back(y - 1);
      adj[y - 1].first = false;
      adj[y - 1].second.push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}