// Travelling Salesman
// UVa ID: 10702
// Verdict: Accepted
// Submission Date: 2018-02-25
// UVa Run Time: 0.030s
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

const int MAXV = 110, MAXT = 1010;

int C, S, E, T;
int profit[MAXV][MAXV], dest[MAXV], dp[MAXV][MAXT];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> C >> S >> E >> T, C > 0)
    {
        for (int i = 1; i <= C; i++)
            for (int j = 1; j <= C; j++)
                cin >> profit[i][j];
        for (int i = 1; i <= E; i++)
            cin >> dest[i];
        for (int i = 1; i <= C; i++)
            for (int j = 0; j <= T; j++)
                dp[i][j] = -1;

        // dp[v][k] = max(dp[v][k], dp[u][k - 1] + profit[u][v]), 1 <= u <= C, u != v.
        dp[S][0] = 0;
        for (int k = 1; k <= T; k++)
            for (int v = 1; v <= C; v++)
                for (int u = 1; u <= C; u++)
                {
                    if (u == v) continue;
                    if (dp[u][k - 1] < 0) continue;
                    dp[v][k] = max(dp[v][k], dp[u][k - 1] + profit[u][v]);
                }

        int maxProfit = 0;
        for (int i = 1; i <= E; i++)
            maxProfit = max(maxProfit, dp[dest[i]][T]);
        cout << maxProfit << '\n';
    }

    return 0;
}
