#include <bits/stdc++.h>
using namespace std;

const double SQRT3 = sqrt(3.0);

pair<int,int> getHex(double x, double y, double s) {
    double cx = 2.0 * x / (3.0 * s);
    double cy = 2.0 * y / (SQRT3 * s);
    int r0 = (int)floor(cx + 0.5);
    int l0 = (int)floor(cy + 0.5);
    double best = 1e100;
    int br = r0, bl = l0;
    for (int dr = -1; dr <= 1; ++dr) for (int dl = -1; dl <= 1; ++dl) {
        int r = r0 + dr, l = l0 + dl;
        if ((r + l) & 1) continue;
        double xc = r * 1.5 * s;
        double yc = l * 0.5 * SQRT3 * s;
        double d = (x - xc) * (x - xc) + (y - yc) * (y - yc);
        if (d < best) { best = d; br = r; bl = l; }
    }
    return make_pair(br, bl);
}

double distCenter(double x, double y, int r, int l, double s) {
    double xc = r * 1.5 * s;
    double yc = l * 0.5 * SQRT3 * s;
    return hypot(x - xc, y - yc);
}

int main() {
    double s, ax, ay, bx, by;
    cout << fixed << setprecision(3);
    while (cin >> s >> ax >> ay >> bx >> by) {
        if (fabs(s) < 1e-9 && fabs(ax) < 1e-9 && fabs(ay) < 1e-9 && fabs(bx) < 1e-9 && fabs(by) < 1e-9) break;
        auto a = getHex(ax, ay, s);
        auto b = getHex(bx, by, s);
        double ans;
        if (a == b) {
            ans = hypot(ax - bx, ay - by);
        } else {
            int dr = abs(a.first - b.first);
            int dl = abs(a.second - b.second);
            double centerDist;
            if (dr >= dl) centerDist = dr * SQRT3 * s;
            else centerDist = (dr + (dl - dr) / 2) * SQRT3 * s;
            ans = distCenter(ax, ay, a.first, a.second, s) + centerDist + distCenter(bx, by, b.first, b.second, s);
        }
        cout << ans << "\n";
    }
    return 0;
}
