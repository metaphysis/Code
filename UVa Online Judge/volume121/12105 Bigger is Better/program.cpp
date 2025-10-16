// Bigger is Better
// UVa ID: 12105
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_N = 100;        // 最大火柴数
const int MAX_M = 3000;       // 最大模数
const int MAX_DIGITS = 50;    // 最大位数估计
const int INF = 200;          // 无穷大值

int n, m;
int dp[MAX_DIGITS][MAX_M];    // dp[i][r] = 使用i位数模m余r的最小火柴数
int cost[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; // 数字0-9的火柴消耗
int powerMod[MAX_DIGITS];     // powerMod[i] = 10^(i-1) % m

// 初始化数组
void init() {
    // 计算10的幂次模m
    powerMod[1] = 1 % m;
    for (int i = 2; i <= n / 2; i++) {
        powerMod[i] = (powerMod[i - 1] * 10) % m;
    }
    // 初始化dp数组为无穷大
    for (int i = 0; i <= n / 2; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = INF;
        }
    }
}

// 动态规划计算最小火柴数
void computeDP() {
    dp[0][0] = 0;  // 初始状态：0位数，余数0，需要0根火柴
    // 遍历所有可能的位数
    for (int digits = 0; digits <= n / 2; digits++) {
        // 遍历所有可能的余数
        for (int remainder = 0; remainder < m; remainder++) {
            // 如果当前状态不可达，跳过
            if (dp[digits][remainder] > n) continue;
            // 尝试在末尾添加数字0-9
            for (int digit = 0; digit < 10; digit++) {
                int newDigits = digits + 1;
                int newRemainder = (remainder * 10 + digit) % m;
                int newMatches = dp[digits][remainder] + cost[digit];
                // 更新最小火柴数
                if (newMatches < dp[newDigits][newRemainder]) {
                    dp[newDigits][newRemainder] = newMatches;
                }
            }
        }
    }
}

// 构造并输出最大数字
void constructAnswer() {
    // 寻找最大可能的位数
    int maxDigits = 0;
    for (int digits = n / 2; digits >= 1; digits--) {
        if (dp[digits][0] <= n) {
            maxDigits = digits;
            break;
        }
    }
    // 无解情况
    if (maxDigits == 0) {
        printf("-1");
        return;
    }
    int currentRemainder = 0;   // 当前余数
    int remainingMatches = n;   // 剩余火柴数
    // 从高位到低位贪心构造数字
    for (int position = maxDigits; position >= 1; position--) {
        // 从9到0尝试，保证数字尽可能大
        for (int digit = 9; digit >= 0; digit--) {
            // 计算前一位应该有的余数
            int prevRemainder = ((currentRemainder - digit * powerMod[position]) % m + m) % m;
            // 检查是否可行
            if (position == 1) {
                // 最后一位需要特殊处理
                if (prevRemainder == 0 && cost[digit] <= remainingMatches) {
                    printf("%d", digit);
                    remainingMatches -= cost[digit];
                    currentRemainder = prevRemainder;
                    break;
                }
            } else {
                if (dp[position - 1][prevRemainder] + cost[digit] <= remainingMatches) {
                    printf("%d", digit);
                    remainingMatches -= cost[digit];
                    currentRemainder = prevRemainder;
                    break;
                }
            }
        }
    }
}

int main() {
    int caseNumber = 1;
    // 读取输入直到n=0
    while (scanf("%d", &n) == 1 && n != 0) {
        scanf("%d", &m);
        init();           // 初始化数组
        computeDP();      // 动态规划计算
        printf("Case %d: ", caseNumber++);
        constructAnswer(); // 构造并输出答案
        printf("\n");
    }
    return 0;
}
