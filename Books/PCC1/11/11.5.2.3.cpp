#include <bits/stdc++.h>

using namespace std;

const int MAXV = 310;

int n, sum[MAXV] = {0}, possible[MAXV][MAXV];
int stones[MAXV], dp[MAXV][MAXV];

int dfs(int i, int j)
{
    if (i >= j) return 0;
    if (~dp[i][j]) return dp[i][j];
    int r = 0;
    for (int s = i; s < j; s++)
        for (int t = s + 1; t <= j; t++)
            if (possible[s][t])
            {
                int erased = dfs(s + 1, t - 1);
                if (erased == sum[t - 1] - sum[s])
                {
                    erased += dfs(i, s - 1);
                    erased += dfs(t + 1, j);
                    erased += stones[s] + stones[t];
                    r = max(r, erased);
                }
            }
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> stones[i];
        sum[i] = sum[i - 1] + stones[i].second;
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
