// Going in Cycle!!
// UVa ID: 11090
// Verdict: Accepted
// Submission Date: 2017-11-17
// UVa Run Time: 0.060s
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

const int MAXV = 110, INF = 0;
const double EPSILON = 1e-4;

struct edge
{
    int u, v, weight;
};

list<edge> edges[MAXV];
double dist[MAXV], low, middle, high;
int visited[MAXV], counter[MAXV], n, m;

bool spfa()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF, visited[i] = 1, counter[i] = 0;
        q.push(i);
    }

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        if (counter[u] > n) return true;

        visited[u] = 0;
        for (auto e : edges[u])
        {
            if (dist[e.v] > dist[u] + e.weight - middle)
            {
                dist[e.v] = dist[u] + e.weight - middle;
                if (!visited[e.v])
                {
                    q.push(e.v);
                    visited[e.v] = 1, counter[e.v]++;
                }
            }
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, a, b, c;

    cin >> cases;
    for (int c1 = 1; c1 <= cases; c1++)
    {
        cin >> n >> m;

        for (int i = 1; i <= n; i++)
            edges[i].clear();

        int maxc = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> a >> b >> c;
            edges[a].push_back(edge{a, b, c});
            maxc = max(maxc, c);
        }
        maxc += 10;

        cout << "Case #" << c1 << ": ";

        middle = maxc;
        if (!spfa())
        {
            cout << "No cycle found.\n";
            continue;
        }

        low = 0, high = middle;
        while ((high - low) > EPSILON)
        {
            middle = (high + low) / 2.0;
            if (spfa())
                high = middle;
            else
                low = middle;
        }

        cout << fixed << setprecision(2) << high << '\n';
    }

    return 0;
}
