#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>

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

double distance_between_two_points(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double minimum_distance(vector<int> x, vector<int> y) {
  // Constructing the undirected graph
  size_t v = x.size();
  vector<vector<int>> adj(v, vector<int>());
  vector<vector<double> > weight(v, vector<double>());
  for (int i = 0; i < v; i++) {
    for (int j = i; j < v; j++) {
      if (j != i) {
        double distance = distance_between_two_points(x[i], y[i], x[j], y[j]);
        adj[i].push_back(j);
        adj[j].push_back(i);
        weight[i].push_back(distance);
        weight[j].push_back(distance);
      }
    }
  }
  double result = prim(adj, weight);
  return result;
} 

int main() {
  size_t n;
  cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << fixed << setprecision(10) << minimum_distance(x, y) << "\n";
}
