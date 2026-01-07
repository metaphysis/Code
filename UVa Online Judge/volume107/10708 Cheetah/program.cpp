// Cheetah
// UVa ID: 10708
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        double cx, cy, px, py, pDeg, u, v, l;
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &cx, &cy, &px, &py, &pDeg, &u, &v, &l);
        
        double pRad = pDeg * PI / 180.0;
        double dx = px - cx;
        double dy = py - cy;
        
        double a = v * v - u * u;
        double b = -2.0 * u * (dx * cos(pRad) + dy * sin(pRad));
        double c = -(dx * dx + dy * dy);
        
        double t1 = 1e18, t2 = 1e18;
        bool hasSolution = false;
        
        if (fabs(a) < EPS) { // 二次项为零，退化为一次方程
            if (fabs(b) > EPS) {
                double t = -c / b;
                if (t > EPS) t1 = t;
            }
        } else {
            double disc = b * b - 4.0 * a * c;
            if (disc >= -EPS) {
                disc = max(0.0, disc);
                double sqrtDisc = sqrt(disc);
                t1 = (-b + sqrtDisc) / (2.0 * a);
                t2 = (-b - sqrtDisc) / (2.0 * a);
            }
        }
        
        double t = 1e18;
        if (t1 > EPS && t1 < t) t = t1;
        if (t2 > EPS && t2 < t) t = t2;
        
        if (t > l + EPS || t > 1e17) {
            printf("sorry, buddy\n");
            continue;
        }
        
        // 计算捕捉点坐标
        double x = px + u * t * cos(pRad);
        double y = py + u * t * sin(pRad);
        
        // 计算猎豹角度
        double cosC = (dx + u * t * cos(pRad)) / (v * t);
        double sinC = (dy + u * t * sin(pRad)) / (v * t);
        double cRad = atan2(sinC, cosC);
        double cDeg = cRad * 180.0 / PI;
        if (cDeg < 0) cDeg += 360.0;
        
        printf("%.2lf %.2lf %.2lf %.2lf\n", cDeg, t, x, y);
    }
    return 0;
}
