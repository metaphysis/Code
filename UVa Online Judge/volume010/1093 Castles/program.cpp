// Castles
// UVa ID: 1093
// Verdict: Accepted
// Submission Date: 2018-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int ai[110], mi[110], gi[110], visited[110];
list<int> edges[110];

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.first - a.second < b.first - b.second;
}

pair<int, int> dfs(int u)
{
    visited[u] = 1;
    vector<pair<int, int>> prs;
    for (auto v : edges[u])
    {
        if (visited[v]) continue;
        prs.push_back(dfs(v));
    }
    sort(prs.begin(), prs.end(), cmp);
    int r1 = 0, r2 = 0;
    for (auto pr : prs)
    {
        r1 = max(pr.first, r1 + pr.second);
        r2 += pr.second;
    }
    r1 = max(ai[u], r1 + mi[u] + gi[u]);
    r2 += mi[u] + gi[u];
    return make_pair(r1, r2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << "Case " << ++cases << ": ";
        for (int i = 1; i <= n; i++) cin >> ai[i] >> mi[i] >> gi[i];
        for (int i = 1; i <= n; i++) edges[i].clear();
        for (int i = 1, u, v; i < n; i++)
        {
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        int minr = 0x3f3f3f3f;
        for (int i = 1; i <= n; i++)
        {
            memset(visited, 0, sizeof(visited));
            pair<int, int> r = dfs(i);
            minr = min(minr, r.first);
        }
        cout << minr << '\n';
    }

    return 0;
}
