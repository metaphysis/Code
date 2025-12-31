// The Rock
// UVa ID: 10381
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 45;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

string g[MAXN];  // 地图
int n, m;        // 行数和列数
int dist[MAXN][MAXN];  // BFS距离数组
int worst[MAXN][MAXN][4];  // worst[x][y][d]: 如果从(x,y)往方向d走的邻居是墙，从(x,y)到出口的距离
int dp[MAXN][MAXN][MAXN * MAXN];  // dp[x][y][w]: 到达(x,y)时已走w步的最小最坏情况值

// A* 搜索，返回最坏情况下的最短路径长度
int solve(int sx, int sy, int ex, int ey) {
    using state = tuple<int, int, int, int>;  // h, w, x, y
    priority_queue<state, vector<state>, greater<state>> pq;
    pq.push({0, 0, sx, sy});
    memset(dp, 0x3f, sizeof(dp));  // 初始化为无穷大
    dp[sx][sy][0] = 0;
    while (!pq.empty()) {
        auto [h, w, x, y] = pq.top(); pq.pop();
        // 如果当前h值不是最优，跳过
        if (h > dp[x][y][w]) continue;
        // 到达出口，返回答案
        if (x == ex && y == ey) return h;
        // 尝试四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            // 检查边界和是否可走
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (g[nx][ny] == '#' || g[nx][ny] == 'E') continue;
            int nh = 0;  // 新的最坏情况值
            if (g[nx][ny] == '.') {
                // 走到空地：考虑如果(nx,ny)是墙的最坏情况
                nh = max(h, w + worst[x][y][i]);
            } else if (g[nx][ny] == 'X') {
                // 走到出口：直接到达，总步数=w
                nh = max(h, w);
            }
            // 更新 dp，如果找到更优解则加入队列
            if (dp[nx][ny][w + 1] > nh) {
                dp[nx][ny][w + 1] = nh;
                pq.push({nh, w + 1, nx, ny});
            }
        }
    }
    return 0;  // 实际上不会执行到这里，因为题目保证有解
}

// BFS 计算从 (sx,sy) 到所有点的最短距离
void bfs(int sx, int sy) {
    memset(dist, 0x3f, sizeof(dist));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;
    while (!q.empty()) {
        auto [sx, sy] = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = sx + dx[i], ny = sy + dy[i];
              if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (g[nx][ny] == '#' || dist[nx][ny] <= dist[sx][sy] + 1) continue;
            dist[nx][ny] = dist[sx][sy] + 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> g[i];
        int sx, sy, ex, ey;  // 起点和终点坐标
        // 找到起点和终点
        memset(worst, 0, sizeof(worst));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'E') {
                    sx = i;
                    sy = j;
                }
                if (g[i][j] == 'X') {
                    ex = i;
                    ey = j;
                }
            }
        }
        // 预处理 worst 数组
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] != '.') continue;  // 只有空地可能变成墙
                // 假设 (i,j) 是墙
                g[i][j] = '#';
                bfs(ex, ey);  // 从出口做 BFS
                // 更 新(i,j) 的四个邻居的 worst 值
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (g[nx][ny] == '#') continue;
                    // (k + 2) % 4 是从 (nx,ny) 到 (i,j) 的方向的反方向
                    worst[nx][ny][(k + 2) % 4] = dist[nx][ny];
                }
                // 恢复地图
                g[i][j] = '.';
            }
        }
        int result = solve(sx, sy, ex, ey);
        cout << result << '\n';
    }
    return 0;
}
