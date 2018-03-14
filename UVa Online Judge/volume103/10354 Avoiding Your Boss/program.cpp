// Avoiding Your Boss
// UVa ID: 10354
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];
list<int> parent[MAXV];

int P, R, BH, OF, YH, M;
int dist[MAXV], disabled[MAXV];

void dfs(int u)
{
    disabled[u] = 1;
    for (auto v : parent[u])
        if (!disabled[v])
            dfs(v);
}

void mooreDijkstra()
{
    memset(disabled, 0, sizeof(disabled));

    for (int i = 1; i <= P; i++) parent[i].clear();
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(BH, 0));
    dist[BH] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                parent[e2.v].clear();
                parent[e2.v].push_back(e1.v);
                q.push(edge(e2.v, dist[e2.v]));
            }
            else if (dist[e2.v] == dist[e1.v] + e2.w)
            {
                parent[e2.v].push_back(e1.v);
            }
        }
    }

    dfs(OF);
    
    memset(dist, 0x3f, sizeof(dist));
    q.push(edge(YH, 0));
    if (!disabled[YH]) dist[YH] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (disabled[e2.v]) continue;
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }
    
    if (dist[M] != INF) cout << dist[M] << '\n';
    else cout << "MISSION IMPOSSIBLE.\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;

    while (cin >> P >> R >> BH >> OF >> YH >> M)
    {
        for (int i = 1; i <= P; i++) edges[i].clear();
        for (int i = 1; i <= R; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
        }

        mooreDijkstra();
    }

    return 0;
}
