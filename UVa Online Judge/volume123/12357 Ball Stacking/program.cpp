// Ball Stacking
// UVa ID: 12357
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int value[MAXN][MAXN];      // 存储每个球的值
int colSum[MAXN][MAXN];     // g[i][j]：列前缀和
int pyramid[MAXN][MAXN];    // w[i][j]：金字塔区域总和
int dp[MAXN][MAXN];         // dp[i][j]：以(i,j)为右下角的最大和
int suffixMax[MAXN][MAXN];  // sdp[i][j]：后缀最大值

int main() {
    int n;
    // 循环处理每个测试用例，直到遇到 n == 0
    while (cin >> n && n != 0) {
        // 初始化数组（虽然全局变量默认为0，但显式重置更安全）
        memset(value, 0, sizeof(value));
        memset(colSum, 0, sizeof(colSum));
        memset(pyramid, 0, sizeof(pyramid));
        memset(dp, 0, sizeof(dp));
        memset(suffixMax, 0, sizeof(suffixMax));
        
        // 读入球的值并计算列前缀和
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                cin >> value[i][j];
                // 列前缀和：当前值加上上一行同列的值
                colSum[i][j] = colSum[i-1][j] + value[i][j];
            }
        }
        
        // 计算金字塔区域总和 w[i][j]
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                // w[i][j] = g[i][j] + w[i-1][j-1]
                pyramid[i][j] = colSum[i][j] + pyramid[i-1][j-1];
            }
        }
        
        int ans = 0; // 最终答案，初始化为0（可以不选任何球）
        
        // 动态规划，按列进行
        for (int j = 1; j <= n; j++) {
            // 对于当前列j，处理所有可能的行i (i >= j)
            for (int i = j; i <= n; i++) {
                // 情况1：独立的金字塔区域
                dp[i][j] = pyramid[i][j];
                
                // 情况2：与左侧(j-1列)的区域结合
                if (j > 1) {
                    // 使用后缀最大值快速找到左侧最佳区域
                    dp[i][j] = max(dp[i][j], suffixMax[i-1][j-1] + colSum[i][j]);
                }
                
                // 更新全局最大答案
                ans = max(ans, dp[i][j]);
            }
            
            // 计算当前列j的后缀最大值数组 sdp[][j]
            // 从最后一行开始往前计算
            suffixMax[n][j] = dp[n][j];
            for (int i = n - 1; i >= j; i--) {
                suffixMax[i][j] = max(suffixMax[i+1][j], dp[i][j]);
            }
        }
        
        // 输出当前测试用例的答案
        cout << ans << endl;
    }
    return 0;
}
