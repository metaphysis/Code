#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> fa, sz;

    void init(int n) {
        fa.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; i++) fa[i] = i;
    }

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    void join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n >> q) {
        Dsu dsu;
        dsu.init(n * 2);
        for (int i = 0; i < q; i++) {
            int c, x, y;
            cin >> c >> x >> y;
            if (c == 1) {
                if (dsu.find(x) == dsu.find(y + n)) cout << -1 << '\n';
                else {
                    dsu.join(x, y);
                    dsu.join(x + n, y + n);
                }
            } else if (c == 2) {
                if (dsu.find(x) == dsu.find(y)) cout << -1 << '\n';
                else {
                    dsu.join(x, y + n);
                    dsu.join(x + n, y);
                }
            } else if (c == 3) {
                cout << (dsu.find(x) == dsu.find(y)) << '\n';
            } else {
                cout << (dsu.find(x) == dsu.find(y + n)) << '\n';
            }
        }
    }
    return 0;
}
