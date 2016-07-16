// Crosswords (II)
// UVa ID: 312
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>

using namespace std;

int m, n, grid[30][30];
char screen[90][180];
int offset[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

void floodFill(int x, int y)
{
    if (x >= 1 && x <= m && y >= 1 && y <= n)
        if (grid[x][y] == 1)
        {
            grid[x][y] = -3;
            for (int i = 0; i < 4; i++)
                floodFill(x + offset[i][0], y + offset[i][1]);
        }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> m >> n, m && n)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];
                
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (i == 1 || i == m || j == 1 || j == n)
                    if (grid[i][j] == 1)
                        floodFill(i, j);
        
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (grid[i][j] == 1)
                    grid[i][j] = -1;
                    
        int number = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (grid[i][j] == 0 &&
                    (((j == 1 || grid[i][j - 1] < 0) && (j < n && grid[i][j + 1] >= 0)) ||
                    ((i < m && grid[i + 1][j] >= 0) && (i == 1 || grid[i - 1][j] < 0))))
                    grid[i][j] = number++;
        
        for (int i = 1; i <= m; i++)
        {
            bool solidAtRight = false;
            for (int j = n; j >= 1; j--)
            {
                if (grid[i][j] >= 0) solidAtRight = true;
                else if (grid[i][j] == -3 && solidAtRight) grid[i][j] = -2;
            }
        }
        
        memset(screen, 0, sizeof(screen));
        
        int row = 0;  
        for (int i = 1; i <= m; i++)
        {
            int column = 0;
            for (int j = 1; j <= n; j++)
            {
                if (grid[i][j] == -2)
                {
                    for (int x = 0; x < 4; x++)
                        for (int y = 0; y < 6; y++)
                            if (screen[row + x][column + y] == 0)
                                screen[row + x][column + y] = ' ';
                }
                else if (grid[i][j] == -1)
                {
                    for (int x = 0; x < 4; x++)
                        for (int y = 0; y < 6; y++)
                            screen[row + x][column + y] = '+';
                }
                else if (grid[i][j] >= 0)
                {
                    for (int x = 0; x < 4; x++)
                        for (int y = 0; y < 6; y++)
                        {
                            if (x == 0 || x == 3 || y == 0 || y == 5)
                                screen[row + x][column + y] = '+';
                            else
                                screen[row + x][column + y] = ' ';
                        }
                        
                    if (grid[i][j] > 0)
                    {
                        screen[row + 1][column + 1] = grid[i][j] / 100 + '0';
                        screen[row + 1][column + 2] = (grid[i][j] % 100) / 10 + '0';
                        screen[row + 1][column + 3] = grid[i][j] % 10 + '0';
                    }
                }
                
                column += 5;
            }
            
            row += 3;
        }
        
        for (int i = 0; i <= m * 3; i++)
        {
            for (int j = 0; j <= n * 5; j++)
                if (screen[i][j] > 0)
                    cout << screen[i][j];
            cout << endl;
        }
        
        cout << endl;
    }
    
	return 0;
}
