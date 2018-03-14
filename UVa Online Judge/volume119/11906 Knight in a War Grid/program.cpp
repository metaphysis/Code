// Knight in a War Grid
// UVa ID: 11906
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int R, C, M, N, W;
int xi, yi, even, odd;
int grid[110][110], visited[110][110], mark[110][110];
int offset[4][2] = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

void dfs(int i, int j)
{
    visited[i][j] = 1;

    int ki = 0, tag = i * C + j;
    for (int k = 0; k < 4; k++)
    {
        int nexti = i + offset[k][0] * M, nextj = j + offset[k][1] * N;
        if (nexti >= 0 && nextj >= 0 && nexti < R && nextj < C)
            if (!grid[nexti][nextj] && mark[nexti][nextj] != tag)
                ki++, mark[nexti][nextj] = tag;
        
        nexti = i + offset[k][0] * N, nextj = j + offset[k][1] * M;
        if (nexti >= 0 && nextj >= 0 && nexti < R && nextj < C)
            if (!grid[nexti][nextj] && mark[nexti][nextj] != tag)
                ki++, mark[nexti][nextj] = tag;
    }
    if (ki % 2 == 0) even++;
    else odd++;

    for (int k = 0; k < 4; k++)
    {
        int nexti = i + offset[k][0] * M, nextj = j + offset[k][1] * N;
        if (nexti >= 0 && nextj >= 0 && nexti < R && nextj < C)
            if (!grid[nexti][nextj])
                if (!visited[nexti][nextj])
                    dfs(nexti, nextj);
        
        nexti = i + offset[k][0] * N, nextj = j + offset[k][1] * M;
        if (nexti >= 0 && nextj >= 0 && nexti < R && nextj < C)
            if (!grid[nexti][nextj])
                if (!visited[nexti][nextj])
                    dfs(nexti, nextj);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        memset(grid, 0, sizeof(grid));
        cin >> R >> C >> M >> N;
        cin >> W;
        for (int i = 1; i <= W; i++)
        {
            cin >> xi >> yi;
            grid[xi][yi] = 1;
        }
        
        even = odd = 0;
        memset(visited, 0, sizeof(visited));
        memset(mark, -1, sizeof(mark));

        dfs(0, 0);
        
        cout << "Case " << c << ": " << even << ' ' << odd << '\n';
    }

    return 0;
}
