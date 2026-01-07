// Divisors
// UVa ID: 13279
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.290s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5000000;
const long long MOD = 100000007LL;
vector<int> primes;
bool isPrime[MAX_N + 1];

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAX_N; ++i) if (isPrime[i]) {
        primes.push_back(i);
        if ((long long)i * i <= MAX_N)
            for (int j = i * i; j <= MAX_N; j += i)
                isPrime[j] = false;
    }
}

long long compute(int n) {
    long long answer = 1;
    for (int p : primes) {
        if (p > n) break;
        long long totalExp = 0;
        long long pk = p;
        while (pk <= n) {
            long long t = n / pk;
            totalExp = (totalExp + t * (n + 1) - pk * t * (t + 1) / 2) % MOD;
            if (pk > n / p) break;
            pk *= p;
        }
        answer = answer * (totalExp + 1) % MOD;
    }
    return answer;
}

int main() {
    sieve();
    int n;
    while (scanf("%d", &n) == 1 && n != 0) printf("%lld\n", compute(n));
    return 0;
}
