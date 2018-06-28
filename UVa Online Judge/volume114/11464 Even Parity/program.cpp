// Even Parity
// UVa ID: 11464
// Verdict: Accepted
// Submission Date: 2018-06-28
// UVa Run Time: 0.230s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, grid[15][15], parity[15][15], best;

void press(int i, int j)
{
    if (i - 1 >= 0) parity[i - 1][j] = !parity[i - 1][j];
    if (i + 1 < n) parity[i + 1][j] = !parity[i + 1][j];
    if (j - 1 >= 0) parity[i][j - 1] = !parity[i][j - 1];
    if (j + 1 < n) parity[i][j + 1] = !parity[i][j + 1];
}

void dfs(int i, int j, int cnt)
{
    if (cnt >= best) return;
    if (j == n)
    {
        dfs(i + 1, 0, cnt);
        return;
    }

    if (i == 0)
    {
        if (grid[i][j])
        {
            dfs(i, j + 1, cnt);
        }
        else
        {
            dfs(i, j + 1, cnt);
            
            press(i, j);
            dfs(i, j + 1, cnt + 1);
            press(i, j);
        }
    }
    else if (i == n)
    {
        bool ok = true;
        for (int k = 0; k < n; k++)
            if (parity[n - 1][k])
            {
                ok = false;
                break;
            }
        if (ok && cnt < best) best = cnt;
    }
    else
    {
        if (i >= 2)
        {
            bool ok = true;
            for (int k = 0; k < n; k++)
                if (parity[i - 2][k])
                {
                    ok = false;
                    break;
                }
            if (!ok) return;
        }
        if (parity[i - 1][j] && !grid[i][j])
        {
            press(i, j);
            dfs(i, j + 1, cnt + 1);
            press(i, j);
        }
        else
            dfs(i, j + 1, cnt);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int offset[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                parity[i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    int ii = i + offset[k][0], jj = j + offset[k][1];
                    if (ii >= 0 && ii < n && jj >= 0 && jj < n)
                        parity[i][j] += grid[ii][jj];
                }
                parity[i][j] %= 2;
            }

        best = 0x3f3f3f3f;
        dfs(0, 0, 0);

        cout << "Case " << cs << ": ";
        if (best == 0x3f3f3f3f) cout << "-1\n";
        else cout << best << '\n';
    }

    return 0;
}
