// Counting Stars
// UVa ID: 11244
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int H, W, T, nexti, nextj;
int offset[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
char grid[110][110];

void dfs(int i, int j, char old, char replaced)
{
    T++;
    grid[i][j] = replaced;
    for (int k = 0; k < 8; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < H && nextj >= 0 && nextj < W)
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> H >> W)
    {
        if (H == 0 && W == 0) break;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> grid[i][j];

        int stars = 0;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] == '*')
                {
                    T = 0;
                    dfs(i, j, grid[i][j], '.');
                    if (T == 1) stars++;
                }
        cout << stars << '\n';
    }

    return 0;
}
