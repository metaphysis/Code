const int MAXV = 1010;
const int WHITE = 0, GRAY = 1, BLACK = 2;

vector<list<int>> g(MAXV);
int parent[MAXV], color[MAXV], dfn[MAXV], ft[MAXV];
int dfstime, n;

void dfs(int u)
{
    dfn[u] = ++dfstime, color[u] = GRAY;
    for (auto v : g[u])
        if (!color[v])
        {
            parent[v] = u;
            dfs(v);
        }
    ft[u] = ++dfstime, color[u] = BLACK;
}

void search()
{
    memset(color, WHITE, sizeof(color));
    memset(parent, -1, sizeof(parent));
    
    dfstime = 0;
    for (int u = 0; u < n; u++)
        if (!color[u])
            dfs(u);
}
