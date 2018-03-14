// Add Bricks in the Wall
// UVa ID: 11040
// Verdict: Accepted
// Submission Date: 2018-01-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, grid[10][10];
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        for (int i = 1; i <= 9; i += 2)
            for (int j = 1; j <= i; j += 2)
                cin >> grid[i][j];
        for (int i = 1; i <= 9; i += 2)
        {
            for (int j = 2; j <= 9; j += 2)
                grid[i][j] = (grid[i - 2][j - 1] - grid[i][j - 1] - grid[i][j + 1]) / 2;
        }
        for (int i = 2; i <= 9; i += 2)
            for (int j = 1; j <= i; j++)
                grid[i][j] = grid[i + 1][j] + grid[i + 1][j + 1];
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (j > 1) cout << ' ';
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
