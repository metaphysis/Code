// Arrange Some Marbles
// UVa ID: 11125
// Verdict: Accepted
// Submission Date: 2018-10-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int B, C, N[4], dp[4][4][4][4][5000];

int dfs(int d, int sc, int sn, int ec, int en, int mask)
{
    if (mask == 0)
    {
        if (d == 0 || (sc != ec && sn != en)) return 1;
        return 0;
    }
    if (~dp[sc][sn][ec][en][mask]) return dp[sc][sn][ec][en][mask];
    int r = 0;
    for (int c = 0; c < C; c++)
        for (int n = 1; n <= 3 && n <= N[c]; n++)
            if (c != ec && n != en)
            {
                N[c] -= n;
                r += dfs(d + 1, sc, sn, c, n, mask - (n << (c * 3)));
                N[c] += n;
            }
    return dp[sc][sn][ec][en][mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    memset(dp, -1, sizeof(dp));
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> C;
        memset(N, 0, sizeof(N));
        B = 0;
        for (int c = 0; c < C; c++)
        {
            cin >> N[c];
            B |= (N[c] << (c * 3));
        }
        if (B == 0)
        {
            cout << "1\n";
            continue;
        }
        int r = 0;
        for (int c = 0; c < C; c++)
            for (int n = 1; n <= 3 && n <= N[c]; n++)
            r += dfs(0, c, n, c, n, B - (n << (c * 3)));
        cout << r << '\n';
    }

    return 0;
}
