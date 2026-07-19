// Holiday's Accommodatio
// UVa ID: 1669
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.250s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solveCase(int caseNo) {
    int N;
    cin >> N;
    vector<vector<pair<int, ll>>> adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int X, Y;
        ll Z;
        cin >> X >> Y >> Z;
        adj[X].push_back({Y, Z});
        adj[Y].push_back({X, Z});
    }
    vector<int> parent(N + 1, 0);
    vector<ll> parentW(N + 1, 0);
    vector<int> order;
    order.reserve(N);
    // 迭代栈 DFS，避免递归栈溢出
    stack<int> st;
    st.push(1);
    parent[1] = -1; // 根标记
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (auto &e : adj[u]) {
            int v = e.first;
            ll w = e.second;
            if (v == parent[u]) continue;
            parent[v] = u;
            parentW[v] = w;
            st.push(v);
        }
    }
    vector<ll> sz(N + 1, 1); // 初始大小为 1（自身）
    ll ans = 0;
    // 逆序处理，先子后父
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        if (parent[u] == -1) continue; // 根节点跳过
        ll s = sz[u];
        ll other = N - s;
        ans += parentW[u] * 2 * min(s, other);
        sz[parent[u]] += sz[u]; // 累加到父节点
    }
    cout << "Case #" << caseNo << ": " << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        solveCase(t);
    }
    return 0;
}
