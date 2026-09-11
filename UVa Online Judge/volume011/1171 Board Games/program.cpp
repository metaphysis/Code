// Board Games
// UVa ID: 1171
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.090s

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

void bfs(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        int N;
        cin >> N;
        int I, F;
        cin >> I >> F;
        int M;
        cin >> M;
        vector<vector<int>> adj(N), radj(N);
        vector<Edge> edges;
        for (int i = 0; i < M; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            adj[u].push_back(v);
            radj[v].push_back(u);
        }
        vector<bool> reachable(N, false);
        bfs(I, adj, reachable);
        vector<bool> canReachF(N, false);
        bfs(F, radj, canReachF);
        if (!reachable[F]) {
            cout << "infinity\n";
            if (tc != T - 1) cout << '\n';
            continue;
        }
        vector<bool> valid(N, false);
        for (int i = 0; i < N; ++i)
            valid[i] = reachable[i] && canReachF[i];
        vector<Edge> validEdges;
        for (const auto& e : edges)
            if (valid[e.u] && valid[e.v])
                validEdges.push_back(e);
        const long long INF = 4e18;
        vector<long long> dist(N, INF);
        dist[I] = 0;
        for (int i = 0; i < N - 1; ++i) {
            bool updated = false;
            for (const auto& e : validEdges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        bool negCycle = false;
        for (const auto& e : validEdges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                negCycle = true;
                break;
            }
        }
        if (negCycle) cout << "infinity\n";
        else cout << dist[F] << '\n';
        if (tc != T - 1) cout << '\n';
    }
    return 0;
}
