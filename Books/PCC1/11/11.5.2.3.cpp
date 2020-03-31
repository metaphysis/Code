#include <bits/stdc++.h>

using namespace std;

const int MAXV = 60;

int n, sum[MAXV] = {0}, possible[MAXV][MAXV];
int stones[MAXV], dp[MAXV][MAXV];

int dfs(int i, int j)
{
    if (i >= j) return 0;
    if (~dp[i][j]) return dp[i][j];
    int r = 0;
    for (int left = i; left < j; left++)
        for (int right = left + 1; right <= j; right++)
            if (possible[left][right])
            {
                int erased = dfs(left + 1, right - 1);
                if (erased == sum[right - 1] - sum[left])
                {
                    erased += dfs(i, left - 1);
                    erased += dfs(right + 1, j);
                    erased += stones[left] + stones[right];
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
