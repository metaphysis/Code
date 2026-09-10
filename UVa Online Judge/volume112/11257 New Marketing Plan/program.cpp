// New Marketing Plan
// UVa ID: 11257
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.120s

#include <bits/stdc++.h>
using namespace std;

const long double kEpsilon = 1e-12L;

struct Point {
    long double x;
    long double y;

    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator * (long double factor) const {
        return {x * factor, y * factor};
    }
};

long double crossProduct(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

long double getValue(const Point &point, const Point &startPoint, const Point &edgeVector, long double radius) {
    return crossProduct(edgeVector, point - startPoint) - radius * sqrtl(edgeVector.x * edgeVector.x + edgeVector.y * edgeVector.y);
}

Point getIntersection(const Point &startPoint, const Point &endPoint, long double startValue, long double endValue) {
    long double ratio = startValue / (startValue - endValue);
    return startPoint + (endPoint - startPoint) * ratio;
}

vector<Point> clipPolygon(const vector<Point> &polygon, const Point &startPoint, const Point &endPoint, long double radius) {
    vector<Point> result;
    Point edgeVector = endPoint - startPoint;
    int pointCount = polygon.size();
    for (int i = 0; i < pointCount; i++) {
        Point currentPoint = polygon[i];
        Point nextPoint = polygon[(i + 1) % pointCount];
        long double currentValue = getValue(currentPoint, startPoint, edgeVector, radius);
        long double nextValue = getValue(nextPoint, startPoint, edgeVector, radius);
        bool currentInside = currentValue >= -kEpsilon;
        bool nextInside = nextValue >= -kEpsilon;
        if (currentInside && nextInside)
            result.push_back(nextPoint);
        else if (currentInside && !nextInside)
            result.push_back(getIntersection(currentPoint, nextPoint, currentValue, nextValue));
        else if (!currentInside && nextInside) {
            result.push_back(getIntersection(currentPoint, nextPoint, currentValue, nextValue));
            result.push_back(nextPoint);
        }
    }
    return result;
}

bool isRadiusFeasible(const vector<Point> &polygon, long double radius) {
    vector<Point> currentPolygon = polygon;
    int pointCount = polygon.size();
    for (int i = 0; i < pointCount; i++) {
        Point startPoint = polygon[i];
        Point endPoint = polygon[(i + 1) % pointCount];
        currentPolygon = clipPolygon(currentPolygon, startPoint, endPoint, radius);
        if (currentPolygon.empty())
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        vector<Point> polygon(n);
        long double minX = numeric_limits<long double>::max();
        long double maxX = numeric_limits<long double>::lowest();
        long double minY = numeric_limits<long double>::max();
        long double maxY = numeric_limits<long double>::lowest();
        for (int i = 0; i < n; i++) {
            cin >> polygon[i].x >> polygon[i].y;
            minX = min(minX, polygon[i].x);
            maxX = max(maxX, polygon[i].x);
            minY = min(minY, polygon[i].y);
            maxY = max(maxY, polygon[i].y);
        }
        long double left = 0;
        long double right = hypotl(maxX - minX, maxY - minY);
        for (int iteration = 0; iteration < 100; iteration++) {
            long double middle = (left + right) / 2;
            if (isRadiusFeasible(polygon, middle))
                left = middle;
            else
                right = middle;
        }
        cout << fixed << setprecision(3) << (double)left << '\n';
    }
    return 0;
}
