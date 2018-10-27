// Intervals
// UVa ID: 1723
// Verdict: Accepted
// Submission Date: 2018-10-27
// UVa Run Time: 0.100s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 50010, MAXE = 150010;

struct edge
{
    int v, w, next;
    edge (int v = 0, int w = 0, int next = 0): v(v), w(w), next(next) {}
} edges[MAXE];

int idx, n, head[MAXN], dist[MAXN], in[MAXN], mi, mx;

void addEdge(int u, int v, int w)
{
    edges[idx] = edge(v, w, head[u]);
    head[u] = idx++;
}

void spfa()
{
    memset(in, 0, sizeof(in));
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q;
    dist[mx] = 0, in[mx] = 1;
    q.push(mx);
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        in[u] = 0;
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            edge e = edges[i];
            if (dist[e.v] > dist[u] + e.w)
            {
                dist[e.v] = dist[u] + e.w;
                if (!in[e.v])
                {
                    q.push(e.v);
                    in[e.v] = 1;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        cin >> n;
        idx = 0, mi = INF, mx = -INF;
        memset(head, -1, sizeof(head));
        int u, v, w;
        for (int i = 0; i < n; i++)
        {
            cin >> u >> v >> w;
            u++, v++;
            addEdge(v, u - 1, -w);
            mi = min(mi, u), mx = max(mx, v);
        }
        for (int i = mi; i <= mx; i++)
        {
            addEdge(i - 1, i, 1);
            addEdge(i, i - 1, 0);
        }
        spfa();
        if (cs) cout << '\n';
        cout << (dist[mx] - dist[mi - 1]) << '\n';
    }
    
    return 0;
}
