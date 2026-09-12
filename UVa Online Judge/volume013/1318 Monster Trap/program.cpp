// Monster Trap
// UVa ID: 1318
// Verdict: Accepted
// Submission Date: 2026-08-02
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

int graph[210][210];
bool visited[210];

double cmpd(double value) {
    if (fabs(value) < EPS) return 0;
    return value > 0 ? 1 : -1;
}

Vector operator + (const Vector &a, const Vector &b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Vector &a, const Vector &b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &v, double f) { return Vector(v.x * f, v.y * f); }
Vector operator / (const Vector &v, double f) { return Vector(v.x / f, v.y / f); }

double dot(const Vector &a, const Vector &b) { return a.x * b.x + a.y * b.y; }
double cp(const Vector &a, const Vector &b) { return a.x * b.y - a.y * b.x; }
double norm(const Vector &v) { return sqrt(dot(v, v)); }

bool isPointOnSegment(const Point &point, const Point &start, const Point &end) {
    if (cmpd(cp(start - point, end - point)) != 0) return false;
    return cmpd(dot(start - point, end - point)) < 0;
}

bool isOnOtherSegment(const Point &point, const vector<Point> &segmentEndpoints) {
    int segmentCount = segmentEndpoints.size() / 2;
    for (int i = 0; i < segmentCount; i++)
        if (isPointOnSegment(point, segmentEndpoints[i * 2], segmentEndpoints[i * 2 + 1]))
            return true;
    return false;
}

int collectCandidatePoints(const vector<Point> &segmentEndpoints, vector<Point> &candidatePoints) {
    int segmentCount = segmentEndpoints.size() / 2;
    for (int i = 0; i < segmentCount; i++) {
        Point a = segmentEndpoints[i * 2];
        Point b = segmentEndpoints[i * 2 + 1];
        if (!isOnOtherSegment(a, segmentEndpoints))
            candidatePoints.push_back(a);
        if (!isOnOtherSegment(b, segmentEndpoints))
            candidatePoints.push_back(b);
    }
    return candidatePoints.size();
}

bool isSegmentIntersection(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
    double cp1 = cp(q1 - p1, q2 - p1);
    double cp2 = cp(q1 - p2, q2 - p2);
    double cp3 = cp(p1 - q1, p2 - q1);
    double cp4 = cp(p1 - q2, p2 - q2);
    return cmpd(cp1) * cmpd(cp2) < 0 &&
           cmpd(cp3) * cmpd(cp4) < 0;
}

void buildVisibilityGraph(const vector<Point> &candidatePoints, const vector<Point> &segmentEndpoints) {
    int vertexCount = candidatePoints.size();
    int segmentCount = segmentEndpoints.size() / 2;
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < vertexCount; i++)
        for (int j = i + 1; j < vertexCount; j++) {
            bool canConnect = true;
            for (int k = 0; k < segmentCount; k++)
                if (isSegmentIntersection(candidatePoints[i], candidatePoints[j],
                                           segmentEndpoints[k * 2], segmentEndpoints[k * 2 + 1])) {
                    canConnect = false;
                    break;
                }
            if (canConnect) graph[i][j] = graph[j][i] = 1;
        }
}

void dfs(int current, int vertexCount) {
    visited[current] = true;
    for (int next = 0; next < vertexCount; next++)
        if (graph[current][next] && !visited[next])
            dfs(next, vertexCount);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int segmentCount;
    while (cin >> segmentCount && segmentCount) {
        vector<Point> segmentEndpoints;
        for (int i = 0; i < segmentCount; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Point a(x1, y1);
            Point b(x2, y2);
            Vector direction = (b - a) / norm(b - a);
            a = a - direction * 1e-6;
            b = b + direction * 1e-6;
            segmentEndpoints.push_back(a);
            segmentEndpoints.push_back(b);
        }
        vector<Point> candidatePoints;
        collectCandidatePoints(segmentEndpoints, candidatePoints);
        candidatePoints.push_back(Point(0, 0));
        candidatePoints.push_back(Point(1000, 1000));
        buildVisibilityGraph(candidatePoints, segmentEndpoints);
        memset(visited, 0, sizeof(visited));
        int originIndex = candidatePoints.size() - 2;
        int outsideIndex = candidatePoints.size() - 1;
        dfs(originIndex, candidatePoints.size());
        if (visited[outsideIndex]) cout << "no\n";
        else cout << "yes\n";
    }
    return 0;
}
