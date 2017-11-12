// Marcus, help!
// UVa ID: 10452
// Verdict: Accepted
// Submission Date: 2017-11-12
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char grid[10][10];
    
    int cases, m, n;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m >> n;
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        int starti, startj;
        for (int j = 0; j < n; j++)
        {
            if (grid[m - 1][j] == '@')
            {
                starti = m - 1;
                startj = j;
                break;
            }
        }
        
        string path = "IEHOVA#";
        for (int i = 0; i < 7; i++)
        {
            if (i) cout << ' ';
            if (startj - 1 >= 0 && grid[starti][startj - 1] == path[i])
            {
                cout << "left";
                startj -= 1;
                continue;
            }
            if (startj + 1 < n && grid[starti][startj + 1] == path[i])
            {
                cout << "right";
                startj += 1;
                continue;
            }
            if (grid[starti - 1][startj] == path[i])
            {
                cout << "forth";
                starti -= 1;
                continue;
            }
        }
        cout << '\n';
    }

    return 0;
}
