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
  //int initial;
  //Vector of pairs (bool, Vector) -> DIRECTED GRAPH
  vector<pair<bool, vector<unsigned int>>> adj(n, pair<bool, vector<unsigned int>>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    // Mark as unvisited
    adj[x - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
    //initial = x - 1;
  }
  std::cout << dfs(adj);
}
/*
200 100
164 170
197 70
104 177
185 181
18 30
141 107
61 38
190 12
106 4
79 149
125 97
97 198
44 75
109 200
149 140
181 13
109 107
171 107
87 107
102 159
113 63
81 25
172 109
131 43
124 8
78 1
84 9
29 121
157 81
175 149
58 31
35 70
110 85
115 138
35 4
175 177
2 38
160 111
70 166
45 176
181 75
72 141
161 58
170 80
153 69
61 31
25 166
85 170
72 71
104 113
80 178
157 113
134 96
170 85
19 89
49 4
113 143
86 101
118 115
72 104
197 3
74 98
140 121
29 22
122 167
177 196
120 56
171 155
190 133
126 114
63 33
40 68
103 3
172 65
178 68
40 191
29 107
198 3
129 69
19 140
63 160
182 117
181 56
54 12
146 187
175 28
123 200
84 99
157 47
59 16
82 70
123 63
153 72
191 117
2 36
49 100
61 145
129 150
169 196
70 143
*/