#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> par, siz;
    Dsu(int n) {
        par.resize(n);
        siz.assign(n, 1);
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (siz[x] < siz[y]) swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
    }
};

bool canStart(int ban, int sta, int c, const vector<int>& a, const vector<int>& b) {
    int n = a.size(), root = -1, odd = 0;
    vector<int> deg(c, 0);
    Dsu dsu(c);
    for (int i = 0; i < n; i++) {
        if (i == ban) continue;
        deg[a[i]]++;
        deg[b[i]]++;
        dsu.unite(a[i], b[i]);
    }
    if (n == 1) return true;
    if (deg[sta] == 0) return false;
    for (int i = 0; i < c; i++) {
        if (deg[i] == 0) continue;
        if (root == -1) root = dsu.find(i);
        else if (root != dsu.find(i)) return false;
        if (deg[i] % 2 == 1) odd++;
    }
    if (odd == 0) return true;
    if (odd == 2 && deg[sta] % 2 == 1) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    while (cin >> n >> c) {
        if (n == 0 && c == 0) break;
        vector<vector<int>> col(n);
        for (int i = 0; i < c; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                col[x].push_back(i);
            }
        }
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = col[i][0];
            b[i] = col[i].size() == 2 ? col[i][1] : a[i];
        }
        int ans = -1;
        for (int i = 0; i < n; i++) {
            if (canStart(i, b[i], c, a, b)) {
                ans = i;
                break;
            }
            if (a[i] != b[i] && canStart(i, a[i], c, a, b)) {
                ans = i;
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
