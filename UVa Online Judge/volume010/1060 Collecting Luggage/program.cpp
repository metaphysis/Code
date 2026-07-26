// Collecting Luggage
// UVa ID: 1060
// Verdict: Accepted
// Submission Date: 2026-07-25
// UVa Run Time: 0.180s
// https://blog.csdn.net/metaphysis/article/details/163183420

#include <bits/stdc++.h>
using namespace std;

const long double epsilonValue = 1e-10L;
const long double infinityValue = 1e100L;

struct Point {
    long double x;
    long double y;
    Point() {}
    Point(long double xValue, long double yValue) {
        x = xValue;
        y = yValue;
    }
    Point operator +(const Point &other) const {
        return Point(x + other.x, y + other.y);
    }
    Point operator -(const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
    Point operator *(long double value) const {
        return Point(x * value, y * value);
    }
};

long double crossProduct(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

long double crossProduct(const Point &a, const Point &b, const Point &c) {
    return crossProduct(b - a, c - a);
}

long double dotProduct(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

long double distanceBetween(const Point &a, const Point &b) {
    long double deltaX = a.x - b.x;
    long double deltaY = a.y - b.y;
    return sqrtl(deltaX * deltaX + deltaY * deltaY);
}

bool isPointOnSegment(const Point &point, const Point &a, const Point &b) {
    if (fabsl(crossProduct(a, b, point)) > epsilonValue) return false;
    return dotProduct(point - a, point - b) <= epsilonValue;
}

bool isStrictlyInside(const Point &point, const vector<Point> &polygon) {
    int vertexCount = polygon.size();
    for (int i = 0; i < vertexCount; i++) {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % vertexCount];
        if (isPointOnSegment(point, a, b)) return false;
    }
    bool inside = false;
    for (int i = 0, j = vertexCount - 1; i < vertexCount; j = i++) {
        const Point &a = polygon[i];
        const Point &b = polygon[j];
        bool crosses = ((a.y > point.y) != (b.y > point.y));
        if (crosses) {
            long double crossX = (b.x - a.x) * (point.y - a.y) / (b.y - a.y) + a.x;
            if (point.x < crossX) inside = !inside;
        }
    }
    return inside;
}

bool isVisible(const Point &a, const Point &b, const vector<Point> &polygon) {
    Point direction = b - a;
    vector<long double> parameters;
    parameters.push_back(0.0L);
    parameters.push_back(1.0L);
    int vertexCount = polygon.size();
    for (int i = 0; i < vertexCount; i++) {
        Point c = polygon[i];
        Point d = polygon[(i + 1) % vertexCount];
        Point edge = d - c;
        long double denominator = crossProduct(direction, edge);
        if (fabsl(denominator) <= epsilonValue) {
            if (fabsl(crossProduct(a, direction, c)) <= epsilonValue) {
                long double directionLengthSquared = dotProduct(direction, direction);
                if (directionLengthSquared > epsilonValue) {
                    long double firstParameter = dotProduct(c - a, direction) / directionLengthSquared;
                    long double secondParameter = dotProduct(d - a, direction) / directionLengthSquared;
                    if (firstParameter >= -epsilonValue && firstParameter <= 1.0L + epsilonValue) {
                        parameters.push_back(max(0.0L, min(1.0L, firstParameter)));
                    }
                    if (secondParameter >= -epsilonValue && secondParameter <= 1.0L + epsilonValue) {
                        parameters.push_back(max(0.0L, min(1.0L, secondParameter)));
                    }
                }
            }
            continue;
        }
        long double firstParameter = crossProduct(c - a, edge) / denominator;
        long double secondParameter = crossProduct(c - a, direction) / denominator;
        if (firstParameter >= -epsilonValue && firstParameter <= 1.0L + epsilonValue &&
            secondParameter >= -epsilonValue && secondParameter <= 1.0L + epsilonValue) {
            parameters.push_back(max(0.0L, min(1.0L, firstParameter)));
        }
    }
    sort(parameters.begin(), parameters.end());
    vector<long double> uniqueParameters;
    for (long double parameter : parameters) {
        if (uniqueParameters.empty() || fabsl(parameter - uniqueParameters.back()) > epsilonValue) {
            uniqueParameters.push_back(parameter);
        }
    }
    for (int i = 0; i + 1 < (int)uniqueParameters.size(); i++) {
        if (uniqueParameters[i + 1] - uniqueParameters[i] <= epsilonValue) continue;
        long double middleParameter = (uniqueParameters[i] + uniqueParameters[i + 1]) / 2.0L;
        Point middlePoint = a + direction * middleParameter;
        if (isStrictlyInside(middlePoint, polygon)) return false;
    }
    return true;
}

long double getDistanceToBoundaryPoint(const Point &passengerPoint, const Point &boundaryPoint,
                                       const vector<Point> &polygon,
                                       const vector<long double> &shortestDistance) {
    long double answer = infinityValue;
    if (isVisible(passengerPoint, boundaryPoint, polygon)) {
        answer = distanceBetween(passengerPoint, boundaryPoint);
    }
    int vertexCount = polygon.size();
    for (int i = 0; i < vertexCount; i++) {
        if (shortestDistance[i] >= infinityValue / 2.0L) continue;
        if (isVisible(polygon[i], boundaryPoint, polygon)) {
            answer = min(answer, shortestDistance[i] + distanceBetween(polygon[i], boundaryPoint));
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase = 1;
    int vertexCount;
    while (cin >> vertexCount && vertexCount != 0) {
        vector<Point> polygon(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            long double x;
            long double y;
            cin >> x >> y;
            polygon[i] = Point(x, y);
        }
        Point passengerPoint;
        cin >> passengerPoint.x >> passengerPoint.y;
        long double luggageSpeed;
        long double passengerSpeed;
        cin >> luggageSpeed >> passengerSpeed;
        vector<long double> edgeLength(vertexCount);
        vector<long double> prefixLength(vertexCount + 1, 0.0L);
        for (int i = 0; i < vertexCount; i++) {
            edgeLength[i] = distanceBetween(polygon[i], polygon[(i + 1) % vertexCount]);
            prefixLength[i + 1] = prefixLength[i] + edgeLength[i];
        }
        long double perimeter = prefixLength[vertexCount];
        int graphSize = vertexCount + 1;
        vector<vector<long double>> graph(graphSize, vector<long double>(graphSize, infinityValue));
        for (int i = 0; i < graphSize; i++) graph[i][i] = 0.0L;
        for (int i = 0; i < graphSize; i++) {
            Point firstPoint = i == vertexCount ? passengerPoint : polygon[i];
            for (int j = i + 1; j < graphSize; j++) {
                Point secondPoint = j == vertexCount ? passengerPoint : polygon[j];
                if (isVisible(firstPoint, secondPoint, polygon)) {
                    long double edgeCost = distanceBetween(firstPoint, secondPoint);
                    graph[i][j] = edgeCost;
                    graph[j][i] = edgeCost;
                }
            }
        }
        for (int k = 0; k < graphSize; k++) {
            for (int i = 0; i < graphSize; i++) {
                for (int j = 0; j < graphSize; j++) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
        vector<long double> shortestDistance(vertexCount);
        for (int i = 0; i < vertexCount; i++) shortestDistance[i] = graph[vertexCount][i];
        auto canCatch = [&](long double time) {
            long double traveledDistance = luggageSpeed * time;
            long double positionDistance = fmodl(traveledDistance, perimeter);
            if (positionDistance < 0.0L) positionDistance += perimeter;
            int edgeIndex = 0;
            while (edgeIndex + 1 < vertexCount && positionDistance > prefixLength[edgeIndex + 1] - epsilonValue) {
                edgeIndex++;
            }
            long double localDistance = positionDistance - prefixLength[edgeIndex];
            if (localDistance < 0.0L) localDistance = 0.0L;
            long double ratio = edgeLength[edgeIndex] <= epsilonValue ? 0.0L : localDistance / edgeLength[edgeIndex];
            Point boundaryPoint = polygon[edgeIndex] +
                                  (polygon[(edgeIndex + 1) % vertexCount] - polygon[edgeIndex]) * ratio;
            long double shortestPath = getDistanceToBoundaryPoint(passengerPoint, boundaryPoint,
                                                                  polygon, shortestDistance);
            return shortestPath <= passengerSpeed * time + 1e-9L;
        };
        long double lowerBound = 0.0L;
        long double upperBound = 1.0L;
        while (!canCatch(upperBound)) upperBound *= 2.0L;
        for (int iteration = 0; iteration < 100; iteration++) {
            long double middle = (lowerBound + upperBound) / 2.0L;
            if (canCatch(middle)) upperBound = middle;
            else lowerBound = middle;
        }
        long long totalSeconds = llround(upperBound * 60.0L);
        long long minutes = totalSeconds / 60;
        long long seconds = totalSeconds % 60;
        cout << "Case " << testCase++ << ": Time = " << minutes << ":"
             << setw(2) << setfill('0') << seconds << setfill('0') << '\n';
    }
    return 0;
}
