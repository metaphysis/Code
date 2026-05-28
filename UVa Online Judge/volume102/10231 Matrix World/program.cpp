// Matrix World
// UVa ID: 10231
// Verdict: Accepted
// Submission Date: 2026-05-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

struct State {
    int x, y, t;
};

int main() {
    int m, n, caseNo = 1;
    while (cin >> m >> n) {
        vector<string> grid(m);
        for (int i = 0; i < m; i++) cin >> grid[i];

        vector<pair<int, int>> treasures, guards;
        int sx = -1, sy = -1;

        // 收集位置信息：'*' 宝藏，'X' 警卫，'O' 起点
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '*') treasures.push_back({i, j});
                else if (grid[i][j] == 'X') guards.push_back({i, j});
                else if (grid[i][j] == 'O') sx = i, sy = j;
            }
        }

        int tCnt = treasures.size();

        // 多源BFS计算警卫到达每个格子的最短时间
        vector<vector<int>> guardTime(m, vector<int>(n, INF));
        queue<State> q;
        for (auto& g : guards) {
            guardTime[g.first][g.second] = 0;
            q.push({g.first, g.second, 0});
        }
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = cur.x + dx[d], ny = cur.y + dy[d];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if (grid[nx][ny] == '#') continue;
                if (guardTime[nx][ny] > cur.t + 1) {
                    guardTime[nx][ny] = cur.t + 1;
                    q.push({nx, ny, cur.t + 1});
                }
            }
        }

        // BFS计算从(sx,sy)到(tx,ty)的安全最短路径时间（移动时间）
        auto bfs = [&](int sx, int sy, int tx, int ty) -> int {
            if (sx == tx && sy == ty) return 0;
            vector<vector<int>> dist(m, vector<int>(n, INF));
            queue<State> qq;
            // 起点必须在警卫到达之前才能开始（严格小于）
            if (guardTime[sx][sy] > 0) {
                dist[sx][sy] = 0;
                qq.push({sx, sy, 0});
            }
            while (!qq.empty()) {
                State cur = qq.front(); qq.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = cur.x + dx[d], ny = cur.y + dy[d];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    if (grid[nx][ny] == '#') continue;
                    int nt = cur.t + 1;
                    if (nt >= guardTime[nx][ny]) continue;
                    if (dist[nx][ny] > nt) {
                        dist[nx][ny] = nt;
                        qq.push({nx, ny, nt});
                    }
                }
            }
            return dist[tx][ty];
        };

        // 建立距离矩阵：索引0是起点，1..tCnt是宝藏
        vector<vector<int>> dist(tCnt + 1, vector<int>(tCnt + 1, INF));
        vector<pair<int, int>> points;
        points.push_back({sx, sy});
        for (auto& t : treasures) points.push_back(t);

        for (int i = 0; i <= tCnt; i++) {
            for (int j = i + 1; j <= tCnt; j++) {
                int d1 = bfs(points[i].first, points[i].second, points[j].first, points[j].second);
                int d2 = bfs(points[j].first, points[j].second, points[i].first, points[i].second);
                if (d1 < INF) dist[i][j] = d1;
                if (d2 < INF) dist[j][i] = d2;
            }
        }

        // 状态压缩DP：dp[mask][last] = 收集完last后总时间（已包含收集的1秒）
        vector<vector<int>> dp(1 << tCnt, vector<int>(tCnt, INF));
        for (int i = 0; i < tCnt; i++) {
            int d = bfs(sx, sy, points[i + 1].first, points[i + 1].second);
            if (d < INF) {
                int collectEnd = d + 1;
                if (collectEnd < guardTime[points[i + 1].first][points[i + 1].second])
                    dp[1 << i][i] = collectEnd;
            }
        }

        for (int mask = 1; mask < (1 << tCnt); mask++) {
            for (int last = 0; last < tCnt; last++) {
                if (!(mask >> last & 1)) continue;
                if (dp[mask][last] == INF) continue;
                for (int nxt = 0; nxt < tCnt; nxt++) {
                    if (mask >> nxt & 1) continue;
                    int d = dist[last + 1][nxt + 1];
                    if (d >= INF) continue;
                    int arrive = dp[mask][last] + d;
                    int collectEnd = arrive + 1;
                    if (collectEnd < guardTime[points[nxt + 1].first][points[nxt + 1].second])
                        dp[mask | (1 << nxt)][nxt] = min(dp[mask | (1 << nxt)][nxt], collectEnd);
                }
            }
        }

        // 找出最大可收集宝藏数及最小时间
        int maxTreasures = 0, minTime = INF;
        for (int mask = 1; mask < (1 << tCnt); mask++) {
            int cnt = __builtin_popcount(mask);
            if (cnt < maxTreasures) continue;
            for (int last = 0; last < tCnt; last++) {
                if (dp[mask][last] < INF) {
                    if (cnt > maxTreasures) {
                        maxTreasures = cnt;
                        minTime = dp[mask][last];
                    } else if (cnt == maxTreasures) {
                        minTime = min(minTime, dp[mask][last]);
                    }
                }
            }
        }

        cout << "Case " << caseNo++ << ":\n";
        if (maxTreasures == 0) {
            cout << "No treasures can be collected.\n";
        } else {
            cout << "Maximum number of collectible treasures: " << maxTreasures << ".\n";
            cout << "Minimum Time: " << minTime << " sec.\n";
        }
        cout << "\n";
    }
    return 0;
}
