// Triple Shot
// UVa ID: 12921
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    double x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        double det = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
        if (fabs(det) < 1e-12) {
            cout << "Impossible\n";
            continue;
        }
        double a1 = 2 * (x2 - x1), b1 = 2 * (y2 - y1);
        double c1 = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
        double a2 = 2 * (x3 - x1), b2 = 2 * (y3 - y1);
        double c2 = x3 * x3 + y3 * y3 - x1 * x1 - y1 * y1;
        double denom = a1 * b2 - a2 * b1;
        double cx = (c1 * b2 - c2 * b1) / denom;
        double cy = (a1 * c2 - a2 * c1) / denom;
        cout << fixed << setprecision(10) << cx << " " << cy << "\n";
    }
    return 0;
}
