#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// The number of vertices (n) is between 2 and 10^5, that means the largest route between two vertices u and v cannot be greater than 10^5
int infinite = 10*10*10*10*10;

string swapColor(string color) {
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
    int painted = 0;

    for (int i = 0; i < adj.size(); i++) {
        if (painted == adj.size())
            break;

        if (colors[i] == "none") {
            distances[i] = 0;
            previous[i] = 0;
            colors[i] = color;
            painted++;
            color = swapColor(color);
            queue<int> neighbors;
            neighbors.push(i);
            while (!neighbors.empty()) {
                int u = neighbors.front();
                neighbors.pop();
                int paintedUntilHere = painted;
                for (int v : adj[u]) {
                    if (distances[v] == infinite) {
                        neighbors.push(v);
                        distances[v] = distances[u] + 1;
                        previous[v] = u;
                        colors[v] = color;
                        painted++;
                    } else {
                        if (v != previous[u]) // If it's not visiting the father node
                            if (colors[v] == colors[u]) // If this neighbor that isn't the father has the same color (It cannot be painted with only 2 colors)
                                return 0;
                    }
                }
                if (painted > paintedUntilHere)
                    color = swapColor(color);
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
