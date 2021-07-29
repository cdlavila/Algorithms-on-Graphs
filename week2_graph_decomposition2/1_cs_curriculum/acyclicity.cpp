#include <iostream>
#include <vector>

using namespace std;

typedef pair<bool, vector<unsigned int>> vertex;
typedef vector<vertex> graph;

//Global variables
unsigned int clk = 1;

// pre_visit(V)
void pre_visit(vertex &v, unsigned int &x, vector<pair<unsigned int, unsigned int>> &used) {
    used[x].first = clk;
    clk++;
}
// post_visit(V)
void post_visit(vertex &v, unsigned int &x, vector<pair<unsigned int, unsigned int>> &used) {
    used[x].second = clk;
    clk++;
}
// is_visited(V)
bool is_visited(vertex &v) {
    return v.first;
}

// explore(V)
void explore(vertex &v, graph &g, vector<pair<unsigned int, unsigned int>> &used, unsigned int &x, bool &is_cyclic) {
    v.first = true;
    pre_visit(v, x, used);
    // for each vertex reachable from vertex where we are
    unsigned int length = v.second.size();
    for (unsigned int i = 0; i < length; i++) {
        if (!is_visited(g[v.second[i]])) {
            explore(g[v.second[i]], g, used, v.second[i], is_cyclic);
        }
        else {
            if (used[v.second[i]].first < used[x].first && used[v.second[i]].second == 0) {
                is_cyclic = true;
                break;
            }
        }
    }
    post_visit(v, x, used);
}

void dfs(graph &g, bool &is_cyclic) {
    vector<pair<unsigned int, unsigned int>> used (g.size(), make_pair(0, 0));
    unsigned int size = g.size();
    for (unsigned int i = 0; i < size; i++) {
        if (is_cyclic) {
            break;
        }
        if (!is_visited(g[i])) {
            explore(g[i], g, used, i, is_cyclic);
        }
    }
}

bool acyclic(graph &g) {
    bool is_cyclic = false;
    dfs(g, is_cyclic);
    return is_cyclic;
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
    cout << acyclic(adj);
}