// Shopping
// UVa ID: 11813
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.350s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];
int n, m, idx[MAXV], dist[10][MAXV];
int cnt, stores[10], used[10], minLength, cache[10];

void dfs(int depth, int length)
{
    if (depth == cnt)
    {
        length += dist[idx[cache[0]]][0] + dist[idx[cache[cnt - 1]]][0];
        minLength = min(minLength, length);
        return;
    }
    if (length >= minLength) return;
    for (int i = 0; i < cnt; i++)
        if (!used[i])
        {
            used[i] = 1;
            cache[depth] = stores[i];
            int nextLength = length;
            if (depth) nextLength += dist[idx[cache[depth - 1]]][stores[i]];
            dfs(depth + 1, nextLength);
            used[i] = 0;
        }
}

void mooreDijkstra(int i, int u)
{
    memset(dist[i], 0x3f, sizeof(dist[i]));
    priority_queue<edge> q;
    q.push(edge(u, 0));
    dist[i][u] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[i][e2.v] > dist[i][e1.v] + e2.w)
            {
                dist[i][e2.v] = dist[i][e1.v] + e2.w;
                q.push(edge(e2.v, dist[i][e2.v]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, u, v, w, cntOfStores, idxOfStore;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            edges[i].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
        }

        cin >> cnt;
        for (int i = 0; i < cnt; i++)
        {
            cin >> stores[i];
            idx[stores[i]] = i;
            mooreDijkstra(i, stores[i]);
        }
        
        memset(used, 0, sizeof(used));
        minLength = INF;
        dfs(0, 0);
        cout << minLength << '\n';
    }

    return 0;
}
