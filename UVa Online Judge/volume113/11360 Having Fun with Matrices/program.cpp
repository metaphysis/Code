// Having Fun with Matrices
// UVa ID: 11360
// Verdict: Accepted
// Submission Date: 2018-01-10
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

    int cases, grid[16][16], n, m, a, b;
    char digit;
    string operation;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> digit;
                grid[i][j] = digit - '0';
            }
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> operation;
            if (operation == "row" || operation == "col")
            {
                cin >> a >> b;
                if (operation == "row")
                {
                    for (int j = 1; j <= n; j++)
                        swap(grid[a][j], grid[b][j]);
                }
                else
                {
                    for (int j = 1; j <= n; j++)
                        swap(grid[j][a], grid[j][b]);
                }
            }
            else if (operation == "inc" || operation == "dec")
            {
                int offset = (operation == "inc" ? 1 : -1);
                for (int j = 1; j <= n; j++)
                    for (int l = 1; l <= n; l++)
                        grid[j][l] = (grid[j][l] + offset + 10) % 10;
            }
            else
            {
                for (int j = 1; j <= n; j++)
                    for (int l = j + 1; l <= n; l++)
                        swap(grid[j][l], grid[l][j]);
            }
        }
        
        cout << "Case #" << c << '\n';
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cout << grid[i][j];
            cout << '\n';
        }
        cout << '\n'; 
    }

    return 0;
}
