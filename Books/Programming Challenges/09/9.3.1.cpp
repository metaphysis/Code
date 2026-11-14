#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int n;
int parent[MAXV], visited[MAXV], dist[MAXV];

vector<int> g[MAXV];

void bfs(int u)
{
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    memset(dist, -1, sizeof(dist));

    queue<int> q;
    q.push(u);
    visited[u] = 1, dist[u] = 0;

    while (!q.empty())
    {
        u = q.front(); q.pop();
        for (auto v : g[u])
            if (!visited[v])
            {
                q.push(v);
                parent[v] = u, visited[v] = 1, dist[v] = dist[u] + 1;
            }
    }
}

int main(int argc, char *argv[])
{
    while (cin >> n)
    {
        for (int u = 1, edges; u <= n; u++)
        {
            g[u].clear();
            cin >> edges;
            for (int e = 1, v; e <= edges; e++)
            {
                cin >> v;
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }

        bfs(1);

        cout << "Vertex    Parent    Distance\n";
        for (int i = 1; i <= n; i++)
        {
            cout << setw(6) << right << i;
            cout << setw(10) << right << parent[i];
            cout << setw(12) << right << dist[i];
            cout << '\n';
        }
    }

    return 0;
}
