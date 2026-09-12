#include <bits/stdc++.h>
using namespace std;

vector<int> getPrimes() {
    const int maxN = 100000;
    vector<bool> isPrime(maxN + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= maxN; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        if (1LL * i * i > maxN) continue;
        for (int j = i * i; j <= maxN; j += i)
            isPrime[j] = false;
    }
    return primes;
}

int getExp(int n, int p) {
    int sum = 0;
    while (n) {
        n /= p;
        sum += n;
    }
    return sum;
}

long long getCount(int k, const vector<int>& exps) {
    __int128 res = 1;
    for (int e : exps) {
        if (e < k) break;
        res *= e / k + 1;
    }
    return (long long)(res - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> primes = getPrimes();
    int n, x;
    while (cin >> n >> x && (n || x)) {
        vector<int> exps;
        for (int p : primes) {
            if (p > n) break;
            exps.push_back(getExp(n, p));
        }
        sort(exps.rbegin(), exps.rend());
        int maxK = exps[0];
        vector<long long> cnt(maxK + 2);
        for (int k = x; k <= maxK + 1; k++)
            cnt[k] = getCount(k, exps);
        long long ans = 0;
        for (int k = x; k <= maxK; k++) {
            long long cur = cnt[k] - cnt[k + 1];
            ans += cur * (cur - 1) / 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
