// A Daisy Puzzle Game
// UVa ID: 12846
// Verdict: Accepted
// Submission Date: 2023-04-09
// UVa Run Time: 0.610s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, dp[1 << 21][21];

int dfs(int x, int y) {
    if (~dp[x][y]) return dp[x][y];
    for (int b = 0; b < y; b++) {
        if ((x & (1 << b)) &&
            !dfs(x ^ (1 << b), y)) return dp[x][y] = 1;
        if ((x & (1 << b)) &&
            (x & (1 << ((b + 1) % y))) &&
            !dfs(x ^ (1 << b) ^ (1 << ((b + 1) % y)), y)) return dp[x][y] = 1;
    }
    return dp[x][y] = 0;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= 20; i++) dp[0][i] = 0;
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> n >> m;
        int nn = (1 << n) - 1;
        for (int i = 0, b; i < m; i++) {
            cin >> b;
            b--;
            nn -= (1 << b);
        }
        cout << (dfs(nn, n) ? "yes" : "no") << '\n';
    }
    return 0;
}
