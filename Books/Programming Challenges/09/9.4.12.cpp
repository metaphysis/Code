const int MAXN = 10010, INF = 0x7fffffff;

int n;
int d[MAXN], s[MAXN];
int bestU, bestD = INF;

vector<int> edges[MAXN];

void dfs(int u, int father)
{
    s[u] = 1, d[u] = 0;
    for (auto v : edges[u])
    {
        if (v == father) continue;
        dfs(v, u);
        s[u] += s[v];
        d[u] = max(d[u], s[v]);
    }
    d[u] = max(d[u], n - s[u]);
    if (d[u] < bestD) bestD = d[u], bestU = u;
}
