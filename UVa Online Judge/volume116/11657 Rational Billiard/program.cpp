// Rational Billiard
// UVa ID: 11657
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    a = llabs(a); b = llabs(b);
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

int main() {
    long long m, n, x1, y1, x2, y2, p, q;
    while (cin >> m >> n >> x1 >> y1 >> x2 >> y2 >> p >> q) {
        if (m == 0 && n == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && p == 0 && q == 0) break;
        bool hit = false;
        if (p == 0) {
            if (x1 == x2) hit = true;
        } else if (q == 0) {
            if (y1 == y2) hit = true;
        } else {
            int sxs[2] = {1, -1}, sys[2] = {1, -1};
            for (int si = 0; si < 2 && !hit; ++si) {
                long long sx = sxs[si];
                for (int sj = 0; sj < 2 && !hit; ++sj) {
                    long long sy = sys[sj];
                    long long dx = sx * x2 - x1;
                    long long dy = sy * y2 - y1;
                    long long C = p * dy - q * dx;
                    long long A = 2 * m * q;
                    long long B = -2 * n * p;
                    long long g = gcd(A, B);
                    if (C % g == 0) hit = true;
                }
            }
        }
        cout << (hit ? "HIT" : "MISS") << '\n';
    }
    return 0;
}
