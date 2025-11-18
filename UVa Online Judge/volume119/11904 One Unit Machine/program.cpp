// One Unit Machine
// UVa ID: 11904
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAX = 1000000;

long long fact[MAX + 1], invFact[MAX + 1];

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[MAX] = modPow(fact[MAX], MOD - 2);
    for (int i = MAX - 1; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    precompute();
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int n;
        cin >> n;
        vector<int> k(n);
        for (int i = 0; i < n; i++)
            cin >> k[i];
        long long res = 1;
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += k[i];
            res = res * nCr(total - 1, k[i] - 1) % MOD;
        }
        cout << "Case " << caseNum << ": " << res << endl;
    }
    return 0;
}
