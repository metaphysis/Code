// Walking on a Grid
// UVa ID: 10913
// Verdict: Accepted
// Submission Date: 2018-02-23
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

const int MAXV = 80, INF = 0x3f3f3f3f;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n, mostk, dist[MAXV][MAXV][6], grid[MAXV][MAXV];
    int offset[3][2] = {{1, 0}, {0, 1}, {0, -1}};

    while (cin >> n >> mostk)
    {
        if (n == 0 && mostk == 0) break;        

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];

        for (int i = 0; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 0; k <= mostk; k++)
                    dist[i][j][k] = -INF;
        dist[0][1][0] = 0;

        // DP, row by row.
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 0; k <= mostk; k++)
                {
                    if (dist[i - 1][j][k] != -INF)
                    {
                        int nextj = j, nextk = k, nextw = dist[i - 1][j][k];
                        while (nextj >= 1)
                        {
                            nextw += grid[i][nextj];
                            nextk += (grid[i][nextj] >= 0 ? 0 : 1);
                            if (nextk > mostk) break;
                            dist[i][nextj][nextk] = max(dist[i][nextj][nextk], nextw);
                            nextj--;
                        }
                        
                        nextj = j, nextk = k, nextw = dist[i - 1][j][k];
                        while (nextj <= n)
                        {
                            nextw += grid[i][nextj];
                            nextk += (grid[i][nextj] >= 0 ? 0 : 1);
                            if (nextk > mostk) break;
                            dist[i][nextj][nextk] = max(dist[i][nextj][nextk], nextw);
                            nextj++;
                        }
                    }
                }

        cout << "Case " << ++cases << ": ";
        int maxDist = -INF;
        for (int k = 0; k <= mostk; k++)
            maxDist = max(maxDist, dist[n][n][k]);
        if (maxDist == -INF) cout << "impossible\n";
        else cout << maxDist << '\n';
    }

    return 0;
}
