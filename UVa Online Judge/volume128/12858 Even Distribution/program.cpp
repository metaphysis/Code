// Even Distribution
// UVa ID: 12858
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.570s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int I, S;
    while (cin >> I >> S) {
        vector<int> C(I + 1);
        for (int i = 1; i <= I; ++i) cin >> C[i];
        vector<vector<int>> adj(I + 1);
        for (int i = 0; i < S; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        // 每个顶点的set存储所有可能的GCD值
        vector<set<int>> values(I + 1);
        vector<bool> inQueue(I + 1, false);
        queue<int> q;
        for (int i = 1; i <= I; ++i) {
            values[i].insert(C[i]);
            q.push(i);
            inQueue[i] = true;
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
              for (int v : adj[u]) {
                bool updated = false;
                for (int g : values[u]) {
                    int ng = __gcd(g, C[v]);
                    if (values[v].find(ng) == values[v].end()) {
                        values[v].insert(ng);
                        updated = true;
                    }
                }
                if (updated && !inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
        set<int> allValues;
        for (int i = 1; i <= I; ++i)
            for (int g : values[i])
                allValues.insert(g);
        cout << allValues.size() << '\n';
    }
    return 0;
}
