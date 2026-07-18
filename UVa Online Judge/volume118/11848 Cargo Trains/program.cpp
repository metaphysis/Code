// Cargo Trains
// UVa ID: 11848
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.190s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
int cA[MAXN][MAXN], cB[MAXN][MAXN];
bool hasEdge[MAXN][MAXN];
int p[MAXN][MAXN], q[MAXN][MAXN];
int n;

// 对给定的 a 执行朴素 Dijkstra，返回最短路径费用
double dijkstra(double a) {
    double dist[MAXN];
    bool vis[MAXN];
    for (int i = 0; i < n; ++i) { dist[i] = 1e100; vis[i] = false; }
    dist[0] = 0;
    for (int iter = 0; iter < n; ++iter) {
        int u = -1;
        double minD = 1e100;
        for (int i = 0; i < n; ++i)
            if (!vis[i] && dist[i] < minD) { minD = dist[i]; u = i; }
        if (u == -1 || minD == 1e100) break;
        if (u == n - 1) break;          // 已到达汇点
        vis[u] = true;
        for (int v = 0; v < n; ++v)
            if (hasEdge[u][v] && !vis[v]) {
                double w = (double)p[u][v] * a + (double)q[u][v];
                if (dist[u] + w < dist[v]) dist[v] = dist[u] + w;
            }
    }
    return dist[n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        if (n == -1) break;
        int ma, mb, k;
        cin >> ma >> mb >> k;
        // 初始化
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                cA[i][j] = cB[i][j] = -1;
                hasEdge[i][j] = false;
                p[i][j] = q[i][j] = 0;
            }
        // 读入 A 公司边
        for (int i = 0; i < ma; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            cA[u][v] = cA[v][u] = c;
        }
        // 读入 B 公司边
        for (int i = 0; i < mb; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            cB[u][v] = cB[v][u] = c;
        }
        // 合并边，构造线性参数 p 和 q
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                if (cA[i][j] != -1 || cB[i][j] != -1) {
                    hasEdge[i][j] = hasEdge[j][i] = true;
                    if (cA[i][j] != -1 && cB[i][j] != -1) {
                        p[i][j] = cA[i][j] - cB[i][j];
                        q[i][j] = cB[i][j];
                    } else if (cA[i][j] != -1) {
                        p[i][j] = 0;
                        q[i][j] = cA[i][j];
                    } else {
                        p[i][j] = 0;
                        q[i][j] = cB[i][j];
                    }
                    p[j][i] = p[i][j];
                    q[j][i] = q[i][j];
                }
            }
        // 处理每个查询
        for (int i = 0; i < k; ++i) {
            double a;
            cin >> a;
            double ans = dijkstra(a);
            long long result = (long long)(ans + 1e-9);   // 截断（向下取整）
            cout << result << '\n';
        }
    }
    return 0;
}
