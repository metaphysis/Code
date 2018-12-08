// Hotel Booking
// UVa ID: 11635
// Verdict: Accepted
// Submission Date: 2018-12-08
// UVa Run Time: 1.980s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10240, MAXE = 204800, INF = 0x3f3f3f3f;

struct edge
{
    int to, weight, next;
    edge (int to = 0, int weight = 0, int next = 0): to(to), weight(weight), next(next) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
} edges[MAXE];

int head[MAXV], idx;
void addEdge(int u, int v, int weight)
{
    edges[idx] = edge(v, weight, head[u]);
    head[u] = idx++;
    edges[idx] = edge(u, weight, head[v]);
    head[v] = idx++;
}

int dist[MAXV];
void mooreDijkstra(int n, int u)
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[u] = 0;
    priority_queue<edge> q;
    q.push(edge(u, dist[u], -1));
    while (!q.empty())
    {
        edge ue = q.top(); q.pop();
        if (dist[ue.to] < ue.weight) continue;
        for (int i = head[ue.to]; ~i; i = edges[i].next)
        {
            edge ve = edges[i];
            if (dist[ve.to] > dist[ue.to] + ve.weight)
            {
                dist[ve.to] = dist[ue.to] + ve.weight;
                q.push(edge(ve.to, dist[ve.to], -1));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, h, m, hotel[128];
    while (cin >> n)
    {
        if (n == 0) break;
        cin >> h;
        for (int i = 0; i < h; i++) cin >> hotel[i];
        cin >> m;
        idx = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0, u, v, t; i < m; i++)
        {
            cin >> u >> v >> t;
            addEdge(u, v, t);
        }

        hotel[h++] = 1, hotel[h++] = n;
        sort(hotel, hotel + h);
        h = unique(hotel, hotel + h) - hotel;

        list<int> g[128];
        for (int i = 0; i < h; i++)
        {
            mooreDijkstra(n, hotel[i]);
            for (int j = 0; j < h; j++)
            {
                if (j == i) continue;
                if (dist[hotel[j]] <= 600)
                    g[i].push_back(j);
            }
        }

        int answer = -1, visited[128] = {};
        queue<int> q, p;
        q.push(0), p.push(0);
        visited[0] = 1;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            int d = p.front(); p.pop();
            if (u == (h - 1))
            {
                answer = d - 1;
                break;
            }
            for (auto v : g[u])
                if (!visited[v])
                {
                    visited[v] = 1;
                    q.push(v);
                    p.push(d + 1);
                }
        }
        cout << answer << '\n';
    }

    return 0;
}
