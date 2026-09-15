#include <bits/stdc++.h>
using namespace std;

struct Point3 {
    long double x, y, z;
};

struct Point2 {
    long double x, y;
    bool operator < (const Point2 &other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

Point3 operator + (const Point3 &a, const Point3 &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Point3 operator - (const Point3 &a, const Point3 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point3 operator * (const Point3 &a, long double k) {
    return {a.x * k, a.y * k, a.z * k};
}

long double dotProduct(const Point3 &a, const Point3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3 crossProduct(const Point3 &a, const Point3 &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

long double length(const Point3 &a) {
    return sqrtl(dotProduct(a, a));
}

Point3 normalize(const Point3 &a) {
    long double len = length(a);
    return a * (1.0L / len);
}

long double crossProduct(const Point2 &a, const Point2 &b, const Point2 &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point2> getConvexHull(vector<Point2> points) {
    const long double eps = 1e-12L;
    int n = points.size(), lowerSize, upperSize;
    vector<Point2> hull;
    sort(points.begin(), points.end());
    for (const Point2 &point : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull.back(), point) <= eps)
            hull.pop_back();
        hull.push_back(point);
    }
    lowerSize = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while ((int)hull.size() > lowerSize && crossProduct(hull[hull.size() - 2], hull.back(), points[i]) <= eps)
            hull.pop_back();
        hull.push_back(points[i]);
    }
    if (hull.size() > 1)
        hull.pop_back();
    return hull;
}

long double getArea(const vector<Point2> &polygon) {
    long double area = 0.0L;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        area += polygon[i].x * polygon[next].y - polygon[i].y * polygon[next].x;
    }
    return fabsl(area) / 2.0L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Point3 pointA, pointB, pointC, source, normal, axisX, axisY, reference;
    int vertexCount;
    while (cin >> pointA.x >> pointA.y >> pointA.z) {
        cin >> pointB.x >> pointB.y >> pointB.z;
        cin >> pointC.x >> pointC.y >> pointC.z;
        cin >> source.x >> source.y >> source.z;
        cin >> vertexCount;
        normal = crossProduct(pointB - pointA, pointC - pointA);
        normal = normalize(normal);
        reference = {1.0L, 0.0L, 0.0L};
        if (fabsl(dotProduct(normal, reference)) > 0.9L)
            reference = {0.0L, 1.0L, 0.0L};
        axisX = normalize(crossProduct(normal, reference));
        axisY = crossProduct(normal, axisX);
        vector<Point2> projectedPoints;
        for (int i = 0; i < vertexCount; i++) {
            Point3 vertex, direction, projected;
            long double numerator, denominator, ratio;
            cin >> vertex.x >> vertex.y >> vertex.z;
            direction = vertex - source;
            numerator = dotProduct(normal, pointA - source);
            denominator = dotProduct(normal, direction);
            ratio = numerator / denominator;
            projected = source + direction * ratio;
            projectedPoints.push_back({dotProduct(projected - pointA, axisX), dotProduct(projected - pointA, axisY)});
        }
        cout << fixed << setprecision(2) << (double)getArea(getConvexHull(projectedPoints)) << '\n';
    }
    return 0;
}
