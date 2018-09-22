// ACORN
// UVa ID: 1231
// Verdict: Accepted
// Submission Date: 2018-09-22
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int t, h, f, acorn[2001][2001], dp[2001];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> t >> h >> f;
        for (int i = 1, a; i <= t; i++)
        {
            memset(acorn[i], 0, (h + 1) * sizeof(int));
            cin >> a;
            for (int j = 1, n; j <= a; j++)
            {
                cin >> n;
                acorn[i][n]++;
            }
        }

        memset(dp, 0, sizeof(dp));
        for (int tree = 1; tree <= t; tree++)
            dp[h] = max(dp[h], acorn[tree][h]);
        
        for (int height = h - 1; height >= 0; height--)
            for (int tree = 1; tree <= t; tree++)
            {
                acorn[tree][height] += max(acorn[tree][height + 1], (height + f <= h ? dp[height + f] : 0));
                dp[height] = max(dp[height], acorn[tree][height]);
            }

        cout << dp[0] << '\n';
    }

    return 0;
}
