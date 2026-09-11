// Collision of Bacteria
// UVa ID: 11907
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

double distAtTime(const Rect& a, const Rect& b, double t, int r) {
    int px = max(b.x1 - a.x2, a.x1 - b.x2);
    int py = max(b.y1 - a.y2, a.y1 - b.y2);
    double dx = max(0.0, (double)px - 2.0 * r * t);
    double dy = max(0.0, (double)py - 2.0 * r * t);
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        cin >> n;
        vector<Rect> rects(n);
        for (int i = 0; i < n; ++i)
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        int r, d;
        cin >> r >> d;
        double ans = 1e9;
        bool zero = false;
        for (int i = 0; i < n && !zero; ++i)
            for (int j = i + 1; j < n; ++j) {
                if (distAtTime(rects[i], rects[j], 0.0, r) <= d + 1e-9) {
                    ans = 0.0;
                    zero = true;
                    break;
                }
                double low = 0.0, high = 1e9;
                for (int it = 0; it < 60; ++it) {
                    double mid = (low + high) / 2.0;
                    if (distAtTime(rects[i], rects[j], mid, r) <= d + 1e-9)
                        high = mid;
                    else
                        low = mid;
                }
                ans = min(ans, high);
            }
        cout << "Case " << caseNo << ": " << fixed << setprecision(3) << ans << "\n";
    }
    return 0;
}
