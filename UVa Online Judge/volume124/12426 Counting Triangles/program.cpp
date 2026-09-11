// Counting Triangles
// UVa ID: 12426
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long area2(const Point& a, const Point& b, const Point& c) {
    long long cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return cross >= 0 ? cross : -cross;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long K;
        cin >> N >> K;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
        long long K2 = 2 * K;
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N - 1; ++j) {
                int l = j + 1, r = N - 1;
                while (l < r) {
                    int mid = (l + r) / 2;
                    long long a1 = area2(pts[i], pts[j], pts[mid]);
                    long long a2 = area2(pts[i], pts[j], pts[mid + 1]);
                    if (a1 < a2) l = mid + 1;
                    else r = mid;
                }
                int peak = l;
                int leftLow = j + 1, leftHigh = peak;
                int leftBound = j;
                while (leftLow <= leftHigh) {
                    int mid = (leftLow + leftHigh) / 2;
                    if (area2(pts[i], pts[j], pts[mid]) <= K2) {
                        leftBound = mid;
                        leftLow = mid + 1;
                    } else {
                        leftHigh = mid - 1;
                    }
                }
                if (leftBound >= j + 1) ans += (long long)(leftBound - j);
                if (peak + 1 <= N - 1) {
                    int rightLow = peak + 1, rightHigh = N - 1;
                    int rightBound = N;
                    while (rightLow <= rightHigh) {
                        int mid = (rightLow + rightHigh) / 2;
                        if (area2(pts[i], pts[j], pts[mid]) <= K2) {
                            rightBound = mid;
                            rightHigh = mid - 1;
                        } else {
                            rightLow = mid + 1;
                        }
                    }
                    if (rightBound <= N - 1) ans += (long long)(N - rightBound);
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
