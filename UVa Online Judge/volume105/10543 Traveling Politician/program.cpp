// Traveling Politician
// UVa ID: 10543
// Verdict: Accepted
// Submission Date: 2018-02-25
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

const int MAXV = 64;

bool edges[MAXV][MAXV], arrived[MAXV][24];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, k;
    while (cin >> n >> m >> k, n > 0)
    {
        memset(edges, false, sizeof(edges));
        for (int i = 1, u, v; i <= m; i++)
        {
            cin >> u >> v;
            edges[u][v] = true;
        }
        memset(arrived, false, sizeof(arrived));
        arrived[0][1] = true;
        for (int speech = 2; speech <= 20; speech++)
            for (int v = 0; v < n; v++)
                for (int u = 0; u < n; u++)
                    arrived[v][speech] |= (arrived[u][speech - 1] && edges[u][v]);

        int minK = -1;
        for (int i = k; i <= 20; i++)
            if (arrived[n - 1][i])
            {
                minK = i;
                break;
            }
        if (minK > 0) cout << minK << '\n';
        else cout << "LOSER\n";
    }

    return 0;
}
