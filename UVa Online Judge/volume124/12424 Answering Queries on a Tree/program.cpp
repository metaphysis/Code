// Answering Queries on a Tree
// UVa ID: 12424
// Verdict: Accepted
// Submission Date: 2025-12-06
// UVa Run Time: 1.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXC = 11; // 颜色最多10种，索引1~10

int n, m;
int color[MAXN]; // 当前节点颜色
vector<int> g[MAXN]; // 邻接表

// 树链剖分相关数组
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN];
int top[MAXN], dfn[MAXN], rnk[MAXN], timer;

// 线段树（对每个颜色建一棵）
struct SegTree {
    int sum[MAXN << 2];
    void build(int c, int l, int r) {
        sum[c] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(c << 1, l, mid);
        build(c << 1 | 1, mid + 1, r);
    }
    void update(int c, int l, int r, int pos, int val) {
        if (l == r) { sum[c] = val; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(c << 1, l, mid, pos, val);
        else update(c << 1 | 1, mid + 1, r, pos, val);
        sum[c] = sum[c << 1] + sum[c << 1 | 1];
    }
    int query(int c, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[c];
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid) res += query(c << 1, l, mid, ql, qr);
        if (qr > mid) res += query(c << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
} segTree[MAXC]; // 每种颜色一个线段树

// 树链剖分第一遍DFS
void dfs1(int u, int f) {
    fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1; son[u] = 0;
    for (int v : g[u]) if (v != f) {
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

// 树链剖分第二遍DFS
void dfs2(int u, int tp) {
    top[u] = tp; dfn[u] = ++timer; rnk[timer] = u;
    if (son[u]) dfs2(son[u], tp);
    for (int v : g[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
}

// 路径查询（对某种颜色）
int queryPath(int c, int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += segTree[c].query(1, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res += segTree[c].query(1, 1, n, dfn[u], dfn[v]);
    return res;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
        for (int i = 1; i < n; i++) {
            int a, b; scanf("%d %d", &a, &b);
            g[a].push_back(b); g[b].push_back(a);
        }

        timer = 0;
        dfs1(1, 0); dfs2(1, 1);

        // 初始化每种颜色的线段树
        for (int c = 1; c <= 10; c++) segTree[c].build(1, 1, n);
        for (int i = 1; i <= n; i++) segTree[color[i]].update(1, 1, n, dfn[i], 1);

        while (m--) {
            int op, u, v; scanf("%d %d %d", &op, &u, &v);
            if (op == 0) { // 更新操作
                int oldC = color[u]; color[u] = v;
                segTree[oldC].update(1, 1, n, dfn[u], 0);
                segTree[v].update(1, 1, n, dfn[u], 1);
            } else { // 查询操作
                int ans = 0;
                for (int c = 1; c <= 10; c++) {
                    int cnt = queryPath(c, u, v);
                    if (cnt > ans) ans = cnt;
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
