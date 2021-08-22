#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Priority queue where the smallest numbers have higher priority
typedef priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> my_priority_queue;

// The greater int number
int inf = 2147483647;

double prim(vector<vector<int>> &adj, vector<vector<double>> &weight) {
  vector<double> cost(adj.size(), inf);
  vector<int> parent(adj.size(), -1); // -1 represents that this vertex hasn't a parent node
  vector<bool> MST(adj.size(), false);
  int u0 = 0;
  cost[u0] = 0;

  my_priority_queue Q;
  Q.push(make_pair(cost[u0], u0));

  while(!Q.empty()) {
    int v = Q.top().second;
    Q.pop();

    if (MST[v]) continue;
    MST[v] = true;

    for (int i = 0; i < adj[v].size(); i++) {
      int z = adj[v][i];
      if (!MST[z] && cost[z] > weight[v][i]) {
        cost[z] = weight[v][i];
        parent[z] = v;
        Q.push(make_pair(cost[z], z)); // Change priority
      }
    }
  }

  double total_cost = 0;
  for (double i : cost) {
    if (i != inf) {
      total_cost += i;
    }
  }

  return total_cost;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<double> > weight(n, vector<double>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
    weight[x - 1].push_back(w);
    weight[y - 1].push_back(w);
  }
  cout << prim(adj, weight);
}
