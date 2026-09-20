#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100;
const double eps = 1e-9;

struct Point {
    double x, y;
};

Point operator + (Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator - (Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator * (Point a, double k) {
    return {a.x * k, a.y * k};
}

Point operator / (Point a, double k) {
    return {a.x / k, a.y / k};
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double getLength(Point a) {
    return sqrt(dot(a, a));
}

double getDistance(Point a, Point b) {
    return getLength(a - b);
}

Point getLeftNormal(Point a) {
    return {-a.y, a.x};
}

Point getReflection(Point p, Point a, Point b) {
    Point d = b - a;
    Point projection = a + d * (dot(p - a, d) / dot(d, d));
    return projection * 2.0 - p;
}

bool isVisible(Point a, Point b) {
    double low = 0.0, high = 1.0;
    double av[2] = {a.x, a.y}, dv[2] = {b.x - a.x, b.y - a.y};
    for (int i = 0; i < 2; i++) {
        if (fabs(dv[i]) < eps) {
            if (av[i] <= -10.0 + eps || av[i] >= 10.0 - eps) return true;
        } else {
            double t1 = (-10.0 - av[i]) / dv[i], t2 = (10.0 - av[i]) / dv[i];
            if (t1 > t2) swap(t1, t2);
            low = max(low, t1);
            high = min(high, t2);
        }
    }
    return low >= high - eps;
}

vector<double> getShortestDistances(const vector<Point> &points, int source) {
    int n = points.size();
    vector<double> distances(n, inf);
    vector<int> used(n, 0);
    distances[source] = 0.0;
    for (int step = 0; step < n; step++) {
        int current = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (current == -1 || distances[i] < distances[current])) current = i;
        if (current == -1) break;
        used[current] = 1;
        for (int next = 0; next < n; next++) {
            if (!isVisible(points[current], points[next])) continue;
            double newDistance = distances[current] + getDistance(points[current], points[next]);
            if (newDistance < distances[next]) distances[next] = newDistance;
        }
    }
    return distances;
}

double getGroundDistance(Point a, Point b, const vector<Point> &corners) {
    vector<Point> points = {a, b};
    for (Point corner : corners) points.push_back(corner);
    return getShortestDistances(points, 0)[1];
}

vector<double> getAnchorDistances(Point p, const vector<Point> &corners) {
    vector<Point> points = {p};
    for (Point corner : corners) points.push_back(corner);
    return getShortestDistances(points, 0);
}

bool getIntersection(Point start, Point finish, Point a, Point b, double &lineRatio, double &edgeRatio) {
    Point lineDirection = finish - start, edgeDirection = b - a;
    double denominator = cross(lineDirection, edgeDirection);
    if (fabs(denominator) < eps) return false;
    lineRatio = cross(a - start, edgeDirection) / denominator;
    edgeRatio = cross(a - start, lineDirection) / denominator;
    if (lineRatio < -eps || lineRatio > 1.0 + eps) return false;
    if (edgeRatio < -eps || edgeRatio > 1.0 + eps) return false;
    lineRatio = min(1.0, max(0.0, lineRatio));
    edgeRatio = min(1.0, max(0.0, edgeRatio));
    return true;
}

Point mapToUnfoldedGround(Point p, int side, Point u, Point v, Point apex, const vector<Point> &corners) {
    Point actualU = corners[side], actualV = corners[(side + 1) % 4];
    Point actualDirection = (actualV - actualU) / 20.0;
    Point actualNormal = getLeftNormal(actualDirection);
    Point targetDirection = (v - u) / 20.0;
    Point targetNormal = getLeftNormal(targetDirection);
    if (cross(v - u, apex - u) < 0.0) targetNormal = targetNormal * -1.0;
    double along = dot(p - actualU, actualDirection), inward = dot(p - actualU, actualNormal);
    return u + targetDirection * along + targetNormal * inward;
}

double getSurfaceDistance(Point startAnchor, Point finishAnchor, double prefix, double suffix, int firstSide, int direction, int faceCount, double height, const vector<Point> &corners) {
    int currentSide = firstSide;
    Point u = corners[currentSide], v = corners[(currentSide + 1) % 4];
    Point baseDirection = (v - u) / 20.0;
    double slantHeight = sqrt(height * height + 100.0);
    Point apex = (u + v) / 2.0 + getLeftNormal(baseDirection) * slantHeight;
    vector<pair<Point, Point>> edges;
    edges.push_back({u, v});
    for (int i = 1; i < faceCount; i++) {
        if (direction == 1) {
            edges.push_back({v, apex});
            Point newV = getReflection(u, v, apex);
            u = v;
            v = newV;
            currentSide = (currentSide + 1) % 4;
        } else {
            edges.push_back({u, apex});
            Point newU = getReflection(v, u, apex);
            v = u;
            u = newU;
            currentSide = (currentSide + 3) % 4;
        }
    }
    edges.push_back({u, v});
    Point unfoldedFinish = mapToUnfoldedGround(finishAnchor, currentSide, u, v, apex, corners);
    double previousRatio = -eps, firstEdgeRatio = 0.0, lastEdgeRatio = 0.0;
    for (int i = 0; i < (int)edges.size(); i++) {
        double lineRatio, edgeRatio;
        if (!getIntersection(startAnchor, unfoldedFinish, edges[i].first, edges[i].second, lineRatio, edgeRatio)) return inf;
        if (lineRatio + eps < previousRatio) return inf;
        previousRatio = lineRatio;
        if (i == 0) firstEdgeRatio = edgeRatio;
        if (i + 1 == (int)edges.size()) lastEdgeRatio = edgeRatio;
    }
    Point entry = corners[firstSide] + (corners[(firstSide + 1) % 4] - corners[firstSide]) * firstEdgeRatio;
    Point exit = corners[currentSide] + (corners[(currentSide + 1) % 4] - corners[currentSide]) * lastEdgeRatio;
    if (!isVisible(startAnchor, entry)) return inf;
    if (!isVisible(exit, finishAnchor)) return inf;
    return prefix + getDistance(startAnchor, unfoldedFinish) + suffix;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Point> corners = {{-10.0, -10.0}, {10.0, -10.0}, {10.0, 10.0}, {-10.0, 10.0}};
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(10);
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        Point a, b;
        double height;
        cin >> a.x >> a.y >> b.x >> b.y >> height;
        vector<Point> startAnchors = {a}, finishAnchors = {b};
        for (Point corner : corners) {
            startAnchors.push_back(corner);
            finishAnchors.push_back(corner);
        }
        vector<double> startDistances = getAnchorDistances(a, corners);
        vector<double> finishDistances = getAnchorDistances(b, corners);
        double answer = getGroundDistance(a, b, corners);
        for (int firstSide = 0; firstSide < 4; firstSide++) {
            for (int direction : {-1, 1}) {
                for (int faceCount = 1; faceCount <= 4; faceCount++) {
                    for (int startIndex = 0; startIndex < 5; startIndex++) {
                        for (int finishIndex = 0; finishIndex < 5; finishIndex++) {
                            double candidate = getSurfaceDistance(startAnchors[startIndex], finishAnchors[finishIndex], startDistances[startIndex], finishDistances[finishIndex], firstSide, direction, faceCount, height, corners);
                            answer = min(answer, candidate);
                        }
                    }
                }
            }
        }
        cout << "Case " << caseNumber << ": " << answer << '\n';
    }
    return 0;
}
