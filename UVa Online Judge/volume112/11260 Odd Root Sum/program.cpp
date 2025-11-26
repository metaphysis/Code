// Odd Root Sum
// UVa ID: 11260
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000000;

long long calculateSum(long long n) {
    if (n <= 0) return 0;
    long long m = (n % 2 == 1) ? n : n - 1;  // 不超过n的最大奇数
    if (m < 1) return 0;
    
    long long K = sqrt(m);
    __int128 result = 0;
    
    // 计算前K-1个完整区间
    if (K > 1) {
        __int128 oddCount = K / 2;      // 奇数k的个数：1,3,5,...,≤K-1
        __int128 evenCount = (K - 1) / 2;  // 偶数k的个数：2,4,6,...,≤K-1
        
        // 奇数k的贡献：Σ((2i-1)² + (2i-1)) = 4Σi² - 2Σi
        if (oddCount > 0) {
            // Σi = oddCount * (oddCount + 1) / 2
            __int128 sumI = oddCount * (oddCount + 1) / 2;
            // Σi² = oddCount * (oddCount + 1) * (2 * oddCount + 1) / 6
            __int128 sumI2 = oddCount * (oddCount + 1) * (2 * oddCount + 1) / 6;
            
            __int128 oddContrib = 4 * sumI2 - 2 * sumI;
            result += oddContrib;
        }
        
        // 偶数k的贡献：Σ(2i)² = 4Σi²
        if (evenCount > 0) {
            // Σi² = evenCount * (evenCount + 1) * (2 * evenCount + 1) / 6
            __int128 sumJ2 = evenCount * (evenCount + 1) * (2 * evenCount + 1) / 6;
            
            __int128 evenContrib = 4 * sumJ2;
            result += evenContrib;
        }
    }
    
    // 处理最后一个区间[K², m]
    long long start = K * K;
    if (start <= m) {
        long long firstOdd = (start % 2 == 1) ? start : start + 1;  // 区间内第一个奇数
        if (firstOdd <= m) {
            long long lastOdd = (m % 2 == 1) ? m : m - 1;  // 区间内最后一个奇数
            long long count = (lastOdd - firstOdd) / 2 + 1;  // 区间内奇数个数
            result += (__int128)count * K;
        }
    }
    
    return (long long)(result % MOD);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n && n != 0) cout << calculateSum(n) << '\n';
    
    return 0;
}
