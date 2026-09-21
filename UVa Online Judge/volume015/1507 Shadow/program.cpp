#include <bits/stdc++.h>
using namespace std;

using ld = long double;

const ld eps = 1e-12L;
const ld pi = acosl(-1.0L);

struct Point {
    ld x, y;
};

struct Circle {
    Point c;
    ld r;
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator*(const Point &a, ld k) {
    return {a.x * k, a.y * k};
}

ld dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

ld cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

ld cross(const Point &a, const Point &b, const Point &c) {
    return cross(b - a, c - a);
}

ld length(const Point &a) {
    return sqrtl(dot(a, a));
}

ld normAngle(ld a) {
    while (a < 0) a += 2 * pi;
    while (a >= 2 * pi) a -= 2 * pi;
    return a;
}

vector<Point> getHull(vector<Point> p) {
    sort(p.begin(), p.end(), [](const Point &a, const Point &b) {
        if (fabsl(a.x - b.x) > eps) return a.x < b.x;
        return a.y < b.y;
    });
    vector<Point> q;
    for (const Point &pt : p) {
        if (q.empty() || length(pt - q.back()) > eps) q.push_back(pt);
    }
    int n = (int)q.size(), k = 0;
    if (n <= 1) return q;
    vector<Point> hull(2 * n);
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], q[i]) <= eps) k--;
        hull[k++] = q[i];
    }
    int lowSize = k;
    for (int i = n - 2; i >= 0; i--) {
        while (k > lowSize && cross(hull[k - 2], hull[k - 1], q[i]) <= eps) k--;
        hull[k++] = q[i];
    }
    hull.resize(k - 1);
    return hull;
}

bool insidePoly(const Point &p, const vector<Point> &poly) {
    bool inside = true;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) inside = inside && cross(poly[i], poly[(i + 1) % n], p) >= -eps;
    return inside;
}

void addAngleInterval(vector<pair<ld, ld>> &segs, ld mid, ld half) {
    ld left = normAngle(mid - half), right = normAngle(mid + half);
    if (left <= right) segs.push_back({left, right});
    else {
        segs.push_back({left, 2 * pi});
        segs.push_back({0, right});
    }
}

vector<pair<ld, ld>> mergeIntervals(vector<pair<ld, ld>> segs, ld left, ld right) {
    vector<pair<ld, ld>> valid, merged;
    for (auto seg : segs) {
        seg.first = max(seg.first, left);
        seg.second = min(seg.second, right);
        if (seg.first < seg.second - eps) valid.push_back(seg);
    }
    sort(valid.begin(), valid.end());
    for (auto seg : valid) {
        if (merged.empty() || seg.first > merged.back().second + eps) merged.push_back(seg);
        else merged.back().second = max(merged.back().second, seg.second);
    }
    return merged;
}

void addPolyCoveredAngles(const Circle &cir, const vector<Point> &poly, vector<pair<ld, ld>> &segs) {
    vector<ld> cuts = {0, 2 * pi};
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        Point s = poly[i] - cir.c, v = poly[(i + 1) % n] - poly[i];
        ld aa = dot(v, v), bb = 2 * dot(s, v), cc = dot(s, s) - cir.r * cir.r;
        ld delta = bb * bb - 4 * aa * cc;
        if (delta < -eps) continue;
        delta = max((ld)0, delta);
        ld root = sqrtl(delta), t1 = (-bb - root) / (2 * aa), t2 = (-bb + root) / (2 * aa);
        if (t1 >= -eps && t1 <= 1 + eps) {
            Point q = s + v * min((ld)1, max((ld)0, t1));
            cuts.push_back(normAngle(atan2l(q.y, q.x)));
        }
        if (t2 >= -eps && t2 <= 1 + eps && fabsl(t1 - t2) > eps) {
            Point q = s + v * min((ld)1, max((ld)0, t2));
            cuts.push_back(normAngle(atan2l(q.y, q.x)));
        }
    }
    sort(cuts.begin(), cuts.end());
    vector<ld> uniqueCuts;
    for (ld angle : cuts) {
        if (uniqueCuts.empty() || fabsl(angle - uniqueCuts.back()) > eps) uniqueCuts.push_back(angle);
    }
    for (int i = 0; i + 1 < (int)uniqueCuts.size(); i++) {
        ld left = uniqueCuts[i], right = uniqueCuts[i + 1], mid = (left + right) / 2;
        Point p = {cir.c.x + cir.r * cosl(mid), cir.c.y + cir.r * sinl(mid)};
        if (insidePoly(p, poly)) segs.push_back({left, right});
    }
}

ld getArcArea(const Circle &cir, ld left, ld right) {
    ld part1 = cir.r * cir.c.x * (sinl(right) - sinl(left));
    ld part2 = -cir.r * cir.c.y * (cosl(right) - cosl(left));
    ld part3 = cir.r * cir.r * (right - left);
    return (part1 + part2 + part3) / 2;
}

ld getCircleArea(int id, const vector<Circle> &circles, const vector<Point> &poly) {
    const Circle &cur = circles[id];
    vector<pair<ld, ld>> covered;
    bool full = false;
    int n = (int)circles.size();
    for (int j = 0; j < n; j++) {
        if (j == id) continue;
        Point diff = circles[j].c - cur.c;
        ld dis = length(diff), r1 = cur.r, r2 = circles[j].r;
        if (dis <= eps && fabsl(r1 - r2) <= eps) {
            if (id > j) full = true;
            continue;
        }
        if (dis + r1 <= r2 + eps) {
            full = true;
            continue;
        }
        if (dis >= r1 + r2 - eps) continue;
        if (dis <= fabsl(r1 - r2) + eps) continue;
        ld value = (dis * dis + r1 * r1 - r2 * r2) / (2 * dis * r1);
        value = min((ld)1, max((ld)-1, value));
        ld mid = atan2l(diff.y, diff.x), half = acosl(value);
        addAngleInterval(covered, mid, half);
    }
    if (full) return 0;
    if (poly.size() >= 3) addPolyCoveredAngles(cur, poly, covered);
    vector<pair<ld, ld>> merged = mergeIntervals(covered, 0, 2 * pi);
    ld area = 0, pos = 0;
    for (auto seg : merged) {
        if (seg.first > pos + eps) area += getArcArea(cur, pos, seg.first);
        pos = max(pos, seg.second);
    }
    if (pos < 2 * pi - eps) area += getArcArea(cur, pos, 2 * pi);
    return area;
}

ld getPolyArea(const vector<Point> &poly, const vector<Circle> &circles) {
    ld area = 0;
    int n = (int)poly.size();
    if (n < 3) return 0;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], v = poly[(i + 1) % n] - a;
        ld vv = dot(v, v);
        vector<pair<ld, ld>> covered;
        for (const Circle &cir : circles) {
            Point diff = cir.c - a;
            ld mid = dot(diff, v) / vv;
            Point nearest = a + v * mid;
            ld dis2 = dot(nearest - cir.c, nearest - cir.c);
            if (dis2 > cir.r * cir.r + eps) continue;
            ld half = sqrtl(max((ld)0, (cir.r * cir.r - dis2) / vv));
            covered.push_back({mid - half, mid + half});
        }
        vector<pair<ld, ld>> merged = mergeIntervals(covered, 0, 1);
        ld pos = 0, factor = cross(a, v) / 2;
        for (auto seg : merged) {
            if (seg.first > pos + eps) area += factor * (seg.first - pos);
            pos = max(pos, seg.second);
        }
        if (pos < 1 - eps) area += factor * (1 - pos);
    }
    return area;
}

Point transformPoint(ld x, ld y, ld z, ld dx, ld dy, ld dz, ld scale) {
    Point p = {x - z * dx / dz, y - z * dy / dz};
    ld horizontal = sqrtl(dx * dx + dy * dy);
    if (horizontal > eps) {
        ld ux = dx / horizontal, uy = dy / horizontal;
        ld parallel = p.x * ux + p.y * uy;
        p.x += (scale - 1) * parallel * ux;
        p.y += (scale - 1) * parallel * uy;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long dxInput, dyInput, dzInput;
    while (cin >> n >> m >> dxInput >> dyInput >> dzInput) {
        if (n == 0 && m == 0 && dxInput == 0 && dyInput == 0 && dzInput == 0) break;
        ld dx = dxInput, dy = dyInput, dz = dzInput;
        ld dirLength = sqrtl(dx * dx + dy * dy + dz * dz);
        ld scale = fabsl(dz) / dirLength;
        vector<Circle> circles;
        for (int i = 0; i < n; i++) {
            long long xInput, yInput, zInput, rInput;
            cin >> xInput >> yInput >> zInput >> rInput;
            if (rInput > 0) {
                Point center = transformPoint(xInput, yInput, zInput, dx, dy, dz, scale);
                circles.push_back({center, (ld)rInput});
            }
        }
        vector<Point> points;
        for (int i = 0; i < m; i++) {
            long long xInput, yInput, zInput;
            cin >> xInput >> yInput >> zInput;
            points.push_back(transformPoint(xInput, yInput, zInput, dx, dy, dz, scale));
        }
        vector<Point> poly = getHull(points);
        ld area = getPolyArea(poly, circles);
        for (int i = 0; i < (int)circles.size(); i++) area += getCircleArea(i, circles, poly);
        area *= dirLength / fabsl(dz);
        if (fabsl(area) < 5e-10L) area = 0;
        cout << fixed << setprecision(4) << area << '\n';
    }
    return 0;
}
