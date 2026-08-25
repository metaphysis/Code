#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-12L;
const long double INF = 1e100L;

struct Point {
    long double x, y;
    Point operator + (const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator * (long double k) const { return {x * k, y * k}; }
};

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double polyArea(const vector<Point> &p) {
    long double s = 0;
    int n = p.size();
    for (int i = 0; i < n; i++)
        s += cross(p[i], p[(i + 1) % n]);
    return s / 2;
}

long double getMin(const vector<Point> &p, Point u) {
    long double v = INF;
    for (Point q : p)
        v = min(v, dot(q, u));
    return v;
}

long double getMax(const vector<Point> &p, Point u) {
    long double v = -INF;
    for (Point q : p)
        v = max(v, dot(q, u));
    return v;
}

bool update(long double a, long double b, long double &l, long double &r) {
    if (fabsl(a) < EPS)
        return b >= -EPS;
    long double t = -b / a;
    if (a > 0)
        l = max(l, t);
    else
        r = min(r, t);
    return l <= r + EPS;
}

bool getRange(const vector<Point> &a, const vector<Point> &b, Point sp, long double &l, long double &r) {
    vector<Point> all = a;
    all.insert(all.end(), b.begin(), b.end());
    for (int i = 0; i < (int)all.size(); i++) {
        Point e = all[(i + 1) % all.size()] - all[i];
        Point u = {-e.y, e.x};
        long double amin = getMin(a, u), amax = getMax(a, u);
        long double bmin = getMin(b, u), bmax = getMax(b, u);
        long double sv = dot(sp, u);
        if (!update(sv, bmax - amin, l, r))
            return false;
        if (!update(-sv, amax - bmin, l, r))
            return false;
    }
    return l <= r + EPS;
}

vector<Point> clipPoly(const vector<Point> &p, Point a, Point b, long double sg) {
    vector<Point> res;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        Point x = p[i], y = p[(i + 1) % n];
        long double cx = sg * cross(b - a, x - a);
        long double cy = sg * cross(b - a, y - a);
        bool ix = cx >= -EPS, iy = cy >= -EPS;
        if (ix && iy)
            res.push_back(y);
        else if (ix && !iy) {
            Point d = y - x;
            long double z = cross(b - a, a - x) / cross(b - a, d);
            res.push_back(x + d * z);
        } else if (!ix && iy) {
            Point d = y - x;
            long double z = cross(b - a, a - x) / cross(b - a, d);
            res.push_back(x + d * z);
            res.push_back(y);
        }
    }
    return res;
}

long double interArea(vector<Point> a, const vector<Point> &b, Point mv, long double t) {
    vector<Point> q = b;
    for (Point &p : q)
        p = p + mv * t;
    long double sg = polyArea(q) >= 0 ? 1 : -1;
    for (int i = 0; i < (int)q.size(); i++) {
        if (a.empty())
            return 0;
        a = clipPoly(a, q[i], q[(i + 1) % q.size()], sg);
    }
    if (a.size() < 3)
        return 0;
    return fabsl(polyArea(a));
}

void solve() {
    int n, m;
    while (cin >> n) {
        vector<Point> a(n);
        for (Point &p : a)
            cin >> p.x >> p.y;
        Point va;
        cin >> va.x >> va.y;
        cin >> m;
        vector<Point> b(m);
        for (Point &p : b)
            cin >> p.x >> p.y;
        Point vb;
        cin >> vb.x >> vb.y;
        Point mv = vb - va;
        long double left = 0, right = INF;
        if (!getRange(a, b, mv, left, right) || right <= EPS) {
            cout << "never\n";
            continue;
        }
        if (right > 1e50L)
            right = left + 100000;
        if (fabsl(mv.x) < EPS && fabsl(mv.y) < EPS) {
            cout << "never\n";
            continue;
        }
        long double lo = left, hi = right;
        for (int i = 0; i < 120; i++) {
            long double x = (2 * lo + hi) / 3;
            long double y = (lo + 2 * hi) / 3;
            if (interArea(a, b, mv, x) < interArea(a, b, mv, y))
                lo = x;
            else
                hi = y;
        }
        long double best = interArea(a, b, mv, (lo + hi) / 2);
        if (best < 1e-10L) {
            cout << fixed << setprecision(6) << (double)left << '\n';
            continue;
        }
        long double l = left, r = (lo + hi) / 2;
        for (int i = 0; i < 100; i++) {
            long double mid = (l + r) / 2;
            if (interArea(a, b, mv, mid) + 1e-9L >= best)
                r = mid;
            else
                l = mid;
        }
        cout << fixed << setprecision(6) << (double)r << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
