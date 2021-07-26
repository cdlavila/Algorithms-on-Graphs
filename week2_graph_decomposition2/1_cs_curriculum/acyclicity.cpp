#include <iostream>
#include <vector>

using std::vector;
using std::pair;

short acyclic(vector<pair<bool, vector<unsigned int>>> &adj, int node) {
    short answer = 0;
    // Visited
    adj[node].first = true;
    //std::cout << node + 1 << " ";
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
    adj[node].first = false;
    return answer;
}

// DFS(Graph)
int dfs(vector<pair<bool, vector<unsigned int>>> &g) {
    int isCyclic;
    // for each vertex from graph
    unsigned int length = g.size();
    for (unsigned int i = 0; i < length; i++) {
        if (!g[i].first) {
            isCyclic = acyclic(g, i);
            if (isCyclic == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  //Vector of pairs (bool, Vector) -> DIRECTED GRAPH
  vector<pair<bool, vector<unsigned int>>> adj(n, pair<bool, vector<unsigned int>>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    // Mark as unvisited
    adj[x - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
  }
  std::cout << dfs(adj);
}