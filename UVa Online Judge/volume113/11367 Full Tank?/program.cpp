// Full Tank?
// UVa ID: 11367
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 1.220s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, INF = 0x3f3f3f3f;

struct edge
{
    int v, c, w;
    edge(int v = 0, int c = 0, int w = 0):v(v), c(c), w(w) {}
    bool operator<(const edge & e) const { return w > e.w; }
};

list<edge> edges[MAXV];
int n, m, q, c, s, e, prices[MAXV], dist[MAXV][110];

// Moore-Dijkstra algorithm on State-Space graph.
void mooreDijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(s, 0, 0));
    dist[s][0] = 0;

    while (!q.empty())
    {
        edge e1 = q.top();
        q.pop();
        if (e1.c < c)
        {
            if (dist[e1.v][e1.c + 1] > dist[e1.v][e1.c] + prices[e1.v])
            {
                dist[e1.v][e1.c + 1] = dist[e1.v][e1.c] + prices[e1.v];
                q.push(edge(e1.v, e1.c + 1, dist[e1.v][e1.c + 1]));
            }
        }
        for (auto e2 : edges[e1.v])
        {
            if (e2.w > e1.c)
                continue;
            if (dist[e2.v][e1.c - e2.w] > dist[e1.v][e1.c])
            {
                dist[e2.v][e1.c - e2.w] = dist[e1.v][e1.c];
                q.push(edge(e2.v, e1.c - e2.w, dist[e2.v][e1.c - e2.w]));
            }
        }
    }

    int minFuel = INF;
    for (int k = 0; k <= c; k++)
        minFuel = min(minFuel, dist[e][k]);
    if (minFuel == INF)
        cout << "impossible\n";
    else
        cout << minFuel << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;

    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> prices[i];
            edges[i].clear();
        }

        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, 0, w));
            edges[v].push_back(edge(u, 0, w));
        }

        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> c >> s >> e;
            mooreDijkstra();
        }
    }

    return 0;
}
