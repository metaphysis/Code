// Ecosystem
// UVa ID: 626
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int grid[110][110], n;
    
    while (cin >>n)
    {
        memset(grid, 0, sizeof(grid));
        
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];
        
        int total = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    if (grid[i][j] && grid[j][k] && grid[k][i])
                     {
                        if (i == j || j == k || k == i) continue;
                        cout << i << ' ' << j << ' ' << k << '\n';
                        total++;
                     }
        cout << "total:" << total << "\n\n";
    }
    
    return 0;
}
