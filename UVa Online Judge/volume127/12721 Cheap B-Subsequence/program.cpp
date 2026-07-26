// Cheap B-Subsequence
// UVa ID: 12721
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173548

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        string S;
        int B;
        cin >> S >> B;
        int n = (int)S.size();
        // cost[字母][位置] 表示某字母在子序列中位于position时的贡献
        long long cost[26][105] = {};
        for (int c = 0; c < 26; ++c) {
            int Q;
            cin >> Q;
            vector<pair<int, int>> rules;
            for (int i = 0; i < Q; ++i) {
                int P, C;
                cin >> P >> C;
                rules.push_back({P, C});
            }
            // 计算该字母在每个位置1..B上的代价
            for (int pos = 1; pos <= B; ++pos) {
                long long sum = 0;
                for (auto &rule : rules) {
                    int P = rule.first, C = rule.second;
                    if (pos % P == 0)
                        sum += (pos / P) * C;
                }
                cost[c][pos] = sum;
            }
        }
        const long long INF = (1LL << 60);
        vector<vector<long long>> dp(n + 1, vector<long long>(B + 1, INF));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            int idx = S[i - 1] - 'a';
            for (int j = 0; j <= min(i, B); ++j) {
                // 不选当前字符
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                // 选当前字符作为子序列的第j个（前提j>=1）
                if (j >= 1 && dp[i - 1][j - 1] != INF)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + cost[idx][j]);
            }
        }
        cout << "Case #" << tc << ": " << dp[n][B] << "\n";
    }
    return 0;
}
