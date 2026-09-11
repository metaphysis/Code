// Find the Point
// UVa ID: 10695
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;

struct Point {
    double x;
    double y;

    Point operator + (const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point operator - (const Point& other) const {
        return {x - other.x, y - other.y};
    }

    Point operator * (double value) const {
        return {x * value, y * value};
    }
};

struct Circle {
    Point center;
    double radius;
};

double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double getLength(Point a) {
    return sqrt(dotProduct(a, a));
}

double getDistance(Point a, Point b) {
    return getLength(a - b);
}

double getAngle(Point a, Point b, Point c) {
    Point first = a - b;
    Point second = c - b;
    double value = dotProduct(first, second) / getLength(first) / getLength(second);
    value = max(-1.0, min(1.0, value));
    return acos(value) * 180.0 / pi;
}

vector<Circle> buildCircles(Point first, Point second, double angle) {
    vector<Circle> result;
    double radians = angle * pi / 180.0;
    double chordLength = getDistance(first, second);
    double sineValue = sin(radians);

    if (fabs(sineValue) < eps)
        return result;

    double radius = chordLength / (2.0 * fabs(sineValue));
    Point middle = (first + second) * 0.5;
    Point direction = second - first;
    double length = getLength(direction);
    Point normal = {-direction.y / length, direction.x / length};
    double height = sqrt(max(0.0, radius * radius - chordLength * chordLength / 4.0));

    result.push_back({middle + normal * height, radius});
    result.push_back({middle - normal * height, radius});
    return result;
}

vector<Point> getIntersections(Circle first, Circle second) {
    vector<Point> result;
    Point difference = second.center - first.center;
    double distance = getLength(difference);

    if (distance < eps)
        return result;

    if (distance > first.radius + second.radius + eps)
        return result;

    if (distance < fabs(first.radius - second.radius) - eps)
        return result;

    double value = (first.radius * first.radius - second.radius * second.radius + distance * distance) / (2.0 * distance);
    double heightSquared = first.radius * first.radius - value * value;

    if (heightSquared < -eps)
        return result;

    double height = sqrt(max(0.0, heightSquared));
    Point unit = difference * (1.0 / distance);
    Point middle = first.center + unit * value;
    Point normal = {-unit.y, unit.x};

    result.push_back(middle + normal * height);

    if (height > eps)
        result.push_back(middle - normal * height);

    return result;
}

bool isInsideTriangle(Point a, Point b, Point c, Point point) {
    double first = crossProduct(b - a, point - a);
    double second = crossProduct(c - b, point - b);
    double third = crossProduct(a - c, point - c);

    bool allPositive = first > eps && second > eps && third > eps;
    bool allNegative = first < -eps && second < -eps && third < -eps;
    return allPositive || allNegative;
}

bool isValidPoint(Point a, Point b, Point c, Point point, double alpha, double beta, double gamma) {
    if (!isInsideTriangle(a, b, c, point))
        return false;

    if (fabs(getAngle(a, point, b) - alpha) > 1e-7)
        return false;

    if (fabs(getAngle(b, point, c) - beta) > 1e-7)
        return false;

    if (fabs(getAngle(c, point, a) - gamma) > 1e-7)
        return false;

    return true;
}

bool isSamePoint(Point first, Point second) {
    return getDistance(first, second) < 1e-7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, y1, x2, y2, x3, y3;
    int caseNumber = 1;

    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0)
            break;

        int alpha, beta, gamma;
        cin >> alpha >> beta >> gamma;

        Point a = {(double)x1, (double)y1};
        Point b = {(double)x2, (double)y2};
        Point c = {(double)x3, (double)y3};

        vector<Circle> firstCircles = buildCircles(a, b, alpha);
        vector<Circle> secondCircles = buildCircles(b, c, beta);
        vector<Point> answers;

        for (Circle firstCircle : firstCircles)
            for (Circle secondCircle : secondCircles) {
                vector<Point> intersections = getIntersections(firstCircle, secondCircle);

                for (Point point : intersections) {
                    if (!isValidPoint(a, b, c, point, alpha, beta, gamma))
                        continue;

                    bool duplicated = false;

                    for (Point answer : answers)
                        if (isSamePoint(answer, point)) {
                            duplicated = true;
                            break;
                        }

                    if (!duplicated)
                        answers.push_back(point);
                }
            }

        cout << "Case " << caseNumber++ << ":\n";

        if (answers.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << fixed << setprecision(6) << answers[0].x << " " << answers[0].y << "\n";
        }
    }

    return 0;
}
