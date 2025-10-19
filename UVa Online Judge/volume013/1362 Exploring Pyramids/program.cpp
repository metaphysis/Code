// Exploring Pyramids
// UVa ID: 1362
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD = 1000000000;
int main() {
    string S;
    while (cin >> S) {
        int n = S.length();
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        // 初始化：单节点树的方案数为1
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        // 枚举区间长度
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                // 首尾颜色不同，无法形成树结构
                if (S[l] != S[r]) continue;
                // 枚举划分点k
                for (int k = l + 2; k <= r; k++) {
                    // 找到与根节点颜色相同的位置
                    if (S[l] == S[k]) {
                        // 累加方案数：第一棵子树 × 剩余子树
                        dp[l][r] = (dp[l][r] + dp[l + 1][k - 1] * dp[k][r]) % MOD;
                    }
                }
            }
        }
        // 输出整个序列对应的方案数
        cout << dp[0][n-1] << endl;
    }
    return 0;
}
