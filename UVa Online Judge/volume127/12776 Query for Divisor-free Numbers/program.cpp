#include <bits/stdc++.h>
using namespace std;

struct Bit {
    int n;
    vector<int> tr;
    Bit(int n = 0) : n(n), tr(n + 2, 0) {}
    void add(int x, int v) {
        for (; x <= n; x += x & -x) tr[x] += v;
    }
    int sum(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += tr[x];
        return res;
    }
    void rangeAdd(int l, int r, int v) {
        add(l, v);
        add(r + 1, -v);
    }
};

struct Query {
    int l, id;
};

vector<int> getDivs(int x, const vector<int> &spf) {
    vector<int> ds(1, 1);
    while (x > 1) {
        int p = spf[x], c = 0, sz = ds.size();
        while (x % p == 0) {
            x /= p;
            c++;
        }
        int mul = 1;
        for (int k = 1; k <= c; k++) {
            mul *= p;
            for (int j = 0; j < sz; j++) ds.push_back(ds[j] * mul);
        }
    }
    return ds;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, q, mx = 0;
        cin >> n >> q;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }
        vector<vector<Query>> qs(n + 1);
        vector<int> ans(q);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            qs[r].push_back({l, i});
        }
        vector<int> spf(mx + 1);
        for (int i = 2; i <= mx; i++) {
            if (spf[i] == 0) {
                for (int j = i; j <= mx; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
        vector<int> pre(n + 1), nxt(n + 1, n + 1), last(mx + 1);
        for (int i = 1; i <= n; i++) {
            vector<int> ds = getDivs(a[i], spf);
            for (int d : ds) pre[i] = max(pre[i], last[d]);
            last[a[i]] = i;
        }
        fill(last.begin(), last.end(), n + 1);
        for (int i = n; i >= 1; i--) {
            vector<int> ds = getDivs(a[i], spf);
            for (int d : ds) nxt[i] = min(nxt[i], last[d]);
            last[a[i]] = i;
        }
        vector<vector<int>> del(n + 1);
        for (int i = 1; i <= n; i++) {
            if (nxt[i] <= n) del[nxt[i]].push_back(i);
        }
        Bit bit(n + 1);
        for (int r = 1; r <= n; r++) {
            bit.rangeAdd(pre[r] + 1, r, 1);
            for (int i : del[r]) bit.rangeAdd(pre[i] + 1, i, -1);
            for (Query qu : qs[r]) ans[qu.id] = bit.sum(qu.l);
        }
        cout << "Case " << tc << ":\n";
        for (int x : ans) cout << x << '\n';
    }
    return 0;
}
