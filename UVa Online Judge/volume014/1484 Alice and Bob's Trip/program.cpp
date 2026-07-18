// Alice and Bob's Trip
// UVa ID: 1484
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.370s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, L, R;
    while (scanf("%d%d%d", &n, &L, &R) == 3) {
        vector<vector<pair<int,int>>> child(n);
        for (int i = 0; i < n - 1; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            child[a].push_back({b, c});
        }
        vector<int> depth(n, 0), prefix(n, 0), order;
        order.reserve(n);
        vector<int> st;
        st.push_back(0);
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);
            for (auto &e : child[u]) {
                int v = e.first, w = e.second;
                depth[v] = depth[u] + 1;
                prefix[v] = prefix[u] + w;
                st.push_back(v);
            }
        }
        vector<int> dp(n, -1);
        for (int idx = (int)order.size() - 1; idx >= 0; --idx) {
            int u = order[idx];
            if (child[u].empty()) {
                if (prefix[u] >= L && prefix[u] <= R)
                    dp[u] = prefix[u];
            } else {
                bool hasValid = false;
                int bestVal;
                if (depth[u] % 2 == 0) {
                    bestVal = -1;
                    for (auto &e : child[u]) {
                        int v = e.first;
                        if (dp[v] != -1) {
                            if (!hasValid) { hasValid = true; bestVal = dp[v]; }
                            else if (dp[v] > bestVal) bestVal = dp[v];
                        }
                    }
                } else {
                    bestVal = INT_MAX;
                    for (auto &e : child[u]) {
                        int v = e.first;
                        if (dp[v] != -1) {
                            if (!hasValid) { hasValid = true; bestVal = dp[v]; }
                            else if (dp[v] < bestVal) bestVal = dp[v];
                        }
                    }
                }
                if (hasValid) dp[u] = bestVal;
            }
        }
        if (dp[0] == -1) puts("Oh, my god!");
        else printf("%d\n", dp[0]);
    }
    return 0;
}
