// Again Palindromes
// UVa ID: 10617
// Verdict: Accepted
// Submission Date: 2017-04-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int cases;
    string line;
    long long dp[100][100];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;

        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < line.length(); i++)
            for (int j = 0; j + i < line.length(); j++)
            {
                if (i == 0)
                    dp[j][j] = 1;
                else if (line[j] == line[j + i])
                    dp[j][j + i] = dp[j][j + i - 1] + dp[j + 1][j + i] + 1;
                else
                    dp[j][j + i] = dp[j][j + i - 1] + dp[j + 1][j + i] - dp[j + 1][j + i - 1];
            }

        cout << dp[0][line.length() - 1] << '\n';
    }
    return 0;
}
