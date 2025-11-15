// Hidden Truth in Recurrence
// UVa ID: 10547
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstdio>
using namespace std;

// 快速幂取模 (base^exp) % mod
long long powMod(long long base, long long exp, long long mod) {
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
    long long k, n;
    int t;
    int caseNum = 1;
    
    while (cin >> k >> n >> t) {
        if (k == 0 && n == 0 && t == 0) {
            break;
        }
        
        long long mod = 1;
        for (int i = 0; i < t; i++) {
            mod *= 10;
        }
        
        long long ans = powMod(k, n, mod);
        
        printf("Case #%d: %lld\n", caseNum++, ans);
    }
    
    return 0;
}
