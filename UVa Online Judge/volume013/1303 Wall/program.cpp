// Wall
// UVa ID: 1303
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
};

int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point>& P) {
    int n = P.size(), k = 0;
    if (n <= 1) return P;
    sort(P.begin(), P.end());
    vector<Point> H(2 * n);
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k-1);
    return H;
}

double dist(const Point& a, const Point& b) { return hypot(a.x - b.x, a.y - b.y); }

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int N, L;
        cin >> N >> L;
        vector<Point> points(N);
        for (int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;
        vector<Point> hull = convexHull(points);
        double perimeter = 0.0;
        int m = hull.size();
        for (int i = 0; i < m; i++) perimeter += dist(hull[i], hull[(i+1) % m]);
        int result = perimeter + 2 * M_PI * L + 0.5;
        cout << result << (T ? "\n\n" : "\n");
    }
    return 0;
}
