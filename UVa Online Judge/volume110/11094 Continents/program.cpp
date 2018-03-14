// Continents
// UVa ID: 11094
// Verdict: Accepted
// Submission Date: 2018-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int H, W, T, X, Y, nexti, nextj;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char grid[24][24];

void dfs(int i, int j, char old, char replaced)
{
    T++;
    grid[i][j] = replaced;
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = (j + offset[k][1] + W) % W;
        if (nexti >= 0 && nexti < H)
        {
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> H >> W)
    {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> grid[i][j];

        cin >> X >> Y;

        char land = grid[X][Y];

        dfs(X, Y, land, 0);

        int maxLand = 0;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] == land)
                {
                    T = 0;
                    dfs(i, j, grid[i][j], 0);
                    maxLand = max(maxLand, T);
                }

        cout << maxLand << '\n';
    }

    return 0;
}
