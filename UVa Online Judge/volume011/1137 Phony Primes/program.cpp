#include <bits/stdc++.h>
using namespace std;

vector<int> getPrimes(int lim) {
    vector<bool> vis(lim + 1, false);
    vector<int> primes;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;
        primes.push_back(i);
        if ((long long)i * i > lim) continue;
        for (int j = i * i; j <= lim; j += i)
            vis[j] = true;
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> primes = getPrimes(46340);
    int nMin, nMax;
    bool firstCase = true;
    while (cin >> nMin >> nMax) {
        if (!firstCase) cout << '\n';
        firstCase = false;
        int len = nMax - nMin + 1;
        vector<int> rem(len), cnt(len);
        vector<bool> bad(len, false);
        for (int i = 0; i < len; i++)
            rem[i] = nMin + i;
        for (int p : primes) {
            long long first = ((long long)nMin + p - 1) / p * p;
            if (first > nMax) continue;
            for (long long x = first; x <= nMax; x += p) {
                int i = (int)(x - nMin);
                if (rem[i] % p != 0) continue;
                cnt[i]++;
                rem[i] /= p;
                if (rem[i] % p == 0) bad[i] = true;
                if ((nMin + (long long)i - 1) % (p - 1) != 0)
                    bad[i] = true;
            }
        }
        bool found = false;
        for (int i = 0; i < len; i++) {
            long long n = nMin + (long long)i;
            if (n % 2 == 0 || bad[i]) continue;
            if (rem[i] > 1) {
                cnt[i]++;
                if ((n - 1) % (rem[i] - 1) != 0)
                    bad[i] = true;
            }
            if (!bad[i] && cnt[i] >= 3) {
                cout << n << '\n';
                found = true;
            }
        }
        if (!found) cout << "none\n";
    }
    return 0;
}
