// Museums
// UVa ID: 11153
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    int cases;
    cin >> cases;
    for (int caseNo = 1; caseNo <= cases; caseNo++) {
        int d, t, n, m;
        cin >> d >> t >> n >> m;
        vector<int> fee(n + 1), fun(n + 1);
        fee[0] = fun[0] = 0;
        for (int i = 1; i <= n; i++) cin >> fee[i] >> fun[i];
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
        for (int i = 0; i <= n; i++) dist[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }
        // Floyd 最短路
        for (int k = 0; k <= n; k++)
            for (int i = 0; i <= n; i++)
                for (int j = 0; j <= n; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        int totalStates = 1 << n;
        // 预处理每个掩码的总花费和总乐趣
        vector<int> maskCost(totalStates, 0), maskFun(totalStates, 0);
        for (int mask = 0; mask < totalStates; mask++)
            for (int i = 0; i < n; i++)
                if (mask & (1 << i)) {
                    maskCost[mask] += fee[i + 1];
                    maskFun[mask] += fun[i + 1];
                }
        // dp[mask][u] = 最小时间
        vector<vector<int>> dp(totalStates, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        int answer = 0;
        for (int mask = 0; mask < totalStates; mask++)
            for (int u = 0; u <= n; u++) {
                if (dp[mask][u] == INF) continue;
                // 尝试访问新博物馆 v
                for (int v = 1; v <= n; v++) {
                    if (mask & (1 << (v - 1))) continue;  // 已访问
                    if (dist[u][v] == INF) continue;  // 不可达
                    int newMask = mask | (1 << (v - 1));
                    // 检查新掩码的总花费是否超预算
                    if (maskCost[newMask] > d) continue;
                    int newTime = dp[mask][u] + dist[u][v] + 15;
                    int backHomeTime = newTime + dist[v][0];
                    if (backHomeTime <= t) {
                        if (newTime < dp[newMask][v]) dp[newMask][v] = newTime;
                        answer = max(answer, maskFun[newMask]);
                    }
                }
            }
        cout << "Case " << caseNo << ": ";
        if (answer == 0) cout << "No possible trip.";
        else cout << answer;
        cout << '\n';
    }
    return 0;
}
