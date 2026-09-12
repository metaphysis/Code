#include <bits/stdc++.h>
using namespace std;

vector<int> getBasePrimes(int lim) {
    vector<bool> isPrime(lim + 1, true);
    vector<int> primes;
    isPrime[0] = false;
    if (lim >= 1) isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= lim; i++)
        if (isPrime[i])
            for (int j = i * i; j <= lim; j += i)
                isPrime[j] = false;
    for (int i = 3; i <= lim; i += 2)
        if (isPrime[i])
            primes.push_back(i);
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<pair<int, int>> qs(t);
    vector<int> ans(t);
    int maxVal = 0;
    for (int i = 0; i < t; i++) {
        int n, val;
        cin >> n;
        val = n * n;
        qs[i] = {val, i};
        maxVal = max(maxVal, val);
    }
    sort(qs.begin(), qs.end());
    int root = sqrt(maxVal);
    while (1LL * (root + 1) * (root + 1) <= maxVal) root++;
    vector<int> primes = getBasePrimes(root);
    const int block = 1 << 20;
    int pos = 0, cnt = 0;
    while (pos < t && qs[pos].first < 2) {
        ans[qs[pos].second] = 0;
        pos++;
    }
    if (maxVal >= 2) cnt = 1;
    for (int low = 3; low <= maxVal; low += block * 2) {
        int high = min(maxVal, low + block * 2 - 2);
        if (high % 2 == 0) high--;
        int len = (high - low) / 2 + 1;
        vector<char> mark(len, 0);
        for (int p : primes) {
            if (1LL * p * p > high) break;
            long long st = max(1LL * p * p, (1LL * low + p - 1) / p * p);
            if (st % 2 == 0) st += p;
            for (long long j = st; j <= high; j += 2LL * p)
                mark[(j - low) / 2] = 1;
        }
        for (int i = 0; i < len; i++) {
            int val = low + i * 2;
            while (pos < t && qs[pos].first < val) {
                ans[qs[pos].second] = cnt;
                pos++;
            }
            if (!mark[i]) cnt++;
            while (pos < t && qs[pos].first == val) {
                ans[qs[pos].second] = cnt;
                pos++;
            }
        }
    }
    while (pos < t) {
        ans[qs[pos].second] = cnt;
        pos++;
    }
    for (int i = 0; i < t; i++)
        cout << "Case " << i + 1 << ": " << ans[i] << '\n';
    return 0;
}
