// Pole Arrangement
// UVa ID: 1638
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using LL = long long; // 使用 long long 防止溢出
int main() {
    const int MAX_N = 20;
    // dp[n][l][r] 表示 n 根杆子，左边看到 l 根，右边看到 r 根的方案数
    vector<vector<vector<LL>>> dp(MAX_N + 1, vector<vector<LL>>(MAX_N + 1, vector<LL>(MAX_N + 1, 0)));
    // 初始化：只有 1 根杆子时，左右都只能看到这 1 根
    dp[1][1][1] = 1;
    // 动态规划预处理所有情况
    for (int n = 2; n <= MAX_N; n++)
        for (int l = 1; l <= n; l++)
            for (int r = 1; r <= n; r++)
                // 递推公式：
                // 1. 最矮杆放最左边：左边可见数 +1
                // 2. 最矮杆放最右边：右边可见数 +1  
                // 3. 最矮杆放中间：有 n-2 种选择，可见数不变
                dp[n][l][r] = dp[n - 1][l - 1][r] + dp[n - 1][l][r - 1] + (n - 2) * dp[n - 1][l][r];
    int T;
    cin >> T;
    while (T--) {
        int n, l, r;
        cin >> n >> l >> r;
        // 直接查询预处理结果
        cout << dp[n][l][r] << "\n";
    }

    return 0;
}
