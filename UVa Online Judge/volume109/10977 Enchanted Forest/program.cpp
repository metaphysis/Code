// Enchanted Forest
// UVa ID: 10977
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[210][210], visited[210][210], steps[210][210];
    int R, C;
    int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (cin >> R >> C, R > 0)
    {
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                grid[i][j] = visited[i][j] = 0;
                
        int m, blockx, blocky;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> blockx >> blocky;
            grid[blockx][blocky] = 1;
        }
        int n, row, cln, L;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> row >> cln >> L;
            for (int r = max(1, row - L); r <= min(R, row + L); r++)
                for (int c = max(1, cln - L); c <= min(C, cln + L); c++)
                    if ((r - row) * (r - row) + (c - cln) * (c - cln) <= L * L)
                        grid[r][c] = 1;
        }
        
        queue<int> q1, q2;
        q1.push(1); q2.push(1);
        visited[1][1] = 1;
        steps[1][1] = 0;
        while (!q1.empty())
        {
            int r = q1.front(); q1.pop();
            int c = q2.front(); q2.pop();
            for (int k = 0; k < 4; k++)
            {
                int nextr = r + offset[k][0];
                int nextc = c + offset[k][1];
                if (nextr >= 1 && nextr <= R && nextc >= 1 && nextc <= C)
                {
                    if (!visited[nextr][nextc] && !grid[nextr][nextc])
                    {
                        visited[nextr][nextc] = 1;
                        q1.push(nextr);
                        q2.push(nextc);
                        steps[nextr][nextc] = steps[r][c] + 1;
                    }
                }
            }
        }
        if (visited[R][C]) cout << steps[R][C] << '\n';
        else cout << "Impossible.\n";
    }

    return 0;
}
