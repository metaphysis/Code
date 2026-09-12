#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum;
    int mn, se, cnt;
};

struct SegTree {
    vector<Node> tr;
    int inf;
    SegTree(int n) {
        inf = 1e9;
        tr.resize(n * 4 + 5);
        build(1, 1, n);
    }
    void build(int p, int l, int r) {
        tr[p].sum = 0;
        tr[p].mn = 0;
        tr[p].se = inf;
        tr[p].cnt = r - l + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void apply(int p, int v) {
        tr[p].sum += 1LL * (v - tr[p].mn) * tr[p].cnt;
        tr[p].mn = v;
    }
    void push(int p) {
        if (tr[p << 1].mn < tr[p].mn) apply(p << 1, tr[p].mn);
        if (tr[p << 1 | 1].mn < tr[p].mn) apply(p << 1 | 1, tr[p].mn);
    }
    void pull(int p) {
        Node &a = tr[p << 1], &b = tr[p << 1 | 1];
        tr[p].sum = a.sum + b.sum;
        tr[p].mn = min(a.mn, b.mn);
        tr[p].cnt = 0;
        if (a.mn == tr[p].mn) tr[p].cnt += a.cnt;
        if (b.mn == tr[p].mn) tr[p].cnt += b.cnt;
        tr[p].se = min(a.mn == tr[p].mn ? a.se : a.mn, b.mn == tr[p].mn ? b.se : b.mn);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (qr < l || r < ql || v <= tr[p].mn) return;
        if (ql <= l && r <= qr && v < tr[p].se) {
            apply(p, v);
            return;
        }
        int mid = (l + r) >> 1;
        push(p);
        update(p << 1, l, mid, ql, qr, v);
        update(p << 1 | 1, mid + 1, r, ql, qr, v);
        pull(p);
    }
    void update(int n, int r, int v) {
        update(1, 1, n, 1, r, v);
    }
    long long getSum() {
        return tr[1].sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<vector<pair<int, int> > > pts(m + 1);
        for (int i = 0; i < n; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            pts[b].push_back({a, c});
        }
        SegTree st(m);
        long long ans = 0;
        for (int y = m; y >= 1; y--) {
            for (pair<int, int> p : pts[y]) st.update(m, p.second, p.first);
            ans += 1LL * m * m - st.getSum();
        }
        cout << ans << '\n';
    }
    return 0;
}
