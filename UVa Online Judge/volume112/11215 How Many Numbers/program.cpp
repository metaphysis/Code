// How Many Numbers
// UVa ID: 11215
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.530s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    long long num, den;
    Fraction(long long n = 0, long long d = 1) {
        if (d < 0) { n = -n; d = -d; }
        if (n == 0) { num = 0; den = 1; return; }
        long long g = __gcd(llabs(n), d);
        num = n / g;
        den = d / g;
    }
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
};

Fraction addFrac(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den + b.num * a.den, a.den * b.den);
}
Fraction subFrac(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den - b.num * a.den, a.den * b.den);
}
Fraction mulFrac(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.num, a.den * b.den);
}
Fraction divFrac(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den, a.den * b.num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int caseNo = 1;
    while (cin >> n && n) {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        int totalMask = 1 << n;
        vector< set<Fraction> > dp(totalMask);

        for (int i = 0; i < n; ++i)
            dp[1 << i].insert(Fraction(a[i], 1));

        for (int mask = 1; mask < totalMask; ++mask) {
            if ((mask & (mask - 1)) == 0) continue; // 单元素已初始化

            for (int subMask = (mask - 1) & mask; subMask; subMask = (subMask - 1) & mask) {
                int other = mask ^ subMask;
                if (subMask > other) continue;
                if (dp[subMask].empty() || dp[other].empty()) continue;

                for (const Fraction& x : dp[subMask]) {
                    for (const Fraction& y : dp[other]) {
                        dp[mask].insert(addFrac(x, y));
                        dp[mask].insert(subFrac(x, y));
                        dp[mask].insert(subFrac(y, x));
                        dp[mask].insert(mulFrac(x, y));
                        if (y.num != 0) dp[mask].insert(divFrac(x, y));
                        if (x.num != 0) dp[mask].insert(divFrac(y, x));
                    }
                }
            }
        }

        cout << "Case " << caseNo++ << ": " << dp[totalMask - 1].size() << '\n';
    }
    return 0;
}
