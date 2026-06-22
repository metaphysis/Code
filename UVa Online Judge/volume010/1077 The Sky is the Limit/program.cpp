// The Sky is the Limit
// UVa ID: 1077
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Segment {
    double x1, y1, x2, y2; // 保证 x1 < x2
    double getY(double x) const {
        if (x < x1 - EPS || x > x2 + EPS) return -1e100;
        double t = (x - x1) / (x2 - x1);
        return y1 + t * (y2 - y1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, caseNo = 0;
    while (cin >> N && N) {
        ++caseNo;
        vector<Segment> segs;
        vector<double> xs;

        for (int i = 0; i < N; ++i) {
            double X, H, B;
            cin >> X >> H >> B;
            double L = X - B / 2.0;
            double R = X + B / 2.0;
            // 左斜边 (L,0) -> (X,H)
            segs.push_back({L, 0.0, X, H});
            // 右斜边 (X,H) -> (R,0)
            segs.push_back({X, H, R, 0.0});
            xs.push_back(L);
            xs.push_back(R);
            xs.push_back(X);
        }

        // 收集所有线段交点
        int m = segs.size();
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j) {
                double x1 = segs[i].x1, y1 = segs[i].y1;
                double x2 = segs[i].x2, y2 = segs[i].y2;
                double x3 = segs[j].x1, y3 = segs[j].y1;
                double x4 = segs[j].x2, y4 = segs[j].y2;

                double dx1 = x2 - x1, dy1 = y2 - y1;
                double dx2 = x4 - x3, dy2 = y4 - y3;
                double denom = dx1 * dy2 - dy1 * dx2;
                if (fabs(denom) < EPS) continue; // 平行或共线

                // 解参数 t1, t2
                double t1 = ((x3 - x1) * dy2 - (y3 - y1) * dx2) / denom;
                double t2 = ((x3 - x1) * dy1 - (y3 - y1) * dx1) / denom;
                if (t1 > -EPS && t1 < 1.0 + EPS && t2 > -EPS && t2 < 1.0 + EPS) {
                    double ix = x1 + t1 * dx1;
                    xs.push_back(ix);
                }
            }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end(), [](double a, double b) {
            return fabs(a - b) < EPS;
        }), xs.end());

        double totalLength = 0.0;
        for (size_t i = 0; i + 1 < xs.size(); ++i) {
            double xL = xs[i], xR = xs[i + 1];
            if (xR - xL < EPS) continue;
            double xMid = (xL + xR) / 2.0;

            int best = -1;
            double maxY = -1e100;
            for (int k = 0; k < m; ++k) {
                double y = segs[k].getY(xMid);
                if (y > maxY) { maxY = y; best = k; }
            }

            if (best == -1 || maxY < EPS) continue; // 无山覆盖

            double yL = segs[best].getY(xL);
            double yR = segs[best].getY(xR);
            double dx = xR - xL;
            double dy = yR - yL;
            totalLength += sqrt(dx * dx + dy * dy);
        }

        int ans = (int)(totalLength + 0.5 + EPS);
        cout << "Case " << caseNo << ": " << ans << "\n\n";
    }

    return 0;
}
