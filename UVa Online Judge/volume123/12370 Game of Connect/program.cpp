#include <bits/stdc++.h>
using namespace std;

bool buildPath(int s, int t, const vector<vector<pair<int, int>>>& adj, vector<int>& path) {
    int n = adj.size();
    vector<int> parV(n, -1), parE(n, -1), st;
    parV[s] = s;
    st.push_back(s);
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (x == t) break;
        for (auto it : adj[x]) {
            int y = it.first, e = it.second;
            if (parV[y] != -1) continue;
            parV[y] = x;
            parE[y] = e;
            st.push_back(y);
        }
    }
    if (parV[t] == -1) return false;
    path.clear();
    for (int x = t; x != s; x = parV[x]) path.push_back(parE[x]);
    return true;
}

bool augment(int n, int m, const vector<int>& u, const vector<int>& v, vector<int>& take) {
    vector<vector<pair<int, int>>> adj[2];
    vector<int> pre(2 * m, -2), que, path;
    int head = 0;
    adj[0].resize(n);
    adj[1].resize(n);
    for (int i = 0; i < m; i++) {
        for (int c = 0; c < 2; c++) {
            int id = i * 2 + c;
            if (take[id]) {
                adj[c][u[i]].push_back({v[i], id});
                adj[c][v[i]].push_back({u[i], id});
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (!take[i * 2] && !take[i * 2 + 1]) {
            pre[i * 2] = -1;
            pre[i * 2 + 1] = -1;
            que.push_back(i * 2);
            que.push_back(i * 2 + 1);
        }
    }
    while (head < (int)que.size()) {
        int x = que[head++];
        if (take[x]) {
            int y = x ^ 1;
            if (pre[y] == -2) {
                pre[y] = x;
                que.push_back(y);
            }
        } else {
            int id = x / 2, c = x % 2;
            if (!buildPath(u[id], v[id], adj[c], path)) {
                for (int y = x; y != -1; y = pre[y]) take[y] ^= 1;
                return true;
            }
            for (int y : path) {
                if (pre[y] == -2) {
                    pre[y] = x;
                    que.push_back(y);
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, m;
        cin >> n >> m;
        vector<int> u(m), v(m), take(2 * m, 0);
        for (int i = 0; i < m; i++) cin >> u[i] >> v[i];
        int cnt = 0, need = 2 * (n - 1);
        while (cnt < need && augment(n, m, u, v, take)) cnt++;
        cout << "Case " << cs << ": " << (cnt == need ? "YES" : "NO") << '\n';
    }
    return 0;
}
