#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Priority queue where the smallest numbers have higher priority
typedef priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> my_priority_queue;

// The greater long long int number divided by 2 (LLONG_MAX / 2)
long long int inf = 4611686018427387903;

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  vector<long long> dist(adj.size(), inf);
  vector<int> prev(adj.size(), -1); // -1 represents that this vertex hasn't a previous node
  dist[s] = 0;

  my_priority_queue H;
  H.push(make_pair(dist[s], s));

  while(!H.empty()) {
    pair<long long, int> u = H.top(); // Extract min
    H.pop();
    for (int i = 0; i < adj[u.second].size(); i++) {
      int v = adj[u.second][i];
      if (dist[v] > dist[u.second] + cost[u.second][i]) {
        dist[v] = dist[u.second] + cost[u.second][i];
        prev[v] = u.second;
        H.push(make_pair(dist[v], v)); // Change priority
      }
    }
  }
  if (dist[t] != inf)
    return dist[t];

  return -1;
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
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, cost, s, t);
}
