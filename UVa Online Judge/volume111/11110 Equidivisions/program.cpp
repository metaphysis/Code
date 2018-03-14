// Equidivisions
// UVa ID: 11110
// Verdict: Accepted
// Submission Date: 2018-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, T, nexti, nextj;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int grid[110][110];

void dfs(int i, int j, int old, int replaced)
{
    T++;
    grid[i][j] = replaced;
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 1 && nexti <= N && nextj >= 1 && nextj <= N)
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int x, y;
    string line;

    while (cin >> N, N > 0)
    {
        memset(grid, 0, sizeof(grid));

        cin.ignore(1024, '\n');

        int cnt = 1;
        for (int i = 1; i < N; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            while (iss >> x >> y)
                grid[x][y] = cnt;
            cnt++;
        }
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (!grid[i][j])
                    grid[i][j] = cnt;

        int filled = 0, good = 1;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (grid[i][j])
                {
                    T = 0;
                    dfs(i, j, grid[i][j], 0);
                    if (T != N)
                    {
                        good = 0;
                        goto print;
                    }
                    filled++;
                }
        print:
        cout << (good && filled == N ? "good" : "wrong") << '\n';
    }

    return 0;
}
