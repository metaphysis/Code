// Isosceles Triangles
// UVa ID: 1816
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) scanf("%lf %lf", &pts[i].x, &pts[i].y);
        int ans = 0;
        const double EPS = 1e-6;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                for (int k = j + 1; k < N; ++k) {
                    // 叉积判断共线
                    double cross = (pts[j].x - pts[i].x) * (pts[k].y - pts[i].y)
                                 - (pts[j].y - pts[i].y) * (pts[k].x - pts[i].x);
                    if (fabs(cross) < EPS) continue;
                    double d12 = dist(pts[i], pts[j]);
                    double d13 = dist(pts[i], pts[k]);
                    double d23 = dist(pts[j], pts[k]);
                    int eq = 0;
                    if (fabs(d12 - d13) < EPS) ++eq;
                    if (fabs(d12 - d23) < EPS) ++eq;
                    if (fabs(d13 - d23) < EPS) ++eq;
                    if (eq == 1) ++ans;
                }
        printf("%d\n", ans);
    }
    return 0;
}
