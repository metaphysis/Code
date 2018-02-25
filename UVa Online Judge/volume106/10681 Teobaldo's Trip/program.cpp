// Teobaldo's Trip
// UVa ID: 10681
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int C, L, S, E, D;
    int edges[110][110], arrived[110][210];

    while (cin >> C >> L, C > 0)
    {
        memset(edges, false, sizeof(edges));
        for (int i = 1, u, v; i <= L; i++)
        {
            cin >> u >> v;
            edges[u][v] = edges[v][u] = true;
        }

        cin >> S >> E >> D;
        memset(arrived, false, sizeof(arrived));
        arrived[S][0] = true;
        for (int k = 1; k <= D; k++)
            for (int v = 1; v <= C; v++)
                for (int u = 1; u <= C; u++)
                    arrived[v][k] |= arrived[u][k - 1] && edges[u][v];

        if (arrived[E][D]) cout << "Yes, Teobaldo can travel.\n";
        else cout << "No, Teobaldo can not travel.\n";
    }

    return 0;
}
