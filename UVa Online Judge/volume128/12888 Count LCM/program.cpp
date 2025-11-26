// Count LCM
// UVa ID: 12888
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.700s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;

vector<int> primes;
bool isPrime[MAXN];
int mu[MAXN];

void sieve() {
    fill(isPrime, isPrime + MAXN, true);
    isPrime[0] = isPrime[1] = false;
    mu[1] = 1;
    
    for (int i = 2; i < MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p >= MAXN) break;
            isPrime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
}

long long solve(int n, int m) {
    if (n > m) swap(n, m);
    long long res = 0;
    for (int d = 1; d <= n; d++) 
        res += (long long)mu[d] * (n / d) * (m / d);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    sieve();
    
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << solve(n, m) << "\n";
    }
    
    return 0;
}
