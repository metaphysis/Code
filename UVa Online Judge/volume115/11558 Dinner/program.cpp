#include <bits/stdc++.h>
using namespace std;

bool can(int y, const vector<vector<int>>& a, int n) {
    vector<pair<int, int>> ds;
    vector<int> deg(n), ks, is, km, im;
    int m = 0, u = -1, lo = (n + 2) / 3, hi = 2 * n / 3, sz;
    long long l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (a[i][j] < y) deg[i]++;
        ds.push_back({deg[i], i});
    }
    sort(ds.rbegin(), ds.rend());
    for (int i = 0; i < n; i++)
        if (ds[i].first >= i) m = i + 1;
    for (int i = 0; i < m; i++) l += ds[i].first;
    for (int i = m; i < n; i++) r += ds[i].first;
    if (l != 1LL * m * (m - 1) + r) return false;
    for (int i = 0; i < n; i++) {
        if (i < m) ks.push_back(ds[i].second);
        else is.push_back(ds[i].second);
    }
    for (int i = 0; i < (int)ks.size(); i++) {
        for (int j = i + 1; j < (int)ks.size(); j++)
            if (a[ks[i]][ks[j]] >= y) return false;
    }
    for (int i = 0; i < (int)is.size(); i++) {
        for (int j = i + 1; j < (int)is.size(); j++)
            if (a[is[i]][is[j]] < y) return false;
    }
    for (int v : is) {
        bool ok = true;
        for (int w : ks)
            if (a[v][w] >= y) ok = false;
        if (ok) {
            u = v;
            break;
        }
    }
    km = ks;
    if (u != -1) km.push_back(u);
    for (int v : is)
        if (v != u) im.push_back(v);
    sz = km.size();
    if (sz >= lo && sz <= hi) return true;
    if (sz - 1 < lo || sz - 1 > hi) return false;
    for (int v : km) {
        bool ok = true;
        for (int w : im)
            if (a[v][w] < y) ok = false;
        if (ok) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    while (cin >> n >> c) {
        vector<vector<int>> a(n, vector<int>(n, 2008));
        int x, z, y;
        for (int i = 0; i < c; i++) {
            cin >> x >> z >> y;
            x--;
            z--;
            a[x][z] = a[z][x] = y;
        }
        int ans = -1;
        for (int y = 1948; y <= 2008; y++) {
            if (can(y, a, n)) {
                ans = y;
                break;
            }
        }
        if (ans == -1) cout << "Impossible\n";
        else cout << ans << '\n';
    }
    return 0;
}
