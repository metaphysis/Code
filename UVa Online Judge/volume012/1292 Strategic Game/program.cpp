// Strategic Game
// UVa ID: 1292
// Verdict: Accepted
// Submission Date: 2018-11-04
// UVa Run Time: 0.170s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1600;

list<int> edges[MAXV];
int N, M, n, visited[MAXV], sequence[MAXV], parent[MAXV], in[MAXV];

void dfs(int u)
{
    sequence[n++] = u;
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v);
        }
}

int greedy()
{
    memset(visited, 0, sizeof(visited));
    memset(in, 0, sizeof(visited));
    int r = 0;
    for (int i = N - 1; i >= 1; i--)
    {
        int u = sequence[i];
        if (!visited[u] && !visited[parent[u]])
        {
            in[parent[u]] = 1;
            r += 1;
            visited[u] = visited[parent[u]] = 1;
        }
    }
    return r;
}

int main(int argc, char *argv[])
{
    int u, v, m;
    char c1, c2, c3;
    while (cin >> N)
    {
        for (int i = 0; i <= N; i++) edges[i].clear();
        for (int i = 1; i <= N; i++)
        {
            cin >> u >> c1 >> c2 >> m >> c3;
            for (int j = 1; j <= m; j++)
            {
                cin >> v;
                edges[u].push_back(v);
                edges[v].push_back(u);
            }
        }
        memset(visited, 0, sizeof(visited));
        dfs(parent[0] = n = 0);
        cout << greedy() << '\n';
    }

    return 0;
}
