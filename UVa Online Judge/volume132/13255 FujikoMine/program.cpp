// FujikoMine
// UVa ID: 13255
// Verdict: Accepted
// Submission Date: 2026-10-19
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long negInf = -(1LL << 60);

struct Edge {
    int to, weight;
};

struct NodeDp {
    vector<long long> open, complete;
};

int n, m, q;
vector<vector<Edge>> children;
vector<int> parentNode, isTransmission;
vector<NodeDp> dp;

void dfs(int u) {
    int transmissionCount = isTransmission[u] ? 1 : 0;
    dp[u].open.assign(transmissionCount + 1, negInf);
    dp[u].complete.assign(1, negInf);
    dp[u].open[transmissionCount] = 0;
    dp[u].complete[0] = 0;
    for (const Edge &edge : children[u]) {
        int v = edge.to;
        dfs(v);
        vector<long long> newOpen(dp[u].open.size() + dp[v].open.size() - 1, negInf);
        vector<long long> newComplete(dp[u].complete.size() + dp[v].complete.size() - 1, negInf);
        for (int i = 0; i < (int)dp[u].open.size(); i++) {
            if (dp[u].open[i] == negInf) continue;
            newOpen[i] = max(newOpen[i], dp[u].open[i]);
            for (int j = 1; j < (int)dp[v].open.size(); j++) {
                if (dp[v].open[j] == negInf) continue;
                newOpen[i + j] = max(newOpen[i + j], dp[u].open[i] + dp[v].open[j] + edge.weight);
            }
        }
        for (int i = 0; i < (int)dp[u].complete.size(); i++) {
            if (dp[u].complete[i] == negInf) continue;
            for (int j = 0; j < (int)dp[v].complete.size(); j++) {
                if (dp[v].complete[j] == negInf) continue;
                newComplete[i + j] = max(newComplete[i + j], dp[u].complete[i] + dp[v].complete[j]);
            }
        }
        dp[u].open.swap(newOpen);
        dp[u].complete.swap(newComplete);
    }
    if (isTransmission[u]) {
        if (dp[u].complete.size() < dp[u].open.size())
            dp[u].complete.resize(dp[u].open.size(), negInf);
        for (int k = 0; k < (int)dp[u].open.size(); k++)
            dp[u].complete[k] = max(dp[u].complete[k], dp[u].open[k]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> q) {
        children.assign(n, {});
        parentNode.assign(n, -1);
        isTransmission.assign(n, 0);
        dp.assign(n, {});
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            children[u].push_back({v, w});
            parentNode[v] = u;
        }
        for (int i = 0; i < m; i++) {
            int node;
            cin >> node;
            isTransmission[node] = 1;
        }
        vector<int> queries(q);
        for (int i = 0; i < q; i++) cin >> queries[i];
        int root = 0;
        while (parentNode[root] != -1) root = parentNode[root];
        dfs(root);
        for (int k : queries) {
            if (k < 2 || k >= (int)dp[root].complete.size() || dp[root].complete[k] == negInf)
                cout << 0 << '\n';
            else
                cout << dp[root].complete[k] << '\n';
        }
    }
    return 0;
}
