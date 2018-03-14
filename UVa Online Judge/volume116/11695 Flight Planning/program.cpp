// Flight Planning
// UVa ID: 11695
// Verdict: Accepted
// Submission Date: 2018-02-21
// UVa Run Time: 3.110s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2510, INF = 0x3f3f3f3f;

set<int> edges[MAXV];
int n, t, D, visited[MAXV], parent[MAXV];

void dfs(int u, int d)
{
    if (d > D) { D = d; t = u; }
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v, d + 1);
        }
}

vector<int> getDiameter(int s)
{
    memset(visited, 0, (n + 1) * sizeof(int));
    D = -1;
    dfs(s, 0);

    memset(visited, 0, (n + 1) * sizeof(int));
    memset(parent, -1, (n + 1) * sizeof(int));
    D = -1;
    dfs(t, 0);

    vector<int> path;
    while (parent[t] != -1)
    {
        path.push_back(t);
        t = parent[t];
    }
    path.push_back(t);

    return path;
}

int getCenter(int s)
{
    vector<int> path = getDiameter(s);
    return path[path.size() / 2];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++) edges[i].clear();

        for (int i = 1, u, v; i < n; i++)
        {
            cin >> u >> v;
            edges[u].insert(v);
            edges[v].insert(u);
        }

        int maximum = INF, ff = -1, tt = -1, uu = -1, vv = -1;
        vector<int> path = getDiameter(1);
        for (int i = 1; i < path.size(); i++)
        {
            int from = path[i - 1], to = path[i];
            edges[from].erase(to), edges[to].erase(from);

            int u = getCenter(from), v = getCenter(to);
            edges[u].insert(v), edges[v].insert(u);

            getDiameter(u);
            if (maximum > D)
            {
                maximum = D;
                ff = from, tt = to, uu = u, vv = v;
            }

            edges[u].erase(v), edges[v].erase(u);
            edges[from].insert(to), edges[to].insert(from);
        }

        cout << maximum << '\n';
        cout << ff << ' ' << tt << '\n';
        cout << uu << ' ' << vv << '\n';
    }

    return 0;
}
