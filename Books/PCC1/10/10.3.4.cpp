const int MAXV = 110, MAXE = 10010, INF = 0x7f7f7f7f;

struct edge
{
    int u, v, w;
    edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
    bool operator<(const edge &e) const { return w < e.w; }
} edges[MAXE];

vector<edge> g[MAXV];

int n, m;
int parent[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i;
}

int findSet(int x)
{
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

void addEdge(int idx)
{
    edge e = edges[idx];
    g[e.u].push_back(edge(idx, e.v, e.w));
    g[e.v].push_back(edge(idx, e.u, e.w));
}

int chosen[MAXE], shortest[MAXV], longest[MAXV], link[MAXV], idx[MAXV];

void dfs(int father, int u)
{
    for (auto e : g[u])
    {
        if (!chosen[e.u]) continue;
        if (e.v == father) continue;
        if (u)
        {
            longest[e.v] = e.w;
            link[e.v] = e.u;
            if (longest[u] > longest[e.v])
            {
                longest[e.v] = longest[u];
                link[e.v] = link[u];
            }
        }
        else longest[e.v] = -INF;
        dfs(u, e.v);
    }
}

int rmst(int k)
{
    memset(chosen, 0, sizeof(chosen));
    memset(idx, -1, sizeof(idx));

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
    {
        if (!edges[i].u) continue;
        if (unionSet(edges[i].u, edges[i].v)) chosen[i] = 1;
    }

    int components = 0;
    shortest[0] = INF;
    for (int i = 1; i < n; i++)
        if (findSet(i) == i)
        {
            components++;
            shortest[i] = INF;
        }
    if (components > k) return INF;

    for (int i = 0; i < m; i++)
    {
        if (edges[i].u) continue;
        idx[edges[i].v] = i;
        int scc = findSet(edges[i].v);
        if (edges[i].w < shortest[scc])
        {
            shortest[scc] = edges[i].w;
            link[scc] = i;
        }
    }

    for (int i = 1; i < n; i++)
        if (findSet(i) == i)
        {
            if (shortest[i] == INF) return INF;
            chosen[link[i]] = 1;
        }
    
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i < m; i++)
        if (chosen[i])
            addEdge(i);

    while (components < k)
    {
        dfs(-1, 0);
        int delta = INF, selected = INF;
        for (int i = 1; i < n; i++)
        {
            if (idx[i] == -1 || longest[i] == -INF) continue;
            if (edges[idx[i]].w - longest[i] < delta)
            {
                delta = edges[idx[i]].w - longest[i];
                selected = i;
            }
        }
        if (delta == INF) return INF;
        chosen[link[selected]] = 0;
        chosen[idx[selected]] = 1;
        addEdge(idx[selected]);
        components++;
    }

    int sum = 0;
    for (int i = 0; i < m; i++)
        if (chosen[i])
            sum += edges[i].w;
    return sum;
}
