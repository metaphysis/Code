// Fishnet
// UVa ID: 1301
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Line {
    double a;
    double b;
    double c;
};

Line makeLine(Point firstPoint, Point secondPoint) {
    Line line;
    line.a = firstPoint.y - secondPoint.y;
    line.b = secondPoint.x - firstPoint.x;
    line.c = firstPoint.x * secondPoint.y - secondPoint.x * firstPoint.y;
    return line;
}

Point getIntersection(Line firstLine, Line secondLine) {
    double determinant = firstLine.a * secondLine.b - secondLine.a * firstLine.b;
    Point point;
    point.x = (firstLine.b * secondLine.c - secondLine.b * firstLine.c) / determinant;
    point.y = (firstLine.c * secondLine.a - secondLine.c * firstLine.a) / determinant;
    return point;
}

double getArea(Point firstPoint, Point secondPoint, Point thirdPoint, Point fourthPoint) {
    double area = 0.0;
    area += firstPoint.x * secondPoint.y - firstPoint.y * secondPoint.x;
    area += secondPoint.x * thirdPoint.y - secondPoint.y * thirdPoint.x;
    area += thirdPoint.x * fourthPoint.y - thirdPoint.y * fourthPoint.x;
    area += fourthPoint.x * firstPoint.y - fourthPoint.y * firstPoint.x;
    return fabs(area) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cout << fixed << setprecision(6);
    while (cin >> n && n != 0) {
        vector<double> bottomX(n + 2);
        vector<double> topX(n + 2);
        vector<double> leftY(n + 2);
        vector<double> rightY(n + 2);
        bottomX[0] = 0.0;
        topX[0] = 0.0;
        bottomX[n + 1] = 1.0;
        topX[n + 1] = 1.0;
        leftY[0] = 0.0;
        rightY[0] = 0.0;
        leftY[n + 1] = 1.0;
        rightY[n + 1] = 1.0;
        for (int i = 1; i <= n; ++i) cin >> bottomX[i];
        for (int i = 1; i <= n; ++i) cin >> topX[i];
        for (int i = 1; i <= n; ++i) cin >> leftY[i];
        for (int i = 1; i <= n; ++i) cin >> rightY[i];
        vector<Line> verticalLines(n + 2);
        vector<Line> horizontalLines(n + 2);
        for (int i = 0; i <= n + 1; ++i) {
            Point firstPoint = {bottomX[i], 0.0};
            Point secondPoint = {topX[i], 1.0};
            verticalLines[i] = makeLine(firstPoint, secondPoint);
        }
        for (int i = 0; i <= n + 1; ++i) {
            Point firstPoint = {0.0, leftY[i]};
            Point secondPoint = {1.0, rightY[i]};
            horizontalLines[i] = makeLine(firstPoint, secondPoint);
        }
        double answer = 0.0;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j) {
                Point firstPoint = getIntersection(verticalLines[i], horizontalLines[j]);
                Point secondPoint = getIntersection(verticalLines[i + 1], horizontalLines[j]);
                Point thirdPoint = getIntersection(verticalLines[i + 1], horizontalLines[j + 1]);
                Point fourthPoint = getIntersection(verticalLines[i], horizontalLines[j + 1]);
                double area = getArea(firstPoint, secondPoint, thirdPoint, fourthPoint);
                answer = max(answer, area);
            }
        cout << answer << '\n';
    }
    return 0;
}
