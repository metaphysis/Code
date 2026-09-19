#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Point {
    double x, y;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }
    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }
    Point operator * (double value) const {
        return {x * value, y * value};
    }
};

double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double crossProduct(Point a, Point b, Point c) {
    return crossProduct(b - a, c - a);
}

double vectorLength(Point a) {
    return sqrt(dotProduct(a, a));
}

bool equalZero(double value) {
    return fabs(value) < eps;
}

bool pointOnSegment(Point p, Point a, Point b) {
    if (!equalZero(crossProduct(a, b, p))) return false;
    return min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps && min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps;
}

bool properIntersection(Point a, Point b, Point c, Point d) {
    double c1 = crossProduct(a, b, c), c2 = crossProduct(a, b, d), c3 = crossProduct(c, d, a), c4 = crossProduct(c, d, b);
    return ((c1 > eps && c2 < -eps) || (c1 < -eps && c2 > eps)) && ((c3 > eps && c4 < -eps) || (c3 < -eps && c4 > eps));
}

double overlapLength(Point a, Point b, Point c, Point d) {
    Point direction = b - a;
    double length = vectorLength(direction);
    if (length < eps) return 0.0;
    if (!equalZero(crossProduct(direction, d - c))) return 0.0;
    if (!equalZero(crossProduct(direction, c - a))) return 0.0;
    Point unit = direction * (1.0 / length);
    double p1 = 0.0, p2 = length, p3 = dotProduct(c - a, unit), p4 = dotProduct(d - a, unit);
    double left = max(min(p1, p2), min(p3, p4)), right = min(max(p1, p2), max(p3, p4));
    return max(0.0, right - left);
}

bool pointInside(const vector<Point> &polygon, Point point, double shiftX) {
    int n = polygon.size();
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        a.x += shiftX;
        b.x += shiftX;
        if (pointOnSegment(point, a, b)) return false;
        bool aboveA = a.y > point.y, aboveB = b.y > point.y;
        if (aboveA != aboveB) {
            double crossX = a.x + (b.x - a.x) * (point.y - a.y) / (b.y - a.y);
            if (crossX > point.x + eps) inside = !inside;
        }
    }
    return inside;
}

bool polygonsOverlap(const vector<Point> &p, const vector<Point> &q, double shiftX) {
    int n = p.size(), m = q.size();
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        a.x += shiftX;
        b.x += shiftX;
        for (int j = 0; j < m; j++) {
            Point c = q[j], d = q[(j + 1) % m];
            if (properIntersection(a, b, c, d)) return true;
            if (overlapLength(a, b, c, d) > eps && dotProduct(b - a, d - c) > eps) return true;
        }
    }
    for (Point point : p) {
        point.x += shiftX;
        if (pointInside(q, point, 0.0)) return true;
    }
    for (Point point : q)
        if (pointInside(p, point, shiftX)) return true;
    return false;
}

double commonBoundary(const vector<Point> &p, const vector<Point> &q, double shiftX) {
    int n = p.size(), m = q.size();
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        a.x += shiftX;
        b.x += shiftX;
        for (int j = 0; j < m; j++)
            result += overlapLength(a, b, q[j], q[(j + 1) % m]);
    }
    return result;
}

vector<Point> transformPolygon(const vector<Point> &polygon, int edgeId, bool firstPolygon) {
    int n = polygon.size();
    Point origin = polygon[edgeId], direction = polygon[(edgeId + 1) % n] - origin;
    double length = vectorLength(direction);
    Point unit = direction * (1.0 / length);
    vector<Point> result;
    result.reserve(n);
    for (Point point : polygon) {
        Point delta = point - origin;
        if (firstPolygon)
            result.push_back({dotProduct(delta, unit), crossProduct(unit, delta)});
        else
            result.push_back({-dotProduct(delta, unit), -crossProduct(unit, delta)});
    }
    return result;
}

void addCandidates(const vector<Point> &p, const vector<Point> &q, vector<double> &candidates) {
    int n = p.size(), m = q.size();
    for (Point a : p)
        for (Point b : q)
            if (fabs(a.y - b.y) < eps) candidates.push_back(b.x - a.x);
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        if (fabs(a.y - b.y) > eps) {
            for (Point point : q) {
                if (point.y < min(a.y, b.y) - eps || point.y > max(a.y, b.y) + eps) continue;
                double ratio = (point.y - a.y) / (b.y - a.y);
                double x = a.x + (b.x - a.x) * ratio;
                candidates.push_back(point.x - x);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        Point a = q[i], b = q[(i + 1) % m];
        if (fabs(a.y - b.y) > eps) {
            for (Point point : p) {
                if (point.y < min(a.y, b.y) - eps || point.y > max(a.y, b.y) + eps) continue;
                double ratio = (point.y - a.y) / (b.y - a.y);
                double x = a.x + (b.x - a.x) * ratio;
                candidates.push_back(x - point.x);
            }
        }
    }
}

double solvePair(const vector<Point> &originalP, const vector<Point> &originalQ, int edgeP, int edgeQ, double answer) {
    vector<Point> p = transformPolygon(originalP, edgeP, true), q = transformPolygon(originalQ, edgeQ, false);
    vector<double> candidates, uniqueCandidates;
    addCandidates(p, q, candidates);
    sort(candidates.begin(), candidates.end());
    for (double shiftX : candidates)
        if (uniqueCandidates.empty() || fabs(shiftX - uniqueCandidates.back()) > eps) uniqueCandidates.push_back(shiftX);
    for (double shiftX : uniqueCandidates) {
        double boundary = commonBoundary(p, q, shiftX);
        if (boundary <= answer + eps) continue;
        if (!polygonsOverlap(p, q, shiftX)) answer = boundary;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cout << fixed << setprecision(10);
    while (cin >> n) {
        vector<Point> p(n);
        for (Point &point : p) cin >> point.x >> point.y;
        if (!(cin >> m)) break;
        vector<Point> q(m);
        for (Point &point : q) cin >> point.x >> point.y;
        double answer = 0.0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                answer = solvePair(p, q, i, j, answer);
        cout << answer << '\n';
    }
    return 0;
}
