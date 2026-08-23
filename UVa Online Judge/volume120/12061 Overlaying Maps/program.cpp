#include <bits/stdc++.h>
using namespace std;

void solve() {
    double x, y, ax, ay, bx, by, cx, cy, dx, dy;
    cin >> x >> y;
    cin >> ax >> ay;
    cin >> bx >> by;
    cin >> cx >> cy;
    cin >> dx >> dy;
    double p, q, r, s, det, ansX, ansY;
    p = 1.0 - (bx - ax) / x;
    q = -(dx - ax) / y;
    r = -(by - ay) / x;
    s = 1.0 - (dy - ay) / y;
    det = p * s - q * r;
    ansX = (ax * s - q * ay) / det;
    ansY = (p * ay - r * ax) / det;
    cout << fixed << setprecision(4) << ansX << ' ' << ansY << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
