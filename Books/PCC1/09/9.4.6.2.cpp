const int MAXV = 10010;

vector<list<int>> g;

int dfn[MAXV], ic[MAXV], dfstime = 0;

int dfs(int u, int parent)
{
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) ic[u] = 1;
        }
        else if (dfn[v] < dfn[u] && v != parent) lowu = min(lowu, dfn[v]);
    }

    if (parent < 0 && children == 1) ic[u] = 0;
    return lowu;
}
