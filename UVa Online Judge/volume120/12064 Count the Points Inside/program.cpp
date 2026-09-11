// Count the Points Inside
// UVa ID: 12064
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseNo = 1;
    int axInt, ayInt, bxInt, byInt, n, q;
    while (scanf("%d %d %d %d %d %d", &axInt, &ayInt, &bxInt, &byInt, &n, &q) == 6) {
        if (n == 0 && q == 0) break;
        double ax = axInt, ay = ayInt, bx = bxInt, by = byInt;
        vector<double> px(n + 1), py(n + 1);
        for (int i = 1; i <= n; ++i) { int xi, yi; scanf("%d %d", &xi, &yi); px[i] = xi; py[i] = yi; }
        printf("Case %d:\n", caseNo++);
        for (int qi = 0; qi < q; ++qi) {
            int sc; scanf("%d", &sc);
            double cx = px[sc], cy = py[sc];
            double cross = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
            if (fabs(cross) < 1e-12) { printf("Impossible\n"); continue; }
            double den = 2.0 * cross;
            double uxNum = (ax * ax + ay * ay) * (by - cy)
                         + (bx * bx + by * by) * (cy - ay)
                         + (cx * cx + cy * cy) * (ay - by);
            double uyNum = (ax * ax + ay * ay) * (cx - bx)
                         + (bx * bx + by * by) * (ax - cx)
                         + (cx * cx + cy * cy) * (bx - ax);
            double ux = uxNum / den;
            double uy = uyNum / den;
            double rsq = (ax - ux) * (ax - ux) + (ay - uy) * (ay - uy);
            if (rsq > 1e10) { printf("Impossible\n"); continue; }
            int cnt = 3;
            const double eps = 1e-9;
            for (int i = 1; i <= n; ++i) {
                if (i == sc) continue;
                double dx = px[i] - ux;
                double dy = py[i] - uy;
                if (dx * dx + dy * dy <= rsq + eps) ++cnt;
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}
