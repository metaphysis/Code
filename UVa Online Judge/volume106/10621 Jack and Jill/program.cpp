// Jack and Jill
// UVa ID: 10621
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.800s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方向数组：N, E, S, W
const int MAXN = 32;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
const char dirChar[] = {'N', 'E', 'S', 'W'};

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
} jackStart, jackEnd, jillStart, jillEnd;

struct State {
    int x1, y1, x2, y2;
    string s1, s2;
} last;

string g[MAXN];
int visited[MAXN][MAXN][MAXN][MAXN], dist[MAXN][MAXN][MAXN][MAXN];
int n, limit;

bool bfs() {
    if (dist[jackStart.x][jackStart.y][jillStart.x][jillStart.y] < limit) return false;
    memset(visited, 0, sizeof visited);
    queue<State> q;
    q.push({jackStart.x, jackStart.y, jillStart.x, jillStart.y, "", ""});
    visited[jackStart.x][jackStart.y][jillStart.x][jillStart.y] = 1;
    while (!q.empty()) {
        State u = q.front(); q.pop();
        if (u.x1 == jackEnd.x && u.y1 == jackEnd.y && u.x2 == jillEnd.x && u.y2 == jillEnd.y) {
            last = u;
            return true;
        }
        int d1, d2;
        for (int i = 0; i < 4; i++) {
            int nx1, ny1;
            if (u.x1 == jackEnd.x && u.y1 == jackEnd.y) nx1 = u.x1, ny1 = u.y1, d1 = -1;
            else {
                nx1 = u.x1 + dx[i], ny1 = u.y1 + dy[i];
                if (nx1 < 0 || nx1 >= n || ny1 < 0 || ny1 >= n) continue;
                if (g[nx1][ny1] == '*' || g[nx1][ny1] == 'h' || g[nx1][ny1] == 's') continue;
                d1 = i;
            }
            for (int j = 0; j < 4; j++) {
                int nx2, ny2;
                if (u.x2 == jillEnd.x && u.y2 == jillEnd.y) nx2 = u.x2, ny2 = u.y2, d2 = -1;
                else {
                    nx2 = u.x2 + dx[j], ny2 = u.y2 + dy[j];
                    if (nx2 < 0 || nx2 >= n || ny2 < 0 || ny2 >= n) continue;
                    if (g[nx2][ny2] == '*' || g[nx2][ny2] == 'H' || g[nx2][ny2] == 'S') continue;
                    d2 = j;
                }
                if (dist[nx1][ny1][nx2][ny2] >= limit && !visited[nx1][ny1][nx2][ny2]) {
                    visited[nx1][ny1][nx2][ny2] = 1;
                    string ns1 = u.s1, ns2 = u.s2;
                    if (d1 >= 0) ns1 += dirChar[d1];
                    if (d2 >= 0) ns2 += dirChar[d2];
                    q.push({nx1, ny1, nx2, ny2, ns1, ns2});
                }
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    bool firstCase = true;
    // 预计算平方距离表
    for (int a = 0; a < MAXN; a++)
        for (int b = 0; b < MAXN; b++)
            for (int c = 0; c < MAXN; c++)
                for (int d = 0; d < MAXN; d++)
                    dist[a][b][c][d] = (a - c) * (a - c) + (b - d) * (b - d);
    while (cin >> n && n) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        // 读取地图并定位关键点
        for (int i = 0; i < n; ++i) {
            cin >> g[i];
            for (int j = 0; j < n; ++j) {
                if (g[i][j] == 'H') jackStart = Point(i, j);
                else if (g[i][j] == 'S') jackEnd = Point(i, j);
                else if (g[i][j] == 'h') jillStart = Point(i, j);
                else if (g[i][j] == 's') jillEnd = Point(i, j);
            }
        }
        // 二分搜索，最大化最小平方距离
        int left = 0, right = 2 * n * n, best;
        while (left <= right) {
            limit = (left + right) / 2;
            if (bfs()) { best = limit; left = limit + 1; }
            else right = limit - 1;
        }
        // 输出结果
        cout << fixed << setprecision(2) << sqrt(best) << '\n';
        cout << last.s1 << '\n' << last.s2 << '\n';
    }
    return 0;
}
