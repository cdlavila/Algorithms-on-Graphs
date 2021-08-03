#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// The number of vertices (n) is between 2 and 10^5, that means the largest route between two vertices u and v cannot be greater than 10^5
int infinite = 10*10*10*10*10;

string changeColor(string color) {
    if (color == "white")
        return "black";

    if (color == "black")
        return "white";

    return "none";
}

// This implementation is for undirected graphs
int bipartite(vector<vector<int> > &adj) {
    vector<int> distances (adj.size(), infinite);
    vector<int> previous (adj.size(), -1);
    vector<string> colors (adj.size(), "none");
    string color = "white";

    for (int i = 0; i < adj.size(); i++) {
        if (colors[i] == "none") {
            distances[i] = 0;
            previous[i] = 0;
            colors[i] = color;
            color = changeColor(color);
            queue<int> neighbors;
            neighbors.push(i);
            while (!neighbors.empty()) {
                int u = neighbors.front();
                neighbors.pop();
                for (int v : adj[u]) {
                    if (distances[v] == infinite) {
                        neighbors.push(v);
                        distances[v] = distances[u] + 1;
                        previous[v] = u;
                        colors[v] = color;
                    } else {
                        if (v != previous[u])
                            if (colors[v] != color)
                                return 0;
                    }
                }
                color = changeColor(color);
            }
        }
    }

    return 1;
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
    cout << bipartite(adj);
}
