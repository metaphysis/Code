// Cellular Network
// UVa ID: 1456
// Verdict: Accepted
// Submission Date: 2019-02-10
// UVa Run Time: 0.080s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int n, w, p[110] = {};
    long long dp[110][110];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> w;
        for (int i = 1; i <= n; i++)
            cin >> p[i];
        sort(p + 1, p + n + 1, greater<int>());
        for (int i = 1; i <= n; i++)
            p[i] += p[i - 1];
        memset(dp, 0x7f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= w; j++)
                for (int k = 1; k <= i; k++)
                    dp[i][j] = min(dp[i][j], dp[k - 1][j - 1] + i * (p[i] - p[k - 1]));
        cout << fixed << setprecision(4) << 1.0 * dp[n][w] / p[n] << '\n';
    }

    return 0;
}
