// Route Change
// UVa ID: 11833
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 310, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { w > e.w; }
};

list<edge> edges[MAXV];
int n, m, c, k, dist[MAXV], fee[MAXV][MAXV];

void mooreDijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(k, 0));
    dist[k] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                if (e2.v >= c) q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }

    int minFee = INF, routeFee = 0;
    for (int i = c - 1; i >= 0; i--)
    {
        if (i < c - 1) routeFee += fee[i][i + 1];
        minFee = min(minFee, dist[i] + routeFee);
    }
    cout << minFee << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;
    while (cin >> n >> m >> c >> k, n > 0)
    {
        for (int i = 0; i < n; i++)
            edges[i].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
            fee[u][v] = fee[v][u] = w;
        }
        mooreDijkstra();
    }

    return 0;
}
