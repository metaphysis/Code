// Cockroach Escape Networks
// UVa ID: 10805
// Verdict: Accepted
// Submission Date: 2018-02-21
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 32, INF = 0x3f3f3f3f;

list<int> edges[MAXV], mst[MAXV];
list<pair<int, int>> allEdges;
int n, m, t, D, visited[MAXV];

void dfs(int u, int d)
{
    if (d > D) { D = d; t = u; }
    visited[u] = 1;
    for (auto v : mst[u])
        if (!visited[v])
            dfs(v, d + 1);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        for (int i = 0; i < n; i++) edges[i].clear();
        allEdges.clear();
        for (int i = 1, u, v; i <= m; i++)
        {
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
            allEdges.push_back(make_pair(u, v));
        }

        int ert = INF;
        for (auto e : allEdges)
        {
            memset(visited, 0, sizeof(visited));
            for (int j = 0; j < n; j++) mst[j].clear();

            queue<int> q;
            q.push(e.first); q.push(e.second);
            visited[e.first] = 1; visited[e.second] = 1;

            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (auto v : edges[u])
                    if (!visited[v])
                    {
                        visited[v] = 1;
                        mst[u].push_back(v);
                        mst[v].push_back(u);
                        q.push(v);
                    }
            }

            mst[e.first].push_back(e.second);
            mst[e.second].push_back(e.first);

            memset(visited, 0, sizeof(visited));
            D = 0;
            dfs(0, 0);

            memset(visited, 0, sizeof(visited));
            D = 0;
            dfs(t, 0);

            ert = min(ert, D);
        }
        cout << "Case #" << c << ":\n";
        cout << ert << '\n';
        cout << '\n';
    }
 
    return 0;
}
