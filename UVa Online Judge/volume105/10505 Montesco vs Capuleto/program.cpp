// Montesco vs Capuleto
// UVa ID: 10505
// Verdict: Accepted
// Submission Date: 2018-02-04
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

const int BLACK = 0, WHITE = 1;
int n, m, total, blacks, colored[210], bipartite;
list<int> edges[1100];

void dfs(int u, int color)
{
    colored[u] = color;
    total++;
    if (color == BLACK) blacks++;
    for (auto v : edges[u])
    {
        if (colored[v] < 0)
        {
            dfs(v, 1 - color);
        }
        else if (colored[v] == color)
        {
            bipartite = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            edges[i].clear();

        for (int u = 1, v; u <= n; u++)
        {
            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                cin >> v;
                if (v > n) continue;
                edges[u].push_back(v);
                edges[v].push_back(u);
            }
        }

        int invited = 0;
        memset(colored, -1, sizeof(colored));
        for (int i = 1; i <= n; i++)
            if (colored[i] < 0)
            {
                total = blacks = 0, bipartite = 1;
                dfs(i, BLACK);
                if (bipartite) invited += max(blacks, total - blacks);
            }
        cout << invited << '\n';
    }

    return 0;
}
