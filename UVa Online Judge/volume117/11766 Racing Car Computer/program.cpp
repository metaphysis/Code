// Racing Car Computer
// UVa ID: 11766
// Verdict: Accepted
// Submission Date: 2026-01-25
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    int caseNum = 1;
    int n;
    while (cin >> n && n) {
        vector<vector<int>> cnt(n + 2, vector<int>(n + 2, 0));
        // 步骤1：预处理，统计每个区间内可能的车辆数
        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            // 如果 a+b >= n，数据肯定有问题
            if (a + b >= n) continue;
            // 计算合法区间
            int L = a + 1;          // 最小可能位置
            int R = n - b;          // 最大可能位置
            // 区间内的车数不能超过区间长度
            if (cnt[L][R] < R - L + 1) cnt[L][R]++;
        }
        // 步骤2：动态规划
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];  // 不选择任何以i结尾的区间
            for (int j = 0; j < i; j++) {
                // 考虑区间 [j+1, i]
                int length = i - j;  // 区间长度
                int canPlace = min(cnt[j + 1][i], length);  // 最多能放的车数
                dp[i] = max(dp[i], dp[j] + canPlace);
            }
        }
        // 步骤3：输出结果
        int minFaulty = n - dp[n];
        cout << "Case " << caseNum++ << ": " << minFaulty << '\n';
    }
    return 0;
}
