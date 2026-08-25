#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;
const long double inf = 1e100L;

struct Point {
    long double x, y;
};

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double getLen(Point a, Point b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

bool onSeg(Point a, Point b, Point p) {
    if (fabsl(cross(a, b, p)) > eps)
        return false;
    return p.x >= min(a.x, b.x) - eps && p.x <= max(a.x, b.x) + eps && p.y >= min(a.y, b.y) - eps && p.y <= max(a.y, b.y) + eps;
}

bool pointIn(Point p, const vector<Point> &poly) {
    int n = poly.size();
    bool in = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (onSeg(poly[j], poly[i], p))
            return true;
        bool a = poly[i].y > p.y, b = poly[j].y > p.y;
        if (a != b) {
            long double x = poly[j].x + (poly[i].x - poly[j].x) * (p.y - poly[j].y) / (poly[i].y - poly[j].y);
            if (x > p.x)
                in = !in;
        }
    }
    return in;
}

bool isNear(int a, int b, int n) {
    return (a + 1) % n == b || (b + 1) % n == a;
}

bool valid(int a, int b, const vector<Point> &poly) {
    int n = poly.size();
    if (isNear(a, b, n))
        return true;
    Point p = poly[a], q = poly[b], r = {q.x - p.x, q.y - p.y};
    vector<long double> ts;
    ts.push_back(0.0L);
    ts.push_back(1.0L);
    for (int i = 0; i < n; i++) {
        if (i != a && i != b && onSeg(p, q, poly[i]))
            return false;
    }
    for (int i = 0; i < n; i++) {
        Point c = poly[i], d = poly[(i + 1) % n], s = {d.x - c.x, d.y - c.y};
        long double den = r.x * s.y - r.y * s.x;
        if (fabsl(den) <= eps) {
            if (onSeg(p, q, c)) {
                long double t = ((c.x - p.x) * r.x + (c.y - p.y) * r.y) / (r.x * r.x + r.y * r.y);
                ts.push_back(max(0.0L, min(1.0L, t)));
            }
            if (onSeg(p, q, d)) {
                long double t = ((d.x - p.x) * r.x + (d.y - p.y) * r.y) / (r.x * r.x + r.y * r.y);
                ts.push_back(max(0.0L, min(1.0L, t)));
            }
            continue;
        }
        Point w = {c.x - p.x, c.y - p.y};
        long double t = (w.x * s.y - w.y * s.x) / den;
        long double u = (w.x * r.y - w.y * r.x) / den;
        if (t >= -eps && t <= 1.0L + eps && u >= -eps && u <= 1.0L + eps)
            ts.push_back(max(0.0L, min(1.0L, t)));
    }
    sort(ts.begin(), ts.end());
    vector<long double> us;
    for (long double t : ts)
        if (us.empty() || fabsl(t - us.back()) > eps)
            us.push_back(t);
    for (int i = 0; i + 1 < (int)us.size(); i++) {
        if (us[i + 1] - us[i] <= eps)
            continue;
        long double t = (us[i] + us[i + 1]) * 0.5L;
        Point z = {p.x + r.x * t, p.y + r.y * t};
        if (!pointIn(z, poly))
            return false;
    }
    return true;
}

long double solve(const vector<Point> &poly) {
    int n = poly.size();
    vector<vector<bool> > vis(n, vector<bool>(n, false));
    vector<vector<long double> > len(n, vector<long double>(n, 0.0L));
    vector<vector<long double> > dp(n, vector<long double>(n, 0.0L));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            vis[i][j] = vis[j][i] = valid(i, j, poly);
            len[i][j] = len[j][i] = getLen(poly[i], poly[j]);
        }
    for (int gap = 2; gap < n; gap++) {
        for (int i = 0; i + gap < n; i++) {
            int j = i + gap;
            if (gap != n - 1 && !vis[i][j])
                continue;
            long double best = inf;
            for (int k = i + 1; k < j; k++) {
                if (!vis[i][k] || !vis[k][j])
                    continue;
                long double cur = dp[i][k] + dp[k][j];
                if (k != i + 1)
                    cur += len[i][k];
                if (k + 1 != j)
                    cur += len[k][j];
                best = min(best, cur);
            }
            dp[i][j] = best;
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, cas = 0;
    while (cin >> n) {
        vector<Point> poly(n);
        for (int i = 0; i < n; i++)
            cin >> poly[i].x >> poly[i].y;
        cout << "Case " << ++cas << ": " << fixed << setprecision(4) << (double)solve(poly) << '\n';
    }
    return 0;
}
