// Summing the Lengths of the Longest Increasing Subsequence of Permutations
// UVa ID: 11272
// Verdict: Accepted
// Submission Date: 2026-11-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long double PI = 3.141592653589793238462643383279502884L;
    const long double LN10 = logl(10.0L);
    long long n;
    while (cin >> n) {
        long double x = static_cast<long double>(n);
        long double e = 2.0L * sqrtl(x) - 1.711L * powl(x, 1.0L / 6.0L);
        long double lnfact = x * logl(x) - x + 0.5L * logl((2.0L * x + 1.0L / 3.0L) * PI);
        long double L = (lnfact + logl(e)) / LN10;
        long double m = powl(10.0L, L - floorl(L)) * 100.0L;
        int d = static_cast<int>(m);
        if (m - static_cast<long double>(d) < 1e-5L) --d;
        cout << d << '\n';
    }
    return 0;
}
