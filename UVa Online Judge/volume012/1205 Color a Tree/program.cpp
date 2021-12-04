// Color a Tree
// UVa ID: 1205
// Verdict: Accepted
// Submission Date: 2021-11-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int N, R, factor[MAXV], ai[MAXV], bi[MAXV];
double ri[MAXV];
vector<int> g[MAXV], s[MAXV];

void dfs(int u)
{
    ri[u] = (double)ai[u] / bi[u];
    if (!g[u].size()) return;

    for (auto v : g[u])
    {
        dfs(v);
        s[u].push_back(v);
    }

    while (true)
    {
        int maxI = -1;
        double r = 0;
        for (int i = 0; i < s[u].size(); i++)
            if (ri[s[u][i]] >= r)
            {
                r = ri[s[u][i]];
                maxI = i;
            }
        if (r < ri[u]) break;
        ai[u] += ai[s[u][maxI]], bi[u] += bi[s[u][maxI]];
        ri[u] = (double)ai[u] / bi[u];
        for (auto v : s[s[u][maxI]]) s[u].push_back(v);
        s[u].erase(s[u].begin() + maxI);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> R)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; i++) { cin >> factor[i]; ai[i] = factor[i]; bi[i] = 1; }
        for (int i = 1; i <= N; i++) { g[i].clear(); s[i].clear(); }
        for (int i = 1, u, v; i < N; i++)
        {
            cin >> u >> v;
            g[u].push_back(v);
        }

        dfs(R);

        int elapsed = 1, cost = 0;
        priority_queue<pair<double, int>> q;
        q.push(make_pair(ri[R], R));
        while (!q.empty())
        {
            pair<double, int> p = q.top(); q.pop();
            cost += elapsed * factor[p.second];
            for (auto v : g[p.second]) q.push(make_pair(ri[v], v));
            elapsed++;
        }
        cout << cost << '\n';
    }

    return 0;
}
