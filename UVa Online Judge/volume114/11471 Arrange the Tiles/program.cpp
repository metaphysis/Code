// Arrange the Tiles
// UVa ID: 11471
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ALL = 479001600, FACT10 = 3628800;

int fragile = 0, used[12], selected[2];
char tiles[12][4];

void addFragile()
{
    if (tiles[selected[0]][1] != tiles[selected[1]][3]) fragile += 8 * FACT10;
    if (tiles[selected[0]][2] != tiles[selected[1]][0]) fragile += 9 * FACT10;
    
}

void dfs(int depth)
{
    if (depth == 2)
    {
        addFragile();
        return;
    }
    for (int i = 0; i < 12; i++)
    {
        if (used[i]) continue;
        used[i] = 1, selected[depth] = i;
        dfs(depth + 1);
        used[i] = 0, selected[depth] = -1;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        char color;
        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 4; j++)
                cin >> tiles[i][j];

        memset(used, 0, sizeof(used));
        fragile = 0;
        dfs(0);
        cout << "Case " << cs << ": " << (ALL - fragile) << '\n';
    }

    return 0;
}
