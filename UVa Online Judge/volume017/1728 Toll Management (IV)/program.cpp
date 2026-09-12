#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id, w;
};

struct SegTree {
    int n;
    vector<int> mx, tag;
    void init(int n_) {
        n = n_;
        mx.assign(n * 4 + 5, 0);
        tag.assign(n * 4 + 5, INT_MAX);
    }
    void build(int p, int l, int r, vector<int> &a) {
        if (l == r) {
            mx[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return mx[p];
        int m = (l + r) >> 1, res = 0;
        if (ql <= m) res = max(res, query(p << 1, l, m, ql, qr));
        if (qr > m) res = max(res, query(p << 1 | 1, m + 1, r, ql, qr));
        return res;
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tag[p] = min(tag[p], v);
            return;
        }
        int m = (l + r) >> 1;
        if (ql <= m) update(p << 1, l, m, ql, qr, v);
        if (qr > m) update(p << 1 | 1, m + 1, r, ql, qr, v);
    }
    int get(int p, int l, int r, int x, int v) {
        v = min(v, tag[p]);
        if (l == r) return v;
        int m = (l + r) >> 1;
        if (x <= m) return get(p << 1, l, m, x, v);
        return get(p << 1 | 1, m + 1, r, x, v);
    }
};

int n, m, tim;
vector<vector<Edge>> g;
vector<int> fa, dep, sz, son, top, pos, val, edgePos;

void dfs1(int u, int p) {
    int i, v;
    sz[u] = 1;
    fa[u] = p;
    son[u] = 0;
    for (i = 0; i < (int)g[u].size(); i++) {
        v = g[u][i].to;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        val[v] = g[u][i].w;
        edgePos[g[u][i].id] = v;
        dfs1(v, u);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int h) {
    int i, v;
    top[u] = h;
    pos[u] = ++tim;
    if (son[u]) dfs2(son[u], h);
    for (i = 0; i < (int)g[u].size(); i++) {
        v = g[u][i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int pathMax(int u, int v, SegTree &st) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = max(res, st.query(1, 1, n, pos[top[u]], pos[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (pos[u] + 1 <= pos[v]) res = max(res, st.query(1, 1, n, pos[u] + 1, pos[v]));
    return res;
}

void pathUpdate(int u, int v, int w, SegTree &st) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        st.update(1, 1, n, pos[top[u]], pos[u], w);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (pos[u] + 1 <= pos[v]) st.update(1, 1, n, pos[u] + 1, pos[v], w);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, cs, i, u, v, w;
    cin >> t;
    for (cs = 1; cs <= t; cs++) {
        cin >> n >> m;
        vector<int> eu(m + 1), ev(m + 1), ew(m + 1), base(n + 1, 0), mn(m + 1, INT_MAX), b(m + 1, 0);
        g.assign(n + 1, vector<Edge>());
        fa.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        son.assign(n + 1, 0);
        top.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        val.assign(n + 1, 0);
        edgePos.assign(m + 1, 0);
        for (i = 1; i <= m; i++) {
            cin >> u >> v >> w;
            eu[i] = u;
            ev[i] = v;
            ew[i] = w;
            if (i < n) {
                g[u].push_back({v, i, w});
                g[v].push_back({u, i, w});
            }
        }
        tim = 0;
        dfs1(1, 0);
        dfs2(1, 1);
        for (i = 2; i <= n; i++) base[pos[i]] = val[i];
        SegTree st;
        st.init(n);
        st.build(1, 1, n, base);
        for (i = n; i <= m; i++) {
            b[i] = ew[i] - pathMax(eu[i], ev[i], st);
            pathUpdate(eu[i], ev[i], ew[i], st);
        }
        for (i = 1; i < n; i++) mn[i] = st.get(1, 1, n, pos[edgePos[i]], INT_MAX);
        long long ans = 0, a;
        for (i = 1; i <= m; i++) {
            if (i < n) {
                a = mn[i] == INT_MAX ? -1 : mn[i] - ew[i];
                b[i] = -1;
            } else a = -1;
            ans += 1LL * i * a + 1LL * i * i * b[i];
        }
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
