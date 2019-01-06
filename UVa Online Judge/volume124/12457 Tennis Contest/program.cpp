// Tennis Contest
// UVa ID: 12457
// Verdict: Accepted
// Submission Date: 2019-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, visited[64][64];
double p, dp[64][64];

double dfs(int idx, int win)
{
    if (idx == (2 * n - 1))
    {
        if (win >= n)
            return 1.0;
        else
            return 0.0;
    }
    
    if (visited[idx][win])
        return dp[idx][win];

    visited[idx][win] = 1;
    double r = 0;
    r += p * dfs(idx + 1, win + 1);
    r += (1.0 - p) * dfs(idx + 1, win);

    return dp[idx][win] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> p;
        memset(visited, 0, sizeof(visited));
        cout << fixed << setprecision(2) << dfs(0, 0) << '\n';
    }

    return 0;
}
