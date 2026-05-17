// Consecutive Sums
// UVa ID: 12355
// Verdict: Accepted
// Submission Date: 2026-05-17
// UVa Run Time: 0.780s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXB = 10000001;
bool isComp[MAXB];
int primes[700000], cnt;

// 线性筛法，预处理 1e7 以内的所有素数
void sieve() {
    for (int i = 2; i < MAXB; ++i) {
        if (!isComp[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXB; ++j) {
            isComp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    ll q;
    while (cin >> q && q) {
        // 去除所有因子 2，位运算加速
        while ((q & 1) == 0) q >>= 1;
        ll r = 2;
        // 用素数试除奇数部分
        for (int i = 0; i < cnt; ++i) {
            int p = primes[i];
            if ((ll)p * p > q) break;
            if (q % p == 0) {
                int e = 0;
                do {
                    q /= p;
                    ++e;
                } while (q % p == 0);
                r *= (2 * e + 1);
            }
        }
        // 剩余部分为大于 1e7 的奇质数
        if (q > 1) r *= 3;
        cout << r << '\n';
    }
    return 0;
}
