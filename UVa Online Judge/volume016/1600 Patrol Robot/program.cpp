// Patrol Robot
// UVa ID: 1600
// Verdict: Accepted
// Submission Date: 2019-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct walk
{
    int r, c, k;
    walk (int r = 0, int c = 0, int k = 0): r(r), c(c), k(k) {}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, m, n, K, grid[32][32];
    int dp[32][32][32];
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m >> n >> K;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        memset(dp, 0x3f, sizeof(dp));
        queue<walk> q;
        q.push(walk(0, 0, 0));
        dp[0][0][0] = 0;
        while (!q.empty())
        {
            walk s = q.front(); q.pop();
            for (int d = 0; d < 4; d++)
            {
                int nr = s.r + dx[d], nc = s.c + dy[d];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                int nk = grid[nr][nc] ? (s.k + 1) : 0;
                if (nk > K) continue;
                if (dp[s.r][s.c][s.k] + 1 >= dp[nr][nc][nk]) continue;
                dp[nr][nc][nk] = dp[s.r][s.c][s.k] + 1;
                q.push(walk(nr, nc, nk));
            }
        }
        int best = 0x3f3f3f3f;
        for (int i = 0; i <= K; i++)
            best = min(best, dp[m - 1][n - 1][i]);
        if (best == 0x3f3f3f3f) best = -1;
        cout << best << '\n';
    }
    return 0;
}
