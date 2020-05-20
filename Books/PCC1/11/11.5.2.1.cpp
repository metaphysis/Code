#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x7f7f7f7f;

int dp[MAXN][MAXN], n, a[MAXN], sum[MAXN] = {0};

int dfs(int i, int j)
{
    if (~dp[i][j]) return dp[i][j];
    if (i == j) return 0;
    int r = INF;
    for (int k = i; k < j; k++)
        r = min(r, dfs(i, k) + dfs(k + 1, j) + sum[j] - sum[i - 1]);
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    bool useBottomUpMethod = true;

    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        
        if (useBottomUpMethod) {
            memset(dp, 0, sizeof(dp));
            for (int L = 2; L <= n; L++)
                for (int i = 1, j = L; j <= n; i++, j++) {
                    dp[i][j] = INF;
                    for (int k = i; k <= j; k++) {
                        int next = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                        dp[i][j] = min(dp[i][j], next);
                    }
                }
            cout << dp[1][n] << '\n';
        }
        else {
            memset(dp, -1, sizeof(dp));
            cout << dfs(1, n) << '\n';
        }
    }

    return 0;
}
