// Game of Sum
// UVa ID: 10891
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, xi[110], sum[110];

int visited[110][110];
pair<int, int> dp[110][110];

pair<int, int> dfs(int i, int j)
{
    if (i > j) return pair<int, int>(0, 0);
    if (visited[i][j]) return dp[i][j];
    visited[i][j] = 1;
    pair<int, int> r(0, 0);
    for (int k = i; k <= j; k++)
    {
        int s = sum[k] - sum[i - 1];
        pair<int, int> next = dfs(k + 1, j);
        if (s + next.second > r.first)
        {
            r.first = s + next.second;
            r.second = next.first;
        }
        s = sum[j] - sum[k - 1];
        next = dfs(i, k - 1);
        if (s + next.second > r.first)
        {
            r.first = s + next.second;
            r.second = next.first;
        }
    }
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; i++)
        {
            cin >> xi[i];
            sum[i] = xi[i] + sum[i - 1];
        }
        
        memset(visited, 0, sizeof(visited));
        pair<int, int> r = dfs(1, n);
        cout << abs(r.first - r.second) << '\n';
    }

    return 0;
}
