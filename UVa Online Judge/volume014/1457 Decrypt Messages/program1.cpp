#include <bits/stdc++.h>
using namespace std;

using Int64 = long long;
using Poly = vector<Int64>;

Int64 modPow(Int64 a, Int64 e, Int64 mod) {
    Int64 result = 1;
    while (e > 0) {
        if (e & 1) result = result * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return result;
}

void normalize(Poly &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

Poly polySub(Poly a, const Poly &b, Int64 mod) {
    if (a.size() < b.size()) a.resize(b.size(), 0);
    for (int i = 0; i < static_cast<int>(b.size()); ++i) {
        a[i] = (a[i] - b[i] + mod) % mod;
    }
    normalize(a);
    return a;
}

Poly polyMod(Poly a, const Poly &b, Int64 mod) {
    normalize(a);
    if (a.size() < b.size()) return a;
    Int64 inv = modPow(b.back(), mod - 2, mod);
    while (a.size() >= b.size() && !(a.size() == 1 && a[0] == 0)) {
        int diff = static_cast<int>(a.size() - b.size());
        Int64 rate = a.back() * inv % mod;
        for (int i = 0; i < static_cast<int>(b.size()); ++i) {
            a[i + diff] = (a[i + diff] - rate * b[i] % mod + mod) % mod;
        }
        normalize(a);
    }
    return a;
}

Poly polyMulMod(const Poly &a, const Poly &b, const Poly &modPolyValue, Int64 mod) {
    Poly result(a.size() + b.size() - 1, 0);
    for (int i = 0; i < static_cast<int>(a.size()); ++i)
        for (int j = 0; j < static_cast<int>(b.size()); ++j)
            result[i + j] = (result[i + j] + a[i] * b[j]) % mod;
    return polyMod(result, modPolyValue, mod);
}

Poly polyPowMod(Poly a, Int64 e, const Poly &modPolyValue, Int64 mod) {
    Poly result(1, 1);
    while (e > 0) {
        if (e & 1) result = polyMulMod(result, a, modPolyValue, mod);
        a = polyMulMod(a, a, modPolyValue, mod);
        e >>= 1;
    }
    return result;
}

Poly polyGcd(Poly a, Poly b, Int64 mod) {
    while (!(b.size() == 1 && b[0] == 0)) {
        Poly remainder = polyMod(a, b, mod);
        a = b;
        b = remainder;
    }
    Int64 inv = modPow(a.back(), mod - 2, mod);
    for (Int64 &value : a) value = value * inv % mod;
    return a;
}

void splitPoly(const Poly &f, Int64 mod, mt19937_64 &rng, vector<Int64> &roots) {
    if (f.size() == 1) return;
    if (f.size() == 2) {
        roots.push_back((mod - f[0]) % mod);
        return;
    }
    uniform_int_distribution<Int64> distribution(0, mod - 1);
    while (true) {
        Int64 c = distribution(rng);
        Poly base = {c, 1};
        Poly h = polyPowMod(base, (mod - 1) / 2, f, mod);
        Poly one = {1};
        Poly minusOne = {mod - 1};
        Poly left = polyGcd(f, polySub(h, one, mod), mod);
        if (left.size() > 1 && left.size() < f.size()) {
            Poly right = polyGcd(f, polySub(h, minusOne, mod), mod);
            splitPoly(left, mod, rng, roots);
            splitPoly(right, mod, rng, roots);
            return;
        }
    }
}

bool isLeapYear(int year) {
    return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}

string getTime(Int64 seconds) {
    int year = 2000;
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (true) {
        Int64 normalSeconds = static_cast<Int64>(isLeapYear(year) ? 366 : 365) * 86400;
        bool hasLeapSecond = year % 10 == 5 || year % 10 == 8;
        if (seconds < normalSeconds) break;
        if (hasLeapSecond && seconds == normalSeconds) {
            char buffer[64];
            sprintf(buffer, "%04d.12.31 23:59:60", year);
            return buffer;
        }
        seconds -= normalSeconds + (hasLeapSecond ? 1 : 0);
        ++year;
    }
    int days = static_cast<int>(seconds / 86400);
    int hour = static_cast<int>((seconds % 86400) / 3600);
    int minute = static_cast<int>((seconds % 3600) / 60);
    int second = static_cast<int>(seconds % 60);
    if (isLeapYear(year)) monthDays[1] = 29;
    int month = 1;
    while (days >= monthDays[month - 1]) {
        days -= monthDays[month - 1];
        ++month;
    }
    char buffer[64];
    sprintf(buffer, "%04d.%02d.%02d %02d:%02d:%02d", year, month, days + 1, hour, minute, second);
    return buffer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int caseId = 1; caseId <= testCases; ++caseId) {
        Int64 p, q, a;
        cin >> p >> q >> a;
        vector<Int64> roots;
        if (q % p == 0) {
            roots.push_back(a);
        } else {
            Poly function = vector<Int64>(q + 1, 0);
            function[q] = 1;
            function[0] = (p - a) % p;
            Poly frobenius = {p - 1, 0, 1};
            Poly candidate = polyPowMod({0, 1}, p, function, p);
            candidate = polySub(candidate, {0, 1}, p);
            Poly rootPart = polyGcd(function, candidate, p);
            if (rootPart.size() > 1) splitPoly(rootPart, p, rng, roots);
        }
        sort(roots.begin(), roots.end());
        roots.erase(unique(roots.begin(), roots.end()), roots.end());
        cout << "Case #" << caseId << ":\n";
        if (roots.empty()) {
            cout << "Transmission error\n";
            continue;
        }
        for (Int64 root : roots) cout << getTime(root) << '\n';
    }
    return 0;
}
