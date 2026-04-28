// Gain Battle Power
// UVa ID: 12836
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 2.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

        // 计算 L[i]：向左严格递增的最长长度
        vector<int> L(n, 1), R(n, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (a[j] < a[i]) L[i] = max(L[i], L[j] + 1);

        // 计算 R[i]：向右严格递减的最长长度
        for (int i = n - 1; i >= 0; --i)
            for (int j = i + 1; j < n; ++j)
                if (a[j] < a[i]) R[i] = max(R[i], R[j] + 1);

        // 力量值
        vector<int> power(n);
        for (int i = 0; i < n; ++i) power[i] = L[i] + R[i] - 1;

        // 前缀和
        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + power[i];

        // 区间DP + Knuth优化
        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<vector<int>> K(n, vector<int>(n, 0));

        // 初始化：长度为1的区间不需要分割点
        for (int i = 0; i < n; ++i) K[i][i] = i;

        // 枚举区间长度
        for (int len = 2; len <= n; ++len) {
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                int sumLR = pre[r + 1] - pre[l];
                dp[l][r] = INF;

                // 利用 Knuth 优化缩小 k 的范围
                int kMin = K[l][r - 1];
                int kMax = K[l + 1][r];
                for (int k = kMin; k <= kMax && k < r; ++k) {
                    int val = dp[l][k] + dp[k + 1][r] + sumLR;
                    if (val < dp[l][r]) {
                        dp[l][r] = val;
                        K[l][r] = k;
                    }
                }
            }
        }

        printf("Case %d: %d\n", caseNo, dp[0][n - 1]);
    }
    return 0;
}

