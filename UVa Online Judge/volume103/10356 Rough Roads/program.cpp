// Rough Roads
// UVa ID: 10356
// Verdict: Accepted
// Submission Date: 2018-02-09
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

const int MAXV = 510, INF = 0x3fffffff;

struct edge
{
    int to, riding, weight;
    edge (int to = 0, int riding = 0, int weight = 0): to(to), riding(riding), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int dist[MAXV][2], n, m;

void mooreDijkstra(int u)
{
    for (int i = 0; i < n; i++)
        dist[i][0] = dist[i][1] = INF;

    dist[u][1] = 0;
    queue<edge> q;
    q.push(edge(u, 1, 0));

    while (!q.empty())
    {
        edge u = q.front(); q.pop();
        for (auto v : edges[u.to])
        {
            if (v.riding == u.riding) continue;
            if (dist[v.to][v.riding] > dist[u.to][u.riding] + v.weight)
            {
                dist[v.to][v.riding] = dist[u.to][u.riding] + v.weight;
                q.push(edge(v.to, v.riding, dist[v.to][v.riding]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n >> m)
    {
        cout << "Set #" << ++cases << '\n';

        for (int i = 0; i < n; i++)
            edges[i].clear();

        int u, v, w;
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, 0, w));
            edges[u].push_back(edge(v, 1, w));
            edges[v].push_back(edge(u, 0, w));
            edges[v].push_back(edge(u, 1, w));
        }
        mooreDijkstra(0);
        if (dist[n - 1][1] != INF) cout << dist[n - 1][1] << '\n';
        else cout << "?\n";
    }
    return 0;
}
