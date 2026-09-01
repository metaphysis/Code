#include <bits/stdc++.h>
using namespace std;

int main() {
    double a, b, c, d, rope;
    const double eps = 1e-4;
    while (cin >> a >> b >> c >> d >> rope) {
        double dx = c - a, dy = d - b, dist = sqrt(dx * dx + dy * dy);
        if (dist < eps) {
            cout << fixed << setprecision(10) << a << ' ' << b - rope / 2.0 << '\n';
            continue;
        }
        if (rope < dist && dist - rope < eps) rope = dist;
        double centerX = (a + c) / 2.0, centerY = (b + d) / 2.0;
        double halfLong = rope / 2.0, halfFocus = dist / 2.0;
        double value = halfLong * halfLong - halfFocus * halfFocus;
        if (value < 0.0) value = 0.0;
        double halfShort = sqrt(value);
        double unitX = dx / dist, unitY = dy / dist;
        double radius = sqrt((halfLong * unitY) * (halfLong * unitY) + (halfShort * unitX) * (halfShort * unitX));
        double x, y;
        if (radius < eps) {
            if (b < d) {
                x = a;
                y = b;
            } else {
                x = c;
                y = d;
            }
        } else {
            x = centerX - unitX * unitY * halfFocus * halfFocus / radius;
            y = centerY - radius;
        }
        cout << fixed << setprecision(10) << x << ' ' << y << '\n';
    }
    return 0;
}
