// Point of View in Flatland
// UVa ID: 11037
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    double x0, y0, r0, x1, y1, r1, x2, y2, r2;
    while (cin >> x0 >> y0 >> r0 >> x1 >> y1 >> r1 >> x2 >> y2 >> r2) {
        if (fabs(x0) < EPS && fabs(y0) < EPS && fabs(r0) < EPS &&
            fabs(x1) < EPS && fabs(y1) < EPS && fabs(r1) < EPS &&
            fabs(x2) < EPS && fabs(y2) < EPS && fabs(r2) < EPS)
            break;

        double A1 = 2.0 * (x1 - x0);
        double B1 = 2.0 * (y1 - y0);
        double C1 = x0 * x0 + y0 * y0 - x1 * x1 - y1 * y1;
        double D1 = r1 * r1 - r0 * r0;

        double A2 = 2.0 * (x2 - x0);
        double B2 = 2.0 * (y2 - y0);
        double C2 = x0 * x0 + y0 * y0 - x2 * x2 - y2 * y2;
        double D2 = r2 * r2 - r0 * r0;

        double det = A1 * B2 - A2 * B1;
        if (fabs(det) < EPS) continue;

        double Xc = C2 * B1 - C1 * B2;
        double Xd = D2 * B1 - D1 * B2;
        double Yc = A2 * C1 - A1 * C2;
        double Yd = A2 * D1 - A1 * D2;

        double p = Xc - x0 * det;
        double q = Yc - y0 * det;
        double a = Xd * Xd + Yd * Yd;
        double b = 2.0 * (p * Xd + q * Yd) - r0 * r0 * det * det;
        double c = p * p + q * q;

        vector<double> ts;
        if (fabs(a) < EPS) {
            if (fabs(b) > EPS) {
                double t = -c / b;
                ts.push_back(t);
            }
        } else {
            double delta = b * b - 4.0 * a * c;
            if (delta >= -EPS) {
                if (delta < 0) delta = 0;
                double sqrtD = sqrt(delta);
                double t1 = (-b - sqrtD) / (2.0 * a);
                double t2 = (-b + sqrtD) / (2.0 * a);
                ts.push_back(t1);
                ts.push_back(t2);
            }
        }

        bool found = false;
        double bestT = 1e100;
        double bestX = 0, bestY = 0;
        for (double t : ts) {
            if (t < 1.0 - EPS) continue;
            double x = (Xc + Xd * t) / det;
            double y = (Yc + Yd * t) / det;
            double d0 = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
            double d1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
            double d2 = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
            double lambda = sqrt(t);
            if (fabs(d0 / r0 - lambda) > 1e-6) continue;
            if (fabs(d1 / r1 - lambda) > 1e-6) continue;
            if (fabs(d2 / r2 - lambda) > 1e-6) continue;
            if (d0 < r0 - EPS || d1 < r1 - EPS || d2 < r2 - EPS) continue;
            if (t < bestT) {
                bestT = t;
                bestX = x;
                bestY = y;
                found = true;
            }
        }

        if (!found) {
            cout << "No solution\n";
        } else {
            printf("%.2f %.2f\n", bestX, bestY);
        }
    }
    return 0;
}
