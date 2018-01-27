// Marbles on a Tree
// UVa ID: 10672
// Verdict: Accepted
// Submission Date: 2018-01-27
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

    int marbles[10010], n, parent[10010], indeg[10010];
    int u, m, d, v;

    while (cin >> n, n > 0)
    {
        memset(marbles, 0, sizeof(marbles));
        memset(indeg, 0, sizeof(indeg));
        memset(parent, 0, sizeof(parent));

        for (int i = 1; i <= n; i++)
        {
            cin >> u >> m;
            marbles[u] = m;
            cin >> d;
            for (int j = 1; j <= d; j++)
            {
                cin >> v;
                indeg[u]++;
                parent[v] = u;
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (indeg[i] == 0)
                q.push(i);
        int moves = 0;
        while (!q.empty())
        {
            v = q.front(); q.pop();
            moves += abs(marbles[v] - 1);
            u = parent[v];
            if (u)
            {
                marbles[u] += marbles[v] - 1;
                if (--indeg[u] == 0)
                    q.push(u);
            }
        }
        cout << moves << '\n';
    }

    return 0;
}
