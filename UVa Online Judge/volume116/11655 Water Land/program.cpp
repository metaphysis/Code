// Water Land
// UVa ID: 11655
// Verdict: Accepted
// Submission Date: 2018-02-22
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5100, MOD = 100000;

list<int> edges[MAXV], redges[MAXV];
int n, m, cnt1[MAXV], cnt2[MAXV], cnt3[MAXV], visited[MAXV];

void dfs1(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
    {
        if (!visited[v])
            dfs1(v);
        cnt1[u] = (cnt1[u] + cnt1[v] + cnt2[v]) % MOD;
        cnt2[u] = (cnt2[u] + cnt2[v]) % MOD;
    }
}

void dfs2(int u)
{
    visited[u] = 1;
    for (auto v : redges[u])
    {
        if (!visited[v])
            dfs2(v);
        cnt3[u] = (cnt3[u] + cnt3[v]) % MOD;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            edges[i].clear();
            redges[i].clear();
            cnt1[i] = 0;
            cnt2[i] = 1;
            cnt3[i] = 0;
        }
        for (int i = 1, u, v; i <= m; i++)
        {
            cin >> u >> v;
            edges[u].push_back(v);
            redges[v].push_back(u);
            cnt2[u] = 0;
        }
        cnt3[1] = 1;
        
        memset(visited, 0, sizeof(visited));
        dfs1(1);
        memset(visited, 0, sizeof(visited));
        dfs2(n);

        cout << "Case " << c << ": " << cnt1[1] << ' ' << cnt3[n] << '\n';
    }

    return 0;
}
