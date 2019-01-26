// Tour Belt
// UVa ID: 1265
// Verdict: Accepted
// Submission Date: 2019-01-26
// UVa Run Time: 0.080s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5010, INF = 0x7f7f7f7f;

struct edge
{
    int u, v, w;
    edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
} edges[MAXV * MAXV / 2];

int n, m;
int parent[MAXV], ranks[MAXV];
vector<edge> g[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i, ranks[i] = 1;
}

int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

bool validate(int u)
{
    int minW = INF, maxW = 0;
    for (int i = 0; i < n; i++)
        if (findSet(i) == u)
        {
            for (auto e : g[i])
            {
                if (findSet(e.v) == u) minW = min(minW, e.w);
                else maxW = max(maxW, e.w);   
            }
            if (minW <= maxW) return false;
        }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;

        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 0, u, v, w; i < m; i++)
        {
            cin >> u >> v >> w;
            u--, v--;
            g[u].push_back(edge(u, v, w));
            g[v].push_back(edge(v, u, w));
            edges[i] = edge(u, v, w);
        }

        makeSet();
        sort(edges, edges + m);

        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            int uu = edges[i].u, vv = edges[i].v;
            uu = findSet(uu), vv = findSet(vv);
            if (uu != vv)
            {
                ranks[uu] += ranks[vv];
                parent[vv] = uu;
                if (validate(uu)) sum += ranks[uu];
            }
        }
        cout << sum << '\n';
    }

    return 0;
}
