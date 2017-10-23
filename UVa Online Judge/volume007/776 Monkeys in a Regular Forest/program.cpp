// Monkeys in a Regular Forest
// UVa ID: 776
// Verdict: Accepted
// Submission Date: 2017-10-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

const int MAXV = 1010;

char maze[MAXV][MAXV];
int number[MAXV][MAXV];
int rows = 0, columns = 0, maxWidth[MAXV];
int offsetx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int offsety[8] = {1, -1, 0, 1, -1, 0, 1, -1};

void floodFill(int i, int j, char old, int n)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns && maze[i][j] == old)
    {
        maze[i][j] = '0', number[i][j] = n;
        maxWidth[j] = max(maxWidth[j], n);
        for (int k = 0; k < 8; k++)
            floodFill(i + offsetx[k], j + offsety[k], old, n);
    }
}

void release()
{
    memset(maxWidth, 0, sizeof(maxWidth));
        
    int n = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (maze[i][j] != '0')
            {
                floodFill(i, j, maze[i][j], n);
                n++;
            }
                
    for (int i = 0; i < columns; i++)
    {
        int spaces = 0;
        while (maxWidth[i] > 0)
        {
            spaces++;
            maxWidth[i] /= 10;
        }
        maxWidth[i] = spaces;
    }
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (j) cout << ' ';
            cout << setw(maxWidth[j]) << right << number[i][j];
        }
        cout << '\n';
    }
    cout << "%\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line != "%")
        {
            columns = 0;
            for (int i = 0; i < line.length(); i++)
                if (isalpha(line[i]))
                    maze[rows][columns++] = line[i];
            rows++;
            continue;
        }

        release();
        
        rows = 0;
    }
    
    if (rows > 0) release();
    
    return 0;
}
