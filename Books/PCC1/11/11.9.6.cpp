#include <bits/stdc++.h>

using namespace std;

const int MAXN = 310, INF = 0x7f7f7f7f;

int dp[MAXN][MAXN], K[MAXN][MAXN], n, a[MAXN], sum[MAXN] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) K[i][i] = i;
        for (int L = 2; L <= n; L++)
            for (int i = 1, j = L; j <= n; i++, j++)
            {
                dp[i][j] = INF;
                for (int k = K[i][j - 1]; k <= K[i + 1][j]; k++)
                {
                    int next = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                    if (next < dp[i][j])
                    {
                        dp[i][j] = next;
                        K[i][j] = k;
                    }
                }
            }
        cout << dp[1][n] << '\n';
    }

    return 0;
}
