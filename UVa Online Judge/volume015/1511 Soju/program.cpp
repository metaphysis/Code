// Soju 
// UVa ID: 1511
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.180s
// https://blog.csdn.net/metaphysis/article/details/163260154

#include <bits/stdc++.h>
using namespace std;

struct Point { int x, y; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Point> I(n);
        for (int i = 0; i < n; ++i) cin >> I[i].x >> I[i].y;
        int m;
        cin >> m;
        vector<Point> P(m);
        for (int i = 0; i < m; ++i) cin >> P[i].x >> P[i].y;
        sort(I.begin(), I.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
        vector<int> ySorted(n), prefMaxPlus(n), sufMaxMinus(n);
        for (int i = 0; i < n; ++i) {
            ySorted[i] = I[i].y;
            int val = I[i].x + I[i].y;
            prefMaxPlus[i] = (i == 0) ? val : max(prefMaxPlus[i - 1], val);
        }
        for (int i = n - 1; i >= 0; --i) {
            int val = I[i].x - I[i].y;
            sufMaxMinus[i] = (i == n - 1) ? val : max(sufMaxMinus[i + 1], val);
        }
        const int INF = 2e9;
        int ans = INF;
        for (const auto& p : P) {
            int xp = p.x, yp = p.y;
            int idx = upper_bound(ySorted.begin(), ySorted.end(), yp) - ySorted.begin() - 1;
            if (idx >= 0) ans = min(ans, (xp + yp) - prefMaxPlus[idx]);
            int idx2 = upper_bound(ySorted.begin(), ySorted.end(), yp) - ySorted.begin();
            if (idx2 < n) ans = min(ans, (xp - yp) - sufMaxMinus[idx2]);
        }
        cout << ans << '\n';
    }
    return 0;
}
