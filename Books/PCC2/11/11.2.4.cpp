#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;

unsigned long long dp[MAXN][MAXN];

unsigned long long ip(int n, int m)
{
    if (dp[n][m]) return dp[n][m];
    if (n == 1 || m == 1) dp[n][m] = 1;
    else if (n < m) dp[n][m] = ip(n, n);
    else if (n == m) dp[n][m] = 1 + ip(n, m - 1);
    else dp[n][m] = ip(n, m - 1) + ip(n - m, m);
    return dp[n][m];
}

int main(int argc, char *argv[])
{
    int n, m;

    while (cin >> n >> m)
    {
        memset(dp, 0, sizeof(dp));
        cout << ip(n, m) << '\n';
    }

    return 0;
}
