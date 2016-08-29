// The PATH
// UVa ID: 601
// Verdict: Accepted
// Submission Date: 2016-08-29
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char grid[90][90], field[90][90];
int n;

void duplicate()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            field[i][j] = grid[i][j];
}

void fillW(int i, int j)
{
    if (i >= 0 && i < n && j >= 0 && j < n && field[i][j] == 'W')
    {
        field[i][j] = '1';
        fillW(i + 1, j);
        fillW(i - 1, j);
        fillW(i, j + 1);
        fillW(i, j - 1);
    }
}

void fillB(int i, int j)
{
    if (i >= 0 && i < n && j >= 0 && j < n && field[i][j] == 'B')
    {
        field[i][j] = '1';
        fillB(i + 1, j);
        fillB(i - 1, j);
        fillB(i, j + 1);
        fillB(i, j - 1);
    }
}

bool checkW()
{
    // White has a winning path.
    bool edged = false;
    for (int i = 0; i < n; i++)
        if (field[i][0] == 'W')
        {
            edged = true;
            fillW(i, 0);
        }

    if (edged)
    {
        for (int i = 0; i < n; i++)
            if (field[i][n - 1] == '1')
                return true;
    }
    
    return false;
}

bool checkB()
{
    // Black has a winning path.
    bool edged = false;
    for (int i = 0; i < n; i++)
        if (field[0][i] == 'B')
        {
            edged = true;
            fillB(0, i);
        }

    if (edged)
    {
        for (int i = 0; i < n; i++)
            if (field[n - 1][i] == '1')
                return true;
    }
    
    return false;
}

void check()
{
    duplicate();
    if (checkW())
    {
        cout << "White has a winning path.\n";
        return;
    }
    
    duplicate();
    if (checkB())
    {
        cout << "Black has a winning path.\n";
        return;
    }
    
    // White can win in one move.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'U')
            {
                duplicate();
                field[i][j] = 'W';
                
                if (checkW())
                {
                    cout << "White can win in one move.\n";
                    return;
                }
            }
            
    // Black can win in one move.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'U')
            {
                duplicate();
                field[i][j] = 'B';
                
                if (checkB())
                {
                    cout << "Black can win in one move.\n";
                    return;
                }
            }
            
    cout << "There is no winning path.\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        check();
    }
    
	return 0;
}
