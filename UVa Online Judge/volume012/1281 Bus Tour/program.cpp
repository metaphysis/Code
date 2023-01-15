// Bus Tour
// UVa ID: 1281
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, g[24][24], dp[2][1 << 18][20];

int dfs(int idx, int s, int last) {
    if (__builtin_popcount(s) == 1) return dp[idx][s][last] = g[idx ? n - 1 : 0][last + 1];
    if (~dp[idx][s][last]) return dp[idx][s][last];
    int r = INF;
    for (int b = 0; b < n - 2; b++)
        if (b != last && (s & (1 << b)))
            r = min(r, g[last + 1][b + 1] + dfs(idx, s ^ (1 << last), b));
    return dp[idx][s][last] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> n >> m) {
        memset(g, 0x3f, sizeof g);
        for (int i = 0; i < n; i++) g[i][i] = 0;
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            g[u][v] = g[v][u] = w;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        int r = INF;
        for (int i = 0; i < (1 << (n - 2)); i++)
            for (int j = 0; j < n - 2; j++)
                for (int k = 0; k < 2; k++)
                    dp[k][i][j] = -1;
        int MASK = (1 << (n - 2)) - 1;
        for (int s = 0; s < (1 << (n - 2)); s++) {
            if (__builtin_popcount(s) == (n - 2) / 2) {
                for (int b = 0; b < (n - 2); b++)
                    if (s & (1 << b)) {
                        dfs(0, s, b); dfs(0, (~s & MASK) | (1 << b), b);
                        dfs(1, s, b); dfs(1, (~s & MASK) | (1 << b), b);
                    }
                for (int i = 0; i < n - 2; i++)
                    if (s & (1 << i))
                        for (int j = 0; j < n - 2; j++)
                            if (s & (1 << j)) {
                                int m1 = (~s & MASK) | (1 << i);
                                int m2 = (~s & MASK) | (1 << j);
                                r = min(r, dp[0][s][i] + dp[1][m1][i] + dp[1][s][j] + dp[0][m2][j]);
                            }
            }
        }
        cout << "Case " << cases++ << ": " << r << '\n';
    }
    return 0;
}
