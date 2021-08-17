#include <iostream>
#include <vector>

using namespace std;

// The greater possible path from a node u to another node v (10^3 * 10^3) + 1
int inf = 1000001;

int bellmanFord(vector<vector<int> > &adj, vector<vector<int> > &cost, unsigned int V) {
  vector<int> dist(adj.size(), inf);
  vector<int> prev(adj.size(), -1); // -1 represents that this vertex hasn't a previous node
  dist[0] = 0;
  // Repeat |V| + 1 times or |V| times (only to find a negative cycle)
  int i = 1;
  while (i <= V) {
    // For all (u, v) ∈ E
    for (int j = 0; j < adj.size(); j++) {
      int u = j;
      for (int k = 0; k < adj[u].size(); k++) {
        int v = adj[u][k];
        // Relax (u, v)
        if (dist[v] > dist[u] + cost[u][k]) {
          dist[v] = dist[u] + cost[u][k];
          prev[v] = u;
          if (i ==  adj.size())
            return 1;
        }
      }
    }
    i++;
  }
  return 0;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  return bellmanFord(adj, cost, adj.size());
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cout << negative_cycle(adj, cost);
}
