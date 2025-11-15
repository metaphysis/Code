// Stars
// UVa ID: 12493
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
using namespace std;

// 计算欧拉函数 φ(n)
long long eulerPhi(long long n) {
    long long result = n;
    // 质因数分解
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            // 去除所有 p 因子
            while (n % p == 0) {
                n /= p;
            }
            // 应用公式 φ(n) = n × ∏(1 - 1/p)
            result -= result / p;
        }
    }
    // 处理剩余的质因数
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        // 完全星的数量 = φ(n) / 2
        cout << eulerPhi(n) / 2 << "\n";
    }
    return 0;
}
