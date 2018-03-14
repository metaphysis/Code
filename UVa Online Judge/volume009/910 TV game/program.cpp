// TV game
// UVa ID: 910
// Verdict: Accepted
// Submission Date: 2017-04-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// https://github.com/dmitrime/algorithmic-puzzles/blob/d608e78b7bbeee8e9cdfb9d80421186b984328e0/uva/910.cpp
// 原解题代码的状态转移方程有错误，以下为经过修正后能够AC的代码。

#include <bits/stdc++.h>

using namespace std;

struct status
{
    int s, e1, e2, spec;
};

int dp[40][40];
status carpet[40];

int main(int argc, char *argv[])
{
    int N;
    while (cin >> N)
    {
        memset(dp, 0, sizeof dp);
        memset(carpet, 0, sizeof carpet);

        for (int i = 0; i < N; i++)
        {
            char a, b, c, d;
            cin >> a >> b >> c >> d;
            carpet[i].s = a - 'A';
            carpet[i].e1 = b - 'A';
            carpet[i].e2 = c - 'A';

            carpet[i].spec = 0;
            if (d == 'x') carpet[i].spec = 1;
        }

        int m;
        cin >> m;

        dp[0][carpet[0].s] = 1;

        for (int i = 1; i <= m; i++)
            for (int k = 0; k < N; k++)
            {
                dp[i][carpet[k].e1] += dp[i - 1][carpet[k].s];
                dp[i][carpet[k].e2] += dp[i - 1][carpet[k].s];
            }

        int sum = 0;
        for (int k = 0; k < N; k++)
            if (carpet[k].spec)
                sum += dp[m][carpet[k].s];

        cout << sum << '\n';
    }

    return 0;
}
