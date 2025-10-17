// Permutation Counting
// UVa ID: 1485
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;  // 模数
const int MAXN = 1000;       // 最大 N 值

int main() {
    // 预计算所有dp值
    vector<vector<long long>> dp(MAXN + 1, vector<long long>(MAXN + 1, 0));
    dp[0][0] = 1;  // 边界条件：空排列
    
    for (int n = 1; n <= MAXN; n++) {
        dp[n][0] = 1;  // 只有恒等排列满足 E-value=0
        for (int k = 1; k <= n; k++) {
            // 递推公式：dp[n][k] = dp[n - 1][k]*(1 + k) + dp[n - 1][k - 1]*(n - k)
            dp[n][k] = (dp[n - 1][k] * (1 + k) + dp[n - 1][k - 1] * (n - k)) % MOD;
        }
    }
    
    // 处理输入输出
    int N, k;
    while (cin >> N >> k) {
        cout << dp[N][k] << endl;
    }
    
    return 0;
}
