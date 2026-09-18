#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;
const long double pi = acosl(-1.0L);

struct Point {
    long double x, y;
    Point operator+(const Point &p) const {
        return {x + p.x, y + p.y};
    }

    Point operator-(const Point &p) const {
        return {x - p.x, y - p.y};
    }

    Point operator*(long double k) const {
        return {x * k, y * k};
    }
};

struct Segment {
    Point a, b;
};

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

void addAngle(Point p, vector<long double> &angles) {
    if (fabsl(p.x) + fabsl(p.y) < eps) return;
    long double angle = atan2l(p.y, p.x);
    if (angle < 0) angle += 2 * pi;
    angles.push_back(angle);
}

void addIntersection(const Segment &s, const Segment &t, vector<long double> &angles) {
    Point v = s.b - s.a, w = t.b - t.a, delta = t.a - s.a;
    long double den = cross(v, w);
    if (fabsl(den) < eps) return;
    long double u = cross(delta, w) / den, z = cross(delta, v) / den;
    if (u < -eps || u > 1 + eps || z < -eps || z > 1 + eps) return;
    addAngle(s.a + v * u, angles);
}

long double rayDistance(Point dir, const Segment &seg) {
    Point v = seg.b - seg.a;
    long double den = cross(dir, v);
    if (fabsl(den) < eps) return -1;
    long double dist = cross(seg.a, v) / den, pos = cross(seg.a, dir) / den;
    if (dist <= eps || pos < -eps || pos > 1 + eps) return -1;
    return dist;
}

Point lineIntersection(Point dir, const Segment &seg) {
    Point v = seg.b - seg.a;
    return dir * (cross(seg.a, v) / cross(dir, v));
}

bool isInside(Point p, const vector<Point> &poly) {
    bool inside = false;
    int n = (int)poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[j], b = poly[i];
        if ((a.y > p.y) != (b.y > p.y)) {
            long double hitX = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (hitX > p.x) inside = !inside;
        }
    }
    return inside;
}

long double polygonArea(const vector<Point> &poly) {
    long double area = 0;
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) area += cross(poly[i], poly[(i + 1) % n]);
    return fabsl(area) / 2;
}

long double visibleArea(const vector<Point> &poly, const vector<Segment> &segs) {
    vector<long double> angles, events;
    int k = (int)segs.size();
    angles.push_back(0);
    angles.push_back(2 * pi);
    for (int i = 0; i < k; ++i) {
        addAngle(segs[i].a, angles);
        addAngle(segs[i].b, angles);
        for (int j = 0; j < i; ++j) addIntersection(segs[i], segs[j], angles);
    }
    sort(angles.begin(), angles.end());
    for (long double angle : angles) {
        if (events.empty() || angle - events.back() > eps) events.push_back(angle);
    }
    long double area = 0;
    for (int i = 0; i + 1 < (int)events.size(); ++i) {
        long double left = events[i], right = events[i + 1], mid = (left + right) / 2, bestDist = 1e100L;
        Point dir = {cosl(mid), sinl(mid)};
        int bestId = -1;
        for (int j = 0; j < k; ++j) {
            long double dist = rayDistance(dir, segs[j]);
            if (dist > 0 && dist < bestDist) {
                bestDist = dist;
                bestId = j;
            }
        }
        if (bestId == -1) continue;
        if (!isInside(dir * (bestDist / 2), poly)) continue;
        Point leftDir = {cosl(left), sinl(left)}, rightDir = {cosl(right), sinl(right)};
        Point p = lineIntersection(leftDir, segs[bestId]), q = lineIntersection(rightDir, segs[bestId]);
        area += fabsl(cross(p, q)) / 2;
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        Point source;
        cin >> source.x >> source.y;
        vector<Point> poly(n);
        vector<Segment> segs;
        for (int i = 0; i < n; ++i) {
            cin >> poly[i].x >> poly[i].y;
            poly[i] = poly[i] - source;
        }
        for (int i = 0; i < n; ++i) segs.push_back({poly[i], poly[(i + 1) % n]});
        for (int i = 0; i < m; ++i) {
            Point a, b;
            cin >> a.x >> a.y >> b.x >> b.y;
            segs.push_back({a - source, b - source});
        }
        long double totalArea = polygonArea(poly), litArea = visibleArea(poly, segs);
        long double percent = max(0.0L, min(100.0L, litArea / totalArea * 100));
        long long rounded = (long long)floorl(percent * 1000 + 0.5L + 1e-9L);
        cout << rounded / 1000 << '.' << setfill('0') << setw(3) << rounded % 1000 << "%\n";
    }
    return 0;
}
