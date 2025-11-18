// KuPellaKes
// UVa ID: 10968
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> graph(n + 1);
        vector<int> degree(n + 1, 0);
        
        // 构建图和计算度数
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        
        // 统计奇数度顶点
        vector<int> oddVertices;
        for (int i = 1; i <= n; i++)
            if (degree[i] % 2 != 0)
                oddVertices.push_back(i);
        
        // 情况一：没有奇数度顶点
        if (oddVertices.size() == 0) {
            bool allHaveNeighbors = true;
            for (int i = 1; i <= n; i++)
                if (degree[i] == 0) {
                    allHaveNeighbors = false;
                    break;
                }
            cout << (allHaveNeighbors ? "0" : "Poor Koorosh") << endl;
        }
        // 情况二：恰好有两个奇数度顶点
        else if (oddVertices.size() == 2) {
            int u = oddVertices[0], v = oddVertices[1];
            
            // 检查起点和终点是否满足度数条件
            if (degree[u] <= 1 || degree[v] <= 1) {
                cout << "Poor Koorosh" << endl;
                continue;
            }
            
            // BFS寻找最短路径
            vector<int> dist(n + 1, -1);
            queue<int> q;
            dist[u] = 0;
            q.push(u);
            
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                
                for (int neighbor : graph[current])
                    if (dist[neighbor] == -1)
                        // 中间顶点必须度数>2，终点v直接允许
                        if (neighbor == v || degree[neighbor] > 2) {
                            dist[neighbor] = dist[current] + 1;
                            q.push(neighbor);
                        }
            }
            
            cout << (dist[v] != -1 ? to_string(dist[v]) : "Poor Koorosh") << endl;
        }
        // 情况三：其他情况
        else
            cout << "Poor Koorosh" << endl;
    }
    return 0;
}
