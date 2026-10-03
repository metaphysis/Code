#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld PI = acosl(-1.0L), EPS = 1e-18L;

struct Point {
    ld x, y;
    Point operator + (const Point& other) const {
        return {x + other.x, y + other.y};
    }
    Point operator - (const Point& other) const {
        return {x - other.x, y - other.y};
    }
    Point operator * (ld value) const {
        return {x * value, y * value};
    }
};

ld cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

ld dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

ld length(const Point& a) {
    return sqrtl(dot(a, a));
}

ld polygonArea(const vector<Point>& polygon) {
    ld result = 0;
    int n = static_cast<int>(polygon.size());
    for (int i = 0; i < n; ++i)
        result += cross(polygon[i], polygon[(i + 1) % n]);
    return fabsl(result) / 2.0L;
}

struct Line {
    Point p, v;
    ld angle;
};

bool inside(const Line& line, const Point& point) {
    return cross(line.v, point - line.p) >= -EPS;
}

bool parallel(const Line& a, const Line& b) {
    return fabsl(cross(a.v, b.v)) <= EPS;
}

Point lineIntersection(const Line& a, const Line& b) {
    ld denominator = cross(a.v, b.v);
    ld t = cross(b.p - a.p, b.v) / denominator;
    return a.p + a.v * t;
}

vector<Point> halfPlaneIntersection(vector<Line> lines) {
    sort(lines.begin(), lines.end(), [](const Line& a, const Line& b) {
        if (fabsl(a.angle - b.angle) > EPS)
            return a.angle < b.angle;
        return cross(a.v, b.p - a.p) < 0;
    });
    deque<Line> dq;
    for (const Line& line : lines) {
        if (!dq.empty() && parallel(dq.back(), line)) {
            // For equally directed parallel lines, retain the more restrictive one.
            if (!inside(line, dq.back().p))
                dq.back() = line;
            continue;
        }
        while (dq.size() > 1) {
            Point point = lineIntersection(dq[dq.size() - 2], dq.back());
            if (inside(line, point))
                break;
            dq.pop_back();
        }
        while (dq.size() > 1) {
            Point point = lineIntersection(dq[0], dq[1]);
            if (inside(line, point))
                break;
            dq.pop_front();
        }
        dq.push_back(line);
    }
    while (dq.size() > 2) {
        Point point = lineIntersection(dq[dq.size() - 2], dq.back());
        if (inside(dq.front(), point))
            break;
        dq.pop_back();
    }
    while (dq.size() > 2) {
        Point point = lineIntersection(dq[0], dq[1]);
        if (inside(dq.back(), point))
            break;
        dq.pop_front();
    }
    if (dq.size() < 3)
        return {};
    vector<Line> resultLines(dq.begin(), dq.end());
    vector<Point> result;
    int m = static_cast<int>(resultLines.size());
    for (int i = 0; i < m; ++i)
        result.push_back(lineIntersection(resultLines[i], resultLines[(i + 1) % m]));
    return result;
}

ld erodedArea(const vector<Point>& polygon, ld radius) {
    int n = static_cast<int>(polygon.size());
    vector<Line> lines;
    lines.reserve(n);
    for (int i = 0; i < n; ++i) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        Point edge = b - a;
        ld edgeLength = length(edge);
        Point leftNormal = {-edge.y / edgeLength, edge.x / edgeLength};
        // Move the supporting line inward by radius.
        Point shiftedPoint = a + leftNormal * radius;
        Line line;
        line.p = shiftedPoint;
        line.v = edge;
        line.angle = atan2l(edge.y, edge.x);
        lines.push_back(line);
    }
    vector<Point> result = halfPlaneIntersection(lines);
    if (result.size() < 3)
        return 0;
    return polygonArea(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNumber = 1;
    while (cin >> n && n != 0) {
        vector<Point> polygon(n);
        for (Point& point : polygon)
            cin >> point.x >> point.y;
        ld lightRadius, wallDistance;
        cin >> lightRadius >> wallDistance;
        ld area = polygonArea(polygon), perimeter = 0;
        for (int i = 0; i < n; ++i)
            perimeter += length(polygon[(i + 1) % n] - polygon[i]);
        /*
         * Projection:
         *
         *     W = 2P - S
         *
         * Therefore the polygon is scaled by 2, while the light disk
         * still has radius lightRadius on the wall.
         */
        ld totalShadowArea = 4.0L * area + 2.0L * lightRadius * perimeter + PI * lightRadius * lightRadius;
        /*
         * Umbra:
         *
         * After scaling back by 2, the original polygon must contain
         * a disk of radius lightRadius / 2.
         */
        ld innerRadius = lightRadius / 2.0L;
        ld innerArea = erodedArea(polygon, innerRadius);
        ld umbraArea = 4.0L * innerArea;
        ld penumbraArea = totalShadowArea - umbraArea;
        if (umbraArea < 0 && umbraArea > -1e-12L)
            umbraArea = 0;
        if (penumbraArea < 0 && penumbraArea > -1e-12L)
            penumbraArea = 0;
        cout << "Case " << caseNumber++ << ": " << fixed << setprecision(10) << umbraArea << ' ' << umbraArea + penumbraArea << '\n';
    }
    return 0;
}
