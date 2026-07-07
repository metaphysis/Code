// Magic of David Copperfield
// UVa ID: 769
// Verdict: Accepted
// Submission Date: 2026-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    bool firstCase = true;

    while (T--) {
        int N;
        cin >> N;
        int V = N * N;

        // 建图：相邻格子连边
        vector<vector<int>> adj(V + 1);
        auto addEdge = [&](int a, int b) {
            adj[a].push_back(b);
            adj[b].push_back(a);
        };
        for (int r = 0; r < N; ++r)
            for (int c = 0; c < N; ++c) {
                int id = r * N + c + 1;
                if (r > 0) addEdge(id, id - N);
                if (r + 1 < N) addEdge(id, id + N);
                if (c > 0) addEdge(id, id - 1);
                if (c + 1 < N) addEdge(id, id + 1);
            }

        // BFS 求到起点 1 的最短距离
        vector<int> dist(V + 1, -1);
        queue<int> q;
        dist[1] = 0;
        q.push(1);
        int maxDist = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            maxDist = max(maxDist, dist[u]);
            for (int v : adj[u])
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
        }

        // 按距离分层（距离从 1 到 maxDist）
        vector<vector<int>> layers(maxDist + 1);
        for (int id = 2; id <= V; ++id)
            layers[dist[id]].push_back(id);

        // 正向轮次：距离从大到小
        vector<vector<int>> forwardRounds;
        for (int d = maxDist; d >= 1; --d)
            if (!layers[d].empty())
                forwardRounds.push_back(layers[d]);

        // 分配 k：从 2N 开始取奇数
        int k = 2 * N;
        if (k % 2 == 0) ++k;

        // 输出当前测试用例结果
        if (!firstCase) cout << '\n';
        firstCase = false;

        for (const auto &round : forwardRounds) {
            cout << k;
            for (int x : round) cout << ' ' << x;
            cout << '\n';
            k += 2;
        }
    }

    return 0;
}
