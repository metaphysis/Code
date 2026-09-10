// Altitude Triangle
// UVa ID: 12073
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;
};

Point addPoint(const Point &pointA, const Point &pointB) {
    return {pointA.x + pointB.x, pointA.y + pointB.y};
}

Point subtractPoint(const Point &pointA, const Point &pointB) {
    return {pointA.x - pointB.x, pointA.y - pointB.y};
}

Point multiplyPoint(const Point &point, double factor) {
    return {point.x * factor, point.y * factor};
}

double dotProduct(const Point &pointA, const Point &pointB) {
    return pointA.x * pointB.x + pointA.y * pointB.y;
}

double distanceBetween(const Point &pointA, const Point &pointB) {
    double deltaX = pointA.x - pointB.x;
    double deltaY = pointA.y - pointB.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void normalizePoint(Point &point) {
    if (fabs(point.x) < 0.0005) point.x = 0;
    if (fabs(point.y) < 0.0005) point.y = 0;
}

void printPoint(Point point) {
    normalizePoint(point);
    cout << fixed << setprecision(3) << point.x << " " << point.y << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNumber = 1;
    double x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0) break;
        Point pointA = {x1, y1};
        Point pointB = {x2, y2};
        Point pointC = {x3, y3};
        double lengthBC = distanceBetween(pointB, pointC);
        double lengthCA = distanceBetween(pointC, pointA);
        double lengthAB = distanceBetween(pointA, pointB);
        double totalLength = lengthBC + lengthCA + lengthAB;
        // 根据三角形内心的边长加权公式计算正交心 O
        Point pointO;
        pointO.x = (lengthBC * pointA.x + lengthCA * pointB.x + lengthAB * pointC.x) / totalLength;
        pointO.y = (lengthBC * pointA.y + lengthCA * pointB.y + lengthAB * pointC.y) / totalLength;
        Point vectorA = subtractPoint(pointA, pointO);
        Point vectorB = subtractPoint(pointB, pointO);
        Point vectorC = subtractPoint(pointC, pointO);
        double squareA = dotProduct(vectorA, vectorA);
        double squareB = dotProduct(vectorB, vectorB);
        double squareC = dotProduct(vectorC, vectorC);
        double coefficientD = squareB / dotProduct(vectorA, vectorB);
        double coefficientE = squareC / dotProduct(vectorB, vectorC);
        double coefficientF = squareA / dotProduct(vectorC, vectorA);
        Point pointD = addPoint(pointO, multiplyPoint(vectorA, coefficientD));
        Point pointE = addPoint(pointO, multiplyPoint(vectorB, coefficientE));
        Point pointF = addPoint(pointO, multiplyPoint(vectorC, coefficientF));
        cout << "Case " << caseNumber << ":\n";
        printPoint(pointD);
        printPoint(pointE);
        printPoint(pointF);
        ++caseNumber;
    }
    return 0;
}
