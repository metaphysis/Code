// Dropping Water Balloons
// UVa ID: 10934
// Verdict: Accepted
// Submission Date: 2020-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    unsigned long long dp[110][64] = {0};
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= 63; j++)
            dp[i][j] = dp[i - 1][j - 1] + 1 + dp[i][j - 1];
    int k;
    unsigned long long n;
    while (cin >> k >> n)
    {
        if (k == 0) break;
        bool flag = false;
        for (int i = 1; i <= 63; i++)
            if (dp[k][i] >= n)
            {
                cout << i << '\n';
                flag = true;
                break;
            }
        if (flag) continue;
        cout << "More than 63 trials needed.\n";
    }

    return 0;
}
