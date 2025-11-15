// Help Tomisu
// UVa ID: 11440
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000000;
const int MOD = 100000007;

// 快速幂求逆元
long long fastPow(long long base, long long exponent, long long mod) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

// 求模逆元
long long modularInverse(long long x) {
    return fastPow(x, MOD - 2, MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 筛法求质数
    vector<bool> isPrime(MAX_N + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAX_N; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAX_N) {
                for (int j = i * i; j <= MAX_N; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }

    // 预处理阶乘数组
    vector<long long> factorial(MAX_N + 1);
    factorial[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }

    // 预处理连乘积数组：prod[M] = ∏_{p≤M} (1 - 1/p) mod MOD
    vector<long long> product(MAX_N + 1, 1);
    int lastProcessed = 1;
    for (int prime : primes) {
        // 填充 lastProcessed + 1 到 prime - 1 的值
        for (int m = lastProcessed + 1; m < prime; ++m) {
            product[m] = product[lastProcessed];
        }
        // 在质数位置乘上 (prime - 1) / prime
        long long factor = (prime - 1) * modularInverse(prime) % MOD;
        product[prime] = product[lastProcessed] * factor % MOD;
        lastProcessed = prime;
    }
    // 填充剩余部分
    for (int m = lastProcessed + 1; m <= MAX_N; ++m) {
        product[m] = product[lastProcessed];
    }

    // 处理查询
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        long long answer = (factorial[n] * product[m] % MOD - 1 + MOD) % MOD;
        cout << answer << '\n';
    }

    return 0;
}
