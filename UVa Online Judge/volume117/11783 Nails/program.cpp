// Nails
// UVa ID: 11783
// Verdict: Accepted
// Submission Date: 2023-04-08
// UVa Run Time: 0.140s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

double cp(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool pointInBox(point a, point b, point p) {
    return (p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) &&
        (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y));
}

struct segment {
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
} st[1010];

bool isIntersected(segment &s1, segment &s2) {
    double cp1 = cp(s1.p1, s1.p2, s2.p1), cp2 = cp(s1.p1, s1.p2, s2.p2);
    double cp3 = cp(s2.p1, s2.p2, s1.p1), cp4 = cp(s2.p1, s2.p2, s1.p2);
    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (fabs(cp1) <= EPSILON && s1.contains(s2.p1)) return true;
    if (fabs(cp2) <= EPSILON && s1.contains(s2.p2)) return true;
    if (fabs(cp3) <= EPSILON && s2.contains(s1.p1)) return true;
    if (fabs(cp4) <= EPSILON && s2.contains(s1.p2)) return true;
    return false;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, visited[1010];
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) {
            cin >> st[i].p1.x >> st[i].p1.y;
            cin >> st[i].p2.x >> st[i].p2.y;
            visited[i] = 0;
        }
        int r = 0;
        for (int i = 0; i < n; i++) {
            int crossed = 0;
            for (int j = i + 1; j < n; j++)
                if (isIntersected(st[i], st[j])) {
                    r++;
                    crossed = 1;
                    visited[j] = 1;
            }
            if (!crossed && !visited[i]) r += 2;
        }
        cout << r << '\n';
    }
    return 0;
}
