#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2048;

vector<int> edges[MAXV], sequence;
int n, m, visited[MAXV], parent[MAXV], in[MAXV];

void dfs(int u)
{
    sequence.push_back(u);
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
    // Root node can not be checked, or lead to wrong answer.
    for (int i = n - 1; i >= 1; i--)
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
    
    while (cin >> n >> m)
    {
        if (n == 0) break;
        for (int i = 0; i <= n; i++) edges[i].clear();
        for (int u, v, i = 0; i < m; i++)
        {
            cin >> u >> v;
            edges[v].push_back(u);
        }
        memset(visited, 0, sizeof(visited));
        sequence.clear();
        parent[0] = 0;
        dfs(0);
        cout << greedy() << '\n';
    }

    return 0;
}
