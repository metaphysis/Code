// Fukushima Nuclear Blast
// UVa ID: 11978
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.210s

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-12;

struct Point {
    double x;
    double y;
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

double crossProduct(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dotProduct(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

double squaredLength(const Point &point) {
    return dotProduct(point, point);
}

double getEdgeIntersectionArea(const Point &a, const Point &b, double radius) {
    Point direction = b - a;
    double quadraticA = dotProduct(direction, direction);
    double quadraticB = 2.0 * dotProduct(a, direction);
    double quadraticC = dotProduct(a, a) - radius * radius;
    vector<double> parameters = {0.0, 1.0};
    double discriminant = quadraticB * quadraticB - 4.0 * quadraticA * quadraticC;
    if (discriminant > eps) {
        double squareRoot = sqrt(discriminant);
        double parameter1 = (-quadraticB - squareRoot) / (2.0 * quadraticA);
        double parameter2 = (-quadraticB + squareRoot) / (2.0 * quadraticA);
        if (parameter1 > eps && parameter1 < 1.0 - eps) parameters.push_back(parameter1);
        if (parameter2 > eps && parameter2 < 1.0 - eps) parameters.push_back(parameter2);
    }
    sort(parameters.begin(), parameters.end());
    double area = 0.0;
    double radiusSquared = radius * radius;
    for (int i = 0; i + 1 < (int)parameters.size(); i++) {
        double leftParameter = parameters[i];
        double rightParameter = parameters[i + 1];
        if (rightParameter - leftParameter < eps) continue;
        Point leftPoint = a + direction * leftParameter;
        Point rightPoint = a + direction * rightParameter;
        double middleParameter = (leftParameter + rightParameter) / 2.0;
        Point middlePoint = a + direction * middleParameter;
        if (squaredLength(middlePoint) <= radiusSquared + eps) {
            area += crossProduct(leftPoint, rightPoint) / 2.0;
        } else {
            double angle = atan2(crossProduct(leftPoint, rightPoint), dotProduct(leftPoint, rightPoint));
            area += radiusSquared * angle / 2.0;
        }
    }
    return area;
}

double getIntersectionArea(const vector<Point> &polygon, double radius) {
    double area = 0.0;
    int vertexCount = polygon.size();
    for (int i = 0; i < vertexCount; i++) {
        int nextIndex = (i + 1) % vertexCount;
        area += getEdgeIntersectionArea(polygon[i], polygon[nextIndex], radius);
    }
    return fabs(area);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int vertexCount;
        cin >> vertexCount;
        vector<Point> polygon(vertexCount);
        for (int i = 0; i < vertexCount; i++) cin >> polygon[i].x >> polygon[i].y;
        Point explosionCenter;
        int percentage;
        cin >> explosionCenter.x >> explosionCenter.y >> percentage;
        for (int i = 0; i < vertexCount; i++) {
            polygon[i].x -= explosionCenter.x;
            polygon[i].y -= explosionCenter.y;
        }
        double totalArea = 0.0;
        double upperBound = 0.0;
        for (int i = 0; i < vertexCount; i++) {
            int nextIndex = (i + 1) % vertexCount;
            totalArea += crossProduct(polygon[i], polygon[nextIndex]);
            upperBound = max(upperBound, sqrt(squaredLength(polygon[i])));
        }
        totalArea = fabs(totalArea) / 2.0;
        double targetArea = totalArea * percentage / 100.0;
        double lowerBound = 0.0;
        for (int iteration = 0; iteration < 70; iteration++) {
            double middle = (lowerBound + upperBound) / 2.0;
            if (getIntersectionArea(polygon, middle) < targetArea) lowerBound = middle;
            else upperBound = middle;
        }
        long long answer = llround((lowerBound + upperBound) / 2.0);
        cout << "Case " << testCase << ": " << answer << '\n';
    }
    return 0;
}
