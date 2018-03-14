// NumPuzz I
// UVa ID: 12398
// Verdict: Accepted
// Submission Date: 2018-01-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    int cases = 0, grid[3][3];

    while (getline(cin, line))
    {
        cout << "Case #" << ++cases << ":\n";
        memset(grid, 0, sizeof(grid));
        
        for (int i = line.length() - 1; i >= 0; i--)
        {
            if (line[i] == 'a')
            {
                grid[0][0]++, grid[0][1]++, grid[1][0]++;
            }
            else if (line[i] == 'b')
            {
                grid[0][0]++, grid[0][1]++, grid[0][2]++, grid[1][1]++;
            }
            else if (line[i] == 'c')
            {
                grid[0][1]++, grid[0][2]++, grid[1][2]++;
            }
            else if (line[i] == 'd')
            {
                grid[0][0]++, grid[1][0]++, grid[1][1]++, grid[2][0]++;
            }
            else if (line[i] == 'e')
            {
                grid[0][1]++, grid[1][0]++, grid[1][1]++, grid[1][2]++, grid[2][1]++;
            }
            else if (line[i] == 'f')
            {
                grid[0][2]++, grid[1][1]++, grid[1][2]++, grid[2][2]++;
            }
            else if (line[i] == 'g')
            {
                grid[1][0]++, grid[2][0]++, grid[2][1]++;
            }
            else if (line[i] == 'h')
            {
                grid[1][1]++, grid[2][0]++, grid[2][1]++, grid[2][2]++;
            }
            else if (line[i] == 'i')
            {
                grid[1][2]++, grid[2][1]++, grid[2][2]++;
            }
            
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    grid[i][j] %= 10;
        }
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j) cout << ' ';
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
