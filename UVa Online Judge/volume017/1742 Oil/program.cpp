// Oil
// UVa ID: 1742
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.870s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Segment {
    long long l, r, y, w;
};

struct Point {
    long long x, y;
};

struct Event {
    double pos;
    long long delta;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<Segment> segs(n);
        vector<Point> pts;
        for (int i = 0; i < n; ++i) {
            long long x0, x1, y;
            cin >> x0 >> x1 >> y;
            if (x0 > x1) swap(x0, x1);
            segs[i].l = x0;
            segs[i].r = x1;
            segs[i].y = y;
            segs[i].w = x1 - x0;
            pts.push_back({x0, y});
            pts.push_back({x1, y});
        }

        long long ans = 0;

        // 枚举所有端点作为必经点
        for (const auto &p : pts) {
            long long xp = p.x, yp = p.y;
            long long constWeight = 0;
            vector<Event> events;

            for (const auto &seg : segs) {
                if (seg.y == yp) {
                    // 若点 P 就在该线段上，则任何非水平直线都会穿过它
                    if (xp >= seg.l && xp <= seg.r)
                        constWeight += seg.w;
                } else {
                    long long d = seg.y - yp;          // 分母，可正可负
                    double a1 = (double)(seg.l - xp) / d;
                    double a2 = (double)(seg.r - xp) / d;
                    if (a1 > a2) swap(a1, a2);
                    events.push_back({a1, seg.w});
                    events.push_back({a2, -seg.w});
                }
            }

            // 按坐标排序，同坐标先加后减（正增量在前）
            sort(events.begin(), events.end(), [](const Event &e1, const Event &e2) {
                if (e1.pos != e2.pos) return e1.pos < e2.pos;
                return e1.delta > e2.delta;
            });

            long long cur = constWeight;
            ans = max(ans, cur);
            for (const auto &e : events) {
                cur += e.delta;
                ans = max(ans, cur);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
