// Navigation
// UVa ID: 1034
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163183178

#include <bits/stdc++.h>
using namespace std;

const double Pi = acos(-1.0);
const double Epsilon = 1e-8;
const double DistanceTolerance = 0.1;

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double radius;
};

double getDistance(const Point &firstPoint, const Point &secondPoint) {
    return hypot(firstPoint.x - secondPoint.x, firstPoint.y - secondPoint.y);
}

bool isSameCircle(const Circle &firstCircle, const Circle &secondCircle) {
    return getDistance(firstCircle.center, secondCircle.center) <= Epsilon &&
           fabs(firstCircle.radius - secondCircle.radius) <= Epsilon;
}

void addCandidate(vector<Point> &candidates, const Point &point) {
    for (const Point &candidate : candidates)
        if (getDistance(candidate, point) <= DistanceTolerance) return;
    candidates.push_back(point);
}

void getCircleIntersections(const Circle &firstCircle, const Circle &secondCircle, vector<Point> &candidates) {
    double deltaX = secondCircle.center.x - firstCircle.center.x;
    double deltaY = secondCircle.center.y - firstCircle.center.y;
    double centerDistance = hypot(deltaX, deltaY);
    if (centerDistance <= Epsilon) return;
    if (centerDistance > firstCircle.radius + secondCircle.radius + Epsilon) return;
    if (centerDistance < fabs(firstCircle.radius - secondCircle.radius) - Epsilon) return;
    double projection = (firstCircle.radius * firstCircle.radius -
                         secondCircle.radius * secondCircle.radius +
                         centerDistance * centerDistance) /
                        (2.0 * centerDistance);
    double heightSquared = firstCircle.radius * firstCircle.radius - projection * projection;
    if (heightSquared < -Epsilon) return;
    heightSquared = max(0.0, heightSquared);
    double height = sqrt(heightSquared);
    double baseX = firstCircle.center.x + projection * deltaX / centerDistance;
    double baseY = firstCircle.center.y + projection * deltaY / centerDistance;
    Point firstPoint;
    firstPoint.x = baseX - height * deltaY / centerDistance;
    firstPoint.y = baseY + height * deltaX / centerDistance;
    addCandidate(candidates, firstPoint);
    if (height <= Epsilon) return;
    Point secondPoint;
    secondPoint.x = baseX + height * deltaY / centerDistance;
    secondPoint.y = baseY - height * deltaX / centerDistance;
    addCandidate(candidates, secondPoint);
}

bool isValidCandidate(const Point &point, const vector<Circle> &circles) {
    for (const Circle &circle : circles)
        if (fabs(getDistance(point, circle.center) - circle.radius) > DistanceTolerance + Epsilon) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int trialNumber = 0;
    int n;
    while (cin >> n) {
        double receiveTime;
        double destinationX;
        double destinationY;
        cin >> receiveTime >> destinationX >> destinationY;
        if (n == 0) break;
        ++trialNumber;
        vector<Circle> circles;
        bool hasInvalidSignal = false;
        for (int i = 0; i < n; ++i) {
            double initialX;
            double initialY;
            double direction;
            double signalTime;
            cin >> initialX >> initialY >> direction >> signalTime;
            double angle = direction * Pi / 180.0;
            Circle circle;
            circle.center.x = initialX + 100.0 * sin(angle) * signalTime;
            circle.center.y = initialY + 100.0 * cos(angle) * signalTime;
            circle.radius = 350.0 * (receiveTime - signalTime);
            if (circle.radius < -Epsilon) hasInvalidSignal = true;
            circle.radius = max(0.0, circle.radius);
            circles.push_back(circle);
        }
        cout << "Trial " << trialNumber << ": ";
        if (hasInvalidSignal) {
            cout << "Inconsistent\n";
            continue;
        }
        bool allSame = true;
        for (int i = 1; i < n; ++i)
            if (!isSameCircle(circles[0], circles[i])) {
                allSame = false;
                break;
            }
        if (allSame) {
            if (circles[0].radius > Epsilon) {
                cout << "Inconclusive\n";
                continue;
            }
            Point receiver = circles[0].center;
            double distanceToDestination = hypot(receiver.x - destinationX, receiver.y - destinationY);
            if (distanceToDestination <= DistanceTolerance) {
                cout << "Arrived\n";
                continue;
            }
            double heading = atan2(destinationX - receiver.x, destinationY - receiver.y) * 180.0 / Pi;
            if (heading < 0.0) heading += 360.0;
            int roundedHeading = static_cast<int>(floor(heading + 0.5));
            if (roundedHeading == 360) roundedHeading = 0;
            cout << roundedHeading << " degrees\n";
            continue;
        }
        vector<Point> candidates;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                getCircleIntersections(circles[i], circles[j], candidates);
        vector<Point> validCandidates;
        for (const Point &candidate : candidates)
            if (isValidCandidate(candidate, circles)) addCandidate(validCandidates, candidate);
        if (validCandidates.empty()) {
            cout << "Inconsistent\n";
            continue;
        }
        if (validCandidates.size() > 1) {
            cout << "Inconclusive\n";
            continue;
        }
        Point receiver = validCandidates[0];
        double distanceToDestination = hypot(receiver.x - destinationX, receiver.y - destinationY);
        if (distanceToDestination <= DistanceTolerance) {
            cout << "Arrived\n";
            continue;
        }
        double heading = atan2(destinationX - receiver.x, destinationY - receiver.y) * 180.0 / Pi;
        if (heading < 0.0) heading += 360.0;
        int roundedHeading = static_cast<int>(floor(heading + 0.5));
        if (roundedHeading == 360) roundedHeading = 0;
        cout << roundedHeading << " degrees\n";
    }
    return 0;
}
