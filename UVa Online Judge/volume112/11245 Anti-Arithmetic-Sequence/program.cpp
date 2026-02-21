// Anti-Arithmetic-Sequence
// UVa ID: 11245
// Verdict: Accepted
// Submission Date: 2026-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算反等差数列的第n项
long long solve(long long n, int p) {
    if (n == 1) return 1;  // 特殊情况：第一项为1
    
    long long m = n - 1;     // 转换为0-based索引
    long long result = 0;    // 存储结果
    long long base = 1;      // p进制基数
    
    // 将m转换为(p-1)进制，同时解释为p进制数
    while (m > 0) {
        int digit = m % (p - 1);  // 获取(p-1)进制下的当前位
        result += digit * base;   // 按p进制累加到结果
        base *= p;                // 基数乘以p
        m /= (p - 1);            // 移除已处理的位
    }
    
    return result + 1;  // 最终加1得到答案
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        long long n;
        int p;
        cin >> n >> p;
        cout << solve(n, p) << "\n";
    }
    
    return 0;
}
