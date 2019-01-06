// Proving Equivalences
// UVa ID: 12167
// Verdict: Accepted
// Submission Date: 2016-09-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 20010;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
int cases, n, m;
stack<int> s;
vector<list<int>> g(MAXV);

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

void tarjan()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    for (int u = 1; u <= n; u++)
        if (!dfn[u])
            dfs(u);
}



inline int nextChar()
{
    const int LENGTH = 1048576;
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline bool nextInt(int &x)
{
    static char negative = 0, c = nextChar();
    negative = 0, x = 0;
    while ((c < '0' || c > '9') && c != '-') { if (c == EOF) return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        for (int u = 1; u <= n; u++) g[u].clear();

        nextInt(n), nextInt(m);
        for (int e = 1, u, v; e <= m; e++)
        {
            nextInt(u), nextInt(v);
            g[u].push_back(v);
        }

        tarjan();

        if (cscc == 1) cout << "0\n";
        else
        {
            int id[MAXV] = {0}, od[MAXV] = {0};
            for (int u = 1; u <= n; u++)
                for (auto v : g[u])
                {
                    if (scc[u] == scc[v]) continue;
                    od[scc[u]] = id[scc[v]] = 1;
                }

            int tid = 0, tod = 0;
            for (int u = 1; u <= cscc; u++)
            {
                if (!id[u]) tid++;
                if (!od[u]) tod++;
            }
            cout << max(tid, tod) << '\n';
        }
    }

	return 0;
}
