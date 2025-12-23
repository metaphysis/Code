// Make a Crystal
// UVa ID: 11014
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXM = 100000;

int mu[MAXM + 5];
bool isPrime[MAXM + 5];
vector<int> primes;

// 预处理莫比乌斯函数：使用线性筛法
void sieve() {
    fill(isPrime, isPrime + MAXM + 1, true);
    mu[1] = 1;
    for (int i = 2; i <= MAXM; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            mu[i] = -1;  // 质数的莫比乌斯函数值为 -1
        }
        for (int p : primes) {
            if (i * p > MAXM) break;
            isPrime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;  // 有平方因子
                break;
            } else {
                mu[i * p] = -mu[i];  // 积性函数性质
            }
        }
    }
}

int main() {
    sieve();
    int caseNo = 1;
    int N;
    while (scanf("%d", &N) == 1 && N != 0) {
        LL M = N / 2;
        LL ans = 0;
        for (LL d = 1; d <= M; ++d) {
            LL t = M / d;  // floor(M/d)
            LL term = (2 * t + 1);
            term = term * term * term - 1;  // (2t+1)^3 - 1
            ans += mu[d] * term;
        }
        printf("Crystal %d: %lld\n", caseNo++, ans);
    }
    return 0;
}
