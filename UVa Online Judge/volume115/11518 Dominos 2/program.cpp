// Dominos 2
// UVa ID: 11518
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

list<int> dominos[10010];
int visited[10010], cnt = 0;

void dfs(int u)
{
    cnt++;
    visited[u] = 1;
    for (auto v : dominos[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, l, x, y, z;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m >> l;
        for (int i = 1; i <= n; i++)
            dominos[i].clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y;
            dominos[x].push_back(y);
        }

        cnt = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= l; i++)
        {
            cin >> z;
            if (!visited[z])
                dfs(z);
        }
        cout << cnt << '\n';
    }

    return 0;
}
