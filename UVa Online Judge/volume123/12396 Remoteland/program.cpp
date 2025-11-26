// Remoteland
// UVa ID: 12396
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.750s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 5000000;

vector<int> primes;
bool isPrime[MAXN + 1];

void sieve() {
    fill(isPrime, isPrime + MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= MAXN; j += i)
                isPrime[j] = false;
        }
    }
}

long long modPow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int solve(int n) {
    long long result = 1;
    for (int p : primes) {
        if (2 * p > n) break;
        long long exp = 0;
        long long tmp = n;
        while (tmp >= p) {
            tmp /= p;
            exp += tmp;
        }
        if (exp % 2 == 1) exp--;
        result = result * modPow(p, exp, MOD) % MOD;
    }
    return result;
}

int main() {
    sieve();
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        printf("%d\n", solve(n));
    }
    return 0;
}
