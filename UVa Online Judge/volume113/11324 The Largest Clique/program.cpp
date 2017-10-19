// The Largest Clique
// UVa ID: 11324
// Verdict: Accepted
// Submission Date: 2017-10-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1010;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
stack<int> s; vector<list<int>> edges(MAXV);
int n, m;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 1; u <= n; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

int visited[MAXV], cnt[MAXV], id[MAXV];
vector<list<int>> edges1(MAXV);

void dfs(int u)
{
    visited[u] = 1;
    
    int k = 0;
    for (auto v : edges1[u])
    {
        if (!visited[v]) dfs(v);
        k = max(k, cnt[v]);
    }

    cnt[u] += k;
}

void findSemiconnected()
{
    for (int u = 1; u <= cscc; u++)
        edges1[u].clear();

    memset(cnt, 0, sizeof cnt); memset(id, 0, sizeof id);
    for (int u = 1; u <= n; u++)
    {
        cnt[scc[u]]++;
        for (auto v : edges[u])
        {
            if (scc[u] == scc[v]) continue;
            edges1[scc[u]].push_back(scc[v]);
            id[scc[v]]++;
        }
    }

    memset(visited, 0, sizeof visited);
    for (int u = 1; u <= cscc; u++)
        if (!id[u])
            dfs(u);

    cout << *max_element(cnt, cnt + cscc + 1) << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        
        initialize();

        int from, to;
        for (int i = 0; i < m; i++)
        {
            cin >> from >> to;
            edges[from].push_back(to);
        }

        for (int u = 1; u <= n; u++)
            if (!dfn[u])
                tarjan(u);

        if (cscc == 1) cout << n << "\n";
        else findSemiconnected();
    }
    
    return 0;
}
