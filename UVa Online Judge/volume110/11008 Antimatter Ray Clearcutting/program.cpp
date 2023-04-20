// Antimatter Ray Clearcutting
// UVa ID: 11008
// Verdict: Accepted
// Submission Date: 2023-04-20
// UVa Run Time: 0.210s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    point operator - (point p) { return point(x - p.x, y - p.y); };
} ps[20];

int cross(point a, point b) { return a.x * b.y - b.x * a.y; }

int n, m, mask[20][20], dp[1 << 16];

int dfs(int bit) {
    if (~dp[bit]) return dp[bit];
    int cutted = __builtin_popcount(bit);
    if (cutted >= m) return 0;
    if (n - cutted <= 2) return dp[bit] = 1;
    int r = INF, nbit = ~bit & ((1 << n) - 1);
    for (int i = __builtin_ctz(nbit); i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (nbit & (1 << i) && nbit & (1 << j))
                r = min(r, 1 + dfs(bit | mask[i][j]));
    return dp[bit] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        if (cs > 1) cout << '\n';
        cout << "Case #" << cs << ":\n";
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                mask[i][j] = 0;
                for (int k = 0; k < n; k++)
                    if (cross(ps[j] - ps[i], ps[k] - ps[i]) == 0)
                        mask[i][j] |= (1 << k);
            }
        memset(dp, -1, sizeof dp);
        cout << dfs(0) << '\n';
    }
    return 0;
}
