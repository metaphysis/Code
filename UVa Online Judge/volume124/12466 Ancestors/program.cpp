// Ancestors
// UVa ID: 12466
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.470s

#include <bits/stdc++.h>
using namespace std;
const int NEG = -1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        if (N == 0 && K == 0) break;
        vector<int> nodeValue(N);
        for (int i = 0; i < N; ++i) cin >> nodeValue[i];
        vector<vector<int>> children(N);
        for (int i = 1; i < N; ++i) {
            int p; cin >> p;
            children[p].push_back(i);
        }
        // 迭代前序遍历得到顺序，逆序即为后序
        vector<int> order;
        order.reserve(N);
        vector<int> stack;
        stack.push_back(0);
        while (!stack.empty()) {
            int u = stack.back(); stack.pop_back();
            order.push_back(u);
            for (int v : children[u]) stack.push_back(v);
        }
        // dp[u][j] 表示在 u 的子树中选 j 个节点且不选 u 时的最大权值和
        vector<vector<int>> dp(N, vector<int>(K + 1, NEG));
        for (int idx = N - 1; idx >= 0; --idx) {
            int u = order[idx];
            dp[u][0] = 0;
            int curMax = 0; // 当前已合并孩子能达到的最大节点数
            for (int v : children[u]) {
                // 计算孩子 v 的转移数组 h[b]：选 b 个节点，可以选 v 或不选 v
                int childMax = 0;
                for (int b = 0; b <= K; ++b) {
                    int hVal = dp[v][b];
                    if (b == 1) hVal = max(hVal, nodeValue[v]);
                    if (hVal > NEG / 2) childMax = b;
                }
                int ndp[105];
                fill(ndp, ndp + K + 1, NEG);
                for (int i = 0; i <= curMax; ++i) {
                    if (dp[u][i] <= NEG / 2) continue;
                    for (int b = 0; b <= childMax && i + b <= K; ++b) {
                        int hVal = dp[v][b];
                        if (b == 1) hVal = max(hVal, nodeValue[v]);
                        if (hVal <= NEG / 2) continue;
                        ndp[i + b] = max(ndp[i + b], dp[u][i] + hVal);
                    }
                }
                for (int j = 0; j <= K; ++j) dp[u][j] = ndp[j];
                curMax = min(K, curMax + childMax);
            }
        }
        int ans = nodeValue[0]; // 只选根节点
        for (int j = 1; j <= K; ++j) ans = max(ans, dp[0][j]);
        cout << ans << '\n';
    }
    return 0;
}
