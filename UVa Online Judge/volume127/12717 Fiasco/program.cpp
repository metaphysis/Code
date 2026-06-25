// Fiasco
// UVa ID: 12717
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;
int n, m, source;
int g[MAXN][MAXN];          // 存储分配后的边权，-1 表示无边
int origU[25005], origV[25005];  // 保存输入顺序的端点
bool visited[MAXN][MAXN];    // 标记边是否已在 BFS 中被分配

void bfs() {
    queue<int> q;
    int weight = 1;
    q.push(source);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] != -1 && !visited[u][v]) {
                // 边 (u,v) 第一次被发现，分配权重
                g[u][v] = g[v][u] = weight++;
                visited[u][v] = visited[v][u] = true;
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
    for (int cs = 1; cs <= T; ++cs) {
        cin >> n >> m >> source;

        // 初始化邻接矩阵
        memset(g, -1, sizeof(g));
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < m; ++i) {
            int w;
            cin >> origU[i] >> origV[i] >> w;
            // 仅标记存在边，权重暂存为 0（后续被覆盖）
            g[origU[i]][origV[i]] = g[origV[i]][origU[i]] = 0;
        }

        bfs();

        cout << "Case " << cs << ":\n";
        for (int i = 0; i < m; ++i)
            cout << origU[i] << ' ' << origV[i] << ' ' << g[origU[i]][origV[i]] << '\n';
    }
    return 0;
}
