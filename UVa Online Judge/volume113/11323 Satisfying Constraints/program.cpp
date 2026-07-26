// Satisfying Constraints
// UVa ID: 11323
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
// https://blog.csdn.net/metaphysis/article/details/163173440

#include <bits/stdc++.h>
using namespace std;

struct Constraint {
    int a, i, b, j, c;
};

bool checkComponent(int root, int rootVal, int n, const vector<Constraint>& cons,
                    const vector<vector<int>>& adj, int k) {
    vector<int> assign(n, 0);
    queue<int> q;
    assign[root] = rootVal;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int id : adj[u]) {
            const Constraint& con = cons[id];
            int a = con.a, i = con.i, b = con.b, j = con.j, c = con.c;
            if (i == j) {
                int coeff = a + b;
                if (coeff == 0) {
                    if (c != 0) return false;
                    continue;
                }
                if (c % coeff != 0) return false;
                int val = c / coeff;
                if (val < 1 || val > k) return false;
                if (assign[i] == 0) { assign[i] = val; q.push(i); }
                else if (assign[i] != val) return false;
                continue;
            }
            if (a == 0 && b == 0) {
                if (c != 0) return false;
                continue;
            }
            if (a == 0 && b != 0) {
                if (c % b != 0) return false;
                int val = c / b;
                if (val < 1 || val > k) return false;
                if (assign[j] == 0) { assign[j] = val; q.push(j); }
                else if (assign[j] != val) return false;
                continue;
            }
            if (a != 0 && b == 0) {
                if (c % a != 0) return false;
                int val = c / a;
                if (val < 1 || val > k) return false;
                if (assign[i] == 0) { assign[i] = val; q.push(i); }
                else if (assign[i] != val) return false;
                continue;
            }
            // a != 0 and b != 0
            if (u == i) {
                long long lhs = 1LL * c - 1LL * a * assign[i];
                if (lhs % b != 0) return false;
                long long valLL = lhs / b;
                if (valLL < 1 || valLL > k) return false;
                int val = (int)valLL;
                if (assign[j] == 0) { assign[j] = val; q.push(j); }
                else if (assign[j] != val) return false;
            }
            if (u == j) {
                long long lhs = 1LL * c - 1LL * b * assign[j];
                if (lhs % a != 0) return false;
                long long valLL = lhs / a;
                if (valLL < 1 || valLL > k) return false;
                int val = (int)valLL;
                if (assign[i] == 0) { assign[i] = val; q.push(i); }
                else if (assign[i] != val) return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<Constraint> cons(m);
        vector<vector<int>> adj(n);
        bool impossible = false;
        for (int idx = 0; idx < m; ++idx) {
            int a, i, b, j, c;
            cin >> a >> i >> b >> j >> c;
            --i; --j;
            cons[idx] = {a, i, b, j, c};
            if (a == 0 && b == 0 && c != 0) impossible = true;
            adj[i].push_back(idx);
            if (i != j) adj[j].push_back(idx);
        }
        if (impossible) {
            cout << "no\n";
            continue;
        }
        vector<int> vis(n, 0);
        bool ok = true;
        for (int r = 0; r < n && ok; ++r) {
            if (vis[r]) continue;
            vector<int> comp;
            queue<int> qq;
            vis[r] = 1;
            qq.push(r);
            while (!qq.empty()) {
                int u = qq.front(); qq.pop();
                comp.push_back(u);
                for (int id : adj[u]) {
                    int v1 = cons[id].i, v2 = cons[id].j;
                    if (!vis[v1]) { vis[v1] = 1; qq.push(v1); }
                    if (!vis[v2]) { vis[v2] = 1; qq.push(v2); }
                }
            }
            int root = comp[0];
            bool compOk = false;
            for (int val = 1; val <= k; ++val) {
                if (checkComponent(root, val, n, cons, adj, k)) {
                    compOk = true;
                    break;
                }
            }
            if (!compOk) ok = false;
        }
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
