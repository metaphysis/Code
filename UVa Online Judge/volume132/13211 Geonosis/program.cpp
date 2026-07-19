// Geonosis
// UVa ID: 13211
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 2.400s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> w(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> w[i][j];
        vector<int> del(n);
        for (int i = 0; i < n; ++i) cin >> del[i];
        // 反向插入顺序
        vector<int> rev(n);
        for (int i = 0; i < n; ++i) rev[i] = del[n - 1 - i];
        const long long INF = 1e18;
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        vector<bool> inS(n, false);
        long long ans = 0;
        for (int idx = 0; idx < n; ++idx) {
            int k = rev[idx];
            inS[k] = true;
            // 初始化与 k 直接相连的边（只对已加入的顶点）
            for (int i = 0; i < n; ++i) {
                if (inS[i] && i != k) {
                    dist[i][k] = w[i][k];
                    dist[k][i] = w[k][i];
                }
            }
            // 用旧集合 S\{k} 中的顶点作为中间点，更新到 k 的距离
            for (int a = 0; a < n; ++a) {
                if (!inS[a] || a == k) continue;
                for (int i = 0; i < n; ++i) {
                    if (!inS[i] || i == k) continue;
                    if (dist[i][k] > dist[i][a] + dist[a][k])
                        dist[i][k] = dist[i][a] + dist[a][k];
                    if (dist[k][i] > dist[k][a] + dist[a][i])
                        dist[k][i] = dist[k][a] + dist[a][i];
                }
            }
            // 用 k 作为中间点，更新旧集合内部点对的最短路径
            for (int i = 0; i < n; ++i) {
                if (!inS[i] || i == k) continue;
                for (int j = 0; j < n; ++j) {
                    if (!inS[j] || j == k) continue;
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
            // 计算当前集合所有有序点对距离之和
            long long total = 0;
            for (int i = 0; i < n; ++i) {
                if (!inS[i]) continue;
                for (int j = 0; j < n; ++j) {
                    if (!inS[j] || i == j) continue;
                    total += dist[i][j];
                }
            }
            ans += total;
        }
        cout << ans << '\n';
    }
    return 0;
}
