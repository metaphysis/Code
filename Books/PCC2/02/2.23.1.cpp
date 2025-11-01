#include <bits/stdc++.h>

using namespace std;

const int MAXE = 1000010, MAXN = 10010;

struct edge { int v, w, nxt; } g[MAXN];

int head[MAXN], idx;

int parent[MAXN], son[MAXN], depth[MAXN];
int size[MAXN], top[MAXN], dfn[MAXN], rnk[MAXN];
int cnt;

void addEdge(int u, int v, int w) {
    g[idx] = edge{v, w, head[u]};
    head[u] = idx++;
    g[idx] = edge{u, w, head[v]};
    head[v] = idx++;
}

void dfs1(int u, int d) {
    son[u] = -1;
    depth[u] = d;
    size[u] = 1;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        int v = g[i].v;
        if (~depth[v]) continue;
        parent[v] = u;
        dfs1(v, d + 1);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (int i = head[u]; ~i; i = g[i].nxt) {
        int v = g[i].v;
        if (v != son[u] && v != parent[u])
            dfs2(v, v);
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    memset(head, -1, sizeof head);
    idx = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    memset(depth, -1, sizeof depth);
    dfs1(1, 1);
    cnt = 0;
    dfs2(1, 1);
    return 0;
}
