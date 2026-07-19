// Don't Care
// UVa ID: 12784
// Verdict: Accepted
// Submission Date: 2026-07-
// UVa Run Time: s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<vector<int>> adj(n);
        vector<int> indeg(n, 0);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            ++indeg[b];
        }
        // Kahn 拓扑排序检测环
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (indeg[i] == 0) q.push(i);
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : adj[u])
                if (--indeg[v] == 0) q.push(v);
        }
        if ((int)topo.size() != n) {
            cout << 0 << '\n';
            continue;
        }
        // 计算可达性（bitset），按拓扑逆序
        vector<bitset<MAXN>> reach(n);
        for (int idx = n - 1; idx >= 0; --idx) {
            int u = topo[idx];
            reach[u].set(u);
            for (int v : adj[u])
                reach[u] |= reach[v];
        }
        bool ok = true;
        for (int a = 0; a < n && ok; ++a) {
            if (adj[a].empty()) continue;
            // 去重出边终点
            vector<int> ends = adj[a];
            sort(ends.begin(), ends.end());
            ends.erase(unique(ends.begin(), ends.end()), ends.end());
            int k = (int)ends.size();
            for (int i = 0; i < k && ok; ++i)
                for (int j = i + 1; j < k; ++j) {
                    if ((reach[ends[i]] & reach[ends[j]]).none()) {
                        ok = false;
                        break;
                    }
                }
        }
        cout << (ok ? 1 : 0) << '\n';
    }
    return 0;
}
