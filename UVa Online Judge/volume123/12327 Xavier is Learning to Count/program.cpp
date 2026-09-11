// Xavier is Learning to Count
// UVa ID: 12327
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 3.920s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int m, p;
        scanf("%d %d", &m, &p);
        vector<int> a(m);
        for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
        if (p > m) {
            printf("Case #%d:\n\n", caseNo);
            continue;
        }
        sort(a.begin(), a.end());
        // 最大可能的和：最大的 p 个数之和
        int maxSum = 0;
        for (int i = m - p; i < m; ++i) maxSum += a[i];
        // dp[k][s] 表示选 k 个数得到和 s 的方案数
        vector<vector<long long>> dp(p + 1, vector<long long>(maxSum + 1, 0));
        dp[0][0] = 1;
        // curMax[k] 表示当前已处理的数中，选 k 个数的最大可能和（即最大的 k 个数之和）
        vector<int> curMax(p + 1, 0);
        for (int x : a) {
            // 备份旧的 curMax，本次更新使用旧值
            vector<int> oldMax = curMax;
            // 更新 dp：从 k 大到小，使用旧 dp[k-1]
            for (int k = p; k >= 1; --k) {
                int limit = oldMax[k - 1]; // t 的最大值
                // 遍历 t 从 0 到 limit
                for (int t = 0; t <= limit; ++t) {
                    long long val = dp[k - 1][t];
                    if (val) {
                        int s = t + x;
                        if (s <= maxSum) dp[k][s] += val;
                    }
                }
            }
            // 更新 curMax：新的最大 k 数和 = max(旧, 旧(k-1) + x)
            for (int k = 1; k <= p; ++k) {
                int candidate = oldMax[k - 1] + x;
                if (candidate > curMax[k]) curMax[k] = candidate;
                if (curMax[k] > maxSum) curMax[k] = maxSum;
            }
        }
        vector<pair<int, long long>> ans;
        for (int s = 1; s <= maxSum; ++s)
            if (dp[p][s]) ans.push_back({s, dp[p][s]});
        printf("Case #%d:\n", caseNo);
        for (size_t i = 0; i < ans.size(); ++i)
            printf("%d: %lld\n", ans[i].first, ans[i].second);
        printf("\n");
    }
    return 0;
}
