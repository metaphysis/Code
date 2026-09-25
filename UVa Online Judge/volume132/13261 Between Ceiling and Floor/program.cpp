#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 mulMod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 powMod(u64 base, u64 exp, u64 mod) {
    u64 res = 1;
    while (exp > 0) {
        if (exp & 1) res = mulMod(res, base, mod);
        base = mulMod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

bool isPrime(u64 num) {
    if (num < 2) return false;
    for (u64 prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (num % prime == 0) return num == prime;
    u64 odd = num - 1;
    int cnt = 0;
    while ((odd & 1) == 0) {
        odd >>= 1;
        ++cnt;
    }
    for (u64 base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (base % num == 0) continue;
        u64 val = powMod(base % num, odd, num);
        if (val == 1 || val == num - 1) continue;
        bool passed = false;
        for (int i = 1; i < cnt; ++i) {
            val = mulMod(val, val, num);
            if (val == num - 1) {
                passed = true;
                break;
            }
        }
        if (!passed) return false;
    }
    return true;
}

u64 nextVal(u64 val, u64 add, u64 mod) {
    return (mulMod(val, val, mod) + add) % mod;
}

u64 pollardRho(u64 num) {
    if (num % 2 == 0) return 2;
    if (num % 3 == 0) return 3;
    while (true) {
        u64 y = rng() % (num - 1) + 1, add = rng() % (num - 1) + 1;
        u64 len = 1, div = 1, x = 0, saved = 0;
        while (div == 1) {
            x = y;
            for (u64 i = 0; i < len; ++i) y = nextVal(y, add, num);
            for (u64 pos = 0; pos < len && div == 1; pos += 128) {
                saved = y;
                u64 prod = 1, cnt = min(128ULL, len - pos);
                for (u64 i = 0; i < cnt; ++i) {
                    y = nextVal(y, add, num);
                    u64 diff = x > y ? x - y : y - x;
                    prod = mulMod(prod, diff, num);
                }
                div = __gcd(prod, num);
            }
            len <<= 1;
        }
        if (div == num) {
            do {
                saved = nextVal(saved, add, num);
                u64 diff = x > saved ? x - saved : saved - x;
                div = __gcd(diff, num);
            } while (div == 1);
        }
        if (div > 1 && div < num) return div;
    }
}

void factorNum(u64 num, map<u64, int>& factors) {
    if (num == 1) return;
    if (isPrime(num)) {
        ++factors[num];
        return;
    }
    u64 div = pollardRho(num);
    factorNum(div, factors);
    factorNum(num / div, factors);
}

bool isSquare(u64 num) {
    u64 root = sqrtl((long double)num);
    while ((u128)root * root > num) --root;
    while ((u128)(root + 1) * (root + 1) <= num) ++root;
    return (u128)root * root == num;
}

u128 getSigma(u64 num) {
    map<u64, int> factors;
    factorNum(num, factors);
    u128 ans = 1;
    for (const auto& item : factors) {
        u128 sum = 1, power = 1;
        for (int i = 0; i < item.second; ++i) {
            power *= item.first;
            sum += power;
        }
        ans *= sum;
    }
    return ans;
}

string toString(u128 num) {
    if (num == 0) return "0";
    string res;
    while (num > 0) {
        res.push_back('0' + (int)(num % 10));
        num /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    u64 m, k;
    unordered_map<u64, string> ansCache;
    while (cin >> m >> k) {
        if (isSquare(k)) {
            cout << 0 << '\n';
            continue;
        }
        auto it = ansCache.find(m);
        if (it != ansCache.end()) {
            cout << it->second << '\n';
            continue;
        }
        string ans = toString(getSigma(m));
        ansCache.emplace(m, ans);
        cout << ans << '\n';
    }
    return 0;
}
