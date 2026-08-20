// Crime
// UVa ID: 1147
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> color(n + 1, -1);
        bool possible = true;
        int total = 0;
        for (int i = 1; i <= n && possible; ++i) {
            if (color[i] != -1) continue;
            queue<int> q;
            color[i] = 0;
            q.push(i);
            int cnt[2] = {1, 0};
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        cnt[color[v]]++;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
            }
            if (!possible) break;
            total += min(cnt[0], cnt[1]);
        }
        if (!possible) cout << "Impossible\n";
        else cout << total << "\n";
    }
    return 0;
}
