#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> fa, sz;
    Dsu(int n) : fa(n), sz(n, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    void join(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
};

int getVal(char c) {
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'T') return 2;
    return 3;
}

int getMask(int x) {
    return (1 << x) | (1 << ((x + 1) % 4)) | (1 << ((x + 3) % 4));
}

struct TwoSat {
    int n;
    vector<vector<int> > g, rg;
    vector<int> vis, ord, bel;
    TwoSat(int n) : n(n), g(2 * n), rg(2 * n), vis(2 * n), bel(2 * n, -1) {}
    void addEdge(int x, int y) {
        g[x].push_back(y);
        rg[y].push_back(x);
    }
    void addBan(int x, int y) {
        addEdge(x, y ^ 1);
        addEdge(y, x ^ 1);
    }
    void dfs1(int x) {
        vis[x] = 1;
        for (int y : g[x])
            if (!vis[y]) dfs1(y);
        ord.push_back(x);
    }
    void dfs2(int x, int id) {
        bel[x] = id;
        for (int y : rg[x])
            if (bel[y] == -1) dfs2(y, id);
    }
    bool solve() {
        int id = 0;
        for (int i = 0; i < 2 * n; i++)
            if (!vis[i]) dfs1(i);
        reverse(ord.begin(), ord.end());
        for (int x : ord)
            if (bel[x] == -1) dfs2(x, id++);
        for (int i = 0; i < n; i++)
            if (bel[2 * i] == bel[2 * i + 1]) return false;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    while (cin >> n >> t && (n || t)) {
        string s;
        cin >> s;
        Dsu dsu(n);
        for (int i = 0; i < t; i++) {
            int l;
            char ch;
            cin >> l >> ch;
            vector<int> p(l);
            for (int j = 0; j < l; j++) cin >> p[j];
            for (int j = 0; j < l / 2; j++) dsu.join(p[j], p[l - 1 - j]);
        }
        vector<int> mask(n, 15), first(n, -1), root(n);
        for (int i = 0; i < n; i++) {
            root[i] = dsu.find(i);
            mask[root[i]] &= getMask(getVal(s[i]));
            if (first[root[i]] == -1) first[root[i]] = getVal(s[i]);
        }
        bool ok = true;
        vector<vector<int> > val(n);
        vector<int> id(n, -1);
        for (int i = 0; i < n; i++) {
            if (root[i] != i) continue;
            if (!mask[i]) ok = false;
            for (int j = 0; j < 4; j++)
                if (mask[i] & (1 << j)) val[i].push_back(j);
            if (val[i].size() == 3) {
                val[i].clear();
                val[i].push_back(first[i]);
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (root[i] == i && val[i].size() == 2) id[i] = cnt++;
        TwoSat sat(cnt);
        for (int i = 0; i + 1 < n; i++) {
            int x = root[i], y = root[i + 1];
            for (int a = 0; a < (int)val[x].size(); a++) {
                for (int b = 0; b < (int)val[y].size(); b++) {
                    bool cx = val[x][a] != getVal(s[i]);
                    bool cy = val[y][b] != getVal(s[i + 1]);
                    if (!cx || !cy) continue;
                    if (id[x] == -1 && id[y] == -1) ok = false;
                    else if (id[x] == -1) sat.addBan(2 * id[y] + b, 2 * id[y] + b);
                    else if (id[y] == -1) sat.addBan(2 * id[x] + a, 2 * id[x] + a);
                    else sat.addBan(2 * id[x] + a, 2 * id[y] + b);
                }
            }
        }
        if (ok && sat.solve()) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
