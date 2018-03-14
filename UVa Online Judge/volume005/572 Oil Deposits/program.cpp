// Oil Deposits
// UVa ID: 572
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int m, n;
char grid[110][110];

void floodFill(int i, int j)
{
    if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == '@')
    {
        grid[i][j] = '*';

        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                floodFill(i + x, j + y);
    }
}
    
int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> m >> n, m)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        int deposits = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '@')
                {
                    deposits++;
                    floodFill(i, j);
                }
        cout << deposits << endl;
    }
    
	return 0;
}
