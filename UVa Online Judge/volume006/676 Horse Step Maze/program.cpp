// Horse Step Maze
// UVa ID: 676
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int offset[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
int visited[10][10], sx, sy, ex, ey;
int pathx[50010], pathy[50010], moves, done;

void dfs(int x, int y)
{
    if (done) return;
    // First move not counted.
    if (moves - 1 > 50000) return;
    if (x == ex && y == ey)
    {
        for (int i = 0; i < moves; i++)
        {
            if (i) cout << ", ";
            cout << '(' << pathx[i] << ',' << pathy[i] << ')';
        }
        cout << '\n';
        done = 1;
        return;
    }
    visited[x][y] = 1;
    for (int k = 0; k < 4; k++)
    {
        int nextx = x + offset[k][0], nexty = y + offset[k][1];
        if (nextx < 1 || nextx > 9 || nexty < 1 || nexty > 9) continue;
        if (visited[nextx][nexty]) continue;
        pathx[moves] = nextx, pathy[moves] = nexty, moves++;
        dfs(nextx, nexty);
        if (done) return;
        pathx[moves] = x, pathy[moves] = y, moves++;
    }
    visited[x][y] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char ignore;
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';
        cin >> ignore >> sx >> ignore >> sy >> ignore;
        cin >> ignore >> ex >> ignore >> ey >> ignore;
        if (sx == ex && sy == ey)
        {
            cout << '(' << sx << ',' << sy << ')';
            cout << '\n';
            continue;
        }
        int dx = abs(ex - sx), dy = abs(ey - sy);
        dx %= 2, dy %= 2;
        if (dx != dy)
        {
            cout << "fail\n";
            continue;
        }
        moves = done = 0;
        memset(visited, 0, sizeof(visited));
        pathx[moves] = sx, pathy[moves] = sy;
        moves++;
        dfs(sx, sy);
        if (!done) cout << "more than 50000 steps\n";
    }
    return 0;
}
