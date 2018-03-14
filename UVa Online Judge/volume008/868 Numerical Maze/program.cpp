// Numerical Maze
// UVa ID: 868
// Verdict: Accepted
// Submission Date: 2017-11-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int maze[110][110];
int n, m;
int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int found = 0, smallestj;

void dfs(int i, int j, int s, int e)
{
    if (i == n)
    {
        if (!found || j < smallestj) smallestj = j;
        found = 1;
    }
    else
    {
        if (s == e) dfs(i, j, 0, e + 1);
        else
        {
            for (int k = 0; k < 4; k++)
            {
                int ii = i + offset[k][0], jj = j + offset[k][1];
                if (ii >= 1 && ii <= n && jj >= 1 && jj <= m)
                    if (maze[ii][jj] == (s + 1))
                        dfs(ii, jj, s + 1, e);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> maze[i][j];

        for (int j = 1; j <= m; j++)
            if (maze[1][j] == 1)
            {
                found = 0;

                dfs(1, j, 0, 2);
                
                if (found)
                {
                    cout << "1 " << j << '\n';
                    cout << n << ' ' << smallestj << '\n';
                    break;
                }
            }
    }

    return 0;
}
