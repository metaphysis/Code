// Fence
// UVa ID: 667
// Verdict: Accepted
// Submission Date: 2026-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double TWO_PI = 2.0 * PI;
const double EPS = 1e-12;

struct Point {
    double x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    for (int ds = 0; ds < M; ++ds) {
        double k, h;
        int N;
        cin >> k >> h >> N;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;

        vector<pair<double, double>> intervals;
        for (int i = 0; i < N; ++i) {
            int j = (i + 1) % N;
            double theta1 = atan2(pts[i].y, pts[i].x);
            double theta2 = atan2(pts[j].y, pts[j].x);
            if (theta1 < 0) theta1 += TWO_PI;
            if (theta2 < 0) theta2 += TWO_PI;

            double diff = theta2 - theta1;
            if (diff < 0) diff += TWO_PI;
            // 线段张角小于 π
            if (diff > PI) {
                swap(theta1, theta2);
                diff = TWO_PI - diff;
            }
            double start = theta1;
            double end = theta1 + diff;
            if (end <= TWO_PI + EPS) {
                intervals.push_back({start, min(end, TWO_PI)});
            } else {
                intervals.push_back({start, TWO_PI});
                intervals.push_back({0.0, end - TWO_PI});
            }
        }

        // 合并区间
        sort(intervals.begin(), intervals.end());
        double total = 0.0;
        double curL = -1.0, curR = -1.0;
        for (auto &iv : intervals) {
            double l = iv.first, r = iv.second;
            if (curL < 0) {
                curL = l; curR = r;
            } else if (l <= curR + EPS) {
                curR = max(curR, r);
            } else {
                total += curR - curL;
                curL = l;
                curR = r;
            }
        }
        if (curL >= 0) total += curR - curL;
        if (TWO_PI - total < EPS) total = TWO_PI;

        double ans = k * h * total;
        cout << fixed << setprecision(2) << ans;
        if (ds < M - 1) cout << "\n\n";
        else cout << "\n";
    }
    return 0;
}
