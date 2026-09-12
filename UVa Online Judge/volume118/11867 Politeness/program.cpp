#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;
const unsigned long long cap = 1000000008ULL;
vector<int> facPrimes, oddPrimes;
vector<long long> divs;
vector<pair<long long, int>> facs;
long double bestLog;
long long bestMod;
unsigned long long bestCap;

void initPrimes() {
    const int n = 1000000;
    vector<bool> vis(n + 1, false);
    int i, j;
    for (i = 2; i <= n; i++) {
        if (!vis[i]) {
            facPrimes.push_back(i);
            if (i > 2) oddPrimes.push_back(i);
            if (1LL * i * i <= n)
                for (j = i * i; j <= n; j += i)
                    vis[j] = true;
        }
    }
}

vector<pair<long long, int>> factorNum(long long n) {
    vector<pair<long long, int>> res;
    long long p;
    int cnt;
    for (int x : facPrimes) {
        p = x;
        if (p * p > n) break;
        if (n % p == 0) {
            cnt = 0;
            while (n % p == 0) {
                n /= p;
                cnt++;
            }
            res.push_back({p, cnt});
        }
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

void genDiv(int idx, long long cur) {
    if (idx == (int)facs.size()) {
        divs.push_back(cur);
        return;
    }
    long long val = cur;
    int i;
    for (i = 0; i <= facs[idx].second; i++) {
        genDiv(idx + 1, val);
        val *= facs[idx].first;
    }
}

long long modPow(long long a, long long e) {
    long long res = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return res;
}

unsigned long long capMul(unsigned long long a, unsigned long long b) {
    __int128 val = (__int128)a * b;
    if (val >= cap) return cap;
    return (unsigned long long)val;
}

unsigned long long capPow(long long a, long long e) {
    unsigned long long res = 1, base = a;
    while (e > 0) {
        if (e & 1) res = capMul(res, base);
        base = capMul(base, base);
        e >>= 1;
    }
    return res;
}

void dfs(long long rem, int idx, long long last, long double curLog, long long curMod, unsigned long long curCap) {
    if (rem == 1) {
        if (curLog < bestLog) {
            bestLog = curLog;
            bestMod = curMod;
            bestCap = curCap;
        }
        return;
    }
    if (idx >= (int)oddPrimes.size()) return;
    long long lim = min(last, rem), nextMod;
    unsigned long long nextCap;
    long double nextLog;
    for (long long d : divs) {
        if (d < 2) continue;
        if (d > lim) break;
        if (rem % d != 0) continue;
        nextMod = curMod * modPow(oddPrimes[idx], d - 1) % mod;
        nextCap = capMul(curCap, capPow(oddPrimes[idx], d - 1));
        nextLog = curLog + (long double)(d - 1) * log((long double)oddPrimes[idx]);
        dfs(rem / d, idx + 1, d, nextLog, nextMod, nextCap);
    }
}

long long solve(long long p) {
    long long q = p + 1;
    if (q == 1) return 1;
    facs = factorNum(q);
    divs.clear();
    genDiv(0, 1);
    sort(divs.begin(), divs.end());
    bestLog = numeric_limits<long double>::infinity();
    bestMod = 1;
    bestCap = cap;
    dfs(q, 0, q, 0, 1, 1);
    if (bestCap <= mod) return (long long)bestCap;
    return bestMod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initPrimes();
    int t;
    long long p;
    cin >> t;
    while (t--) {
        cin >> p;
        cout << solve(p) << '\n';
    }
    return 0;
}
