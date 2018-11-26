// Cycle Game
// UVa ID: 1561
// Verdict: Accepted
// Submission Date: 2018-11-09
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, numbers[24], dp[24][32][32];

int dfs(int u)
{
    int v = (u - 1 + n) % n;
    int &r = dp[u][numbers[v]][numbers[u]];
    if (~r) return r;
    for (int c = 1; c <= numbers[v]; c++)
    {
        numbers[v] -= c;
        if (!dfs(v)) r = 1;
        numbers[v] += c;
        if (~r) return r;
    }
    for (int c = 1; c <= numbers[u]; c++)
    {
        numbers[u] -= c;
        if (!dfs((u + 1) % n)) r = 1;
        numbers[u] += c;
        if (~r) return r;
    }
    return r = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> numbers[i];
        memset(dp, -1, sizeof(dp));
        cout << (dfs(0) ? "YES" : "NO");
        cout << '\n';
    }

    return 0;
}
