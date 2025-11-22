// Bring Your Own Horse
// UVa ID: 12176
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<int> parent;

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]);
    return parent[x];
}

bool unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a == b) return false;
    parent[b] = a;
    return true;
}

vector<vector<pair<int, int>>> mstGraph;

void dfs(int u, int p, int target, int maxSoFar, vector<int>& visited, int& result) {
    if (u == target) {
        result = maxSoFar;
        return;
    }
    for (auto& e : mstGraph[u]) {
        int v = e.first, w = e.second;
        if (v == p || visited[v]) continue;
        visited[v] = 1;
        dfs(v, u, target, max(maxSoFar, w), visited, result);
        if (result != -1) return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N, R;
        cin >> N >> R;
        vector<Edge> edges(R);
        for (int i = 0; i < R; ++i)
            cin >> edges[i].u >> edges[i].v >> edges[i].w;

        sort(edges.begin(), edges.end());

        parent.resize(N + 1);
        for (int i = 1; i <= N; ++i) parent[i] = i;

        mstGraph.assign(N + 1, vector<pair<int, int>>());

        for (const auto& e : edges) {
            if (unionSet(e.u, e.v)) {
                mstGraph[e.u].emplace_back(e.v, e.w);
                mstGraph[e.v].emplace_back(e.u, e.w);
            }
        }

        int Q;
        cin >> Q;
        cout << "Case " << caseNum << "\n";
        while (Q--) {
            int k, t;
            cin >> k >> t;
            vector<int> visited(N + 1, 0);
            visited[k] = 1;
            int result = -1;
            dfs(k, -1, t, 0, visited, result);
            cout << result << "\n";
        }
        cout << "\n";
    }
    return 0;
}
