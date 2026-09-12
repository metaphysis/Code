#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> buildGraph(int dig, int deg) {
    vector<pair<int, int>> seg[10] = {
        {{0, 1}, {1, 3}, {3, 5}, {5, 4}, {4, 2}, {2, 0}},
        {{1, 3}, {3, 5}},
        {{0, 1}, {1, 3}, {2, 3}, {4, 2}, {5, 4}},
        {{0, 1}, {1, 3}, {3, 5}, {5, 4}, {2, 3}},
        {{1, 3}, {3, 5}, {2, 0}, {2, 3}},
        {{0, 1}, {2, 0}, {2, 3}, {3, 5}, {5, 4}},
        {{0, 1}, {2, 0}, {2, 3}, {3, 5}, {5, 4}, {4, 2}},
        {{0, 1}, {1, 3}, {3, 5}},
        {{0, 1}, {1, 3}, {3, 5}, {5, 4}, {4, 2}, {2, 0}, {2, 3}},
        {{0, 1}, {1, 3}, {3, 5}, {5, 4}, {2, 0}, {2, 3}}
    };
    vector<int> id(6, -1);
    int cnt = 0;
    for (auto e : seg[dig]) {
        if (id[e.first] == -1) id[e.first] = cnt++;
        if (id[e.second] == -1) id[e.second] = cnt++;
    }
    vector<vector<int>> g(cnt);
    for (auto e : seg[dig]) {
        int pre = id[e.first], now;
        for (int j = 1; j <= deg + 1; j++) {
            if (j == deg + 1) now = id[e.second];
            else {
                now = (int)g.size();
                g.push_back(vector<int>());
            }
            g[pre].push_back(now);
            g[now].push_back(pre);
            pre = now;
        }
    }
    return g;
}

bool isConnected(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> vis(n);
    queue<int> que;
    que.push(0);
    vis[0] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = 1;
            que.push(v);
        }
    }
    for (int i = 0; i < n; i++) if (!vis[i]) return false;
    return true;
}

vector<array<int, 3>> getRoads(const vector<vector<int>>& g, const vector<int>& core) {
    int n = g.size();
    vector<int> isCore(n);
    vector<array<int, 3>> res;
    for (int u : core) isCore[u] = 1;
    for (int u : core) for (int v : g[u]) {
        int pre = u, now = v, len = 1;
        while (!isCore[now]) {
            int nxt = g[now][0] == pre ? g[now][1] : g[now][0];
            pre = now;
            now = nxt;
            len++;
        }
        int a = min(u, now), b = max(u, now);
        res.push_back({a, b, len});
    }
    sort(res.begin(), res.end());
    return res;
}

bool isSame(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    if (n != (int)b.size()) return false;
    if (!isConnected(a) || !isConnected(b)) return false;
    vector<int> da, db, ca, cb;
    for (int i = 0; i < n; i++) {
        da.push_back(a[i].size());
        db.push_back(b[i].size());
        if (a[i].size() != 2) ca.push_back(i);
        if (b[i].size() != 2) cb.push_back(i);
    }
    sort(da.begin(), da.end());
    sort(db.begin(), db.end());
    if (da != db || ca.size() != cb.size()) return false;
    if (ca.empty()) return true;
    vector<array<int, 3>> ra = getRoads(a, ca), rb = getRoads(b, cb);
    vector<int> p(ca.size());
    iota(p.begin(), p.end(), 0);
    do {
        bool ok = true;
        for (int i = 0; i < (int)ca.size(); i++) if (a[ca[i]].size() != b[cb[p[i]]].size()) ok = false;
        if (!ok) continue;
        vector<int> to(n, -1);
        for (int i = 0; i < (int)ca.size(); i++) to[ca[i]] = cb[p[i]];
        vector<array<int, 3>> cur;
        for (auto e : ra) {
            int x = min(to[e[0]], to[e[1]]), y = max(to[e[0]], to[e[1]]);
            cur.push_back({x, y, e[2]});
        }
        sort(cur.begin(), cur.end());
        if (cur == rb) return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    int segCnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    for (int tc = 1; tc <= t; tc++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<pair<int, int>> ans;
        for (int dig = 0; dig <= 9; dig++) {
            if (m % segCnt[dig] != 0) continue;
            int deg = m / segCnt[dig] - 1;
            if (deg < 0) continue;
            vector<vector<int>> ref = buildGraph(dig, deg);
            if ((int)ref.size() != n) continue;
            if (isSame(g, ref)) ans.push_back({dig, deg});
        }
        if (tc > 1) cout << '\n';
        cout << "Case " << tc << ": " << ans.size() << '\n';
        for (auto x : ans) cout << x.first << ' ' << x.second << '\n';
    }
    return 0;
}
