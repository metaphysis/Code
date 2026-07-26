// Men at Work
// UVa ID: 1130
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.040s
// https://blog.csdn.net/metaphysis/article/details/163213913

#include <bits/stdc++.h>
using namespace std;

const int MOD = 2520;          // 1~9 的最小公倍数
int N;
vector<string> grid;           // 初始状态，'.' 开放，'*' 阻塞
vector<string> period;         // 周期数字字符 '0'~'9'
int dist[50][50][2520];        // 距离数组，-1 表示未访问

// 判断 (r,c) 在时间 t（t 已对 MOD 取模）是否开放
bool isOpen(int r, int c, int t) {
    int d = period[r][c] - '0';
    if (d == 0) return grid[r][c] == '.';
    int k = t / d;
    bool initOpen = (grid[r][c] == '.');
    if (k % 2 == 0) return initOpen;
    return !initOpen;
}

int solve() {
    // 起点在时间 0 必须开放
    if (!isOpen(0, 0, 0)) return -1;
    memset(dist, -1, sizeof(dist));
    queue<tuple<int,int,int>> q;
    dist[0][0][0] = 0;
    q.push({0, 0, 0});
    int dr[5] = {0, 1, -1, 0, 0};  // 停留、下、上、右、左
    int dc[5] = {0, 0, 0, 1, -1};
    while (!q.empty()) {
        auto [r, c, tm] = q.front(); q.pop();
        if (r == N - 1 && c == N - 1) return dist[r][c][tm];
        int nt = (tm + 1) % MOD;
        for (int i = 0; i < 5; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (!isOpen(nr, nc, nt)) continue;
            if (dist[nr][nc][nt] == -1) {
                dist[nr][nc][nt] = dist[r][c][tm] + 1;
                q.push({nr, nc, nt});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> N) {
        grid.resize(N);
        period.resize(N);
        for (int i = 0; i < N; i++) cin >> grid[i];
        for (int i = 0; i < N; i++) cin >> period[i];
        if (!firstCase) cout << '\n';
        firstCase = false;
        int ans = solve();
        if (ans == -1) cout << "NO\n";
        else cout << ans << '\n';
    }
    return 0;
}
