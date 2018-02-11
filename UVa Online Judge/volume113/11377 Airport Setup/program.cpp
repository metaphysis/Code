// Airport Setup
// UVa ID: 11377
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.040s
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

const int MAXV = 4010, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];
int n, m, dist[MAXV], airport[MAXV];

void mooreDijkstra(int u)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(u, 0));
    dist[u] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, u, v, k, q;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m >> k;

        for (int i = 0; i < MAXV; i++)
            edges[i].clear();

        memset(airport, 0, sizeof(airport));
        for (int i = 1; i <= k; i++)
        {
            cin >> u;
            airport[u] = 1;
            edges[2 * u - 1].push_back(edge(2 * u, 0));
            edges[2 * u].push_back(edge(2 * u - 1, 0));
        }
        for (int i = 1; i <= n; i++)
        {
            if (!airport[i])
            {
                edges[2 * i - 1].push_back(edge(2 * i, 1));
                edges[2 * i].push_back(edge(2 * i - 1, 1));
            }
        }
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v;
            edges[2 * u].push_back(edge(2 * v - 1, 0));
            edges[2 * v].push_back(edge(2 * u - 1, 0));
        }

        cout << "Case " << c << ":\n";

        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> u >> v;
            if (u == v)
            {
                cout << "0\n";
                continue;
            }
            mooreDijkstra(2 * u - 1);
            if (dist[2 * v] == INF) cout << "-1\n";
            else cout << dist[2 * v] << '\n';
        }
        cout << '\n';
    }

    return 0;
}
