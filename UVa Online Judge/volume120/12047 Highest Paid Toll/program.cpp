// Highest Paid Toll
// UVa ID: 12047
// Verdict: Accepted
// Submission Date: 2018-02-10
// UVa Run Time: 0.130s
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

const int MAXV = 10010, INF = 0x7f7f7f7f;

struct edge
{
    int u, v, w;
    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges1[MAXV], edges2[MAXV], allEdges;
int n, m, s, t, p, dist1[MAXV], dist2[MAXV];

void mooreDijkstra()
{
    // source to others vertices.
    memset(dist1, 0x7f, sizeof(dist1));
    
    priority_queue<edge> q;
    q.push(edge(0, s, 0));
    dist1[s] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto e : edges1[u.v])
        {
            if (dist1[e.v] > dist1[u.v] + e.w)
            {
                dist1[e.v] = dist1[u.v] + e.w;
                q.push(edge(0, e.v, dist1[e.v]));
            }
        }
    }

    // destination to others vertices.
    memset(dist2, 0x7f, sizeof(dist2));
    q.push(edge(0, t, 0));
    dist2[t] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto e : edges2[u.v])
        {
            if (dist2[e.v] > dist2[u.v] + e.w)
            {
                dist2[e.v] = dist2[u.v] + e.w;
                q.push(edge(0, e.v, dist2[e.v]));
            }
        }
    }

    // try all edges to find max toll with constrain.
    int toll = -1;
    for (auto e : allEdges)
    {
        if (dist1[e.u] == INF) continue;
        if (dist2[e.v] == INF) continue;
        if (dist1[e.u] + e.w + dist2[e.v] <= p)
            toll = max(toll, e.w);
    }
    cout << toll << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m >> s >> t >> p;
        int u, v, c;
        for (int i = 1; i <= n; i++)
        {
            edges1[i].clear();
            edges2[i].clear();
        }
        allEdges.clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> c;
            edges1[u].push_back(edge(u, v, c));
            edges2[v].push_back(edge(v, u, c));
            allEdges.push_back(edge(u, v, c));
        }
        mooreDijkstra();
    }

    return 0;
}
