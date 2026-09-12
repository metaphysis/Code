#include <bits/stdc++.h>
using namespace std;

const int maxN = 50005;

int n, timer;
int val[maxN], fa[maxN], dep[maxN], siz[maxN], son[maxN];
int top[maxN], dfn[maxN], rev[maxN];
vector<int> edge[maxN];

int getGcd(int a, int b) {
    return __gcd(a, b);
}

void dfsSize(int u, int p) {
    fa[u] = p;
    dep[u] = dep[p] + 1;
    siz[u] = 1;
    son[u] = -1;
    for (int v : edge[u]) {
        if (v == p) continue;
        dfsSize(v, u);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfsTop(int u, int t) {
    top[u] = t;
    dfn[u] = ++timer;
    rev[timer] = u;
    if (son[u] != -1) dfsTop(son[u], t);
    for (int v : edge[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfsTop(v, v);
    }
}

struct SegTree {
    int tree[maxN * 4];
    void build(int p, int l, int r) {
        if (l == r) {
            tree[p] = val[rev[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);
        tree[p] = getGcd(tree[p * 2], tree[p * 2 + 1]);
    }
    void update(int p, int l, int r, int pos, int x) {
        if (l == r) {
            tree[p] = x;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(p * 2, l, mid, pos, x);
        else update(p * 2 + 1, mid + 1, r, pos, x);
        tree[p] = getGcd(tree[p * 2], tree[p * 2 + 1]);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) / 2, ans = 0;
        if (ql <= mid) ans = getGcd(ans, query(p * 2, l, mid, ql, qr));
        if (qr > mid) ans = getGcd(ans, query(p * 2 + 1, mid + 1, r, ql, qr));
        return ans;
    }
};

int queryPath(int u, int v, SegTree &seg) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans = getGcd(ans, seg.query(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    ans = getGcd(ans, seg.query(1, 1, n, dfn[u], dfn[v]));
    return ans;
}

int solve() {
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> val[i];
            edge[i].clear();
        }
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        timer = 0;
        dep[0] = 0;
        dfsSize(0, -1);
        dfsTop(0, 0);
        SegTree seg;
        seg.build(1, 1, n);
        int q;
        cin >> q;
        while (q--) {
            int type, u, v;
            cin >> type >> u >> v;
            if (type == 1) cout << queryPath(u, v, seg) << '\n';
            else {
                val[u] = v;
                seg.update(1, 1, n, dfn[u], v);
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
