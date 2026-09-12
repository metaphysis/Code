#include <bits/stdc++.h>
using namespace std;

const long long lim = 10000000000000000LL;

void multiplyValue(long long &x, long long y) {
    if (y <= 0 || x > lim / y)
        throw "bad";
    x *= y;
}

long long getGcd(long long a, long long b) {
    while (a) {
        b %= a;
        swap(a, b);
    }
    return b;
}

long long getGreatestFactor(long long n) {
    if (n <= 3)
        return n;
    while (n % 2 == 0) {
        n /= 2;
        if (n < 4)
            return n;
    }
    while (n % 3 == 0) {
        n /= 3;
        if (n < 9)
            return n;
    }
    long long p = 5, step = 2;
    while (p * p <= n) {
        while (n % p == 0) {
            n /= p;
            if (n < p * p)
                return n;
        }
        p += step;
        step = 6 - step;
    }
    return n;
}

void solve(long long a, long long b, long long &i, long long &j) {
    if (a == 1)
        throw "bad";
    long long p, q = 0;
    set<long long> usedPrimes;
    while (a != 1 || b != 1) {
        if (q > 0) {
            p = 0;
            if (a % q == 0 || b % q == 0)
                p = getGreatestFactor(q);
            if (a % q == 0)
                p = max(p, getGreatestFactor(a / q));
            else
                p = max(p, getGreatestFactor(a));
            if (b % q == 0)
                p = max(p, getGreatestFactor(b / q));
            else
                p = max(p, getGreatestFactor(b));
        } else {
            p = max(getGreatestFactor(a), getGreatestFactor(b));
        }
        usedPrimes.insert(p);
        q = 0;
        if (a % p == 0) {
            long long count = 0;
            assert(b % p != 0);
            do {
                ++count;
                a /= p;
            } while (a % p == 0);
            if (count % 2 == 0) {
                ++count;
                multiplyValue(j, p);
            } else {
                long long g = getGcd(a, p - 1);
                a /= g;
                q = (p - 1) / g;
                b *= q;
            }
            count = (count + 1) / 2;
            while (count--)
                multiplyValue(i, p);
        }
        if (b % p == 0) {
            long long count = 0;
            assert(a % p != 0);
            do {
                ++count;
                b /= p;
            } while (b % p == 0);
            if (count % 2 == 0) {
                ++count;
                multiplyValue(i, p);
            } else {
                long long g = getGcd(b, p - 1);
                b /= g;
                q = (p - 1) / g;
                a *= q;
            }
            count = (count + 1) / 2;
            while (count--)
                multiplyValue(j, p);
        }
    }
    if (i == 1 || j == 1) {
        for (long long p = 2;; ++p) {
            if (getGreatestFactor(p) == p && usedPrimes.insert(p).second) {
                multiplyValue(i, p);
                multiplyValue(j, p);
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m;
    while (cin >> m && m) {
        try {
            long long i = 1, j = 1;
            solve(m, 1, i, j);
            cout << m << " " << i << " " << j << "\n";
        } catch (const char *) {
            cout << m << " No solution\n";
        }
    }
    return 0;
}
