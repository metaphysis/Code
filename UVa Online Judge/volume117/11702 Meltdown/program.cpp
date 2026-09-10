// Meltdown
// UVa ID: 11702
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.050s

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double inf = 1e100;

struct Point {
    double x;
    double y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
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

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double length(Point a) {
    return sqrt(dot(a, a));
}

bool equalDouble(double a, double b) {
    return fabs(a - b) <= eps;
}

bool onSegment(Point p, Point a, Point b) {
    if (fabs(cross(p - a, b - a)) > eps)
        return false;
    return dot(p - a, p - b) <= eps;
}

bool pointInPolygonOrBoundary(Point p, const vector<Point> &polygon) {
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % n];
        if (onSegment(p, a, b))
            return true;
    }
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % n];
        bool crossHeight = (a.y > p.y) != (b.y > p.y);
        if (crossHeight) {
            double crossX = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (crossX > p.x)
                inside = !inside;
        }
    }
    return inside;
}

void addParameter(vector<double> &parameters, double value) {
    if (value < -eps || value > 1.0 + eps)
        return;
    value = max(0.0, min(1.0, value));
    parameters.push_back(value);
}

bool segmentInside(Point a, Point b, const vector<Point> &polygon) {
    Point direction = b - a;
    double directionLengthSquare = dot(direction, direction);
    vector<double> parameters;
    parameters.push_back(0.0);
    parameters.push_back(1.0);
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        Point c = polygon[i];
        Point d = polygon[(i + 1) % n];
        Point edge = d - c;
        double denominator = cross(direction, edge);
        if (fabs(denominator) > eps) {
            double t = cross(c - a, edge) / denominator;
            double u = cross(c - a, direction) / denominator;
            if (t >= -eps && t <= 1.0 + eps && u >= -eps && u <= 1.0 + eps)
                addParameter(parameters, t);
        } else if (fabs(cross(c - a, direction)) <= eps && directionLengthSquare > eps) {
            double t1 = dot(c - a, direction) / directionLengthSquare;
            double t2 = dot(d - a, direction) / directionLengthSquare;
            addParameter(parameters, t1);
            addParameter(parameters, t2);
        }
    }
    sort(parameters.begin(), parameters.end());
    vector<double> uniqueParameters;
    for (double value : parameters) {
        if (uniqueParameters.empty() || !equalDouble(value, uniqueParameters.back()))
            uniqueParameters.push_back(value);
    }
    for (int i = 0; i + 1 < (int)uniqueParameters.size(); i++) {
        double left = uniqueParameters[i];
        double right = uniqueParameters[i + 1];
        if (right - left <= eps)
            continue;
        double middle = (left + right) / 2.0;
        Point testPoint = a + direction * middle;
        if (!pointInPolygonOrBoundary(testPoint, polygon))
            return false;
    }
    return true;
}

double getArrivalTime(Point start, Point target, Point edgeStart, Point edgeDirection, double parameter, double v, double c) {
    Point current = edgeStart + edgeDirection * parameter;
    return current.y / v + length(current - target) / c;
}

double minimizeOnInterval(Point target, Point edgeStart, Point edgeDirection, Point endPoint,
                          double left, double right, double v, double c) {
    for (int iteration = 0; iteration < 100; iteration++) {
        double middleLeft = (2.0 * left + right) / 3.0;
        double middleRight = (left + 2.0 * right) / 3.0;
        double valueLeft = getArrivalTime(edgeStart, target, edgeStart, edgeDirection, middleLeft, v, c);
        double valueRight = getArrivalTime(edgeStart, target, edgeStart, edgeDirection, middleRight, v, c);
        if (valueLeft < valueRight)
            right = middleRight;
        else
            left = middleLeft;
    }
    double parameter = (left + right) / 2.0;
    return getArrivalTime(edgeStart, target, edgeStart, edgeDirection, parameter, v, c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int targetX;
    int targetY;
    int v;
    int c;
    while (cin >> n >> targetX >> targetY >> v >> c) {
        if (n == 0 && targetX == 0 && targetY == 0 && v == 0 && c == 0)
            break;
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++)
            cin >> polygon[i].x >> polygon[i].y;
        Point target(targetX, targetY);
        vector<Point> nodes = polygon;
        nodes.push_back(target);
        int nodeCount = n + 1;
        vector<vector<pair<int, double>>> graph(nodeCount);
        for (int i = 0; i < nodeCount; i++) {
            for (int j = i + 1; j < nodeCount; j++) {
                if (segmentInside(nodes[i], nodes[j], polygon)) {
                    double distance = length(nodes[i] - nodes[j]);
                    graph[i].push_back({j, distance});
                    graph[j].push_back({i, distance});
                }
            }
        }
        vector<double> shortestDistance(nodeCount, inf);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> queue;
        shortestDistance[n] = 0.0;
        queue.push({0.0, n});
        while (!queue.empty()) {
            double currentDistance = queue.top().first;
            int currentNode = queue.top().second;
            queue.pop();
            if (currentDistance > shortestDistance[currentNode] + eps)
                continue;
            for (auto edge : graph[currentNode]) {
                int nextNode = edge.first;
                double nextDistance = currentDistance + edge.second;
                if (nextDistance + eps < shortestDistance[nextNode]) {
                    shortestDistance[nextNode] = nextDistance;
                    queue.push({nextDistance, nextNode});
                }
            }
        }
        double answer = inf;
        for (int edgeIndex = 0; edgeIndex < n; edgeIndex++) {
            Point edgeStart = polygon[edgeIndex];
            Point edgeEnd = polygon[(edgeIndex + 1) % n];
            Point edgeDirection = edgeEnd - edgeStart;
            for (int destinationIndex = 0; destinationIndex < nodeCount; destinationIndex++) {
                Point destination = nodes[destinationIndex];
                vector<double> parameters;
                parameters.push_back(0.0);
                parameters.push_back(1.0);
                for (int vertexIndex = 0; vertexIndex < n; vertexIndex++) {
                    Point vertex = polygon[vertexIndex];
                    double denominator = cross(edgeDirection, vertex - destination);
                    if (fabs(denominator) > eps) {
                        double value = -cross(edgeStart - destination, vertex - destination) / denominator;
                        addParameter(parameters, value);
                    }
                }
                sort(parameters.begin(), parameters.end());
                vector<double> uniqueParameters;
                for (double value : parameters) {
                    if (uniqueParameters.empty() || !equalDouble(value, uniqueParameters.back()))
                        uniqueParameters.push_back(value);
                }
                for (double parameter : uniqueParameters) {
                    Point source = edgeStart + edgeDirection * parameter;
                    if (segmentInside(source, destination, polygon)) {
                        double currentTime = source.y / v + length(source - destination) / c;
                        if (destinationIndex < n)
                            currentTime += shortestDistance[destinationIndex] / c;
                        answer = min(answer, currentTime);
                    }
                }
                for (int i = 0; i + 1 < (int)uniqueParameters.size(); i++) {
                    double left = uniqueParameters[i];
                    double right = uniqueParameters[i + 1];
                    if (right - left <= eps)
                        continue;
                    double middle = (left + right) / 2.0;
                    Point middlePoint = edgeStart + edgeDirection * middle;
                    if (!segmentInside(middlePoint, destination, polygon))
                        continue;
                    double currentTime = minimizeOnInterval(
                        target,
                        edgeStart,
                        edgeDirection,
                        destination,
                        left,
                        right,
                        v,
                        c
                    );
                    if (destinationIndex < n)
                        currentTime += shortestDistance[destinationIndex] / c;
                    answer = min(answer, currentTime);
                }
            }
        }
        cout << fixed << setprecision(4) << answer + 1e-9 << '\n';
    }
    return 0;
}
