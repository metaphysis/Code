#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;
const int maxN = 15000;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<pair<u64, int> > fac;
unordered_map<u64, int> pos;
u64 curX;
int ansN, ansM;

u64 mulMod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 powMod(u64 a, u64 b, u64 mod) {
    u64 res = 1;
    while (b) {
        if (b & 1) res = mulMod(res, a, mod);
        a = mulMod(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, x;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        int i;
        for (i = 1; i < s; ++i) {
            x = mulMod(x, x, n);
            if (x == n - 1) break;
        }
        if (i == s) return false;
    }
    return true;
}

u64 gcdVal(u64 a, u64 b) {
    while (b) {
        u64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

u64 pollardRho(u64 n) {
    if (n % 2 == 0) return 2;
    while (true) {
        u64 c = rng() % (n - 1) + 1, x = rng() % (n - 2) + 2, y = x, d = 1;
        while (d == 1) {
            x = (mulMod(x, x, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            u64 dif = x > y ? x - y : y - x;
            d = gcdVal(dif, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n) {
    if (n == 1) return;
    if (isPrime(n)) {
        fac.push_back(make_pair(n, 1));
        return;
    }
    u64 d = pollardRho(n);
    factor(d);
    factor(n / d);
}

void checkDiv(u64 a) {
    u64 m = a + 1, b, s;
    if (m > maxN) return;
    b = curX / a;
    if ((b + 2) % m) return;
    s = (b + 2) / m;
    auto it = pos.find(s);
    if (it == pos.end()) return;
    int n = it->second;
    if (ansN == -1 || n < ansN || (n == ansN && (int)m < ansM)) {
        ansN = n;
        ansM = (int)m;
    }
}

void genDiv(int idx, u64 val) {
    if (idx == (int)fac.size()) {
        checkDiv(val);
        return;
    }
    u64 p = fac[idx].first;
    int e = fac[idx].second;
    for (int i = 0; i <= e; ++i) {
        genDiv(idx + 1, val);
        if (i < e) val *= p;
    }
}

void init() {
    int phi[maxN + 1];
    u64 sum = 0;
    for (int i = 0; i <= maxN; ++i) phi[i] = i;
    for (int i = 2; i <= maxN; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= maxN; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    phi[1] = 1;
    for (int i = 1; i <= maxN; ++i) {
        sum += phi[i];
        pos[sum] = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    long long in;
    while (cin >> in && in != -1) {
        if (in == 0) {
            cout << "1 1\n";
            continue;
        }
        curX = (u64)in * 2;
        fac.clear();
        factor(curX);
        sort(fac.begin(), fac.end());
        vector<pair<u64, int> > tmp;
        for (auto x : fac) {
            if (tmp.empty() || tmp.back().first != x.first) tmp.push_back(x);
            else ++tmp.back().second;
        }
        fac = tmp;
        ansN = ansM = -1;
        genDiv(0, 1);
        if (ansN == -1) cout << "NOT FOUND\n";
        else cout << ansN << ' ' << ansM << '\n';
    }
    return 0;
}
