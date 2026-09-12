#include <bits/stdc++.h>
using namespace std;

struct Tri
{
    int typ, x, y, z;
};

int n;
vector<vector<int>> g, rg;
vector<pair<int, int>> base;
vector<Tri> tri;
vector<int> ord, com, vis;

int neg(int x) {
    return x ^ 1;
}

int lit(int x, bool val) {
    return 2 * (x - 1) + (val ? 0 : 1);
}

void addClause(int a, int b) {
    g[neg(a)].push_back(b);
    g[neg(b)].push_back(a);
    rg[b].push_back(neg(a));
    rg[a].push_back(neg(b));
}

void dfsOne(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (!vis[v]) dfsOne(v);
    }
    ord.push_back(u);
}

void dfsTwo(int u, int id) {
    com[u] = id;
    for (int v : rg[u]) {
        if (com[v] == -1) dfsTwo(v, id);
    }
}

bool solveTwo(const vector<int>& units, vector<int>& ans) {
    int cnt = 2 * n, id = 0;
    g.assign(cnt, vector<int>());
    rg.assign(cnt, vector<int>());
    for (auto p : base) addClause(p.first, p.second);
    for (int x : units) addClause(x, x);
    vis.assign(cnt, 0);
    ord.clear();
    for (int i = 0; i < cnt; i++) {
        if (!vis[i]) dfsOne(i);
    }
    com.assign(cnt, -1);
    for (int i = cnt - 1; i >= 0; i--) {
        int u = ord[i];
        if (com[u] == -1) dfsTwo(u, id++);
    }
    for (int i = 0; i < n; i++) {
        if (com[2 * i] == com[2 * i + 1]) return false;
    }
    ans.clear();
    for (int i = 0; i < n; i++) {
        if (com[2 * i] > com[2 * i + 1]) ans.push_back(i + 1);
    }
    return true;
}

bool searchCase(int pos, vector<int>& units, vector<int>& ans) {
    if (pos == (int)tri.size()) return solveTwo(units, ans);
    Tri t = tri[pos];
    int a = lit(t.x, t.typ == 1), b = lit(t.y, t.typ == 1), c = lit(t.z, t.typ == 1);
    units.push_back(a);
    if (searchCase(pos + 1, units, ans)) return true;
    units.pop_back();
    units.push_back(b);
    if (searchCase(pos + 1, units, ans)) return true;
    units.pop_back();
    units.push_back(c);
    if (searchCase(pos + 1, units, ans)) return true;
    units.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int m, k;
        cin >> n >> m >> k;
        base.clear();
        tri.clear();
        for (int i = 0; i < m; i++) {
            int typ, x, y;
            cin >> typ >> x >> y;
            if (typ == 1) base.push_back({lit(x, true), lit(y, true)});
            else if (typ == 2) base.push_back({lit(x, true), lit(y, false)});
            else if (typ == 3) base.push_back({lit(x, false), lit(y, false)});
            else {
                base.push_back({lit(x, true), lit(y, true)});
                base.push_back({lit(x, false), lit(y, false)});
            }
        }
        for (int i = 0; i < k; i++) {
            int typ, x, y, z;
            cin >> typ >> x >> y >> z;
            tri.push_back({typ, x, y, z});
        }
        vector<int> units, ans;
        bool ok = searchCase(0, units, ans);
        cout << "Case " << cs << ": ";
        if (!ok) {
            cout << "Impossible.\n";
            continue;
        }
        cout << "Possible " << ans.size();
        for (int id : ans) cout << " " << id;
        cout << ".\n";
    }
    return 0;
}
