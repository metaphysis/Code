// Ordering Tasks
// UVa ID: 10305
// Verdict: Accepted
// Submission Date: 2017-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;
int visited[MAXV];
vector<list<int>> edges(MAXV);
vector<int> ts;
int n, m;

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
    ts.push_back(u);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m, n > 0)
    {
        for (int u = 1; u <= n; u++)
            edges[u].clear();
            
        int from, to;
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to;
            edges[from].push_back(to);
        }
        
        ts.clear();
        memset(visited, 0, sizeof visited);
        for (int u = 1; u <= n; u++)
            if (!visited[u])
                dfs(u);

        reverse(ts.begin(), ts.end());
        for (int i = 0; i < ts.size(); i++)
        {
            if (i) cout << ' ';
            cout << ts[i];
        }
        cout << '\n';
    }
    
    return 0;
}
