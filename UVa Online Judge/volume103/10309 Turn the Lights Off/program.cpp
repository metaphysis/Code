// Turn the Lights Off
// UVa ID: 10309
// Verdict: Accepted
// Submission Date: 2018-06-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int best, grid[10][10];

void press(int i, int j)
{
    grid[i][j] = !grid[i][j];
    if (i - 1 >= 0) grid[i - 1][j] = !grid[i - 1][j];
    if (i + 1 < 10) grid[i + 1][j] = !grid[i + 1][j];
    if (j - 1 >= 0) grid[i][j - 1] = !grid[i][j - 1];
    if (j + 1 < 10) grid[i][j + 1] = !grid[i][j + 1];
}

int finished = 0;

void dfs(int i, int j, int cnt)
{
    if (finished) return;
    if (j == 10)
    {
        dfs(i + 1, 0, cnt);
        return;
    }
    
    if (i == 0)
    {
        dfs(i, j + 1, cnt);

        press(i, j);
        dfs(i, j + 1, cnt + 1);
        press(i, j);
    }
    else if (i == 10)
    {
        bool ok = true;
        for (int k = 0; k < 10; k++)
            if (grid[9][k])
            {
                ok = false;
                break;
            }
        if (ok && cnt < best)
        {
            best = cnt;
            finished = 1;
        }
    }
    else
    {
        if (i >= 2)
        {
            bool ok = true;
            for (int k = 0; k < 10; k++)
                if (grid[i - 2][k])
                {
                    ok = false;
                    break;
                }
            if (!ok) return;
        }
        if (grid[i - 1][j])
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

    string name;
    while (getline(cin, name))
    {
        if (name == "end") break;
        char light;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
            {
                cin >> light;
                grid[i][j] = (light == '#' ? 0 : 1);
            }
        best = 100, finished = 0;
        dfs(0, 0, 0);
        cout << name << ' ' << best << '\n';
        cin.ignore(256, '\n');
    }

    return 0;
}
