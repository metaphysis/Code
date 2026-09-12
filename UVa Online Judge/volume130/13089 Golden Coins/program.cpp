#include <bits/stdc++.h>
using namespace std;

void dfs(int cur, int par, int dep, int &val, const vector<int> &coin, const vector<vector<int>> &graph) {
    if (coin[cur] & 1) val ^= dep;
    for (int nxt : graph[cur]) {
        if (nxt == par) continue;
        dfs(nxt, cur, dep + 1, val, coin, graph);
    }
}

int getXor(int root, const vector<int> &coin, const vector<vector<int>> &graph) {
    int val = 0;
    dfs(root, 0, 0, val, coin, graph);
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, caseNo = 1;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> coin(n + 1);
        vector<vector<int>> graph(n + 1);
        int i, u, v, ans = 0, root, val;
        for (i = 1; i <= n; i++) cin >> coin[i];
        for (i = 1; i < n; i++) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        for (root = 1; root <= n; root++) {
            val = getXor(root, coin, graph);
            if (val == 0) ans++;
        }
        cout << "Case " << caseNo++ << ": " << ans << '\n';
    }
    return 0;
}
