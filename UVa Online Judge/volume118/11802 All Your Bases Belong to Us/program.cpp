// All Your Bases Belong to Us
// UVa ID: 11802
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int MOD = 1000000007;
const int MAXP = 500;

vector<int> getPrimes(int limit) {
    vector<bool> isComp(limit + 1, false);
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (!isComp[i]) {
            primes.push_back(i);
            if ((int64)i * i <= limit)
                for (int j = i * i; j <= limit; j += i) isComp[j] = true;
        }
    }
    return primes;
}

int main() {
    vector<int> primes = getPrimes(MAXP);
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int64 n, k;
        scanf("%lld %lld", &n, &k);
        int64 prod1 = 1; // 对应 K = k
        int64 prod2 = 1; // 对应 K = k+1
        for (int p : primes) {
            if (p > n) break;
            int64 m = 0;
            int64 tmp = n;
            while (tmp) {
                tmp /= p;
                m += tmp;
            }
            if (m >= k) {
                int64 cnt = m / k + 1;
                prod1 = prod1 * (cnt % MOD) % MOD;
            }
            if (m >= k + 1) {
                int64 cnt = m / (k + 1) + 1;
                prod2 = prod2 * (cnt % MOD) % MOD;
            }
        }
        int64 ans = (prod1 - prod2 + MOD) % MOD;
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
