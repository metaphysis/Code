// Triangle Hazard
// UVa ID: 12165
// Verdict: Accepted
// Submission Date: 2023-04-12
// UVa Run Time: 0.220s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    point P, Q, R, A, B, C;
    double m1, m2, m3, m4, m5, m6;
    int N;
    cin >> N;
    cout << fixed << setprecision(8);
    while (N--) {
        cin >> P.x >> P.y >> Q.x >> Q.y >> R.x >> R.y;
        cin >> m1 >> m2 >> m3 >> m4 >> m5 >> m6;
        double k1 = m5 / m6, k2 = m1 / m2, k3 = m3 / m4;
        double x1 = (k1 + k1 * k2 + k1 * k2 * k3) / (1.0 - k1 * k2 * k3);
        double x2 = (k2 + k2 * k3 + k1 * k2 * k3) / (1.0 - k1 * k2 * k3);
        double x3 = (k3 + k3 * k1 + k1 * k2 * k3) / (1.0 - k1 * k2 * k3);
        A = R + (R - P) * x1, B = P + (P - Q) * x2, C = Q + (Q - R) * x3;
        cout << A.x << ' ' << A.y << ' ';
        cout << B.x << ' ' << B.y << ' ';
        cout << C.x << ' ' << C.y << '\n';
    }
    return 0;
}
