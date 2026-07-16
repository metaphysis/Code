// The Four in One Stadium
// UVa ID: 10322
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    const double PI = acos(-1.0);
    const double EPS = 1e-10;
    double Ar1, Ar2, Ar3;
    cout << fixed << setprecision(10);
    while (cin >> Ar1 >> Ar2 >> Ar3) {
        double r1 = sqrt(Ar1 / PI);
        double r2 = sqrt(Ar2 / PI);
        double r3 = sqrt(Ar3 / PI);
        double r[3] = {r1, r2, r3};

        // 计算三个圆心坐标
        double d12 = r1 + r2;
        double x3 = (d12 * d12 + (r1 - r2) * (r1 + r2 + 2 * r3)) / (2 * d12);
        double y3 = sqrt((r1 + r3) * (r1 + r3) - x3 * x3);
        double Ox[3] = {0.0, d12, x3};
        double Oy[3] = {0.0, 0.0, y3};

        // 计算记分板半径 Sr
        double k1 = 1.0 / r1, k2 = 1.0 / r2, k3 = 1.0 / r3;
        double S = k1 + k2 + k3;
        double D = k1 * k2 + k2 * k3 + k3 * k1;
        double sqrtD = sqrt(D);
        double Sr = 1.0 / (S + 2.0 * sqrtD);

        // 计算中立区面积 An
        double p12x = r1, p12y = 0.0;
        double p13x = x3 * r1 / (r1 + r3);
        double p13y = y3 * r1 / (r1 + r3);
        double p23x = d12 + (r2 / (r2 + r3)) * (x3 - d12);
        double p23y = (r2 / (r2 + r3)) * y3;
        double v1x = p13x - p12x, v1y = p13y - p12y;
        double v2x = p23x - p12x, v2y = p23y - p12y;
        double An = 0.5 * fabs(v1x * v2y - v1y * v2x);

        // 计算大圆半径 R，枚举与哪两个小圆相切
        double R = 1e100;
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                int k = 3 - i - j;
                double Rcur = r[i] + r[j];
                double t = r[j] / (r[i] + r[j]); // 圆心在 O_iO_j 上，距 O_i 为 r[j]
                double cx = Ox[i] + t * (Ox[j] - Ox[i]);
                double cy = Oy[i] + t * (Oy[j] - Oy[i]);
                double dx = Ox[k] - cx;
                double dy = Oy[k] - cy;
                double dist = sqrt(dx * dx + dy * dy);
                if (dist + r[k] <= Rcur + EPS)
                    R = min(R, Rcur);
            }
        }
        // 若无可行方案（如三圆相等），用笛卡尔定理
        if (R > 1e90) {
            double kNeg = S - 2.0 * sqrtD;
            R = 1.0 / fabs(kNeg);
        }
        cout << R << " " << Sr << " " << An << "\n";
    }
    return 0;
}
