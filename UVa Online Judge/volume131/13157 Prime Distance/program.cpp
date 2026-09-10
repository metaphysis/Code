// Prime Distance
// UVa ID: 13157
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 100000;

vector<int> prefCnt(MAXN + 1), prefSum(MAXN + 1);
vector<int> twinCnt(MAXN + 1), twinSum(MAXN + 1);
vector<long long> cntOne(MAXN + 1), cntTwo(MAXN + 1), cntThree(MAXN + 1), cntFour(MAXN + 1);
vector<long long> fact(MAXN + 1), invFact(MAXN + 1);

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

int main() {
    // 筛素数
    vector<bool> isPrime(MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i)
        if (isPrime[i])
            for (int j = i * i; j <= MAXN; j += i) isPrime[j] = false;

    // 质数前缀计数和前缀和
    for (int i = 1; i <= MAXN; ++i) {
        prefCnt[i] = prefCnt[i - 1] + (isPrime[i] ? 1 : 0);
        prefSum[i] = prefSum[i - 1] + (isPrime[i] ? i : 0);
    }

    // 孪生素数对 (p, p+2) 且 p 为奇数质数
    for (int i = 1; i <= MAXN; ++i) {
        twinCnt[i] = twinCnt[i - 1];
        twinSum[i] = twinSum[i - 1];
        if (i >= 3 && isPrime[i] && isPrime[i + 2]) {
            twinCnt[i] = twinCnt[i - 1] + 1;
            twinSum[i] = twinSum[i - 1] + i;
        }
    }

    // 预处理每种大小的有效集合数量
    for (int n = 1; n <= MAXN; ++n) {
        cntOne[n] = n;
        // 两个点：距离为质数
        int x = n - 1;
        cntTwo[n] = 1LL * n * prefCnt[x] - prefSum[x];
        // 三个点：间隔 (2,p) 或 (p,2)，p 为孪生小值
        if (n >= 3) {
            int y = n - 2;
            cntThree[n] = 2LL * ((long long)(n - 2) * twinCnt[y] - twinSum[y]);
        } else cntThree[n] = 0;
        // 四个点：唯一间隔 (2,3,2)
        cntFour[n] = (n >= 8) ? (n - 7) : 0;
    }

    // 阶乘和逆元
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN] = modPow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) invFact[i - 1] = invFact[i] * i % MOD;

    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        int n, m;
        scanf("%d %d", &n, &m);
        long long ans = 0;
        ans = (ans + cntOne[n] % MOD * comb(m - 1, 0)) % MOD;
        ans = (ans + cntTwo[n] % MOD * comb(m - 1, 1)) % MOD;
        ans = (ans + cntThree[n] % MOD * comb(m - 1, 2)) % MOD;
        ans = (ans + cntFour[n] % MOD * comb(m - 1, 3)) % MOD;
        printf("Case %d: %lld\n", cas, ans);
    }
    return 0;
}
