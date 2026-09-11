// Crime Scene
// UVa ID: 11726
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-12;

struct Point {
    double x;
    double y;
    Point() {}
    Point(double xValue, double yValue) : x(xValue), y(yValue) {}
    Point operator + (const Point &other) const {
        return Point(x + other.x, y + other.y);
    }
    Point operator - (const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
    Point operator * (double value) const {
        return Point(x * value, y * value);
    }
};

struct Circle {
    Point center;
    double radius;
};

double crossProduct(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double crossProduct(const Point &a, const Point &b, const Point &c) {
    return crossProduct(b - a, c - a);
}

double dotProduct(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

double getDistance(const Point &a) {
    return sqrt(dotProduct(a, a));
}

bool comparePoint(const Point &a, const Point &b) {
    if (fabs(a.x - b.x) > eps) return a.x < b.x;
    return a.y < b.y;
}

vector<Point> getConvexHull(vector<Point> points) {
    sort(points.begin(), points.end(), comparePoint);
    vector<Point> uniquePoints;
    for (const Point &point : points) {
        if (uniquePoints.empty() || fabs(point.x - uniquePoints.back().x) > eps || fabs(point.y - uniquePoints.back().y) > eps) uniquePoints.push_back(point);
    }
    points = uniquePoints;
    if (points.size() <= 1) return points;
    vector<Point> lowerHull;
    for (const Point &point : points) {
        while (lowerHull.size() >= 2 && crossProduct(lowerHull[lowerHull.size() - 2], lowerHull.back(), point) <= eps) lowerHull.pop_back();
        lowerHull.push_back(point);
    }
    vector<Point> upperHull;
    for (int i = static_cast<int>(points.size()) - 1; i >= 0; --i) {
        while (upperHull.size() >= 2 && crossProduct(upperHull[upperHull.size() - 2], upperHull.back(), points[i]) <= eps) upperHull.pop_back();
        upperHull.push_back(points[i]);
    }
    lowerHull.pop_back();
    upperHull.pop_back();
    lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());
    return lowerHull;
}

double normalizeAngle(double angle) {
    while (angle < 0) angle += 2.0 * pi;
    while (angle >= 2.0 * pi) angle -= 2.0 * pi;
    if (fabs(angle) < eps || fabs(angle - 2.0 * pi) < eps) return 0.0;
    return angle;
}

void addAngle(vector<double> &angles, double angle) {
    angles.push_back(normalizeAngle(angle));
}

void addEquationAngles(vector<double> &angles, const Point &direction, double value) {
    double length = getDistance(direction);
    if (length < eps) return;
    if (value > length + eps || value < -length - eps) return;
    double ratio = value / length;
    ratio = max(-1.0, min(1.0, ratio));
    double baseAngle = atan2(direction.y, direction.x);
    double deltaAngle = acos(ratio);
    addAngle(angles, baseAngle + deltaAngle);
    addAngle(angles, baseAngle - deltaAngle);
}

double getPointSupport(const Point &point, double cosValue, double sinValue) {
    return point.x * cosValue + point.y * sinValue;
}

double getCircleSupport(const Circle &circle, double cosValue, double sinValue) {
    return circle.center.x * cosValue + circle.center.y * sinValue + circle.radius;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseNumber = 1; caseNumber <= testCases; ++caseNumber) {
        int objectCount;
        cin >> objectCount;
        vector<Point> allPoints;
        vector<Circle> circles;
        for (int i = 0; i < objectCount; ++i) {
            char objectType;
            cin >> objectType;
            if (objectType == 'c') {
                double centerX, centerY, radius;
                cin >> centerX >> centerY >> radius;
                circles.push_back({Point(centerX, centerY), radius});
            } else {
                int sideCount;
                cin >> sideCount;
                for (int j = 0; j < sideCount; ++j) {
                    double x, y;
                    cin >> x >> y;
                    allPoints.push_back(Point(x, y));
                }
            }
        }
        vector<Point> convexHull = getConvexHull(allPoints);
        vector<double> angles;
        angles.push_back(0.0);
        int hullSize = static_cast<int>(convexHull.size());
        int circleCount = static_cast<int>(circles.size());
        if (hullSize >= 3) {
            for (int i = 0; i < hullSize; ++i) {
                Point currentPoint = convexHull[i];
                Point nextPoint = convexHull[(i + 1) % hullSize];
                Point edge = nextPoint - currentPoint;
                addAngle(angles, atan2(-edge.x, edge.y));
            }
        } else if (hullSize == 2) {
            Point edge = convexHull[1] - convexHull[0];
            addAngle(angles, atan2(-edge.x, edge.y));
            addAngle(angles, atan2(-edge.x, edge.y) + pi);
        }
        for (const Point &point : convexHull) {
            for (const Circle &circle : circles) {
                addEquationAngles(angles, point - circle.center, circle.radius);
            }
        }
        for (int i = 0; i < circleCount; ++i) {
            for (int j = i + 1; j < circleCount; ++j) {
                Point direction = circles[i].center - circles[j].center;
                double value = circles[j].radius - circles[i].radius;
                addEquationAngles(angles, direction, value);
            }
        }
        sort(angles.begin(), angles.end());
        vector<double> uniqueAngles;
        for (double angle : angles) {
            if (uniqueAngles.empty() || fabs(angle - uniqueAngles.back()) > 1e-11) uniqueAngles.push_back(angle);
        }
        angles = uniqueAngles;
        double answer = 0.0;
        int pointIndex = 0;
        for (int i = 0; i < static_cast<int>(angles.size()); ++i) {
            double leftAngle = angles[i];
            double rightAngle = i + 1 < static_cast<int>(angles.size()) ? angles[i + 1] : angles[0] + 2.0 * pi;
            double middleAngle = (leftAngle + rightAngle) * 0.5;
            double cosValue = cos(middleAngle);
            double sinValue = sin(middleAngle);
            if (hullSize > 0) {
                if (i == 0) {
                    pointIndex = 0;
                    for (int j = 1; j < hullSize; ++j) {
                        if (getPointSupport(convexHull[j], cosValue, sinValue) > getPointSupport(convexHull[pointIndex], cosValue, sinValue)) pointIndex = j;
                    }
                } else {
                    while (hullSize >= 2) {
                        int nextIndex = (pointIndex + 1) % hullSize;
                        double currentValue = getPointSupport(convexHull[pointIndex], cosValue, sinValue);
                        double nextValue = getPointSupport(convexHull[nextIndex], cosValue, sinValue);
                        if (nextValue > currentValue + 1e-11) pointIndex = nextIndex;
                        else break;
                    }
                }
            }
            double maximumSupport = -1e100;
            bool selectedPoint = false;
            int selectedCircle = -1;
            if (hullSize > 0) {
                maximumSupport = getPointSupport(convexHull[pointIndex], cosValue, sinValue);
                selectedPoint = true;
            }
            for (int j = 0; j < circleCount; ++j) {
                double circleSupport = getCircleSupport(circles[j], cosValue, sinValue);
                if (circleSupport > maximumSupport) {
                    maximumSupport = circleSupport;
                    selectedPoint = false;
                    selectedCircle = j;
                }
            }
            double sineDifference = sin(rightAngle) - sin(leftAngle);
            double cosineDifference = cos(leftAngle) - cos(rightAngle);
            if (selectedPoint) {
                answer += convexHull[pointIndex].x * sineDifference;
                answer += convexHull[pointIndex].y * cosineDifference;
            } else {
                answer += circles[selectedCircle].center.x * sineDifference;
                answer += circles[selectedCircle].center.y * cosineDifference;
                answer += circles[selectedCircle].radius * (rightAngle - leftAngle);
            }
        }
        cout << "Case #" << caseNumber << ": " << fixed << setprecision(6) << answer << '\n';
    }
    return 0;
}
