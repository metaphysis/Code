// Sultan and Khairun Shundori 
// UVa ID: 11612
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163250814

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    Point castle;
    while (cin >> n, n) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].idx = i;
        }
        castle = pts[0];
        bool collinear = true;
        int dx0 = pts[1].x - castle.x, dy0 = pts[1].y - castle.y;
        for (size_t i = 2; i < pts.size(); i++) {
            int dx = pts[i].x - castle.x, dy = pts[i].y - castle.y;
            if (1LL * dx0 * dy - 1LL * dy0 * dx != 0) {
                collinear = false;
                break;
            }
        }
        if (collinear) {
            cout << "no solution\n";
            continue;
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
        others.push_back(baseIdx);
        for (int i = 0; i < others.size(); i++)
            if (others[i] == 0) {
                baseIdx = i;
                break;
            }
        cout << "0";
        int size = others.size();
        for (int i = 1; i < size; i++) cout << ' ' << others[(baseIdx + i) % size];
        cout << " 0\n";
    }
    return 0;
}
