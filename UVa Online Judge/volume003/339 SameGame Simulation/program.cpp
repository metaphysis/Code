// SameGame Simulation
// UVa IDs: 339
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int M, N, grid[50][50], cases = 0;
int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void floodFill(int row, int column, int value)
{
    if (row >= 1 && row <= M && column >= 1 && column <= N)
        if (grid[row][column] == value)
        {
            grid[row][column] = -1;
            for (int k = 0; k < 4; k++)
                floodFill(row + offset[k][0], column + offset[k][1], value);
        }
}

void adjust()
{
    // drop down
    for (int c = 1; c <= N; c++)
    {
        int low = 1;
        while (low <= M && grid[low][c] >= 0) low++;
        if (low == M + 1) continue;
        
        for (int up = low + 1; up <= M; up++)
            if (grid[up][c] >= 0)
            {
                grid[low][c] = grid[up][c];
                grid[up][c] = -1;
                low++;
            }
    }
    
    // slide left
    int movedColumn = 0;
    for (int c = N; c >= 1; c--)
    {
        bool emptyColumn = true;
        for (int r = 1; r <= M; r++)
            if (grid[r][c] >= 0)
            {
                emptyColumn = false;
                break;
            }
        if (emptyColumn == false)
            continue;

        for (int r = 1; r <= M; r++)
        {
            for (int emptyC = c; emptyC < N - movedColumn; emptyC++)
                grid[r][emptyC] = grid[r][emptyC + 1];
        }
        
        for (int r = 1; r <= M; r++)
            grid[r][N - movedColumn] = -1;
            
        movedColumn++;
    }
}

void display()
{
    for (int r = M; r >= 1; r--)
    {
        for (int c = 1; c <= N; c++)
            cout << " " << grid[r][c];
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> M >> N, M && N)
    {
        for (int r = 1; r <= M; r++)
            for (int c = 1; c <= N; c++)
                cin >> grid[r][c];
                
        int row, column;
        while (cin >> row >> column, row && column)
        {
            //cout << row << " " << column << endl;
            
            if (row <= 0 || row > M || column <= 0 || column > N)
                continue;
            if (grid[row][column] == -1)
                continue;
            
            bool linked = false;
            for (int k = 0; k < 4; k++)
            {
                int nextRow = row + offset[k][0], nextColumn = column + offset[k][1];
                if (nextRow < 1 || nextRow > M || nextColumn < 1 || nextColumn > N)
                    continue;
                if (grid[nextRow][nextColumn] == grid[row][column])
                {
                    linked = true;
                    break;
                }
            }
            
            if (linked == false)
                continue;
            
            //cout << row << " " << column << " linked." << endl;
            floodFill(row, column, grid[row][column]);
            
            //cout << "after flood fill" << endl;
            //display();
            
            adjust();
            
            //cout << "after adjust" << endl;
            //display();
        }
        
        if (cases)
            cout << endl;
            
        cout << "Grid " << ++cases << "." << endl;
        
        int cell = 0;
        for (int r = 1; r <= M; r++)
            for (int c = 1; c <= N; c++)
                if (grid[r][c] >= 0)
                    cell++;
                    
        if (cell == 0)
            cout << "    Game Won" << endl;
        else
        {
            for (int r = M; r >= 1; r--)
            {
                cout << "   ";
                for (int c = 1; c <= N; c++)
                    if (grid[r][c] >= 0)
                        cout << " " << grid[r][c];
                    else
                        cout << "  ";
                cout << endl;
            }
        }
    }
    
	return 0;
}
