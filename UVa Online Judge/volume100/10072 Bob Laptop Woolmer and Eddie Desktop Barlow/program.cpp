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
    int dp[128][16][16][16], n, bt[128], bl[128], fl[110], track[128][16][16][16];
    int BT, BL, AR;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0, a, b, c; i < n; i++)
        {
            cin >> a >> b >> c;
            bt[i] = (8 * a + 2 * c + 5) / 10;
            bl[i] = (a + 7 * b + 2 * c + 5) / 10;
            fl[i] = (4 * a + 4 * b + 2 * c + 5) / 10;
        }
        cin >> BT >> BL >> AR;
        memset(dp, -1, sizeof(dp));
        dp[0][0][0][0] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= BT; j++)
                for (int k = 0; k <= BL; k++)
                    for (int l = 0; l <= AR; l++)
                        if (~dp[i][j][k][l])
                        {
                            if (dp[i][j][k][l] > dp[i + 1][j][k][l])
                            {
                                dp[i + 1][j][k][l] = dp[i][j][k][l];
                                track[i + 1][j][k][l] = 0;
                            }
                            if (dp[i][j][k][l] + bt[i] > dp[i + 1][j + 1][k][l])
                            {
                                dp[i + 1][j + 1][k][l] = dp[i][j][k][l] + bt[i];
                                track[i + 1][j + 1][k][l] = 1;
                            }
                            if (dp[i][j][k][l] + bl[i] > dp[i + 1][j][k + 1][l])
                            {
                                dp[i + 1][j][k + 1][l] = dp[i][j][k][l] + bl[i];
                                track[i + 1][j][k + 1][l] = 2;
                            }
                            if (dp[i][j][k][l] + fl[i] > dp[i + 1][j][k][l + 1])
                            {
                                dp[i + 1][j][k][l + 1] = dp[i][j][k][l] + fl[i];
                                track[i + 1][j][k][l + 1] = 3;
                            }
                        }
        if (cases++) cout << '\n';
        cout << "Team #" << cases << "\n";
        cout << "Maximum Effective Score = " << dp[n][BT][BL][AR] << '\n';
        vector<int> players[4];
        int idx = n, lastBT = BT, lastBL = BL, lastAR = AR;
        while (idx)
        {
            int playerType = track[idx][lastBT][lastBL][lastAR];
            players[playerType].push_back(idx);
            if (playerType == 1) lastBT--;
            if (playerType == 2) lastBL--;
            if (playerType == 3) lastAR--;
            idx--;
        }
        cout << "Batsmen :";
        reverse(players[1].begin(), players[1].end());
        for (auto p : players[1]) cout << ' ' << p;
        cout << '\n';
        cout << "Bowlers :";
        reverse(players[2].begin(), players[2].end());
        for (auto p : players[2]) cout << ' ' << p;
        cout << '\n';
        cout << "All-rounders :";
        reverse(players[3].begin(), players[3].end());
        for (auto p : players[3]) cout << ' ' << p;
        cout << '\n';
    }

    return 0;
}
