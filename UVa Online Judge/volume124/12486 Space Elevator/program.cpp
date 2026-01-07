// Space Elevator
// UVa ID: 12486
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 使用 unsigned long long 避免溢出
typedef unsigned long long ULL;

// 记忆化数组：dp[pos][hasOne] 和 visited[pos][hasOne]
ULL dp[25][2];
bool visited[25][2];
string digits;
int len;

// 数位 DP：统计 [0, x] 中吉利数的个数
ULL dfs(int pos, bool hasOne, bool isLimit) {
    // 到达最后一位，成功构造一个数（包括 0）
    if (pos == len) return 1;
    
    // 非限制状态才能使用记忆化
    if (!isLimit && visited[pos][hasOne]) {
        return dp[pos][hasOne];
    }
    
    // 当前位可选数字的上限
    int upper = isLimit ? digits[pos] - '0' : 9;
    ULL res = 0;
    
    // 枚举当前位的所有可能数字
    for (int d = 0; d <= upper; d++) {
        if (d == 4) continue; // 跳过数字 4
        if (hasOne && d == 3) continue; // 前一位是 1 时跳过 3（避免 13）
        
        // 递归处理下一位，更新 hasOne 状态
        res += dfs(pos + 1, d == 1, isLimit && (d == upper));
    }
    
    // 只在非限制状态保存结果
    if (!isLimit) {
        dp[pos][hasOne] = res;
        visited[pos][hasOne] = true;
    }
    
    return res;
}

// 计算 [1, x] 中吉利数的个数
ULL countValid(ULL x) {
    if (x == 0) return 0;
    
    // 将 x 转换为字符串，便于按位处理
    digits = to_string(x);
    len = digits.length();
    
    // 重置 visited 数组
    memset(visited, 0, sizeof(visited));
    
    // 计算 [0, x] 的吉利数个数，然后减去 0（因为题目从 1 开始）
    return dfs(0, false, true) - 1;
}

// 二分查找第 n 个吉利数
ULL findNthValid(ULL n) {
    // 二分查找范围：下界 1，上界 1e19（足够大）
    ULL left = 1, right = 10000000000000000000ULL;
    
    while (left < right) {
        ULL mid = left + (right - left) / 2;
        if (countValid(mid) >= n)
            right = mid;
        else
            left = mid + 1;
    }
    
    return left;
}

int main() {
    ULL n;
    while (cin >> n) {
        cout << findNthValid(n) << endl;
    }
    return 0;
}
