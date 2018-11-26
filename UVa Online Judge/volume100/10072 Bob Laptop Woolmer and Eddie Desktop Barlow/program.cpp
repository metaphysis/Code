// Bob Laptop Woolmer and Eddie Desktop Barlow
// UVa ID: 10072
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int dp[100][10][10][10], n, bt[110], bl[110], fl[110];
    int AT, BL, AR;
    
    while (cin >> n, n > 0)
    {
        for (int i = 1, a, b, c; i <= n; i++)
        {
            cin >> a >> b >> c;
            bt[i] = (8 * a + 2 * c + 5) / 10;
            bl[i] = (7 * a + b + 2 * c + 5) / 10;
            fl[i] = (4 * a + 4 * b + 2 * c + 5) / 10;
        }
        cin >> AT >> BL >> AR;
        memset(dp, -1, sizeof(dp));
        dp[0][0][0][0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = AT; j >= 1; j--)
                for (int k = BL; k >= 0; k--)
                    for (int l = AR; l >= 0; l--)
                        if (~dp[i - 1][j - 1][k][l])
                            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j - 1][k][l] + bt[i]);
            for (int k = BL; k >= 1; k--)
                for (int j = AT; j >= 0; j--)
                    for (int l = AR; l >= 0; l--)
                        if (~dp[i - 1][j][k - 1][l])
                            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k - 1][l] + bl[i]);
            for (int l = AR; l >= 1; l--)
                for (int j = AT; j >= 1; j--)
                    for (int k = BL; k >= 1; k--)
                        if (~dp[i - 1][j][k][l - 1])
                            dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l - 1] + fl[i]);
        }
        if (cases++) cout << '\n';
        cout << "Team #" << cases << ":\n";
        cout << "Maximum Effective Score = " << dp[n][AT][BL][AR] << '\n';
        cout << "Batsmen :\n";
        cout << "Bowlers :\n";
        cout << "All-rounders :\n";
    }

    return 0;
}
