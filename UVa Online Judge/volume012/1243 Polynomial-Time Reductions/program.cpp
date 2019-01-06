// Polynomial-Time Reductions
// UVa ID: 1243
// Verdict: Accepted
// Submission Date: 2019-01-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 10010;

int n, m, g[MAXV][MAXV], reductions, verticesInSCC;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> edges(MAXV);
stack<int> s;

void reset()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 0; u < MAXV; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        verticesInSCC = 0;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            verticesInSCC++;
            if (u == v) break;
            
        }
        if (verticesInSCC > 1) reductions += verticesInSCC;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n >> m)
    {
        if (n == 0) break;

        reset();

        for (int i = 0, u, v; i < m; i++)
        {
            cin >> u >> v;
            edges[u].push_back(v);
        }

        reductions = 0;
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);

        memset(g, 0, sizeof(g));
        for (int u = 1; u <= n; u++)
            for (auto v : edges[u])
                if (scc[u] != scc[v])
                    g[scc[u]][scc[v]] = 1;
                    
        // Floyd-Warshall.
        for (int k = 1; k <= cscc; k++)
            for (int i = 1; i <= cscc; i++)
                for (int j = 1; j <= cscc; j++)
                    g[i][j] |= (g[i][k] & g[k][j]);

        for (int i = 1; i <= cscc; i++)
            for (int j = 1; j <= cscc; j++)
                if (g[i][j])
                {
                    int neededReduction = 1;
                    for (int k = 1; k <= cscc; k++)
                        if (g[i][k] && g[k][j])
                        {
                            neededReduction = 0;
                            break;
                        }
                    reductions += neededReduction;
                }

        cout << "Case " << ++cases << ": " << reductions << '\n';
    }

    return 0;
}
