#include <iostream>
#include <vector>

using std::vector;
using std::pair;

typedef vector<pair<bool, vector<unsigned int>>> graph;
typedef pair<bool, vector<unsigned int>> vertex;

short isCyclic = 0;

// Visited(vertex)
bool visited(vertex &v) {
    return v.first;
}

// Explore(vertex)
vertex explore(vertex &v, graph &g) {
    v.first = true;
    vertex end;
    // for each vertex reachable from vertex where we are
    unsigned int length = v.second.size();
    for (unsigned int i = 0; i < length; i++){
        if (!visited(g[v.second[i]])) {
            end = explore(g[v.second[i]], g);
        } else {
            return g[v.second[i]];
        }
    }
    if (end == v) {
        isCyclic = 1;
    }
    return end;
}

// DFS(Graph)
void dfs(graph &g) {
    // for each vertex from graph
    unsigned int length = g.size();
    for (unsigned int i = 0; i < length; i++) {
        if (!visited(g[i])) {
            explore(g[i], g);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    //Vector of pairs (pair<bool, unsigned int>, Vector) -> DIRECTED GRAPH
    graph g(n, pair<bool, vector<unsigned int>>());
    for (int i = 0; i < m; i++) {
        unsigned int x, y;
        std::cin >> x >> y;
        // Mark as unvisited
        g[x - 1].first = false;
        g[x - 1].second.push_back(y - 1);
    }
    dfs(g);
    std::cout << isCyclic;
}