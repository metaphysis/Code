// Count the Numbers
// UVa ID: 10712
// Verdict: Accepted
// Submission Date: 2025-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

char numberStr[12], subSeqStr[12];  // 数字字符串和子序列字符串
int targetSubSeq, numLen, subSeqLen;  // 目标子序列，数字长度，子序列长度
int dp[2][12][12][2];  // 记忆化数组：flag × 位置 × 匹配位置 × 是否开始

// 递归记忆化搜索函数
int dfs(int isTight, int currentPos, int matchPos, int hasStarted) {
    // 递归终止条件：处理完所有数位
    if (currentPos == numLen) return (matchPos == subSeqLen);
    
    // 记忆化检查
    if (dp[isTight][currentPos][matchPos][hasStarted] != -1) 
        return dp[isTight][currentPos][matchPos][hasStarted];

    int newMatchPos, digit, result = 0;
    int upperBound = isTight ? (numberStr[currentPos] - '0') : 9;
    
    // 枚举当前位所有可能的数字
    for (digit = 0; digit <= upperBound; digit++) {
        // 如果受限且当前数字超过上界，跳出循环
        if (isTight && digit > (numberStr[currentPos] - '0')) break;

        newMatchPos = matchPos;
        
        // 尝试匹配子序列
        if (digit == (subSeqStr[newMatchPos] - '0')) 
            newMatchPos++;
        
        // KMP思想：处理匹配失败时的回退
        if (matchPos != subSeqLen && matchPos != 0 && matchPos == newMatchPos) {
            newMatchPos = 0;
            // 寻找最长可能的前缀匹配
            while (digit == (subSeqStr[newMatchPos] - '0')) 
                newMatchPos++;
        }
        
        // 处理前导零情况：如果还在前导零阶段且目标子序列是0且当前位是0
        if (hasStarted == 0 && targetSubSeq == 0 && digit == 0) 
            newMatchPos = 0;
        
        // 递归搜索下一位
        int newIsTight = (isTight == 1 && digit == (numberStr[currentPos] - '0'));
        int newHasStarted = hasStarted || (digit != 0);
        result += dfs(newIsTight, currentPos + 1, newMatchPos, newHasStarted);
    }

    // 记忆化存储结果
    return dp[isTight][currentPos][matchPos][hasStarted] = result;
}

// 统计 [0, x] 范围内包含目标子序列的数字个数
int countNumbersUpTo(int upperBound) {
    if (upperBound < 0) return 0;
    
    // 将数字和子序列转换为字符串
    sprintf(numberStr, "%d", upperBound);
    sprintf(subSeqStr, "%d", targetSubSeq);
    numLen = strlen(numberStr);
    subSeqLen = strlen(subSeqStr);
    
    // 初始化记忆化数组
    memset(dp, -1, sizeof(dp));
    
    // 开始搜索，初始状态：受限、位置0、匹配位置0、未开始
    // 如果目标子序列是0，额外加上数字0本身
    return dfs(1, 0, 0, 0) + (targetSubSeq == 0);
}

int main() {
    int lowerBound, upperBound;
    
    // 处理多组测试数据，直到输入-1 -1 -1
    while (scanf("%d %d %d", &lowerBound, &upperBound, &targetSubSeq) != EOF) {
        if (lowerBound == -1 && upperBound == -1 && targetSubSeq == -1) break;
        
        // 计算区间 [lowerBound, upperBound] 内的结果
        int result = countNumbersUpTo(upperBound) - countNumbersUpTo(lowerBound - 1);
        printf("%d\n", result);
    }
    return 0;
}
