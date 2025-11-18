// Christmas Tree
// UVa ID: 13274
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
vector<int> dp;

void dfs(int u, int parent, int k) {
    vector<int> childrenValues;
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u, k);
        childrenValues.push_back(dp[v]);
    }
    if (childrenValues.empty()) {
        dp[u] = 1;
        return;
    }
    sort(childrenValues.rbegin(), childrenValues.rend());
    if (childrenValues.size() < k) {
        dp[u] = 1;
    } else {
        int sum = 0;
        for (int i = 0; i < k; i++)
            sum += childrenValues[i];
        dp[u] = 1 + sum;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        int n, k;
        cin >> n >> k;
        tree.assign(n + 1, vector<int>());
        dp.assign(n + 1, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        dfs(1, -1, k);
        cout << "Case " << caseNum << ": " << dp[1] << "\n";
    }
    return 0;
}
