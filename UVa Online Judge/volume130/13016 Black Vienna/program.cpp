#include <bits/stdc++.h>
using namespace std;

struct Query {
    int u, v, p, r;
};

bool spread(int st, vector<vector<pair<int, int>>> &adj, int val[]) {
    queue<int> que;
    que.push(st);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto e : adj[u]) {
            int v = e.first, c = e.second, nv = c - val[u];
            if (nv < 0 || nv > 1) return false;
            if (val[v] == -1) {
                val[v] = nv;
                que.push(v);
            } else if (val[v] != nv) {
                return false;
            }
        }
    }
    return true;
}

bool checkGraph(vector<vector<pair<int, int>>> &adj, bool ban[]) {
    int val[26];
    fill(val, val + 26, -1);
    for (int i = 0; i < 26; i++)
        if (ban[i]) val[i] = 0;
    for (int i = 0; i < 26; i++)
        if (ban[i] && !spread(i, adj, val)) return false;
    for (int i = 0; i < 26; i++) {
        if (val[i] != -1) continue;
        int oldVal[26];
        copy(val, val + 26, oldVal);
        val[i] = 0;
        if (!spread(i, adj, val)) {
            copy(oldVal, oldVal + 26, val);
            val[i] = 1;
            if (!spread(i, adj, val)) return false;
        }
    }
    return true;
}

bool checkCandidate(vector<Query> &qs, int a, int b, int c) {
    bool ban[26] = {};
    ban[a] = true;
    ban[b] = true;
    ban[c] = true;
    vector<vector<pair<int, int>>> adj(26);
    for (auto q : qs) {
        int cnt = 2 - (ban[q.u] ? 1 : 0) - (ban[q.v] ? 1 : 0);
        int sum = q.p == 1 ? q.r : cnt - q.r;
        if (sum < 0 || sum > 2) return false;
        adj[q.u].push_back({q.v, sum});
        adj[q.v].push_back({q.u, sum});
    }
    return checkGraph(adj, ban);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Query> qs;
        for (int i = 0; i < n; i++) {
            string s;
            int p, r;
            cin >> s >> p >> r;
            qs.push_back({s[0] - 'A', s[1] - 'A', p, r});
        }
        int ans = 0;
        for (int i = 0; i < 26; i++)
            for (int j = i + 1; j < 26; j++)
                for (int k = j + 1; k < 26; k++)
                    if (checkCandidate(qs, i, j, k)) ans++;
        cout << ans << '\n';
    }
    return 0;
}
