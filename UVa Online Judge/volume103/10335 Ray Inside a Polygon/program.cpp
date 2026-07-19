// Ray Inside a Polygon
// UVa ID: 10335
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double epsilon = 1e-10;
const double pi = acos(-1.0);

struct Point {
    double x;
    double y;
};

Point operator + (const Point &firstPoint, const Point &secondPoint) {
    return {firstPoint.x + secondPoint.x, firstPoint.y + secondPoint.y};
}

Point operator - (const Point &firstPoint, const Point &secondPoint) {
    return {firstPoint.x - secondPoint.x, firstPoint.y - secondPoint.y};
}

Point operator * (const Point &point, double value) {
    return {point.x * value, point.y * value};
}

double getCrossProduct(const Point &firstPoint, const Point &secondPoint) {
    return firstPoint.x * secondPoint.y - firstPoint.y * secondPoint.x;
}

double getDotProduct(const Point &firstPoint, const Point &secondPoint) {
    return firstPoint.x * secondPoint.x + firstPoint.y * secondPoint.y;
}

bool isSameRoundedPoint(const Point &firstPoint, const Point &secondPoint) {
    long long firstX = llround(firstPoint.x * 100.0);
    long long firstY = llround(firstPoint.y * 100.0);
    long long secondX = llround(secondPoint.x * 100.0);
    long long secondY = llround(secondPoint.y * 100.0);
    return firstX == secondX && firstY == secondY;
}

bool isVertexPoint(const Point &hitPoint, const vector<Point> &polygon) {
    for (const Point &vertex : polygon)
        if (isSameRoundedPoint(hitPoint, vertex))
            return true;
    return false;
}

Point getReflectedDirection(const Point &direction, const Point &edgeStart, const Point &edgeEnd) {
    Point edgeVector = edgeEnd - edgeStart;
    double edgeLengthSquare = getDotProduct(edgeVector, edgeVector);
    double projectionFactor = getDotProduct(direction, edgeVector) / edgeLengthSquare;
    Point projection = edgeVector * projectionFactor;
    return projection * 2.0 - direction;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int vertexCount, reflectionCount;
    while (cin >> vertexCount >> reflectionCount) {
        if (vertexCount == 0 && reflectionCount == 0)
            break;
        Point currentPoint;
        double angle;
        cin >> currentPoint.x >> currentPoint.y >> angle;
        vector<Point> polygon(vertexCount);
        for (int i = 0; i < vertexCount; i++)
            cin >> polygon[i].x >> polygon[i].y;
        double radian = angle * pi / 180.0;
        Point direction = {cos(radian), sin(radian)};
        bool isLost = false;
        Point answerPoint;
        for (int currentReflection = 0; currentReflection <= reflectionCount; currentReflection++) {
            double minimumDistance = 1e100;
            int hitEdgeIndex = -1;
            Point hitPoint;
            for (int i = 0; i < vertexCount; i++) {
                Point edgeStart = polygon[i];
                Point edgeEnd = polygon[(i + 1) % vertexCount];
                Point edgeVector = edgeEnd - edgeStart;
                double denominator = getCrossProduct(direction, edgeVector);
                if (fabs(denominator) < epsilon)
                    continue;
                Point difference = edgeStart - currentPoint;
                double rayParameter = getCrossProduct(difference, edgeVector) / denominator;
                double edgeParameter = getCrossProduct(difference, direction) / denominator;
                if (rayParameter > epsilon && edgeParameter >= -epsilon && edgeParameter <= 1.0 + epsilon) {
                    if (rayParameter < minimumDistance) {
                        minimumDistance = rayParameter;
                        hitEdgeIndex = i;
                        hitPoint = currentPoint + direction * rayParameter;
                    }
                }
            }
            if (isVertexPoint(hitPoint, polygon)) {
                isLost = true;
                break;
            }
            if (currentReflection == reflectionCount) {
                answerPoint = hitPoint;
                break;
            }
            Point edgeStart = polygon[hitEdgeIndex];
            Point edgeEnd = polygon[(hitEdgeIndex + 1) % vertexCount];
            direction = getReflectedDirection(direction, edgeStart, edgeEnd);
            currentPoint = hitPoint;
        }
        if (isLost) cout << "lost forever...\n";
        else {
            if (fabs(answerPoint.x) < 0.0005) answerPoint.x = 0.0;
            if (fabs(answerPoint.y) < 0.0005) answerPoint.y = 0.0;
            cout << fixed << setprecision(2) << answerPoint.x << ' ' << answerPoint.y << '\n';
        }
    }
    return 0;
}
