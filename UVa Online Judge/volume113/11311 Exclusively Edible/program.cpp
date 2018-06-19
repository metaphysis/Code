// Exclusively Edible
// UVa ID: 11311
// Verdict: Accepted
// Submission Date: 2018-06-18
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cache[50][50][50][50];

int setValue(int m, int n, int r, int c, int value)
{
    cache[m][n][r][c] = value;
    cache[m][n][m - r - 1][c] = value;
    cache[m][n][r][n - c - 1] = value;
    cache[m][n][m - r - 1][n - c - 1] = value;
    return value;
}

int dfs(int m, int n, int r, int c)
{
    if (~cache[m][n][r][c]) return cache[m][n][r][c];
    for (int i = 0; i < m; i++)
    {
        if (i < r && !dfs(m - (i + 1), n, r - (i + 1), c)) return setValue(m, n, r, c, 1);
        if (i > r && !dfs(i, n, r, c)) return setValue(m, n, r, c, 1);
    }
    for (int j = 0; j < n; j++)
    {
        if (j < c && !dfs(m, n - (j + 1), r, c - (j + 1))) return setValue(m, n, r, c, 1);
        if (j > c && !dfs(m, j, r, c)) return setValue(m, n, r, c, 1);
    }
    return setValue(m, n, r, c, 0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, m, n, r, c;
    cin >> cases;
    memset(cache, -1, sizeof(cache));
    cache[1][1][0][0] = 0;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m >> n >> r >> c;
        cout << (dfs(m, n, r, c) ? "Gretel" : "Hansel") << '\n';
    }

    return 0;
}
