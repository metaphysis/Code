// Manhattan
// UVa ID: 10319
// Verdict: Accepted
// Submission Date: 2018-05-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> g(MAXV);
stack<int> s;

void dfs(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : g[u])
    {
        if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
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

void tarjan(int T)
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    for (int i = 0; i < T; i++)
        if (!dfn[i])
            dfs(i);
}

void addEdge(int u, int v)
{
    g[u ^ 1].push_back(v);
    g[v ^ 1].push_back(u);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, S, A, T, m, s1, a1, s2, a2;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> S >> A >> m;
        for (int u = 0; u < MAXV; u++) g[u].clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> s1 >> a1 >> s2 >> a2;

            s1--, a1--, s2--, a2--;
            s1 *= 2, s2 *= 2, a1 *= 2, a2 *= 2;
            a1 += 2 * S, a2 += 2 * S;
            
            if (s1 == s2 && a1 == a2) continue;
            if(a1 > a2) s1 ^= 1, s2 ^= 1;
            if(s1 > s2) a1 ^= 1, a2 ^= 1;
            if(s1 == s2)
            {
                g[s1 ^ 1].push_back(s2);
                continue;
            }
            if(a1 == a2)
            {
                g[a1 ^ 1].push_back(a2);
                continue;
            }
            
            // (s1 & a2) | (s2 & a1) <=> (s1 | a1) & (s1 | s2) & (a1 | a2) & (s2 | a2)
            addEdge(s1, a1), addEdge(s1, s2), addEdge(a1, a2), addEdge(s2, a2);
        }

        T = 2 * (S + A);
        tarjan(T);

        bool flag = true;
        for (int j = 0; j < T && flag; j += 2)
            if (scc[j] == scc[j ^ 1])
                flag = false;
        cout << (flag ? "Yes" : "No") << '\n';
    }

    return 0;
}
