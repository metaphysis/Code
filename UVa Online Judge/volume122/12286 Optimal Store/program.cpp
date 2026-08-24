#include <bits/stdc++.h>
using namespace std;

using Ld = long double;
const Ld eps = 1e-18L;

struct Point {
    Ld x, y;
    Point(Ld x = 0, Ld y = 0) : x(x), y(y) {}
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (Ld k) const {
        return Point(x * k, y * k);
    }
    Point operator / (Ld k) const {
        return Point(x / k, y / k);
    }
};

Point dir[4] = {Point(0, 1), Point(0, -1), Point(1, 0), Point(-1, 0)};
Point p[3];

Ld getLen(Point v) {
    return sqrtl(v.x * v.x + v.y * v.y);
}

Ld getVal(Point q) {
    return getLen(q - p[0]) + 2.0L * getLen(q - p[1]) + 2.0L * getLen(q - p[2]);
}

Ld solve() {
    Point now = (p[0] + p[1] + p[2]) / 3.0L;
    for (Ld step = 1e4L; step > eps; step /= 2.0L) {
        bool moved = true;
        while (moved) {
            moved = false;
            Ld oldVal = getVal(now);
            for (int i = 0; i < 4; ++i) {
                Point next = now + dir[i] * step;
                if (getVal(next) < oldVal) {
                    now = next;
                    moved = true;
                    break;
                }
            }
        }
    }
    return getVal(now);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x1, y1, x2, y2, x3, y3, cas = 0;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        if (x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1 && x3 == -1 && y3 == -1) break;
        p[0] = Point(x1, y1);
        p[1] = Point(x2, y2);
        p[2] = Point(x3, y3);
        Ld ans = 1e100L;
        for (int i = 0; i < 3; ++i) {
            swap(p[0], p[i]);
            ans = min(ans, solve());
            swap(p[0], p[i]);
        }
        cout << "Case " << ++cas << ": " << fixed << setprecision(8) << (double)ans << '\n';
    }
    return 0;
}
