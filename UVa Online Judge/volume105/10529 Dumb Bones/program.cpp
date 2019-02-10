// Dumb Bones
// UVa ID: 10529
// Verdict: Accepted
// Submission Date: 2019-02-10
// UVa Run Time: 0.100s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double dp[1010], pl, pr;
    while (cin >> n, n > 0)
    {
        cin >> pl >> pr;
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = 1e20;
                for (int j = 0; j < i; j++)
                    dp[i] = min(dp[i], (dp[j] * (1 - pr) + dp[i - 1 - j] * (1 - pl)) / (1 - pl - pr));
            dp[i] += 1.0 / (1 - pl - pr);
        }
        cout << fixed << setprecision(2) << dp[n] << '\n';
    }

    return 0;
}
