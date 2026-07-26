// Dome of Circus
// UVa ID: 1473
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.170s
// https://blog.csdn.net/metaphysis/article/details/163173899

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double rho;  // 到z轴的距离
    double z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<Point> pts;
        double zMax = 0.0;
        for (int i = 0; i < n; ++i) {
            double x, y, z;
            cin >> x >> y >> z;
            double rho = sqrt(x * x + y * y);
            pts.push_back({rho, z});
            if (z > zMax) zMax = z;
        }
        // 计算 F(h) = max_i { rho_i^2 * h^3 / (h - z_i)^2 }
        auto F = [&](double h) -> double {
            double maxVal = 0.0;
            for (const auto &p : pts) {
                if (p.rho == 0.0) continue;
                double val = p.rho * p.rho * h * h * h / ((h - p.z) * (h - p.z));
                if (val > maxVal) maxVal = val;
            }
            return maxVal;
        };
        // 三分搜索，区间 (zMax, 3*zMax]
        double lo = zMax + 1e-9;
        double hi = 3.0 * zMax;
        // 若 hi <= lo（仅当 zMax 极小时），适当调整
        if (hi <= lo) hi = lo + 1.0;
        for (int iter = 0; iter < 100; ++iter) {
            double m1 = lo + (hi - lo) / 3.0;
            double m2 = hi - (hi - lo) / 3.0;
            if (F(m1) < F(m2)) hi = m2;
            else lo = m1;
        }
        double h = (lo + hi) / 2.0;
        // 计算对应的 r
        double r = 0.0;
        for (const auto &p : pts) {
            if (p.rho == 0.0) continue;
            double val = p.rho * h / (h - p.z);
            if (val > r) r = val;
        }
        cout << fixed << setprecision(3) << h << ' ' << r << '\n';
    }
    return 0;
}
