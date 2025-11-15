// RSA
// UVa ID: 12799
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>

using namespace std;

// 使用试除法分解 n 为 p 和 q
void factorize(long long n, long long &p, long long &q) {
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            return;
        }
    }
    p = n;
    q = 1;
}

// 扩展欧几里得算法求逆元
long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// 快速幂取模
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    long long n, e, c;
    while (cin >> n >> e >> c) {
        long long p, q;
        factorize(n, p, q);
        long long phiN = (p - 1) * (q - 1);
        long long d = modInverse(e, phiN);
        long long m = modPow(c, d, n);
        cout << m << endl;
    }
    return 0;
}
