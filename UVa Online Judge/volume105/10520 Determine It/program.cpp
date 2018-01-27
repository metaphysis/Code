// Determine It
// UVa ID: 10520
// Verdict: Accepted
// Submission Date: 2018-01-28
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

long long dp[24][24], n, m;

long long dfs(int i, int j)
{
    if (dp[i][j] >= 0) return dp[i][j];
    if (i < j)
    {
        long long a = 0;
        for (int k = i; k < j; k++)
            a = max(a, dfs(i, k) + dfs(k + 1, j));
        dp[i][j] = a;
    }
    else
    {
        long long a = 0, b = 0;
        if (i < n)
        {
            for (int k = i + 1; k <= n; k++)
                a = max(a, dfs(k, 1) + dfs(k, j));
        }
        
        if (j > 0)
        {
            for (int k = 1; k < j; k++)
                b = max(b, dfs(i, k) + dfs(n, k));
        }
        
        dp[i][j] = a + b;
    }
    return dp[i][j];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        memset(dp, -1, sizeof(dp));
        dp[n][1] = m;
        dfs(1, n);
        cout << dp[1][n] << '\n';
    }

    return 0;
}
