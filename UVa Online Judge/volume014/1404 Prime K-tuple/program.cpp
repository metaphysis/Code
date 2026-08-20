// Prime K-tuple
// UVa ID: 1404
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.480s

#include <bits/stdc++.h>
using namespace std;

vector<int> smallPrimes;

void generateSmallPrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) if (isPrime[i])
        for (int j = i * i; j <= limit; j += i) isPrime[j] = false;
    for (int i = 2; i <= limit; ++i) if (isPrime[i]) smallPrimes.push_back(i);
}

int countTuples(long long a, long long b, int k, int s) {
    long long len = b - a + 1;
    if (len <= 0) return 0;
    vector<char> isPrime(len, true);
    for (long long i = 0; i < len; ++i) {
        long long num = a + i;
        if (num < 2) isPrime[i] = false;
    }
    for (int p : smallPrimes) {
        if ((long long)p * p > b) break;
        long long start = max((long long)p * p, (a + p - 1) / p * p);
        for (long long j = start; j <= b; j += p) isPrime[j - a] = false;
    }
    vector<long long> primesInRange;
    for (long long i = 0; i < len; ++i) if (isPrime[i]) primesInRange.push_back(a + i);
    if (k == 1) return (s == 0) ? (int)primesInRange.size() : 0;
    int cnt = 0, n = (int)primesInRange.size();
    for (int i = 0; i + k - 1 < n; ++i)
        if (primesInRange[i + k - 1] - primesInRange[i] == s) ++cnt;
    return cnt;
}

int main() {
    generateSmallPrimes(50000);
    int T;
    cin >> T;
    while (T--) {
        long long a, b;
        int k, s;
        cin >> a >> b >> k >> s;
        cout << countTuples(a, b, k, s) << endl;
    }
    return 0;
}
