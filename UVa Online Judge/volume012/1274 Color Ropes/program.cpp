// Color Ropes
// UVa ID: 1274
// Verdict: Accepted
// Submission Date: 2026-10-15
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10L;

struct Point3 {
    long double x, y, z;
};

struct Point2 {
    long double x, y;
};

struct Plane {
    Point3 point, normal;
};

Point3 operator - (const Point3 &a, const Point3 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point3 crossProduct(const Point3 &a, const Point3 &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

long double dotProduct(const Point3 &a, const Point3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int getSign(long double value) {
    if (value > eps) return 1;
    if (value < -eps) return -1;
    return 0;
}

bool getPlane(const vector<Point3> &points, Plane &plane) {
    int n = points.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point3 first = points[j] - points[i];
            for (int k = j + 1; k < n; k++) {
                Point3 second = points[k] - points[i];
                Point3 normal = crossProduct(first, second);
                if (fabsl(normal.x) > eps || fabsl(normal.y) > eps || fabsl(normal.z) > eps) {
                    plane.point = points[i];
                    plane.normal = normal;
                    return true;
                }
            }
        }
    }
    return false;
}

long double getPlaneValue(const Plane &plane, const Point3 &point) {
    return dotProduct(plane.normal, point - plane.point);
}

Point3 getIntersection(const Point3 &a, const Point3 &b, long double valueA, long double valueB) {
    long double ratio = valueA / (valueA - valueB);
    return {a.x + (b.x - a.x) * ratio, a.y + (b.y - a.y) * ratio, a.z + (b.z - a.z) * ratio};
}

Point2 projectPoint(const Point3 &point, const Plane &plane) {
    long double ax = fabsl(plane.normal.x), ay = fabsl(plane.normal.y), az = fabsl(plane.normal.z);
    if (ax >= ay && ax >= az) return {point.y, point.z};
    if (ay >= ax && ay >= az) return {point.x, point.z};
    return {point.x, point.y};
}

long double crossProduct(const Point2 &a, const Point2 &b, const Point2 &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isOnSegment(const Point2 &a, const Point2 &b, const Point2 &point) {
    if (fabsl(crossProduct(a, b, point)) > eps) return false;
    return point.x >= min(a.x, b.x) - eps && point.x <= max(a.x, b.x) + eps &&
           point.y >= min(a.y, b.y) - eps && point.y <= max(a.y, b.y) + eps;
}

bool isInside(const vector<Point2> &polygon, const Point2 &point) {
    int n = polygon.size();
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point2 first = polygon[i], second = polygon[(i + 1) % n];
        if (isOnSegment(first, second, point)) return false;
        if ((first.y > point.y) != (second.y > point.y)) {
            long double crossX = first.x + (second.x - first.x) * (point.y - first.y) / (second.y - first.y);
            if (crossX > point.x + eps) inside = !inside;
        }
    }
    return inside;
}

int countCrossings(const vector<Point3> &polygon, const vector<Point3> &rope, const Plane &plane) {
    int n = polygon.size(), m = rope.size(), result = 0;
    vector<Point2> projectedPolygon;
    vector<long double> values(m);
    for (const Point3 &point : polygon)
        projectedPolygon.push_back(projectPoint(point, plane));
    for (int i = 0; i < m; i++)
        values[i] = getPlaneValue(plane, rope[i]);
    for (int i = 0; i < m; i++) {
        int next = (i + 1) % m;
        if ((values[i] < -eps && values[next] > eps) || (values[i] > eps && values[next] < -eps)) {
            Point3 intersection = getIntersection(rope[i], rope[next], values[i], values[next]);
            if (isInside(projectedPolygon, projectPoint(intersection, plane))) result++;
        }
    }
    for (int i = 0; i < m; i++) {
        if (getSign(values[i]) != 0) continue;
        int previous = (i - 1 + m) % m;
        if (getSign(values[previous]) == 0) continue;
        int left = previous, right = (i + 1) % m;
        while (getSign(values[left]) == 0) left = (left - 1 + m) % m;
        while (getSign(values[right]) == 0) right = (right + 1) % m;
        if (getSign(values[left]) * getSign(values[right]) < 0) {
            if (isInside(projectedPolygon, projectPoint(rope[i], plane))) result++;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        int n, m;
        cin >> n;
        vector<Point3> firstRope(n);
        for (Point3 &point : firstRope) cin >> point.x >> point.y >> point.z;
        cin >> m;
        if (n == 0 && m == 0) break;
        vector<Point3> secondRope(m);
        for (Point3 &point : secondRope) cin >> point.x >> point.y >> point.z;
        Plane plane;
        vector<Point3> polygon, otherRope;
        if (getPlane(firstRope, plane)) {
            polygon = firstRope;
            otherRope = secondRope;
        } else {
            getPlane(secondRope, plane);
            polygon = secondRope;
            otherRope = firstRope;
        }
        int crossings = countCrossings(polygon, otherRope, plane);
        if (crossings % 2 == 0) cout << "Separable\n";
        else cout << "Inseparable\n";
    }
    return 0;
}
