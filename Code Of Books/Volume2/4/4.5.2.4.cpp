#include <bits/stdc++.h>

using namespace std;

const int MAXV = 310;

int n, possible[MAXV][MAXV];
int dp[MAXV][MAXV], stones[MAXV], sum[MAXV] = {0};

int dfs(int i, int j)
{
    if (i >= j) return 0;
    if (~dp[i][j]) return dp[i][j];
    if (possible[i][j]) {
        int erased = dfs(i + 1, j - 1);
        if (erased == sum[j - 1] - sum[i])
            return dp[i][j] = erased + stones[i] + stones[j];
    }
    int r = 0;
    for (int k = i; k < j; k++)
        r = max(r, dfs(i, k) + dfs(k + 1, j));
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> stones[i];
        sum[i] = sum[i - 1] + stones[i];
    }
    memset(possible, 0, sizeof possible);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (__gcd(stones[i], stones[j]) == 1)
                possible[i][j] = 1;
    memset(dp, -1, sizeof dp);
    cout << dfs(1, n) << '\n';

    return 0;
}
