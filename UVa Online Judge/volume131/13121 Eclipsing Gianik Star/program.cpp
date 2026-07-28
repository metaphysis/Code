// Eclipsing Gianik Star
// UVa ID: 13121
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.400s
// https://blog.csdn.net/metaphysis/article/details/163267769

#include <bits/stdc++.h>
using namespace std;

// 扩展欧几里得，返回 gcd(a,b)，并求出 x,y 使 ax+by=gcd
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// 求 a 在模 m 下的逆元，保证 gcd(a,m)=1 且 m>1
long long modInv(long long a, long long m) {
    long long x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

// 自定义 gcd，处理负数
long long gcdll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

int main() {
    int N;
    while (cin >> N) {
        vector<long long> alpha(N), beta(N);
        for (int i = 0; i < N; ++i) {
            long long rho;
            cin >> rho >> alpha[i] >> beta[i];
        }
        const long long MOD = 360;
        long long ans = LLONG_MAX;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                long long a = beta[i] - beta[j];
                long long b = alpha[j] - alpha[i];
                long long g = gcdll(a, MOD);
                if (b % g != 0) continue;
                long long aPrime = a / g;
                long long bPrime = b / g;
                long long m = MOD / g;
                long long t0;
                if (m == 1) t0 = 0;
                else {
                    long long aMod = (aPrime % m + m) % m;
                    long long inv = modInv(aMod, m);
                    t0 = (bPrime * inv) % m;
                    if (t0 < 0) t0 += m;
                }
                if (t0 < ans) ans = t0;
            }
        }
        if (ans == LLONG_MAX) cout << "GIANIK IS NEVER ECLIPSED\n";
        else cout << ans << '\n';
    }
    return 0;
}
