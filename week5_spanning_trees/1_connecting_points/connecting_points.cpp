#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Disjoint set implementation
class disjoint_set {
private:
    int *rank, *parent;
    unsigned int n;
public:
    // default constructor
    disjoint_set() = default;

    // Constructor to create and initialize sets of n items
    disjoint_set(unsigned int n) {
      rank = new int[n];
      parent = new int[n];
      this->n = n;
      makeSet();
    }

    // Creates n single item sets
    void makeSet() {
      for (int i = 0; i < n; i++) {
        parent[i] = i;
      }
    }

    // Finds set of given item x
    int find(int x) {
      // Finds the representative of the set that x is an element of
      if (parent[x] != x) {
        // if x is not the parent of itself Then x is not the representative of his set,
        parent[x] = find(parent[x]);
        // so we recursively call Find on its parent and move I's node directly under the representative of this set
      }
      return parent[x];
    }

    // Do union of two sets represented by x and y.
    void Union(int x, int y) {
      // Find current sets of x and y
      int xSet = find(x);
      int ySet = find(y);

      // If they are already in same set
      if (xSet == ySet)
        return;

      // Put smaller ranked item under bigger ranked item if ranks are different
      if (rank[xSet] < rank[ySet]) {
        parent[xSet] = ySet;
      } else if (rank[xSet] > rank[ySet]) {
        parent[ySet] = xSet;
      } else { // If ranks are same, then increment rank.
        parent[ySet] = xSet;
        rank[xSet]++;
      }
    }
};

// Undirected edge implementation
class edge{
public:
    int u, v;
    double weight;

    // default constructor
    edge() = default;

    // Constructor
    edge(int u, int v, double weight) {
      this->u = u;
      this->v = v;
      this->weight = weight;
    }
};

// Sorting function by weight
bool sorting_by_weight(edge a, edge b) {
  return a.weight < b.weight;
}

// Kruskal's algorithm implementation
pair<vector<edge>, double> kruskal(vector<edge> &edges) {
  double total_cost = 0;
  // for all u ∈ V : MakeSet(v)
  disjoint_set ds(edges.size());
  // X ← empty set
  vector<edge> X(0);
  // sort the edges E by weight
  sort(edges.begin(), edges.end(), sorting_by_weight);
  // for all {u, v} ∈ E in non-decreasing weight order:
  for(edge e: edges) {
    int u = e.u;
    int v = e.v;
    if (ds.find(u) != ds.find(v)) {
      X.push_back(e);
      ds.Union(u, v);
      total_cost += e.weight;
    }
  }
  return make_pair(X, total_cost);
}

// Distance between two point function
double distance_between_two_points(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double minimum_distance(vector<int> x, vector<int> y) {
  // Constructing the undirected graph
  unsigned int v = x.size();
  vector<edge> edges(v);
  for (int i = 0; i < v; i++) {
    for (int j = i; j < v; j++) {
      if (j != i) {
        double weight = distance_between_two_points(x[i], y[i], x[j], y[j]);
        edge e(i, j, weight);
        edges.push_back(e);
      }
    }
  }
  pair<vector<edge>, double> result = kruskal(edges);
  return result.second;
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

/*
int main() {
  int V, E;
  cin >> V >> E;
  vector<edge> edges(E);
  for (int i = 0; i < E; i++) {
    int u, v;
    double w;
    cin >> u >> v >> w;
    edge newEdge(u, v, w);
    edges[i] = newEdge;
  }
  cout << kruskal(edges);
}
 */