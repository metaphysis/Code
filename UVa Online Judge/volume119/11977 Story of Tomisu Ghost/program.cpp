// Story of Tomisu Ghost
// UVa ID: 11977
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.170s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MOD = 10000019;
vector<int> primes;
bool isPrime[MAXN];

// 筛法生成所有质数
void sieve() {
    fill(isPrime, isPrime + MAXN, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAXN; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i + i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

// 快速幂取模 (a^b % MOD)
long long modPow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    sieve(); // 预处理质数表
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, t;
        scanf("%d %d", &n, &t);
        long long ans = 1;
        bool found = false; // 标记是否存在至少一个质数满足条件
        for (int p : primes) {
            if (p > n) break; // 质数超过n，不再对n!有贡献
            // 计算 n! 中质因子 p 的个数 (勒让德公式)
            long long cnt = 0;
            long long temp = n;
            while (temp > 0) {
                cnt += temp / p;
                temp /= p;
            }
            // 如果该质因子的个数足够支持至少t个尾随零
            if (cnt >= t) {
                found = true;
                long long k = cnt / t; // 在b中，p的指数最大可以为k
                ans = (ans * modPow(p, k)) % MOD; // 将 p^k 乘入答案
            }
        }
        if (found) printf("Case %d: %lld\n", caseNo, ans);
        else printf("Case %d: -1\n", caseNo);
    }
    return 0;
}
