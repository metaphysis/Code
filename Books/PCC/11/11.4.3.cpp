const int MAXV = 10010, INF = 0x3f3f3f3f;

struct EDGE
{
    int u, v, next;
    EDGE (int u = 0, int v = 0, int next = 0): u(u), v(v), next(next) {}
} edges[MAXV << 1];

struct NODE
{
    int in, selfOut, selfChildOut;
} dp[MAXV];

int idx, head[MAXV];

void addEdge(int u, int v)
{
    edges[idx] = EDGE(u, v, head[u]);
    head[u] = idx++;
    edges[idx] = EDGE(v, u, head[v]);
    head[v] = idx++;
}

void dfs(int u, int father)
{
    dp[u].in = 1;
    dp[u].selfOut = dp[u].selfChildOut = 0;
    int x = INF, hasChild = 0, hasFirstStateIncluded = 0;
    for (int i = head[u]; ~i; i = edges[i].next)
    {
        int v = edges[i].v;
        if (v == father) continue;
        dfs(v, u);
        hasChild = 1;
        dp[u].in += min(dp[v].in, min(dp[v].selfOut, dp[v].selfChildOut));
        dp[u].selfOut += min(dp[v].in, dp[v].selfOut);
        if (dp[v].in > dp[v].selfOut) x = min(x, dp[v].in - dp[v].selfOut);
        else hasFirstStateIncluded = 1;
        dp[u].selfChildOut = min(INF, dp[u].selfChildOut + dp[v].selfOut);
    }
    if (!hasChild) dp[u].selfOut = INF;
    else 
    {
        if (!hasFirstStateIncluded) dp[u].selfOut += x;
    }
}
