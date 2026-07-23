// DDR King
// UVa ID: 10272
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAXN = 500;
    vector<long long> sum(MAXN + 1, 0), maxSum(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; ++i) {
        long long base = (i / 4) * (i / 4) + 1;
        sum[i] = sum[i - 1] + base;
        maxSum[i] = 3 * sum[i];          // 全 PERFECT 时的得分（缩放后）
    }
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        long long M;
        cin >> N >> K >> M;
        if (M % 100 != 0) { cout << "No\n"; continue; }
        long long S = M / 100;            // 缩放后的总分
        if (K > N) { cout << "No\n"; continue; }
        if (S < sum[K]) { cout << "No\n"; continue; }
        S -= maxSum[K];                   // 强制一个长度为 K 的段且视为全 PERFECT
        if (S < 0) {
            // 负值通过调整 K 段内的 PERFECT 个数来补偿，只保留奇偶信息
            S = (S % 2 == 0 ? 0 : 1);
        }
        if (S == 0) { cout << "Yes\n"; continue; }
        int R = N - K;                    // 剩余箭头数（用于其他段和重置）
        if (R <= 0) { cout << "No\n"; continue; }
        const long long NEG = -1e18;
        vector<vector<long long>> dp(R + 1, vector<long long>(2, NEG));
        dp[0][0] = 0;
        // DP：每步可添加一段长度为 j 的得分段（j=0 表示只加一个重置，得0）
        for (int i = 0; i <= R; ++i) {
            for (int p = 0; p < 2; ++p) {
                if (dp[i][p] == NEG) continue;
                // j=0 时只消耗 1 个重置，不增加得分
                for (int j = 0; j <= K && i + j + 1 <= R; ++j) {
                    long long add = maxSum[j];        // maxSum[0] = 0
                    int np = (p + (add & 1)) & 1;     // 新奇偶性
                    dp[i + j + 1][np] = max(dp[i + j + 1][np], dp[i][p] + add);
                }
            }
        }
        if (S <= dp[R][S & 1]) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
