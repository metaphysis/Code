#include <bits/stdc++.h>
using namespace std;

int main() {
    const double pi = acos(-1.0), g = 9.81, r = 0.11, w = 7.32, h = 2.44, eps = 1e-9;
    double a, b, c;
    while (cin >> a >> b >> c) {
        if (fabs(a) < eps && fabs(b) < eps && fabs(c) < eps) break;
        double ar = a * pi / 180.0, br = b * pi / 180.0;
        double vx = c * cos(br) * cos(ar), vy = c * sin(br);
        if (vx <= eps) {
            cout << "out\n";
            continue;
        }
        double t = 11.0 / vx, side = c * cos(br) * sin(ar) * t;
        if (fabs(side) > w / 2.0 + eps) {
            cout << "out\n";
            continue;
        }
        double land = 2.0 * vy / g;
        if (t > land + eps) {
            cout << "bounce\n";
            continue;
        }
        double y = r + vy * t - g * t * t / 2.0;
        if (y <= h + eps) cout << "goal\n";
        else cout << "out\n";
    }
    return 0;
}
