// Annoying Painting Tool
// UVa ID: 11230
// Verdict: Accepted
// Submission Date: 2018-01-25
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, r, c, grid[110][110];
    char pixel;

    while (cin >> n >> m >> r >> c)
    {
        if (n == 0) break;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> pixel;
                grid[i][j] = pixel - '0';
            }

        int cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (grid[i][j])
                {
                    if (i + r - 1 <= n && j + c - 1 <= m)
                    {
                        for (int k = 0; k < r; k++)
                            for (int l = 0; l < c; l++)
                                grid[i + k][j + l] = !grid[i + k][j + l];
                        cnt++;
                    }
                }
                
        int black = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (grid[i][j])
                    black++;
        if (black > 0) cout << "-1\n";
        else cout << cnt << '\n';
    }

    return 0;
}
