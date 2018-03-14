// Commandos
// UVa ID: 11463
// Verdict: Accepted
// Submission Date: 2018-02-15
// UVa Run Time: 0.010s
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
int n, m, s, t, distS[MAXV], distT[MAXV];

int mooreDijkstra()
{
    // source to others vertices.
    memset(distS, 0x3f, sizeof(distS));
    
    priority_queue<edge> q;
    q.push(edge(s, 0));
    distS[s] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (distS[e2.v] > distS[e1.v] + e2.w)
            {
                distS[e2.v] = distS[e1.v] + e2.w;
                q.push(edge(e2.v, distS[e2.v]));
            }
        }
    }

    // destination to others vertices.
    memset(distT, 0x3f, sizeof(distT));
    q.push(edge(t, 0));
    distT[t] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (distT[e2.v] > distT[e1.v] + e2.w)
            {
                distT[e2.v] = distT[e1.v] + e2.w;
                q.push(edge(e2.v, distT[e2.v]));
            }
        }
    }

    int maximum = 0;
    for (int i = 0; i < n; i++)
        maximum = max(maximum, distS[i] + distT[i]);
    return maximum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        int u, v;
        for (int i = 0; i < n; i++)
            edges[i].clear();

        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v;
            edges[u].push_back(edge(v, 1));
            edges[v].push_back(edge(u, 1));
        }
        cin >> s >> t;
        cout << "Case " << c << ": " << mooreDijkstra() << '\n';;
    }

    return 0;
}
