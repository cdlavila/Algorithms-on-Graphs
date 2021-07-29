#include <iostream>
#include <vector>

using namespace std;

typedef pair<bool, vector<unsigned int>> vertex;
typedef vector<vertex> graph;

//Global variables
unsigned int clockk = 1;

// pre_visit(V)
void pre_visit(vertex &v, unsigned int &x, vector<pair<unsigned int, unsigned int>> &used) {
    used[x].first = clockk;
    clockk++;
}
// post_visit(V)
void post_visit(vertex &v, vector<int> &order, unsigned int &x, vector<pair<unsigned int, unsigned int>> &used) {
    used[x].second = clockk;
    order.insert(order.begin(), x);
    clockk++;
}
// is_visited(V)
bool is_visited(vertex &v) {
    return v.first;
}

// explore(V)
void explore(vertex &v, graph &g, vector<pair<unsigned int, unsigned int>> &used, vector<int> &order, unsigned int &x) {
    v.first = true;
    pre_visit(v, x, used);
    // for each vertex reachable from vertex where we are
    unsigned int length = v.second.size();
    for (unsigned int i = 0; i < length; i++) {
        if (!is_visited(g[v.second[i]])) {
            explore(g[v.second[i]], g, used, order, v.second[i]);
        }
    }
    post_visit(v, order, x, used);
}

vector<int> dfs(graph &g, vector<pair<unsigned int, unsigned int>> &used, vector<int> &order) {
    unsigned int size = g.size();
    for (unsigned int i = 0; i < size; i++) {
        if (!is_visited(g[i])) {
            explore(g[i], g, used, order, i);
        }
    }
    return order;
}

vector<int> topologicalSort(graph adj) {
  vector<pair<unsigned int, unsigned int>> used(adj.size());
  vector<int> order;
  dfs(adj, used, order);
  return order;
}

int main() {
  unsigned int n, m;
  std::cin >> n >> m;
  graph adj(n);
  for (unsigned int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].second.push_back(y - 1);
    adj[x - 1].first = false;
  }
  vector<int> order = topologicalSort(adj);
  for (unsigned int i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
