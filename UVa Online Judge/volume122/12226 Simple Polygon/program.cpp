// Simple Polygon
// UVa ID: 12226
// Verdict: Accepted
// Submission Date: 2026-07-21
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].idx = i;
        }
        int baseIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (pts[i].y < pts[baseIdx].y || (pts[i].y == pts[baseIdx].y && pts[i].x < pts[baseIdx].x))
                baseIdx = i;
        }
        Point base = pts[baseIdx];
        vector<int> others;
        for (int i = 0; i < n; ++i)
            if (i != baseIdx) others.push_back(i);
        auto half = [&](const Point& p) -> int {
            return (p.y > base.y || (p.y == base.y && p.x > base.x)) ? 0 : 1;
        };
        sort(others.begin(), others.end(), [&](int i, int j) {
            const Point &a = pts[i], &b = pts[j];
            int ha = half(a), hb = half(b);
            if (ha != hb) return ha < hb;
            long long cross = 1LL * (a.x - base.x) * (b.y - base.y) - 1LL * (a.y - base.y) * (b.x - base.x);
            if (cross != 0) return cross > 0;
            long long da = 1LL * (a.x - base.x) * (a.x - base.x) + 1LL * (a.y - base.y) * (a.y - base.y);
            long long db = 1LL * (b.x - base.x) * (b.x - base.x) + 1LL * (b.y - base.y) * (b.y - base.y);
            return da < db;
        });
        int m = others.size();
        if (m > 1) {
            int last = others[m - 1];
            int pos = m - 2;
            while (pos >= 0) {
                int cur = others[pos];
                long long cross = 1LL * (pts[cur].x - base.x) * (pts[last].y - base.y) - 1LL * (pts[cur].y - base.y) * (pts[last].x - base.x);
                if (cross != 0) break;
                --pos;
            }
            if (pos + 1 < m - 1) {
                reverse(others.begin() + pos + 1, others.end());
            }
        }
        cout << baseIdx;
        for (int idx : others) cout << ' ' << idx;
        cout << '\n';
    }
    return 0;
}
