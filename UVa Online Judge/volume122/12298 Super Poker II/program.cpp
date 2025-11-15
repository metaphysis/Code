// Super Poker II
// UVa ID: 12298
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.370s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_B = 50000;

bool isComposite[MAX_B + 10];  // 标记合数，true 表示是合数
bool isLost[5][MAX_B + 10];    // 标记丢失的牌，isLost[i][j] 表示第 i 种花色数值 j 的牌是否丢失
ll dp[5][MAX_B + 10];          // dp[i][j] 表示前 i 种花色凑出总和 j 的方案数
ll prefixSum[MAX_B + 10];      // 前缀和数组

// 筛法预处理合数
void sieve() {
    memset(isComposite, 0, sizeof(isComposite));
    // 标记合数
    for (int i = 2; i * i <= MAX_B; i++) {
        if (!isComposite[i]) {
            for (int j = i * i; j <= MAX_B; j += i) {
                isComposite[j] = true;
            }
        }
    }
    // 1 不是合数
    isComposite[1] = false;
}

int main() {
    sieve();
    
    int start, end, lostCount;
    while (scanf("%d%d%d", &start, &end, &lostCount) && (start || end || lostCount)) {
        // 初始化
        memset(isLost, 0, sizeof(isLost));
        memset(dp, 0, sizeof(dp));
        
        // 花色映射表
        int suitMap[256] = {0};
        suitMap['S'] = 1;
        suitMap['H'] = 2; 
        suitMap['C'] = 3;
        suitMap['D'] = 4;
        
        // 读取丢失的牌
        while (lostCount--) {
            char inputStr[20];
            scanf("%s", inputStr);
            int value = 0, index = 0;
            // 解析数值部分
            while (inputStr[index] >= '0' && inputStr[index] <= '9') {
                value = value * 10 + (inputStr[index] - '0');
                index++;
            }
            // 解析花色
            int suit = suitMap[inputStr[index]];
            if (value <= end) {
                isLost[suit][value] = true;
            }
        }
        
        // 动态规划初始化
        dp[0][0] = 1;
        
        // 对每种花色进行动态规划
        for (int suit = 1; suit <= 4; suit++) {
            // 计算前一种花色的前缀和
            prefixSum[0] = dp[suit - 1][0];
            for (int j = 1; j <= end; j++) {
                prefixSum[j] = prefixSum[j - 1] + dp[suit - 1][j];
            }
            
            // 初始假设：所有数都可以使用
            for (int j = suit; j <= end; j++) {
                dp[suit][j] = prefixSum[j - 1];
            }
            
            // 修正：减去使用质数或丢失牌的方案
            for (int value = 1; value <= end; value++) {
                // 如果是质数或者牌丢失
                if (!isComposite[value] || isLost[suit][value]) {
                    // 从大到小更新，避免重复计算
                    for (int k = end; k >= value; k--) {
                        dp[suit][k] -= dp[suit - 1][k - value];
                    }
                }
            }
        }
        
        // 输出结果
        for (int n = start; n <= end; n++) {
            printf("%lld\n", dp[4][n]);
        }
        printf("\n");
    }
    
    return 0;
}
