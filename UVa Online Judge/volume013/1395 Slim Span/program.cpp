// Slim Span
// UVa ID: 1395
// Verdict: Accepted
// Submission Date: 2019-02-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, MAXE = 10010, INF = 0x7f7f7f7f;

struct edge
{
    int u, v, w;
    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w < e.w; }
} edges[MAXE];

int n, m, parent[MAXN];

void makeSet()
{
    for (int i = 1; i <= n; i++) parent[i] = i;
}

int findSet(int x)
{
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        if (n == 0) break;
        for (int i = 0, ai, bi, wi; i < m; i++)
        {
            cin >> ai >> bi >> wi;
            edges[i] = edge(ai, bi, wi);
        }
        sort(edges, edges + m);
        int best = INF;
        for (int i = 0; i < m; i++)
        {
            makeSet();
            int cnt = n;
            for (int j = i, u, v; j < m; j++)
            {
                u = findSet(edges[j].u), v = findSet(edges[j].v);
                if (u == v) continue;
                parent[u] = v;
                if (--cnt == 1)
                {
                    best = min(best, edges[j].w - edges[i].w);
                    break;
                }
            }
        }
        if (best == INF) best = -1;
        cout << best << '\n';
    }

    return 0;
}
