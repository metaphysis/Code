// Warfare And Logistics
// UVa ID: 1416
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.860s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, m, L;
    while (cin >> n >> m >> L) {
        vector<tuple<int, int, int>> edges;
        vector<vector<long long>> originalDist(n + 1, vector<long long>(n + 1, INF));
        
        for (int i = 1; i <= n; i++)
            originalDist[i][i] = 0;
        
        // 存储所有边
        for (int i = 0; i < m; i++) {
            int a, b, s;
            cin >> a >> b >> s;
            edges.emplace_back(a, b, s);
            // 构建原始图时取最短的边
            if (s < originalDist[a][b]) {
                originalDist[a][b] = originalDist[b][a] = s;
            }
        }
        
        // 计算原始图的最短路径
        auto originalFloyd = originalDist;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (originalFloyd[i][k] < INF && originalFloyd[k][j] < INF)
                        originalFloyd[i][j] = min(originalFloyd[i][j], originalFloyd[i][k] + originalFloyd[k][j]);
        
        long long originalCost = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                originalCost += (originalFloyd[i][j] < INF ? originalFloyd[i][j] : L);
        
        long long maxCost = 0;
        
        // 对每条边尝试删除
        for (auto& e : edges) {
            int a = get<0>(e), b = get<1>(e), s = get<2>(e);
            
            // 重新初始化距离矩阵
            vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
            for (int i = 1; i <= n; i++)
                dist[i][i] = 0;
            
            // 构建删除该边后的图
            for (auto& edge : edges) {
                int u = get<0>(edge), v = get<1>(edge), w = get<2>(edge);
                // 如果是被删除的边，跳过
                if (u == a && v == b && w == s) continue;
                // 否则取最短的边
                if (w < dist[u][v]) {
                    dist[u][v] = dist[v][u] = w;
                }
            }
            
            // 计算删除该边后的最短路径
            for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        if (dist[i][k] < INF && dist[k][j] < INF)
                            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            
            long long newCost = 0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    newCost += (dist[i][j] < INF ? dist[i][j] : L);
            
            maxCost = max(maxCost, newCost);
        }
        
        cout << originalCost << " " << maxCost << endl;
    }
    return 0;
}
