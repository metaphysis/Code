// Toll Road
// UVa ID: 12182
// Verdict: Accepted
// Submission Date: 2026-04-27
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<pair<int, int>> graph[MAXN];
bool visited[MAXN];
long long dp[MAXN];
long long ans;

void dfs(int u, int parent) {
    visited[u] = true;
    dp[u] = 0; // 不包含父边，初始为0
    for (auto &edge : graph[u]) {
        int v = edge.first;
        int w = edge.second;
        if (v == parent) continue;
        dfs(v, u);
        if (dp[v] + w > 0) dp[u] += dp[v] + w;
    }
    ans = max(ans, dp[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        for (int i = 0; i < MAXN; ++i) graph[i].clear();
        memset(visited, false, sizeof(visited));
        ans = -1e18;

        int maxNode = 0;
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n; ++i) {
            int a, b, p;
            cin >> a >> b >> p;
            edges.emplace_back(a, b, p);
            maxNode = max(maxNode, max(a, b));
        }

        for (auto &e : edges) {
            int a = get<0>(e), b = get<1>(e), p = get<2>(e);
            graph[a].emplace_back(b, p);
            graph[b].emplace_back(a, p);
        }

        for (int i = 1; i <= maxNode; ++i) {
            if (!graph[i].empty() && !visited[i]) {
                dfs(i, -1);
            }
        }

        cout << max(0LL, ans) << '\n';
    }

    return 0;
}
