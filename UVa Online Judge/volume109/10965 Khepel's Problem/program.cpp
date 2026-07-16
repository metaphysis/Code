// Khepel's Problem
// UVa ID: 10965
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Sprinkler {
    int r, c, p, R, init;
};

int getDirIndex(char ch) {
    if (ch == 'N') return 0;
    if (ch == 'E') return 1;
    if (ch == 'S') return 2;
    return 3;
}

long long ceilDiv(long long a, long long b) {
    if (a >= 0) return (a + b - 1) / b;
    else return a / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, k;
    while (cin >> m >> n >> k) {
        if (m == 0 && n == 0 && k == 0) break;
        vector<vector<bool>> safe(m, vector<bool>(n, true));
        vector<Sprinkler> sprs;
        sprs.reserve(k);
        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};
        for (int i = 0; i < k; ++i) {
            int r, c, p, R;
            char d;
            cin >> r >> c >> p >> R >> d;
            --r; --c;
            safe[r][c] = false;
            sprs.push_back({r, c, p, R, getDirIndex(d)});
        }
        long long a, b;
        cin >> a >> b;
        for (const auto &sp : sprs) {
            long long T = (long long)sp.p + 1;
            for (int dir = 0; dir < 4; ++dir) {
                int needMod = (dir - sp.init + 4) % 4;
                long long low = a - sp.p + 1;
                long long high = b;
                long long jMin = ceilDiv(low, T);
                if (jMin < 0) jMin = 0;
                long long jMax = high / T;
                if (jMin > jMax) continue;
                long long rem = (needMod - jMin % 4 + 4) % 4;
                long long first = jMin + rem;
                if (first > jMax) continue;
                for (int step = 1; step <= sp.R; ++step) {
                    int nr = sp.r + dr[dir] * step;
                    int nc = sp.c + dc[dir] * step;
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) break;
                    safe[nr][nc] = false;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (safe[i][j]) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
