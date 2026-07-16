// Counting Heaps
// UVa ID: 1436
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
vector<int> primes;
vector<int> spf(MAXN + 1);
vector<long long> primeExp(MAXN + 1);

// 线性筛，求最小质因子
void sieve() {
    for (int i = 2; i <= MAXN; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > MAXN) break;
            spf[i * p] = p;
        }
    }
}

// 快速幂取模
long long modPow(long long base, long long exp, long long mod) {
    base %= mod;
    long long res = 1 % mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long m;
        cin >> n >> m;

        vector<int> parent(n + 1);
        parent[1] = 0;
        for (int i = 2; i <= n; ++i) cin >> parent[i];

        // 计算子树大小
        vector<int> subSize(n + 1, 1);
        for (int i = n; i >= 2; --i)
            subSize[parent[i]] += subSize[i];

        // 清空本次需要用到的质数指数（只清空 ≤ n 的质数）
        for (int p : primes) {
            if (p > n) break;
            primeExp[p] = 0;
        }

        // 减去每个子树大小的质因子指数（分母部分）
        for (int i = 1; i <= n; ++i) {
            int x = subSize[i];
            while (x > 1) {
                int p = spf[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    ++cnt;
                }
                primeExp[p] -= cnt;
            }
        }

        // 加上 n! 的质因子指数
        for (int p : primes) {
            if (p > n) break;
            long long exp = 0;
            long long power = p;
            while (power <= n) {
                exp += n / power;
                if (power > n / p) break;
                power *= p;
            }
            primeExp[p] += exp;
        }

        // 计算结果
        long long ans = 1 % m;
        for (int p : primes) {
            if (p > n) break;
            if (primeExp[p] > 0)
                ans = ans * modPow(p, primeExp[p], m) % m;
        }
        cout << ans << '\n';
    }

    return 0;
}
