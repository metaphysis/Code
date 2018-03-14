// Even Obsession
// UVa ID: 12950
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.110s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV], allEdges;
int n, m, dist[MAXV][2];

void mooreDijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    
    priority_queue<edge> q;
    q.push(edge(1, 0));
    dist[1][0] = 0;

    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto e : edges[u.v])
        {
            for (int k = 0; k <= 1; k++)
                if (dist[e.v][k] > dist[u.v][1 - k] + e.w)
                {
                    dist[e.v][k] = dist[u.v][1 - k] + e.w;
                    q.push(edge(e.v, dist[e.v][k]));
                }
        }
    }

    int toll = INF;
    if (dist[n][0] == INF) cout << "-1\n";
    else cout << dist[n][0] << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        int u, v, c;
        for (int i = 1; i <= n; i++)
            edges[i].clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> c;
            edges[u].push_back(edge(v, c));
            edges[v].push_back(edge(u, c));
        }
        mooreDijkstra();
    }

    return 0;
}
