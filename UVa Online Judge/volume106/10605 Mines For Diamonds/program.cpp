// Mines For Diamonds
// UVa ID: 10605
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int INF = 0x3f3f3f3f;
const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m, cnt;
char grid[MAXN][MAXN];
struct Point { int x, y; };
Point deposits[MAXN];

// 计算曼哈顿距离
inline int manhattan(Point a, Point b) { return abs(a.x - b.x) + abs(a.y - b.y);}

// BFS计算矿点到最近边界的距离
int bfs(int sx, int sy) {
    bool visited[MAXN][MAXN] = {false};
    queue<pair<Point, int>> q;
    q.push({{sx, sy}, 0});
    visited[sx][sy] = true;
    while (!q.empty()) {
        auto [pos, dist] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = pos.x + dirs[d][0], ny = pos.y + dirs[d][1];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (visited[nx][ny]) continue;
            if (grid[nx][ny] == '#') return dist + 1;
            visited[nx][ny] = true;
            q.push({{nx, ny}, dist + 1});
        }
    }
    return 0;  // 应该不会发生，因为网格被#包围
}

void solve() {
    // 读取输入
    scanf("%d%d", &n, &m);
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", grid[i] + 1);
        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '*')
                deposits[cnt++] = {i, j};
    }
    if (cnt == 0) {
        printf("0\n");
        return;
    }
    // 1. 计算每个矿点到边界的距离
    int dist[MAXN];
    for (int i = 0; i < cnt; ++i)
        dist[i] = bfs(deposits[i].x, deposits[i].y);
    // 2. 初始化DP数组
    int dp[1 << MAXN][MAXN], g[1 << MAXN], f[1 << MAXN];
    memset(dp, INF, sizeof(dp)); memset(g, INF, sizeof(g)); memset(f, INF, sizeof(f));
    // 初始化：单个矿点的链
    for (int i = 0; i < cnt; ++i) dp[1 << i][i] = dist[i];
    // 3. 计算dp[mask][i]：访问mask中的矿点，最后是i，形成一条链
    for (int mask = 1; mask < (1 << cnt); ++mask)
        for (int j = 0; j < cnt; ++j) {
            if (!(mask & (1 << j))) continue;
            if (dp[mask][j] == INF) continue;
            // 尝试从j扩展到其他矿点k
            for (int k = 0; k < cnt; ++k) {
                if (mask & (1 << k)) continue;  // k不在mask中
                int newMask = mask | (1 << k);
                int newDist = dp[mask][j] + manhattan(deposits[j], deposits[k]);
                if (newDist < dp[newMask][k]) {
                    dp[newMask][k] = newDist;
                }
            }
        }
    // 4. 计算g[mask]：mask中的矿点形成一条链的最小长度
    for (int mask = 1; mask < (1 << cnt); ++mask)
        for (int j = 0; j < cnt; ++j)
            if (mask & (1 << j))
                g[mask] = min(g[mask], dp[mask][j]);
    // 5. 计算f[mask]：访问mask中的矿点的最优解（可多条链）
    f[0] = 0;
    for (int mask = 1; mask < (1 << cnt); ++mask)
        // 枚举子集
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
            f[mask] = min(f[mask], f[mask ^ sub] + g[sub]);
    printf("%d\n", f[(1 << cnt) - 1]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}
