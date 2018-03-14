// Squares (II)
// UVa ID: 559
// Verdict: Accepted
// Submission Date: 2017-04-23
// UVa Run Time: 0.880s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int games, h, w, m, dp[1100][1100] = {0};
    int r, c, s;

    cin >> games;

    for (int g = 1; g <= games; g++)
    {
        cin >> h >> w >> m;

        for (int y = 1; y <= h; y++)
        {
            for (int x = 1; x <= w; x++)
                dp[y][x] = 1;
            dp[y][w + 1] = 0;
        }

        for (int i = 1; i <= m; i++)
        {
            cin >> r >> c;

            // translate coordinate.
            r = h - r + 1;
            
            // find the maximum size of square at (r, c).
            for (int i = 1; i <= r; i++)
                for (int j = w; j >= 1; j--)
                    if (dp[i][j])
                            dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j + 1], dp[i][j + 1])) + 1;

            // fill the occupied cell.
            s = dp[r][c];
            for (int y = 0; y < s; y++)
                for (int x = 0; x < s; x++)
                    dp[r - y][c + x] = 0;
        }

        // find the maximum size of square with smallest r and c.
        s = 0;
        for (int i = 1; i <= h; i++)
            for (int j = w; j >= 1; j--)
                if (dp[i][j])
                {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j + 1], dp[i][j + 1])) + 1;

                    if (s < dp[i][j] || (s == dp[i][j] && (i > r || j < c)))
                    {
                        s = dp[i][j];
                        r = i, c = j;
                    }
                }

        if (s == 0)
            cout << "game over\n";
        else
        {
            r = h - r + 1;
            cout << r << ' ' << c << ' ' << s << '\n';
        }
    }

	return 0;
}
