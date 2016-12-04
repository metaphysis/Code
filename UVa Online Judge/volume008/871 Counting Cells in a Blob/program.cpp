// Counting Cells in a Blob
// UVa ID: 871
// Verdict: Accepted
// Submission Date: 2016-12-04
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

const int MAX_SIZE = 30;

char grid[MAX_SIZE][MAX_SIZE], rows, columns;

int largest_blob = 0, blob = 0;

void flood_fill(int i, int j, char old, char replaced)
{
    if (i >= 0 && i < rows && j >= 0 && j < columns && grid[i][j] == old)
    {
        grid[i][j] = replaced;

        blob++;

        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                flood_fill(i + x, j + y, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    string line;
    
    getline(cin, line);
    cases = stoi(line);

    getline(cin, line);

    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        memset(grid, '0', sizeof(grid));

        largest_blob = 0;
        rows = 0;

        while (getline(cin, line), line.length() > 0)
        {
            for (int j = 0; j < line.length(); j++)
                grid[rows][j] = line[j];
            rows++;
            columns = line.length();
        }
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                if (grid[i][j] == '1')
                {
                    blob = 0;
                    flood_fill(i, j, '1', '0');
                    largest_blob = max(largest_blob, blob);
                }
        
        cout << largest_blob << '\n';
    }

	return 0;
}
