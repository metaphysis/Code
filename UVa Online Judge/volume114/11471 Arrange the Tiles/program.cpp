// Arrange the Tiles
// UVa ID: 11471
// Verdict: Accepted
// Submission Date: 2018-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// https://github.com/arash16/prays/blob/master/UVA/vol-114/11471.cpp

#include <bits/stdc++.h>

using namespace std;

int typesOfTiles, cntOfTiles[12], grid[4][3];
string tiles[12];

int dfs(int i, int j)
{
    if (j == 3) i += 1, j = 0;
    if (i == 4) return 1;

    int cnt = 0;
    for (int type = 0; type < typesOfTiles; type++)
    {
        if (cntOfTiles[type] <= 0) continue;
        if (i && tiles[grid[i - 1][j]][2] != tiles[type][0]) continue;
        if (j && tiles[grid[i][j - 1]][1] != tiles[type][3]) continue;
        grid[i][j] = type;
        cnt += (cntOfTiles[type]--) * dfs(i, j + 1);
        cntOfTiles[type]++;
    }
    return cnt;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        for (int i = 0; i < 12; i++) cin >> tiles[i];

        sort(tiles, tiles + 12);

        cntOfTiles[0] = 1, typesOfTiles = 1;
        for (int i = 1; i < 12; i++)
            if (tiles[i] == tiles[typesOfTiles - 1])
                cntOfTiles[typesOfTiles - 1]++;
            else
            {
                tiles[typesOfTiles] = tiles[i];
                cntOfTiles[typesOfTiles++] = 1;
            }

        cout << "Case " << cs << ": " << dfs(0, 0) << '\n';
    }

    return 0;
}
