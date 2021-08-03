#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// The number of vertices (n) is between 2 and 10^5, that means the largest route between two vertices u and v cannot be greater than 10^5
int infinite = 10*10*10*10*10;

vector<int> reconstructPath(int s, int u, vector<int> previous) {
    vector<int> result (1, s);
    while (u != s) {
        result.insert(result.begin() + 1, u);
        u = previous[u];
    }
    return result;
}

pair<int, vector<int>> distance(vector<vector<int> > &adj, int s, int t) {
  vector<int> distances (adj.size(), infinite);
  vector<int> previous (adj.size(), -1); // -1 represents that this node hasn't a previous node
  previous[s] = 0;
  distances[s] = 0;
  queue<int> neighbors;
  neighbors.push(s);
  while (!neighbors.empty()) {
      int u = neighbors.front();
      neighbors.pop();
      for (int v : adj[u]) {
          if (distances[v] == infinite) {
              neighbors.push(v);
              distances[v] = distances[u] + 1;
              previous[v] = u;
          }
      }
  }

  if (distances[t] != infinite)
      return make_pair(distances[t], previous);

  return make_pair(-1, vector<int> (0));
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  cin >> s >> t;
  s--, t--;
  pair<int, vector<int>> distanceAndPrevious = distance(adj, s, t);
  cout << distanceAndPrevious.first;
  // This is not part of the assignment
  vector<int> path = reconstructPath(s, t, distanceAndPrevious.second);
  cout << "\nPath: ";
  for (int i: path) {
      cout << i + 1 << " ";
  }
}
