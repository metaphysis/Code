// Hell on the Markets
// UVa ID: 1614
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    int n;
    // 循环读取多个测试用例
    while (scanf("%d", &n) == 1) {
        vector<int> tradeVolume(n);  // 存储每分钟的交易量
        long long totalSum = 0;      // 交易总量
        
        // 读取输入并计算总和
        for (int i = 0; i < n; i++) {
            scanf("%d", &tradeVolume[i]);
            totalSum += tradeVolume[i];
        }

        // 如果总和为奇数，直接输出 No
        if (totalSum % 2 != 0) {
            printf("No\n");
            continue;
        }

        long long targetSum = totalSum / 2;  // 目标总和
        vector<int> signAssignment(n, -1);   // 符号分配，默认全为 -1

        // 从后往前贪心选择
        for (int i = n - 1; i >= 0; i--) {
            if (tradeVolume[i] <= targetSum) {
                signAssignment[i] = 1;           // 选择该交易量
                targetSum -= tradeVolume[i];     // 更新剩余目标值
            }
        }

        // 输出结果
        printf("Yes\n");
        for (int i = 0; i < n; i++) {
            printf("%d", signAssignment[i]);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
