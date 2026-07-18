// Translation or Rotation
// UVa ID: 10760
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

bool isZero(double x) {
    return fabs(x) < EPS;
}

int main() {
    double ax, ay, apx, apy, bx, by, bpx, bpy;
    while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &ax, &ay, &apx, &apy, &bx, &by, &bpx, &bpy) == 8) {
        if (isZero(ax) && isZero(ay) && isZero(apx) && isZero(apy) &&
            isZero(bx) && isZero(by) && isZero(bpx) && isZero(bpy)) break;
        double vx = bx - ax, vy = by - ay;
        double vpx = bpx - apx, vpy = bpy - apy;
        double tx = apx - ax, ty = apy - ay;
        if (fabs(vx - vpx) < EPS && fabs(vy - vpy) < EPS) {
            if (fabs(tx) < EPS && fabs(ty) < EPS) printf("No move.\n");
            else printf("Translation by vector <%.1f,%.1f>.\n", tx, ty);
        } else {
            double cross = vx * vpy - vy * vpx;
            double dot = vx * vpx + vy * vpy;
            double angleRad = atan2(cross, dot);
            double angleDeg = angleRad * 180.0 / acos(-1.0);
            if (angleDeg < 0.0) angleDeg += 360.0;
            double cosA = cos(angleRad), sinA = sin(angleRad);
            double d_x = apx - (cosA * ax - sinA * ay);
            double d_y = apy - (sinA * ax + cosA * ay);
            double det = (1.0 - cosA) * (1.0 - cosA) + sinA * sinA;
            double c_x = ((1.0 - cosA) * d_x - sinA * d_y) / det;
            double c_y = (sinA * d_x + (1.0 - cosA) * d_y) / det;
            if (fabs(c_x) < EPS) c_x = 0.0;
            if (fabs(c_y) < EPS) c_y = 0.0;
            printf("Rotation around (%.1f,%.1f) by %.1f degrees counterclockwise.\n", c_x, c_y, angleDeg);
        }
    }
    return 0;
}
