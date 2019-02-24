// Jin Ge Jin Qu Hao
// UVa ID: 12563
// Verdict: Accepted
// Submission Date: 2019-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, t, songs[60], sum;
    int jgjq = 678;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> n >> t;
        sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> songs[i];
            sum += songs[i];
        }
        
        if (sum + jgjq <= t)
        {
            cout << (n + 1) << ' ' << (sum + jgjq) << '\n';
            continue;
        }
        
        int up = min(t - 1, sum);
        int dp[up + 1][2] = {};
        dp[0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = up; j >= songs[i]; j--)
                if (dp[j - songs[i]][0])
                {
                    dp[j][0] = 1;
                    dp[j][1] = max(dp[j][1], dp[j - songs[i]][1] + 1);
                }
        int maxSongs = 0, maxi = 0;
        for (int i = 0; i <= up; i++)
        {
            if (!dp[i][0]) continue;
            if (dp[i][1] >= maxSongs)
            {
                maxSongs = dp[i][1];
                maxi = i;
            }
        }
        cout << (maxSongs + 1) << ' ' << (maxi + jgjq) << '\n';
    }

    return 0;
}
