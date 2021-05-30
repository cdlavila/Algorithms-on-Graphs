#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int reach(vector<pair<bool, vector<unsigned int>>> &adj, int x, int y) {
  //write your code here
    int answer = 0;
    adj[x].first = true;
    unsigned int limit = adj[x].second.size();
    for (size_t i = 0; i < limit; i++) {
        int w = adj[x].second[i];
        if (!adj[w].first) {
            answer = reach(adj, w, y);
        }
    }
    if (adj[y].first) {
        return 1;
    }
    else return answer;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<pair<bool, vector<unsigned int>>> adj(n, pair<bool, vector<unsigned int>>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
    adj[y - 1].first = false;
    adj[y - 1].second.push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
