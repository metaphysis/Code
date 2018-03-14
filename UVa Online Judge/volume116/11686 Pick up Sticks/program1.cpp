// Pick up Sticks
// UVa ID: 11686
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.700s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000010;
int color[MAXV], ts[MAXV], cnt, n, m, cycled = 0;
vector<list<int>> edges(MAXV);

void dfs(int u)
{
    if (cycled) return;
    color[u] = 1;
    for (auto v : edges[u])
        if (!color[v]) dfs(v);
        else
        {
            if (color[v] == 1)
            {
                cycled = 1;
                return;
            }
        }
    color[u] = 2;
    ts[cnt++] = u;
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

        cycled = 0, cnt = 0;
        memset(color, 0, (n + 1) * sizeof(int));
        for (int u = 1; u <= n; u++)
            if (!color[u])
                dfs(u);

        if (cycled) cout << "IMPOSSIBLE\n";
        else
        {
            for (int i = cnt - 1; i >= 0; i--)
                cout << ts[i] << '\n';
        }
    }
    
    return 0;
}
