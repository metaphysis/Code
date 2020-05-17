const int MAXV = 10010;

int n;
int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> edges(MAXV);
stack<int> s;

void dfs(int u)
{
    dfn[u] = low[u] = ++dfstime;
    s.push(u);
    for (auto v : edges[u])
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
    memset(dfn, 0, sizeof(dfn)), memset(scc, 0, sizeof(scc));
    for (int u = 0; u < n; u++)
        if (!dfn[u])
            dfs(u);
}
