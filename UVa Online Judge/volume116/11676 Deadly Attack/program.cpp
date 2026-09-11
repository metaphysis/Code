// Deadly Attack
// UVa ID: 11676
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double twoPi = 2.0 * pi;
double wallX, wallY, wallR;
double cannonX, cannonY;
double distanceToCenter, centerAngle;

// 计算某个方向上射线穿过圆的面积微元函数
double getValue(double angle) {
    double delta = angle - centerAngle;
    double projection = distanceToCenter * cos(delta);
    double discriminant = wallR * wallR - distanceToCenter * distanceToCenter * sin(delta) * sin(delta);
    if (projection <= 0.0 || discriminant <= 0.0)
        return 0.0;
    return 2.0 * projection * sqrt(discriminant);
}

double getSimpson(double left, double right, double leftValue, double midValue, double rightValue) {
    return (right - left) * (leftValue + 4.0 * midValue + rightValue) / 6.0;
}

double integrate(double left, double right, double leftValue, double midValue, double rightValue, double whole, double limit) {
    double mid = (left + right) / 2.0;
    double leftMid = (left + mid) / 2.0;
    double rightMid = (mid + right) / 2.0;
    double leftMidValue = getValue(leftMid);
    double rightMidValue = getValue(rightMid);
    double leftPart = getSimpson(left, mid, leftValue, leftMidValue, midValue);
    double rightPart = getSimpson(mid, right, midValue, rightMidValue, rightValue);
    if (limit <= 0.0 || fabs(leftPart + rightPart - whole) <= 15.0 * 1e-10)
        return leftPart + rightPart + (leftPart + rightPart - whole) / 15.0;
    return integrate(left, mid, leftValue, leftMidValue, midValue, leftPart, limit - 1.0) + integrate(mid, right, midValue, rightMidValue, rightValue, rightPart, limit - 1.0);
}

double getArea(double left, double right) {
    if (left >= right)
        return 0.0;
    double mid = (left + right) / 2.0;
    double leftValue = getValue(left);
    double midValue = getValue(mid);
    double rightValue = getValue(right);
    double whole = getSimpson(left, right, leftValue, midValue, rightValue);
    return integrate(left, right, leftValue, midValue, rightValue, whole, 30.0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, r;
    int p, q, a, t;
    while (cin >> x >> y >> r) {
        if (x == 0 && y == 0 && r == 0)
            break;
        cin >> p >> q >> a >> t;
        wallX = x;
        wallY = y;
        wallR = r;
        cannonX = p;
        cannonY = q;
        double dx = wallX - cannonX;
        double dy = wallY - cannonY;
        distanceToCenter = hypot(dx, dy);
        centerAngle = atan2(dy, dx);
        double attackLeft = a * pi / 180.0 - t * pi / 360.0;
        double attackRight = a * pi / 180.0 + t * pi / 360.0;
        double hitHalfAngle = asin(wallR / distanceToCenter);
        double area = 0.0;
        for (int k = -3; k <= 3; k++) {
            double hitLeft = centerAngle - hitHalfAngle + k * twoPi;
            double hitRight = centerAngle + hitHalfAngle + k * twoPi;
            double left = max(attackLeft, hitLeft);
            double right = min(attackRight, hitRight);
            area += getArea(left, right);
        }
        cout << fixed << setprecision(1) << area << '\n';
    }
    return 0;
}
