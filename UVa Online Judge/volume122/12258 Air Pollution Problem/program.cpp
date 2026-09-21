#include <bits/stdc++.h>
using namespace std;

const double Pi = acos(-1.0);
const double Eps = 1e-12;

struct Point {
    double x, y;
};

struct Event {
    double angle;
    Point vec;
};

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Point subtractPoint(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

double getAreaRatio(Point center, Point point, double angle, double radius) {
    Point direction = {cos(angle), sin(angle)};
    Point vec = subtractPoint(center, point);
    double distance = crossProduct(direction, vec);
    double value = distance / radius;
    value = max(-1.0, min(1.0, value));
    double remain = sqrt(max(0.0, 1.0 - value * value));
    return 0.5 + (asin(value) + value * remain) / Pi;
}

void updateAnswer(double areaRatio, int count, int total, double &answer) {
    if (count < 0 || count > total) return;
    double value = fabs(areaRatio - (double)count / total);
    answer = max(answer, value);
}

void updateLine(Point center, Point point, double angle, double radius, int count, int total, double &answer) {
    double areaRatio = getAreaRatio(center, point, angle, radius);
    updateAnswer(areaRatio, count, total, answer);
    updateAnswer(areaRatio, count + 1, total, answer);
}

double normalizeAngle(double angle) {
    while (angle < 0) angle += Pi;
    while (angle >= Pi) angle -= Pi;
    return angle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int scenario = 1;
    while (true) {
        int centerX, centerY, radius, n;
        cin >> centerX >> centerY >> radius >> n;
        if (!cin || (centerX == 0 && centerY == 0 && radius == 0 && n == 0)) break;
        Point center = {(double)centerX, (double)centerY};
        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        double answer = 0.0;
        for (int i = 0; i < n; i++) {
            vector<Event> events;
            events.reserve(n - 1);
            int currentCount = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                Point vec = subtractPoint(points[j], points[i]);
                if (vec.y > 0 || (fabs(vec.y) < Eps && vec.x < 0)) currentCount++;
                double angle = atan2(vec.y, vec.x);
                angle = normalizeAngle(angle);
                events.push_back({angle, vec});
            }
            sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
                return a.angle < b.angle;
            });
            double centerDistance = hypot(center.x - points[i].x, center.y - points[i].y);
            double specialAngle = -1.0;
            if (centerDistance > Eps) {
                specialAngle = normalizeAngle(atan2(center.y - points[i].y, center.x - points[i].x) - Pi / 2.0);
            }
            int index = 0;
            int zeroBeforeCount = currentCount;
            int zeroDelta = 0;
            while (index < (int)events.size() && events[index].angle < Eps) {
                Point direction = {1.0, 0.0};
                double derivative = -dotProduct(direction, events[index].vec);
                int delta = derivative > 0 ? 1 : -1;
                zeroBeforeCount -= delta;
                zeroDelta += delta;
                index++;
            }
            if (index > 0) {
                updateLine(center, points[i], 0.0, radius, zeroBeforeCount, n, answer);
                updateLine(center, points[i], 0.0, radius, currentCount, n, answer);
            } else {
                updateLine(center, points[i], 0.0, radius, currentCount, n, answer);
            }
            double previousAngle = 0.0;
            if (specialAngle > Eps && specialAngle < Pi - Eps) {
                if (specialAngle < (index < (int)events.size() ? events[index].angle : Pi) - Eps)
                    updateLine(center, points[i], specialAngle, radius, currentCount, n, answer);
            }
            while (index < (int)events.size()) {
                double angle = events[index].angle;
                if (specialAngle > previousAngle + Eps && specialAngle < angle - Eps)
                    updateLine(center, points[i], specialAngle, radius, currentCount, n, answer);
                Point direction = {cos(angle), sin(angle)};
                double derivative = -dotProduct(direction, events[index].vec);
                int delta = derivative > 0 ? 1 : -1;
                int beforeCount = currentCount;
                int afterCount = currentCount + delta;
                updateLine(center, points[i], angle, radius, beforeCount, n, answer);
                updateLine(center, points[i], angle, radius, afterCount, n, answer);
                currentCount = afterCount;
                previousAngle = angle;
                index++;
            }
            if (specialAngle > previousAngle + Eps && specialAngle < Pi - Eps)
                updateLine(center, points[i], specialAngle, radius, currentCount, n, answer);
        }
        cout << "Scenario " << scenario++ << ": " << fixed << setprecision(6) << answer << '\n';
    }
    return 0;
}
