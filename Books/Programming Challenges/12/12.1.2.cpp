#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
char grid[MAXN][MAXN];
int rows, columns, total = 0;
int offset[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

void dfs1(int i, int j, char old, char replaced)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns && grid[i][j] == old)
    {
        total++;
        grid[i][j] = replaced;
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                dfs1(i + x, j + y, old, replaced);
    }
}

void dfs2(int i, int j, char old, char replaced)
{
    total++;
    grid[i][j] = replaced;
    for (int k = 0; k < 8; k++)
    {
        int nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < rows && nextj >= 0 && nextj < columns)
            if (grid[nexti][nextj] == old)
                dfs2(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    
    return 0;
}

