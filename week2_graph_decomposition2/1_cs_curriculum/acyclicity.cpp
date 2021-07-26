#include <iostream>
#include <vector>

using std::vector;
using std::pair;

short acyclic(vector<pair<bool, vector<unsigned int>>> &adj, int node) {
    short answer = 0;
    // Visited
    adj[node].first = true;
    unsigned int limit = adj[node].second.size();
    for (int i = 0; i < limit; i++) {
        int next_node = adj[node].second[i];
        //If it hasn't already been visited
        if (!adj[next_node].first) {
            answer = acyclic(adj, next_node);
        } else {
            return 1;
        }
    }
    return answer;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int initial;
  //Vector of pairs (bool, Vector) -> DIRECTED GRAPH
  vector<pair<bool, vector<unsigned int>>> adj(n, pair<bool, vector<unsigned int>>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    // Mark as unvisited
    adj[x - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
    initial = x - 1;
  }
  std::cout << acyclic(adj, initial);
}