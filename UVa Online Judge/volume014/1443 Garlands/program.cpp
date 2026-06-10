// Garlands
// UVa ID: 1443
// Verdict: Accepted
// Submission Date: 2026-06-10
// UVa Run Time: 4.940s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, d;
int sum[40010];          // 前缀和，sum[i] = w1 + ... + wi
int dp[40010][2];        // dp[i][0/1]：前 i 个物品分成偶数/奇数段所需的最少段数

// 检查当最重半段重量不超过 X 时是否可行
bool check(int X) {
    // 初始化
    for (int i = 0; i <= n; ++i) dp[i][0] = dp[i][1] = INF;
    dp[0][0] = 0;                     // 0 个物品，0 段（偶数），段数为 0

    // i 必须是偶数，因为每段长度是偶数
    for (int i = 2; i <= n; i += 2) {
        // 枚举最后一个半段的长度 j，对应段长度为 2*j
        for (int j = 1; j <= d && 2 * j <= i; ++j) {
            int secondHalf = sum[i] - sum[i - j];            // 后半段的和
            if (secondHalf > X) break;                       // 后半段已超限，更大的 j 只会更大
            int firstHalf = sum[i - j] - sum[i - 2 * j];      // 前半段的和
            if (firstHalf > X) continue;                     // 前半段超限，尝试下一个 j

            // 状态转移：当前段是第 (前段数+1) 段，奇偶性翻转
            dp[i][0] = min(dp[i][0], dp[i - 2 * j][1] + 1);
            dp[i][1] = min(dp[i][1], dp[i - 2 * j][0] + 1);
        }
    }
    // 需要总段数 = m-1，检查其奇偶性且段数不超过 m-1
    return dp[n][(m - 1) & 1] <= m - 1;
}

int main() {
    int Z;
    scanf("%d", &Z);
    while (Z--) {
        scanf("%d %d %d", &n, &m, &d);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int w;
            scanf("%d", &w);
            sum[i] = sum[i - 1] + w;
        }

        // 可行性剪枝：总长度 n 必须为偶数，且每段至少 2 个，最多 2d 个
        if ((n & 1) || n < 2 * (m - 1) || n > 2 * (m - 1) * d) {
            printf("BAD\n");
            continue;
        }

        int left = 1, right = sum[n], ans = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
