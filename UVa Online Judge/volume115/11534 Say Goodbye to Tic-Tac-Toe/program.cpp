// Say Goodbye to Tic-Tac-Toe
// UVa ID: 11534
// Verdict: Accepted
// Submission Date: 2019-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

string grid;
int T, sg[MAXN][3][3];
map<char, int> key = {{'X', 1}, {'O', 2}};

int dfs(int n, int l, int r)
{
    if (~sg[n][l][r]) return sg[n][l][r];
    if (n == 0) return sg[n][l][r] = 0;
    int visited[MAXN] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 2; j++)
        {
            if (i == 1 && j == l) continue;
            if (i == n && j == r) continue;
            int grundy = dfs(i - 1, l, j) ^ dfs(n - i, j, r);
            visited[grundy] = 1;
        }
    for (int g = 0; ; g++) if (!visited[g]) return sg[n][l][r] = g;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(sg, -1, sizeof(sg));
    cin >> T;
    while (T--)
    {
        cin >> grid;
        int l = 0, r = 0, moves = 0, n = 0, grundy = 0;
        for (auto c : grid)
        {
            if (c == '.') n++;
            else
            {
                r = key[c];
                grundy ^= dfs(n, l, r);
                l = r, n = 0, moves++;
            }
        }
        grundy ^= dfs(n, l, 0);
        if (moves & 1) grundy = !grundy;
        cout << (grundy ? "Possible." : "Impossible.") << '\n';
    }

    return 0;
}
