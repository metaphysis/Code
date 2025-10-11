// String Factoring
// UVa ID: 11022
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
int dp[105][105]; // dp[l][r]存储子串s[l..r]的最小权重
char str[105];    // 输入字符串
// 递归计算子串str[left..right]的最小权重
int dfs(int left, int right) {
    if (left == right) // 子串长度为1，权重为1
        return 1;
    if (dp[left][right]) // 如果已经计算过，直接返回
        return dp[left][right];
    int &result = dp[left][right];
    result = 0xfffffff; // 初始化为一个很大的值
    // 枚举分割点，将子串分为两部分
    for (int split = left; split < right; split++) {
        result = min(result, dfs(left, split) + dfs(split + 1, right));
    }
    int subLen = right - left + 1; // 当前子串的长度
    // 检查所有可能的周期长度
    for (int period = 1; period <= subLen; period++) {
        if (subLen % period == 0) { // 周期长度必须能整除子串长度
            int k, j;
            // 检查子串是否由长度为period的子串重复构成
            for (k = left, j = 0; k <= right; k++) {
                if (str[k] != str[j + left])
                    break;
                j++;
                if (j >= period) j = 0; // 重置索引，模拟周期性
            }
            // 如果整个子串都匹配，并且周期不是整个子串本身
            if (k == right + 1 && right != left + period - 1) {
                result = min(result, dfs(left, left + period - 1));
            }
        }
    }
    return result;
}
int main() {
    while (scanf("%s", str) == 1) {
        if (!strcmp(str, "*"))
            break;
        memset(dp, 0, sizeof(dp)); // 初始化dp数组
        int len = strlen(str);
        printf("%d\n", dfs(0, len - 1));
    }
    return 0;
}
