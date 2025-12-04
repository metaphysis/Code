// Joyful Ride
// UVa ID: 11184
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

int main() {
    int n;
    int caseNum = 1;
    while (scanf("%d", &n) == 1 && n != 0) {
        printf("Case %d:", caseNum);
        caseNum++;
        // 只有当 n ≡ 0 或 3 (mod 4) 时有解
        if (n % 4 != 3 && n % 4 != 0) {
            printf(" -1\n");
            continue;
        }
        // 计算关键参数：需要跳过的差值索引
        int skipIndex = (n + 1) / 4 * 2 - 1;
        if (n % 4 == 0) skipIndex++;  // n ≡ 0 (mod 4) 时特殊处理
        // 生成序列
        int currentHeight = 1 + skipIndex;
        printf(" 1 %d", currentHeight);
        int operationCount = 0;  // 已执行的操作次数
        for (int diff = 1; diff < n; diff++) {
            if (diff == skipIndex) continue;  // 跳过特定的差值
            // 交替进行加法和减法
            if (operationCount % 2 != skipIndex % 2) currentHeight += diff;
            else currentHeight -= diff;
            printf(" %d", currentHeight);
            operationCount++;
        }
        printf("\n");
    }
    return 0;
}
