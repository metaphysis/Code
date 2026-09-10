// L's in a Circle
// UVa ID: 11829
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), ios::sync_with_stdio(false);
    const double sqrt2 = sqrt(2.0);
    const double A = 14.0 + 3.0 * sqrt2;
    const double B = 89.0 / 2.0 + 15.0 * sqrt2;
    auto f = [&](double x) {
        return x * x * x - A * x * x + B * x + 2.0;
    };
    double lo = 4.0, hi = 5.0;
    for (int i = 0; i < 100; ++i) {
        double mid = (lo + hi) / 2.0;
        if (f(mid) > 0.0) lo = mid;
        else hi = mid;
    }
    double s = (lo + hi) / 2.0;
    double q = s / 2.0 - 1.0 / (4.0 * s);
    double ratio = sqrt(1.0 + q * q);
    double a;
    while (cin >> a) {
        if (a < -0.5) break;
        printf("%.10f\n", a * ratio);
    }
    return 0;
}
