// Instant View of Big Bang
// UVa ID: 11721
// Verdict: Accepted
// Submission Date: 2018-12-22
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1100, MAXE = 3100, INF = 0x3f3f3f3f;

struct edge { int u, v, w; } edges1[MAXE];

int dist[MAXV], n, m, visited[MAXV];
list<int> edges2[MAXV];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges2[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;
        for (int i = 0; i <= n; i++) edges2[i].clear();
        for (int i = 0, x, y, t; i < m; i++)
        {
            cin >> x >> y >> t;
            x++, y++;
            edges1[i].u = y, edges1[i].v = x, edges1[i].w = t;
            edges2[y].push_back(x);
        }

        memset(dist, 0, sizeof(dist));
        int updated = 1;
        for (int k = 1; k < n && updated; k++)
        {
            updated = 0;
            for (int i = 0; i < m; i++)
                if (dist[edges1[i].v] > dist[edges1[i].u] + edges1[i].w)
                {
                    dist[edges1[i].v] = dist[edges1[i].u] + edges1[i].w;
                    updated = 1;
                }
        }

        vector<int> vertices;
        for (int i = 0; i < m; i++)
            if (dist[edges1[i].v] > dist[edges1[i].u] + edges1[i].w)
            {
                vertices.push_back(edges1[i].u);
                vertices.push_back(edges1[i].v);
            }
        cout << "Case " << cs << ":";
        if (vertices.size() == 0) cout << " impossible";
        else
        {
            memset(visited, 0, sizeof(visited));
            for (auto v : vertices)
                if (!visited[v])
                    dfs(v);
            for (int v = 1; v <= n; v++)
                if (visited[v])
                    cout << ' ' << (v - 1);
        }
        cout << '\n';
    }

    return 0;
}
