// Digit Sum
// UVa ID: 12517
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;
// 计算从1到x的所有数的十进制数字之和
long long sum_digits_up_to(long long x) {
    if (x <= 0) return 0; // 如果x<=0，直接返回0
    long long ans = 0;    // 存储结果
    long long factor = 1; // 当前位的权重（1, 10, 100, ...）
    while (factor <= x) { // 遍历每一位
        long long full_cycles = x / (factor * 10); // 完整周期数
        long long remainder = x % (factor * 10);   // 剩余部分
        // 完整周期的贡献：每个周期数字0-9各出现factor次，和为45
        ans += full_cycles * factor * 45;
        long long digit = remainder / factor; // 当前位的数字
        // 数字0到digit-1各出现factor次
        for (int d = 0; d < digit; d++) {
            ans += factor * d;
        }
        // 数字digit出现(remainder % factor) + 1次
        ans += digit * (remainder % factor + 1);
        factor *= 10; // 移动到下一位
    }
    return ans;
}
int main() {
    long long M, N;
    while (cin >> M >> N) {
        if (M == 0 && N == 0) break; // 输入0 0时结束
        // 输出[M, N]区间的数字和
        cout << sum_digits_up_to(N) - sum_digits_up_to(M - 1) << endl;
    }
    return 0;
}
