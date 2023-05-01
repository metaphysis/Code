// Hedge Mazes
// UVa ID: 12363
// Verdict: Accepted
// Submission Date: 2023-05-01
// UVa Run Time: 0.060s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;

struct edge { int u, v, b, nxt; } g[200010];

int R, C, Q;
int cnt, head[MAXV];
int visited[MAXV], dfn[MAXV], low[MAXV];

void dfs(int u, int parent, int depth) {
    visited[u] = 1; dfn[u] = low[u] = depth;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        int v = g[i].v;
        if (v != parent && visited[v] == 1) low[u] = min(low[u], dfn[v]);
        if (!visited[v]) {
            dfs(v, u, depth + 1);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) g[i].b = 1;
        }
    }
    visited[u] = 2;
}

int parent[MAXV], ranks[MAXV];
int findSet(int x) {
    return x == parent[x] ? x : parent[x] = findSet(parent[x]);
}

bool unionSet(int x, int y) {
    x = findSet(x), y = findSet(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> R >> C >> Q, R) {
        cnt = 0;
        memset(head, -1, sizeof head);
        for (int i = 0, u, v; i < C; i++) {
            cin >> u >> v;
            g[cnt] = edge{u, v, 0, head[u]};
            head[u] = cnt++;
            g[cnt] = edge{v, u, 0, head[v]};
            head[v] = cnt++;
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));
        for (int u = 1; u <= R; u++)
            if (!visited[u])
                dfs(u, -1, 1);
        for (int i = 0; i <= R; i++) parent[i] = i, ranks[i] = 0;
        for (int i = 0; i < cnt; i++)
            if (g[i].b)
                unionSet(g[i].u, g[i].v);
        for (int i = 0, u, v; i < Q; i++) {
            cin >> u >> v;
            if (findSet(u) == findSet(v)) cout << 'Y';
            else cout << 'N';
            cout << '\n';
        }
        cout << "-\n";
    }
    return 0;
}
