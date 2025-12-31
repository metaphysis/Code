// Optimal Symmetric Paths
// UVa ID: 12295
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const int MOD = 1000000009, INF = 0x3f3f3f3f;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int dist[MAXN][MAXN], grid[MAXN][MAXN], cost[MAXN][MAXN], dp[MAXN * MAXN];
vector<int> g[MAXN * MAXN];         // 隐式图的邻接表
vector<int> parent[MAXN * MAXN];    // 每个节点的最短路径前驱节点

// 记忆化搜索：从节点 u 出发到达副对角线的最优路径数量
int dfs(int u) {
    int answer = 0;
    for (auto v : g[u]) {
        if (~dp[v]) answer = (answer + dp[v]) % MOD;
        else answer = (answer + dfs(v)) % MOD;
    }
    return dp[u] = answer;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        // 读入网格
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        // 计算对称权重矩阵，仅考虑副对角线及其左上方区域
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i + j >= n) continue;  // 忽略右下方区域
                int si = n - 1 - j, sj = n - 1 - i;  // 对称点坐标
                if (i + j == n - 1) cost[i][j] = grid[i][j];  // 副对角线上的点
                else cost[i][j] = grid[i][j] + grid[si][sj];   // 非对角线点，加上对称点权重
            }
        // Dijkstra 求最短路径
        memset(dist, 0x3f, sizeof dist);
        for (int i = 0; i < n * n; i++) parent[i].clear();
        dist[0][0] = cost[0][0];
        using state = tuple<int, int, int>;
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push({dist[0][0], 0, 0});
        while (!pq.empty()) {
            auto [d, x, y] = pq.top(); pq.pop();
            if (d > dist[x][y]) continue;
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir], ny = y + dy[dir];
                // 确保在网格内且位于副对角线左上方
                if (nx < 0 || nx >= n || ny < 0 || ny >= n || nx + ny >= n) continue;
                int nd = d + cost[nx][ny];
                if (nd < dist[nx][ny]) {
                    dist[nx][ny] = nd;
                    pq.push({nd, nx, ny});
                    parent[nx * n + ny].clear();
                    parent[nx * n + ny].push_back(x * n + y);
                } else if (nd == dist[nx][ny]) {
                    parent[nx * n + ny].push_back(x * n + y);
                }
            }
        }
        // 构建隐式图：从每个节点的前驱节点连边
        for (int i = 0; i < n * n; i++) g[i].clear();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i + j >= n) continue;
                for (auto p : parent[i * n + j])
                    g[p].push_back(i * n + j);
            }
        // 初始化记忆数组
        memset(dp, -1, sizeof dp);
        // 找出到达副对角线的最小总权重
        int best = INF;
        for (int i = 0; i < n; i++) best = min(best, dist[i][n - 1 - i]);
        // 设置副对角线上节点的 dp 值
        for (int i = 0; i < n; i++) dp[i * n + n - 1 - i] = dist[i][n - 1 - i] == best;
        // 从起点 (0,0) 开始 DFS 统计最优路径数量
        cout << dfs(0) << "\n";
    }
    return 0;
}
