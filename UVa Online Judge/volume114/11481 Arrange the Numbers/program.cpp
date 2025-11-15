// Arrange the Numbers
// UVa ID: 11481
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000;

long long fact[MAXN + 5], invFact[MAXN + 5];

// 快速幂取模
long long modPow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 预计算阶乘和逆元阶乘
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    invFact[MAXN] = modPow(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN - 1; i >= 0; i--) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
}

// 组合数 C(n, r) 模 MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// 计算答案
long long solve(int N, int M, int K) {
    if (K > M) return 0;
    int R = M - K; // 需要错排的数量
    long long res = 0;
    for (int i = 0; i <= R; i++) {
        long long sign = (i % 2 == 0) ? 1 : -1; // 容斥符号
        long long term = nCr(R, i) * fact[N - K - i] % MOD;
        res = (res + sign * term + MOD) % MOD;
    }
    res = res * nCr(M, K) % MOD;
    return res;
}

int main() {
    precompute();
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N, M, K;
        cin >> N >> M >> K;
        cout << "Case " << tc << ": " << solve(N, M, K) << endl;
    }
    return 0;
}
