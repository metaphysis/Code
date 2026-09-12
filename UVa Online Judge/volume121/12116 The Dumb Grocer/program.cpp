#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

vector<int> primes;

i128 comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    k = min(k, n - k);
    i128 res = 1;
    for (int i = 1; i <= k; i++) res = res * (n - k + i) / i;
    return res;
}

long long solve(long long n) {
    long long x = n + 1;
    vector<int> exps;
    for (int p : primes) {
        if (1LL * p * p > x) break;
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            exps.push_back(cnt);
        }
    }
    if (x > 1) exps.push_back(1);
    int sum = 0;
    for (int e : exps) sum += e;
    i128 ans = 0;
    for (int k = 1; k <= sum; k++) {
        i128 cur = 0;
        for (int t = 1; t <= k; t++) {
            i128 ways = comb(k, t);
            for (int e : exps) ways *= comb(e + t - 1, t - 1);
            if ((k - t) & 1) cur -= ways;
            else cur += ways;
        }
        ans += cur;
    }
    return (long long)ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<bool> mark(46341);
    for (int i = 2; i <= 46340; i++) {
        if (!mark[i]) {
            primes.push_back(i);
            if (1LL * i * i <= 46340)
                for (int j = i * i; j <= 46340; j += i) mark[j] = true;
        }
    }
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        long long n;
        cin >> n;
        cout << "Case " << cs << ": " << solve(n) << '\n';
    }
    return 0;
}
