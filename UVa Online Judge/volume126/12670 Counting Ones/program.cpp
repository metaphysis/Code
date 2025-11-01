// Counting Ones
// UVa ID: 12670
// Verdict: Accepted
// Submission Date: 2025-10-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

typedef unsigned long long ull;

// 计算从 1 到 n 的所有数的二进制中 1 的个数总和
ull countOnes(ull n) {
    ull total = 0; // 存储总个数
    ull currentPower = 1; // 2^k
    ull nextPower = 2; // 2^(k+1)
    
    // 遍历每一位
    while (currentPower <= n) {
        // 完整周期的贡献
        total += ((n + 1) / nextPower) * currentPower;
        // 不完整周期的贡献
        ull remainder = (n + 1) % nextPower;
        if (remainder > currentPower) {
            total += remainder - currentPower;
        }
        
        // 移动到下一位
        currentPower <<= 1;
        nextPower <<= 1;
    }
    return total;
}

int main() {
    ull A, B;
    // 处理多组测试用例
    while (cin >> A >> B) {
        // 计算 [A, B] 区间的 1 的个数 = countOnes(B) - countOnes(A-1)
        ull result = countOnes(B) - countOnes(A - 1);
        cout << result << endl;
    }
    return 0;
}
