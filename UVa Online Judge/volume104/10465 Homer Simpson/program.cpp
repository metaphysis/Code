// Homer Simpson
// UVa ID: 10465
// Verdict: Accepted
// Submission Date: 2018-01-17
// UVa Run Time: 0.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n, t, burgers[20010][2];
    
    while (cin >> m >> n >> t)
    {
        memset(burgers, 0, sizeof(burgers));

        burgers[0][0] = 1;
        for (int i = 0; i <= t; i++)
            if (burgers[i][0])
            {
                burgers[i + m][0] = 1;
                burgers[i + m][1] = max(burgers[i + m][1], burgers[i][1] + 1);
            }

        for (int i = 0; i <= t; i++)
            if (burgers[i][0])
            {
                burgers[i + n][0] = 1;
                burgers[i + n][1] = max(burgers[i + n][1], burgers[i][1] + 1);
            }

        if (burgers[t][0]) cout << burgers[t][1] << '\n';
        else
        {
            int maxb = 0, mint = 0x3fffffff;
            for (int i = t - 1; i >= 0; i--)
                if (burgers[i][0])
                {
                    maxb = burgers[i][1];
                    mint = t - i;
                    break;
                }

            cout << maxb << ' ' << mint << '\n';
        }
    }

    return 0;
}
