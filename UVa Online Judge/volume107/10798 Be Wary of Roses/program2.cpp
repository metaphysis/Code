// Be Wary of Roses
// UVa ID: 10798
// Verdict: Accepted
// Submission Date: 2025-12-23
// UVa Run Time: 0.270s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 24, MAXM = 12;
int offset[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

struct state {
    int x, y, l, u, r, d, w;
    state (int x = 0, int y = 0, int l = 0, int u = 0, int r = 0, int d = 0): x(x), y(y), l(l), u(u), r(r), d(d) {
        w = max(max(l, r), max(u, d));
    }
    bool operator<(const state& s) const { return w > s.w; }
};

int n, visited[MAXN][MAXN][MAXM][MAXM][MAXM][MAXM];
string g[MAXN];

int bfs (int x, int y) {
    memset(visited, 0, sizeof(visited));
    priority_queue<state> q;
    visited[x][y][0][0][0][0] = 1;
    q.push(state(x, y, 0, 0, 0, 0));
    while (!q.empty()) {
        state current = q.top(); q.pop();
        for (int i = 0; i < 4; i++) {
            state nxt = current;
            int x = current.x + offset[i][0], y = current.y + offset[i][1];
            if (x < 0 || x >= n || y < 0 || y >= n) return current.w;
            nxt.x = x, nxt.y = y;
            if (g[x][y] == 'R') nxt.l++;
            if (g[y][n - 1 - x] == 'R') nxt.u++;
            if (g[n - 1 - x][n - 1 - y] == 'R') nxt.r++;
            if (g[n - 1 - y][x] == 'R') nxt.d++;
            if (visited[x][y][nxt.l][nxt.u][nxt.r][nxt.d]) continue;
            visited[x][y][nxt.l][nxt.u][nxt.r][nxt.d] = 1;
            q.push(state(x, y, nxt.l, nxt.u, nxt.r, nxt.d));
        }
    }
    return -1;
}

int main () {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> g[i];
        cout << "At most " << bfs(n / 2, n / 2) << " rose(s) trampled.\n";
    }
    return 0;
}
