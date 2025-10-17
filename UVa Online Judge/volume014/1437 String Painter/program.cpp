// String Painter
// UVa ID: 1437
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    string A, B;
    while (cin >> A >> B) {
        int n = A.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Step 1: 计算dp[i][j] - 将空白串刷成B[i..j]的最小次数
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;  // 单个字符需要1次操作
            for (int j = i + 1; j < n; ++j) {
                // 最坏情况：先刷i位置，再刷剩下的
                dp[i][j] = dp[i + 1][j] + 1;
                // 寻找优化机会：如果B[i] == B[k]，可以合并操作
                for (int k = i + 1; k <= j; ++k) {
                    if (B[i] == B[k]) {
                        // 状态转移：dp[i][j] = min(dp[i][j], dp[i+1][k] + dp[k+1][j])
                        dp[i][j] = min(dp[i][j], dp[i + 1][k] + (k + 1 > j ? 0 : dp[k + 1][j]));
                    }
                }
            }
        }

        // Step 2: 计算ans[i] - 将A[0..i]刷成B[0..i]的最小次数
        vector<int> ans(n, 0);
        // 初始化第一个字符
        if (A[0] == B[0]) {
            ans[0] = 0;  // 第一个字符相同，不需要操作
        } else {
            ans[0] = 1;  // 第一个字符不同，需要1次操作
        }

        for (int i = 1; i < n; ++i) {
            if (A[i] == B[i]) {
                // 当前字符相同，继承前一个结果
                ans[i] = ans[i - 1];
            } else {
                // 当前字符不同，考虑所有可能的分割点
                ans[i] = dp[0][i];  // 最坏情况：整个区间重刷
                for (int j = 0; j < i; ++j) {
                    // 在j处分割：前j个字符用ans[j]，后面的用dp[j+1][i]
                    ans[i] = min(ans[i], ans[j] + dp[j + 1][i]);
                }
            }
        }

        cout << ans[n - 1] << endl;
    }
    return 0;
}
