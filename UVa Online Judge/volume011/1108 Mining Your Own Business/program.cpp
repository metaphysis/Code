// Mining Your Own Business
// UVa ID: 1108
// Verdict: Accepted
// Submission Date: 2024-11-24
// UVa Run Time: 0.310s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010;

struct EDGE
{
    int u, v, used, nxt;
    EDGE (int u = 0, int v = 0, int used = 0, int nxt = 0): u(u), v(v), used(used), nxt(nxt) {}
} g[MAXV << 1];

struct edge {
    int u, v;
    bool operator==(const edge e) const {
        return (e.u == u && e.v == v) || (e.u == v && e.v == u);
    }
};

int idx, head[MAXV];

void addEdge(int u, int v) {
    g[idx] = EDGE(u, v, 0, head[u]);
    head[u] = idx++;
    g[idx] = EDGE(v, u, 0, head[v]);
    head[v] = idx++;
}

int dfn[MAXV], ic[MAXV], dfstime = 0;

stack<edge> stk;

int vbcc = 0;
set<int> vbc[MAXV];

int dfs(int u, int father) {
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        if (g[i].used) continue;
        g[i].used = g[i ^ 1].used = 1;
        edge eu = edge{g[i].u, g[i].v};
        stk.push(eu);
        int v = g[i].v;
        if (!dfn[v]) {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) {
                ic[u] = 1;
                vbc[vbcc].clear();
                while (stk.size()) {
                    edge ev = stk.top();
                    stk.pop();
                    vbc[vbcc].insert(ev.u);
                    vbc[vbcc].insert(ev.v);
                    if (ev == eu) break;
                }
                vbcc++;
            }
        } else lowu = min(lowu, dfn[v]);
    }
    if (father < 0) ic[u] = children > 1;
    return lowu;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    int n;
    while (cin >> n) {
        if (n == 0) break;
        idx = 0;
        memset(head, -1, sizeof head);
        int mx = 1;
        for (int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            mx = max(mx, max(u, v));
        }
        dfstime = 0;
        memset(ic, 0, sizeof ic);
        memset(dfn, 0, sizeof dfn);
        vbcc = 0;
        dfs(1, -1);
        cout << "Case " << cases++ << ": ";
        long long shafts = 0, ways = 1;
        for (int i = 0; i < vbcc; i++) {
            int cv = 0;
            for (auto u : vbc[i])
                if (ic[u])
                    cv++;
            if (cv == 1) shafts++, ways *= (vbc[i].size() - cv);
        }
        if (vbcc == 1) cout << 2 << ' ' << 1LL * mx * (mx - 1) / 2 << '\n';
        else cout << shafts << ' ' << ways << '\n';
    }
    return 0;
}
