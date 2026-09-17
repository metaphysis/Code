#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
    double cost;
    Edge(int from = 0, int to = 0, double cost = 0.0) : from(from), to(to), cost(cost) {}
};

int n, m;
vector<char> visited;
vector<vector<int>> adj;

bool compareEdge(const Edge &a, const Edge &b) {
    return a.cost > b.cost;
}

bool canReach(int current, int target) {
    if (current == target) return true;
    visited[current] = true;
    for (int next : adj[current])
        if (!visited[next] && canReach(next, target)) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(4);
    while (testCount--) {
        cin >> n >> m;
        vector<Edge> edges(m);
        adj.assign(n, vector<int>());
        for (int i = 0; i < m; i++) {
            int from, to;
            double cost;
            cin >> from >> to >> cost;
            from--;
            to--;
            edges[i] = Edge(from, to, cost);
            adj[from].push_back(to);
        }
        sort(edges.begin(), edges.end(), compareEdge);
        double answer = 0.0;
        for (const Edge &edge : edges) {
            vector<int>::iterator it = find(adj[edge.from].begin(), adj[edge.from].end(), edge.to);
            adj[edge.from].erase(it);
            visited.assign(n, false);
            if (canReach(edge.from, edge.to)) {
                adj[edge.from].push_back(edge.to);
                answer += edge.cost;
            } else {
                adj[edge.from].push_back(edge.to);
                adj[edge.to].push_back(edge.from);
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
