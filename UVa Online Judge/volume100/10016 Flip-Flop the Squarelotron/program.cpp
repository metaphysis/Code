// Flip-Flop the Squarelotron
// UVa ID: 10016
// Verdict: Accepted
// Submission Date: 2018-01-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int grid[110][110], n;

void flipUpDown(int ring)
{
    int firstRow = ring, firstCln = ring, lastCln = n - ring + 1;
    for (int cln = firstCln; cln <= lastCln; cln++)
    {
        if (cln == firstCln || cln == lastCln)
        {
            for (int row = firstRow; row <= n / 2; row++)
                swap(grid[row][cln], grid[n + 1 - row][cln]);  
        }
        else
        {
            swap(grid[firstRow][cln], grid[n + 1 - firstRow][cln]);
        }
    }
}

void flipLeftRight(int ring)
{
    int firstCln = ring, firstRow = ring, lastRow = n - ring + 1;
    for (int row = firstRow; row <= lastRow; row++)
    {
        if (row == firstRow || row == lastRow)
        {
            for (int cln = firstCln; cln <= n / 2; cln++)
                swap(grid[row][cln], grid[row][n + 1 - cln]);
        }
        else
        {
            swap(grid[row][firstCln], grid[row][n + 1 - firstCln]);
        }
    }
}

void flipMainDiagonal(int ring)
{
    int firstRow = ring, firstCln = ring, lastRow = n + 1 - ring, lastCln = n + 1 - ring;
    for (int cln = firstCln + 1; cln <= lastCln; cln++)
        swap(grid[firstRow][cln], grid[cln][firstRow]);
    for (int row = firstRow + 1; row < lastRow; row++)
        swap(grid[row][lastCln], grid[lastCln][row]);
}

void flipMainInverseDiagonal(int ring)
{
    int firstRow = ring, firstCln = ring, lastRow = n + 1 - ring, lastCln = n + 1 - ring;
    for (int cln = firstCln; cln < lastCln; cln++)
        swap(grid[firstRow][cln], grid[n + 1 - cln][n + 1 - firstRow]);
    for (int row = firstRow + 1; row < lastRow; row++)
        swap(grid[row][firstCln], grid[n + 1 - firstCln][n + 1 - row]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];
        int rings = n / 2 + (n & 1), t, move;
        for (int r = 1; r <= rings; r++)
        {
            cin >> t;
            for (int j = 1; j <= t; j++)
            {
                cin >> move;
                if (move == 1) flipUpDown(r);
                else if (move == 2) flipLeftRight(r);
                else if (move == 3) flipMainDiagonal(r);
                else if (move == 4) flipMainInverseDiagonal(r);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j > 1) cout << ' ';
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
