// Il Gioco dell'X
// UVa ID: 260
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[200][200];
bool visited[200][200];
int n;
int step[6][2] = {{0, -1}, {-1, -1}, {-1, 0}, {0, 1}, {1, 1}, {1, 0}};

void dfs(int x, int y)
{
    visited[x][y] = true;
    
    for (int i = 0; i < 6; i++)
    {
        int xx = x + step[i][0];
        int yy = y + step[i][1];
        
        if (xx >= 0 && xx < n && yy >= 0 && yy < n &&
            board[xx][yy] == 'b' && visited[xx][yy] == false)
            dfs(xx, yy);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases = 0;
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board[i][j];
        
        // check black just enough
        bool blackWin = false;
        for (int i = 0; i < n; i++)
        {
            if (board[0][i] == 'b')
            {
                for (int x = 0; x < n; x++)
                    for (int y = 0; y < n; y++)
                        visited[x][y] = false;

                dfs(0, i);

                for (int k = 0; k < n; k++)
                    if (visited[n - 1][k])
                    {
                        blackWin = true;
                        break;
                    }
            }

            if (blackWin)
                break;
        }
        
        cases++;
        cout << cases << " " << (blackWin ? "B" : "W") << endl;
    }
    
	return 0;
}
