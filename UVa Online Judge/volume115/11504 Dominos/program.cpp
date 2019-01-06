// Dominos
// UVa ID: 11504
// Verdict: Accepted
// Submission Date: 2016-09-12
// UVa Run Time: 0.096s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010;

int visited[MAXV], cases, n, m;
stack<int> s;
vector<int> g[MAXV];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : g[u])
        if (!visited[v])
            dfs(v);
    s.push(u);
}

void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : g[u])
        if (!visited[v])
            rdfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        while (!s.empty()) s.pop();
        for (int u = 1; u <= n; u++) g[u].clear(), visited[u] = 0;

        cin >> n >> m;
        for (int e = 1, u, v; e <= m; e++)
        {
            cin >> u >> v;
            g[u].push_back(v);
        }

        for (int u = 1; u <= n; u++)
            if (!visited[u])
                dfs(u);

        int cc = 0;
        for (int u = 1; u <= n; u++) visited[u] = 0;
        while (!s.empty())
        {
            int u = s.top();
            if (!visited[u])
                rdfs(u), cc++;
            s.pop();
        }
        
        cout << cc << '\n';
    }

    return 0;
}
