// Inventory
// UVa ID: 1248
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f; // 表示无穷大的常数值
int dp[1005][105]; // dp[i][j] = 第i天结束后剩余j单位材料的最小总成本

int main() {
    int T; // 测试用例数量
    cin >> T;
    
    while (T--) {
        int n; // 生产天数
        cin >> n;
        
        // 初始化：第0天结束时剩余0材料，成本为0；其他状态不可达
        memset(dp[0], 0x3f, sizeof(dp[0]));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            int p, maxv, d;
            cin >> p >> maxv >> d; // 单价、最大订购量、当天需求
            
            // 初始化第i天的状态为不可达
            memset(dp[i], 0x3f, sizeof(dp[i]));
            
            // 从前一天的状态进行转移
            for (int j = 0; j <= 100; j++) {
                if (dp[i-1][j] == INF) continue; // 前一天状态不可达，跳过
                
                // j是第i-1天剩余的材料（第i天可用）
                if (j + maxv < d) continue; // 即使订购最大量也不够需求，不可能
                
                if (j <= d) {
                    // 情况1：前一天剩余不够当天需求
                    // 需要购买至少(d-j)单位来满足当天需求
                    // extra是多购买留给第i+1天的量
                    int extra = min(100, j + maxv - d);
                    int total_order = extra + d - j; // 总订购量
                    dp[i][extra] = min(dp[i][extra], 
                                      dp[i-1][j] + total_order * p);
                } else {
                    // 情况2：前一天剩余足够当天需求
                    // 不需要为当天需求订购，但可以购买extra单位留给明天
                    int extra = min(100, maxv);
                    dp[i][extra] = min(dp[i][extra], 
                                      dp[i-1][j] + extra * p);
                }
            }
            
            // 优化处理：如果多留材料成本更高，不如少留材料
            // 从后往前更新，保证dp[i][j]单调递减
            for (int j = 99; j >= 0; j--) {
                if (dp[i][j+1] != INF) {
                    // 少留1单位材料就少买1单位，节省p成本
                    dp[i][j] = min(dp[i][j], dp[i][j+1] - p);
                }
            }
        }
        
        // 最终答案：第n天结束后剩余0材料的最小成本
        cout << dp[n][0] << endl;
    }
    
    return 0;
}
