// Polygon Visibility
// UVa ID: 746
// Verdict: Accepted
// Submission Date: 2026-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    point(int a = 0, int b = 0) : x(a), y(b) {}
    point operator - (const point& o) const { return point(x - o.x, y - o.y); }
    point operator + (const point& o) const { return point(x + o.x, y + o.y); }
};

long long cross(point o, point a, point b) {
    return 1LL * (a.x - o.x) * (b.y - o.y) - 1LL * (a.y - o.y) * (b.x - o.x);
}

pair<int, int> internalTangent(vector<point>& A, vector<point>& B, int f) {
    int n = (int)A.size(), m = (int)B.size();
    int i = 0, j = 0, update;
    do {
        update = 0;
        while (f * cross(A[i], B[j], B[(j + m - 1) % m]) > 0 ||
               f * cross(A[i], B[j], B[(j + 1) % m]) > 0) {
            j = (j + 1) % m;
        }
        while (f * cross(B[j], A[i], A[(i + n - 1) % n]) > 0 ||
               f * cross(B[j], A[i], A[(i + 1) % n]) > 0) {
            i = (i + 1) % n;
            update = 1;
        }
    } while (update);
    if (f == 1 && cross(B[j], A[i], A[(i + 1) % n]) == 0) i = (i + 1) % n;
    if (f == -1 && cross(B[j], A[i], A[(i + n - 1) % n]) == 0) i = (i + n - 1) % n;
    return {i, j};
}

void toSlope(point p, point q) {
    int dx = q.x - p.x, dy = q.y - p.y;
    if (dx == 0) cout << "VERTICAL\n";
    else {
        double slope = (double)dy / dx;
        if (fabs(slope) < 1e-3) slope = 0.0;
        cout << fixed << setprecision(3) << slope << '\n';
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m, cases = 1;
    while (cin >> n >> m, n && m) {
        vector<point> A(n), B(m);
        for (int i = 0; i < n; ++i) cin >> A[i].x >> A[i].y;
        for (int i = 0; i < m; ++i) cin >> B[i].x >> B[i].y;
        auto [i1, j1] = internalTangent(A, B, 1);
        auto [i2, j2] = internalTangent(A, B, -1);
        cout << "Instance " << cases++ << ":\n";
        toSlope(A[i1], B[j1]);
        int now = i1;
        do {
            cout << A[now].x << " " << A[now].y << "\n";
            now = (now + 1) % n;
        } while (now != i2);
        cout << A[i2].x << " " << A[i2].y << "\n";
        toSlope(A[i2], B[j2]);
    }
    return 0;
}
