// How Many Dependencies?
// UVa ID: 10926
// Verdict: Accepted
// Submission Date: 2018-02-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

list<int> edges[MAXV];
int n, m, v, d, ds[MAXV], visited[MAXV], colored[MAXV];

void dfs(int u)
{
    d++;
    visited[u] = 1;
    colored[u] = 1;
    for (auto v : edges[u])
        if (!colored[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
        {
            edges[i].clear();
            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                cin >> v;
                edges[i].push_back(v);
            }
        }
        memset(ds, 0, sizeof(ds));
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; i++)
            if (!visited[i])
            {
                memset(colored, 0, sizeof(colored));
                d = 0;
                dfs(i);
                ds[i] = d;
            }
        
        int maxD = *max_element(ds + 1, ds + n + 1);
        for (int i = 1; i <= n; i++)
            if (ds[i] == maxD)
            {
                cout << i << '\n';
                break;
            }
    }

    return 0;
}
