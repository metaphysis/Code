// Cool Points
// UVa ID: 11355
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

// 计算点 (x, y) 的极角 [0, 2*PI)
double getAngle(double x, double y) {
    double angle = atan2(y, x);
    if (angle < 0) angle += 2 * PI;
    return angle;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, R; cin >> N >> R;
        vector<pair<double, double>> segs;
        for (int i = 0; i < N; ++i) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            double a1 = getAngle(x1, y1);
            double a2 = getAngle(x2, y2);
            double diff = fabs(a1 - a2);
            if (diff < EPS) continue; // 忽略退化为点的线段
            if (a1 > a2) swap(a1, a2);
            if (diff < PI) segs.emplace_back(a1, a2);
            else {
                segs.emplace_back(0, a1);
                segs.emplace_back(a2, 2 * PI);
            }
        }
        // 合并区间
        vector<pair<double, double>> merged;
        sort(segs.begin(), segs.end());
        for (auto& seg : segs) {
            if (merged.empty() || seg.first > merged.back().second + EPS)
                merged.push_back(seg);
            else merged.back().second = max(merged.back().second, seg.second);
        }
        // 计算总阻挡角度
        double blocked = 0;
        for (auto& seg : merged) blocked += seg.second - seg.first;
        double cool = 2 * PI - blocked;
        double percentage = (cool / (2 * PI)) * 100.0;
        printf("Case %d: %.2lf%%\n", t, percentage);
    }
    return 0;
}
