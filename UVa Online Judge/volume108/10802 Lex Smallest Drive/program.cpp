// Lex Smallest Drive
// UVa ID: 10802
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, s, successed, failed, depth;
int g[110][110], walk[256];

void dfs(int previous, int u, int sink)
{
    if (failed || successed) return;
    if (depth > 150)
    {
        failed = 1;
        return;
    }
    if (u == sink)
    {
        for (int i = 0; i <= depth; i++)
        {
            if (i) cout << ' ';
            cout << walk[i];
        }
        cout << '\n';
        successed = 1;
        return;
    }
    for (int v = 0; v < n; v++)
    {
        if (!g[u][v]) continue;
        if (v == previous) continue;
        walk[++depth] = v;
        dfs(u, v, sink);
        depth--;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m >> s;
        memset(g, 0, sizeof(g));
        for (int u, v, i = 0; i < m; i++)
        {
            cin >> u >> v;
            g[u][v] = g[v][u] = 1;
        }

        cout << "Case #" << cs << ":\n";
        for (int i = 0; i < n; i++)
        {
            successed = failed = depth = 0;
            walk[0] = s;
            dfs(-1, s, i);
            if (failed)
                cout << "No drive.\n";
        }
        cout << '\n';
    }

    return 0;
}
