// Make Polygon
// UVa ID: 10445
// Verdict: Accepted
// Submission Date: 2023-04-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
} ps[32];

const double PI = acos(-1);
int norm(point a) { return a.x * a.x + a.y * a.y; }
double abs(point a) { return sqrt(norm(a)); }
int dot(point a, point b) { return a.x * b.x + a.y * b.y; }
int cross(point a, point b) { return a.x * b.y - b.x * a.y; }

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    cout << fixed << setprecision(6);
    while (cin >> n, n >= 3) {
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        int area = 0;
        for (int i = 0; i < n; i++)
            area += ps[i].x * ps[(i + 1) % n].y - ps[(i + 1) % n].x * ps[i].y;
        if (area < 0) reverse(ps, ps + n);
        double mina = 360, maxa = 0;
        for (int i = 0; i < n; i++) {
            point a = ps[i], b = ps[(i + 1) % n], c = ps[(i + 2) % n];
            double alpha = acos(1.0 * dot(a - b, c - b) / abs(a - b) / abs(c - b)) / PI * 180;
            if (cross(b - a, c - a) < 0) alpha = 360 - alpha;
            mina = min(mina, alpha);
            maxa = max(maxa, alpha);
        }
        cout << mina << ' ' << maxa << '\n';
    }
    return 0;
}
