// Wetlands of Florida
// UVa ID: 469
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char matrix[110][110];
int counter, row = 0, column = 0;

void restore()
{
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= column; j++)
            if (matrix[i][j] == 'X')
                matrix[i][j] = 'W';
}

void flood_fill(int r, int c)
{
    if (r >= 1 && r <= row && c >= 1 && c <= column)
    {
        if (matrix[r][c] == 'W')
        {
            counter++;
            matrix[r][c] = 'X';
            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0) continue;
                    flood_fill(r + i, c + j);
                }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    getline(cin, line);
    int cases = stoi(line);
    
    getline(cin, line);
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        row = 0;
        while (getline(cin, line), line.length() > 0)
        {
            if (isalpha(line.front()))
            {
                for (int j = 0; j < line.length(); j++)
                    matrix[row + 1][j + 1] = line[j];
                row++;
                column = line.length();
            }
            else
            {
                istringstream iss(line);
                int cell_row, cell_column;
                iss >> cell_row >> cell_column;
                
                counter = 0;
                flood_fill(cell_row, cell_column);
                restore();
                cout << counter << '\n';
            }
        }
    }
    
	return 0;
}
