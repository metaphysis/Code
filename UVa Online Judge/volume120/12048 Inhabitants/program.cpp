// Inhabitants
// UVa ID: 12048
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

bool onSegment(const Point& p, const Point& a, const Point& b) {
    if (cross(b - a, p - a) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<Point> poly(n);
        for (int i = 0; i < n; ++i) cin >> poly[i].x >> poly[i].y;

        int Q;
        cin >> Q;

        while (Q--) {
            Point p;
            cin >> p.x >> p.y;

            if (p.x == poly[0].x && p.y == poly[0].y) {
                cout << 'y' << '\n';
                continue;
            }

            long long c1 = cross(poly[1] - poly[0], p - poly[0]);
            long long c2 = cross(poly[n - 1] - poly[0], p - poly[0]);

            if (c1 < 0 || c2 > 0) {
                cout << 'n' << '\n';
                continue;
            }

            if (c1 == 0) {
                cout << (onSegment(p, poly[0], poly[1]) ? 'y' : 'n') << '\n';
                continue;
            }

            if (c2 == 0) {
                cout << (onSegment(p, poly[0], poly[n - 1]) ? 'y' : 'n') << '\n';
                continue;
            }

            // 二分查找最大的 i (1 <= i <= n-2) 使得 cross(poly[i]-poly[0], p-poly[0]) >= 0
            int l = 1, r = n - 2;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (cross(poly[mid] - poly[0], p - poly[0]) >= 0) l = mid;
                else r = mid - 1;
            }
            int i = l;

            // 检查点是否在三角形 (poly[0], poly[i], poly[i+1]) 内
            if (cross(poly[i + 1] - poly[i], p - poly[i]) >= 0)
                cout << 'y' << '\n';
            else
                cout << 'n' << '\n';
        }
    }

    return 0;
}
