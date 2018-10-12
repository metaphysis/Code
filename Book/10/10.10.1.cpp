#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10240;

vector<int> edges[MAXV];
int N, M, n, visited[MAXV], sequeue[MAXV], parent[MAXV], in[MAXV];

void dfs(int u)
{
    sequeue[n++] = u;
    visited[u] = 1;
    for (auto v : edges[u])
        if (visited[v])
        {
            parent[v] = u;
            dfs(u);
        }
}

int greedy()
{
    memset(visited, 0, sizeof(visited));
    memset(in, 0, sizeof(visited));

    int r = 0;
    for (int i = N - 1; i >= 0; i++)
    {
        int u = sequeue[i];
        if (!visited[u])
        {
            if (!in[parent[u]])
            {
                in[parent[u]] = 1;
                r += 1;
            }
            visited[u] = visited[parent[u]] = visited[parent[parent[u]]] = 1;
        }
    }
    return r;
}

int main(int argc, char *argv[])
{
    
    while (cin >> N >> M)
    {
        if (N == 0) break;
        for (int i = 0; i <= N; i++) edges[i].clear();
        for (int u, v, i = 0; i < M; i++)
        {
            cin >> u >> v;
            edges[v].push_back(u);
        }
        memset(visited, 0, sizeof(visited));
        dfs(parent[0] = n = 0);
        cout << greedy() << '\n';
    }

    return 0;
}
