// ASCII Area
// UVa ID: 1641
// Verdict: Accepted
// Submission Date: 2021-12-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int h, w;
char g[110][110];
int offset[8][2] = {-1, 0, 1, 0, 0, -1, 0, 1, -1, -1, 1, 1, -1, 1, 1, -1};

void dfs(int i, int j)
{
    g[i][j] = '*';
    for (int k = 0; k < 8; k++)
    {
        int ni = i + offset[k][0], nj = j + offset[k][1];
        if (ni >= 0 && ni <= h + 1 && nj >= 0 && nj <= w + 1)
            if (g[ni][nj] == '.')
            {
                if (k < 4) dfs(ni, nj);
                if ((k == 4 || k == 5) && g[i][nj] == '\\' && g[ni][j] == '\\') dfs(ni, nj);
                if ((k == 6 || k == 7) && g[i][nj] == '/' && g[ni][j] == '/') dfs(ni, nj);      
            }
    }
}

void show()
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
            cout << g[i][j];
        cout << '\n';
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    while (cin >> h >> w)
    {
        memset(g, '.', sizeof g);
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                cin >> g[i][j];
        dfs(0, 0);
        int area = 0;
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
            {
                if (g[i][j] == '.') area += 2;
                else if (g[i][j] == '/' || g[i][j] == '\\') area += 1;
            }
        cout << area / 2 << '\n';
        //show();
    }

    return 0;
}
