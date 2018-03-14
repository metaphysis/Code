// Deciding victory in Go
// UVa ID: 852
// Verdict: Accepted
// Submission Date: 2016-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 9;
char grid[MAX_SIZE][MAX_SIZE];
int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int black_stone, white_stone, points;

void flood_fill(int i, int j, char old, char replaced)
{
    if (i >= 0 && i < 9 && j >= 0 && j < 9)
    {
        if (grid[i][j] == old)
        {
            points++;
            grid[i][j] = replaced;
            for (int k = 0; k < 4; k++)
                flood_fill(i + offset[k][0], j + offset[k][1], old, replaced);
        }
        else
        {
            if (grid[i][j] == 'X') black_stone++;
            else if (grid[i][j] == 'O') white_stone++;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        int black = 0, white = 0;
        
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'X') black++;
                if (grid[i][j] == 'O') white++;
            }

        if (black == 0 && white == 0)
        {
            cout << "Black 0 White 0\n";
            continue;
        }
        
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (grid[i][j] == '.')
                {
                    black_stone = 0, white_stone = 0, points = 0;
                    
                    flood_fill(i, j, '.', 'F');
                    
                    if (black_stone == 0) white += points;
                    if (white_stone == 0) black += points;
                }
            
        cout << "Black " << black << " White " << white << '\n';
    }
    
	return 0;
}
