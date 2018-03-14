// Flight Planner
// UVa ID: 10337
// Verdict: Accepted
// Submission Date: 2018-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    const int INF = 0x3fffffff;
    int cases, X, wind[1010][10], fuel[1010][10];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> X;
        X /= 100;

        for (int i = 9; i >= 0; i--)
            for (int j = 0; j < X; j++)
                cin >> wind[j][i];

        for (int i = 0; i <= X; i++)
            for (int j = 0; j <= 9; j++)
                fuel[i][j] = INF;

        fuel[0][0] = 0;
        for (int interval = 0; interval < X; interval++)
            for (int altitude = 0; altitude <= 9; altitude++)
                if (fuel[interval][altitude] < INF)
                {
                    if (altitude == 0)
                    {
                        fuel[interval + 1][altitude] = min(fuel[interval + 1][altitude],
                            fuel[interval][altitude] + 30 - wind[interval][altitude]);
                        fuel[interval + 1][altitude + 1] = min(fuel[interval + 1][altitude + 1],
                            fuel[interval][altitude] + 60 - wind[interval][altitude]);
                    }
                    else if (altitude == 9)
                    {
                        fuel[interval + 1][altitude] = min(fuel[interval + 1][altitude],
                            fuel[interval][altitude] + 30 - wind[interval][altitude]);
                        fuel[interval + 1][altitude - 1] = min(fuel[interval + 1][altitude - 1],
                            fuel[interval][altitude] + 20 - wind[interval][altitude]);
                    }
                    else
                    {
                        fuel[interval + 1][altitude] = min(fuel[interval + 1][altitude],
                            fuel[interval][altitude] + 30 - wind[interval][altitude]);
                        fuel[interval + 1][altitude + 1] = min(fuel[interval + 1][altitude + 1],
                            fuel[interval][altitude] + 60 - wind[interval][altitude]);
                        fuel[interval + 1][altitude - 1] = min(fuel[interval + 1][altitude - 1],
                            fuel[interval][altitude] + 20 - wind[interval][altitude]);
                    }
                }

        cout << fuel[X][0] << "\n\n";
    }

    return 0;
}
