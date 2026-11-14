#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210, INF = 0x7f7f7f7f;

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

    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        for (int i = 1; i <= n; i++) {
            a[n + i] = a[i];
            sum[n + i] = sum[n + i - 1] + a[n + i];
        }
        memset(dp, -1, sizeof(dp));
        int r = INF;
        for (int i = 1; i <= n; i++)
            r = min(r, dfs(i, n + i - 1));
        cout << r << '\n';
    }

    return 0;
}
