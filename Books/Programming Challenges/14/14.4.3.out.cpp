#include <bits/stdc++.h>

using namespace std;

const int MAXN = 256;
int grid[MAXN][MAXN], visited[MAXN][MAXN], length;
int offsetx[4] = {1, -1, 0, 0}, offsety[4] = {0, 0, 1, -1};

void dfs(int x, int y)
{
    visited[x][y] = 1;
    for (int k = 0; k < 4; k++)
    {
        int nx = x + offsetx[k], ny = y + offsety[k];
        if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN) continue;
        if (visited[nx][ny]) continue;
        if (grid[nx][ny]) { length += 1; continue; }
        dfs(nx, ny);
    }
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        memset(grid, 0, sizeof(grid));
        int x1, y1, x2, y2;
        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            for (int x = x1; x < x2; x++)
                for (int y = y1; y < y2; y++)
                    grid[x][y] = 1;
        }
        memset(visited, 0, sizeof(visited));
        length = 0;
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                if (!grid[i][j] && !visited[i][j])
                    dfs(i, j);
        cout << "Case " << ++cases << ": " << length << '\n';
    }
    return 0;
}
