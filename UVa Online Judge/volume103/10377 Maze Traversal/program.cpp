// Maze Traversal
// UVa ID: 10377
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string direct = "NESW", line;
    int cases, n, m, grid[64][64], x, y, d;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    char mark;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
    
        cin >> n >> m;
        cin.ignore(1024, '\n');

        memset(grid, 0, sizeof(grid));
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            for (int j = 1; j <= m; j++)
                if (line[j - 1]  == '*')
                    grid[i][j] = 1;
        }
        cin >> x >> y;
        cin.ignore(1024, '\n');
        d = 0;
        while (getline(cin, line), line.length() > 0)
        {
            for (int i = 0; i < line.length(); i++)
            {
                mark = line[i];
                if (mark == 'F')
                {
                    if (grid[x + offset[d][0]][y + offset[d][1]]) continue;
                    x += offset[d][0], y += offset[d][1];
                }
                else if (mark == 'R')
                {
                    d = (d + 1) % 4;
                }
                else if (mark == 'L')
                {
                    d = (d + 3) % 4;
                }
                else if (mark == 'Q')
                {
                    cout << x << ' ' << y << ' ' << direct[d] << '\n';
                }
            }
        }
    }

    return 0;
}
