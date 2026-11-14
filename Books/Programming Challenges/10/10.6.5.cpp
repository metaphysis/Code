#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210, UNVISITED = -1, WHITE = 0, BLACK = 1;

int n, m;
vector<int> g[MAXN];
int parent[MAXN], linked[MAXN], base[MAXN], color[MAXN];

void initialize() { for (int i = 0; i <= n; i++) g[i].clear(); }
void addEdge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }

int lca(int u, int v)
{
    static int token = 0, key[MAXN] = {};
    for (++token; ; swap(u, v)) {
        if (u == 0) continue;
        if (key[u] == token) return u;
        key[u] = token;
        u = base[parent[linked[u]]];
    }
}

void shrink(int u, int v, int p, queue<int> &q)
{
    while (base[u] != p) {
        parent[u] = v, v = linked[u];
        if (color[v] == BLACK) q.push(v), color[v] = WHITE;
        base[u] = base[v] = p, u = parent[v];
    }
}

int bfs(int u)
{
    for (int i = 0; i <= n; i++) base[i] = i;
    memset(color, UNVISITED, sizeof(color));
    queue<int> q;
    q.push(u); color[u] = WHITE;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (auto v : g[u]) {
            if (color[v] == UNVISITED) {
                parent[v] = u, color[v] = BLACK;
                if (!linked[v]) {
                    for (int prev; u; v = prev, u = parent[v]) {
                        prev = linked[u];
                        linked[u] = v, linked[v] = u;
                    }
                    return 1;
                }
                q.push(linked[v]); color[linked[v]] = WHITE;
            } else if (color[v] == WHITE && base[v] != base[u]) {
                int p = lca(u, v);
                shrink(v, u, p, q);
                shrink(u, v, p, q);
            }
        }
    }
    return 0;
}

int edmonds()
{
    memset(parent, 0, sizeof(parent));
    memset(linked, 0, sizeof(linked));
    int matches = 0;
    for (int i = 1; i <= n; i++) {
        if (!linked[i] && bfs(i))
            matches++;
    }
    return matches;
}

int main(int argc, char *argv[])
{
    while (cin >> n >> m) {
        initialize();
        for (int i = 1, u, v; i <= m; i++) {
            cin >> u >> v;
            addEdge(u, v);
        }
        cout << edmonds() << '\n';
    }
    return 0;
}
