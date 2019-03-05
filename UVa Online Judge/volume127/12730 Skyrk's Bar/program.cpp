// Skyrk's Bar
// UVa ID: 12730
// Verdict: Accepted
// Submission Date: 2019-03-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, K;
double dp[1000001], sum[1000001];
    
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> K;
        sum[0] = 0;
        for (int i = 1; i <= N; i++)
        {
            if (i <= K + 1) dp[i] = 1;
            else dp[i] = 1 + 2.0 * sum[i - K - 1] / i;
            sum[i] = sum[i - 1] + dp[i];
        }
        cout << "Case #" << cs << ": ";
        cout << fixed << setprecision(4) << dp[N] << '\n';
    }

    return 0;
}
