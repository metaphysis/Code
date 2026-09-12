#include <bits/stdc++.h>
using namespace std;

int n, m, k, cnt;
vector<vector<int>> bad;
vector<int> ans, cur;

bool dfs(int pos, const vector<int>& mat, const vector<int>& used) {
    if (pos == n) {
        cnt++;
        if (cnt == k) ans = cur;
        return cnt >= k;
    }
    int sz = 2 * n;
    vector<vector<int>> g(sz), rg(sz);
    for (int i = pos; i < n; i++) {
        for (int x = 0; x < n; x++) {
            if (used[x] || bad[i][x]) continue;
            int u, v;
            if (mat[i] == x) u = n + x, v = i;
            else u = i, v = n + x;
            g[u].push_back(v);
            rg[v].push_back(u);
        }
    }
    vector<int> vis(sz), ord, comp(sz, -1);
    function<void(int)> dfs1 = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        ord.push_back(u);
    };
    function<void(int, int)> dfs2 = [&](int u, int id) {
        comp[u] = id;
        for (int v : rg[u]) if (comp[v] == -1) dfs2(v, id);
    };
    for (int i = 0; i < sz; i++) if (!vis[i]) dfs1(i);
    int id = 0;
    for (int i = sz - 1; i >= 0; i--) {
        int u = ord[i];
        if (comp[u] == -1) dfs2(u, id++);
    }
    for (int x = 0; x < n; x++) {
        if (used[x] || bad[pos][x]) continue;
        if (x != mat[pos] && comp[pos] != comp[n + x]) continue;
        vector<int> nxt = mat, nused = used;
        if (x != mat[pos]) {
            vector<int> pre(sz, -1);
            queue<int> que;
            que.push(n + x);
            pre[n + x] = n + x;
            while (!que.empty() && pre[pos] == -1) {
                int u = que.front();
                que.pop();
                for (int v : g[u]) {
                    if (pre[v] != -1) continue;
                    pre[v] = u;
                    que.push(v);
                }
            }
            vector<int> path;
            for (int u = pos; ; u = pre[u]) {
                path.push_back(u);
                if (u == n + x) break;
            }
            reverse(path.begin(), path.end());
            for (int i = 1; i + 1 < (int)path.size(); i += 2) nxt[path[i]] = path[i + 1] - n;
            nxt[pos] = x;
        }
        cur[pos] = x;
        nused[x] = 1;
        if (dfs(pos + 1, nxt, nused)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> m >> k;
        bad.assign(n, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0, x; j < n; j++) {
                cin >> x;
                bad[j][x - 1] = 1;
            }
        }
        vector<int> mat(n, -1), col(n, -1), seen(n);
        function<bool(int)> findMatch = [&](int u) {
            for (int x = 0; x < n; x++) {
                if (bad[u][x] || seen[x]) continue;
                seen[x] = 1;
                if (col[x] == -1 || findMatch(col[x])) {
                    col[x] = u;
                    return true;
                }
            }
            return false;
        };
        bool ok = true;
        for (int i = 0; i < n; i++) {
            fill(seen.begin(), seen.end(), 0);
            if (!findMatch(i)) ok = false;
        }
        for (int x = 0; x < n; x++) if (col[x] != -1) mat[col[x]] = x;
        cnt = 0;
        ans.assign(n, -1);
        cur.assign(n, -1);
        if (ok) dfs(0, mat, vector<int>(n));
        cout << "Case #" << tc << ":";
        if (cnt < k) cout << " -1";
        else {
            for (int x : ans) cout << ' ' << x + 1;
        }
        cout << '\n';
    }
    return 0;
}
