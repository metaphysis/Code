// Triangular Square
// UVa ID: 10725
// Verdict: Accepted
// Submission Date: 2025-12-25
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

double work(double a, double b, double c) {
    double cosA = (b * b + c * c - a * a) / (2 * b * c);
    double cosB = (a * a + c * c - b * b) / (2 * a * c);
    if (cosA > EPS && cosB > EPS) {
        double cotA = cosA / sqrt(1 - cosA * cosA);
        double cotB = cosB / sqrt(1 - cosB * cosB);
        return c / (1 + cotA + cotB);
    } else if (cosA > EPS) {
        double cotA = cosA / sqrt(1 - cosA * cosA);
        return c / (1 + cotA);
    } else if (cosB > EPS) {
        double cotB = cosB / sqrt(1 - cosB * cosB);
        return c / (1 + cotB);
    } else {
        return c;
    }
}

double solve(double a, double b, double c) {
    double r = work(a, b, c);
    r = max(r, work(a, c, b));
    r = max(r, work(b, a, c));
    r = max(r, work(b, c, a));
    r = max(r, work(c, a, b));
    r = max(r, work(c, b, a));
    return r * r;
}

int main() {
    int T; cin >> T;
    while (T--) {
        double a, b, c; cin >> a >> b >> c;
        cout << fixed << setprecision(6) << solve(a, b, c) << endl;
    }
    return 0;
}
