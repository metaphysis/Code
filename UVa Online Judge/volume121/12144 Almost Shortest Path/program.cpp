// Almost Shortest Path
// UVa ID: 12144
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 510, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { w > e.w; }
};

list<edge> edges[MAXV];
int n, m, s, t, dist[MAXV], visited[MAXV], route[MAXV][MAXV];
vector<int> parent[MAXV];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : parent[u])
    {
        route[v][u] = 1;
        if (!visited[v])
            dfs(v);
    }
}

void mooreDijkstra()
{
    for (int i = 0; i < n; i++)
        parent[i].clear();

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(s, 0));
    dist[s] = 0;

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
    
    if (dist[t] == INF)
    {
        cout << "-1\n";
        return;
    }
    
    memset(visited, 0, sizeof(visited));
    memset(route, 0, sizeof(route));
    dfs(t);
    
    memset(dist, 0x3f, sizeof(dist));
    q.push(edge(s, 0));
    dist[s] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (route[e1.v][e2.v]) continue;
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }
    
    if (dist[t] == INF) cout << "-1\n";
    else cout << dist[t] << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;

    while (cin >> n >> m, n > 0)
    {
        cin >> s >> t;
        for (int i = 0; i < n; i++)
            edges[i].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
        }
        mooreDijkstra();
    }

    return 0;
}
