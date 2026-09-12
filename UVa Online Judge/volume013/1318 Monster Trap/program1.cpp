// Monster Trap
// UVa ID: 1318
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct Point {
    double x;
    double y;
};

struct Segment {
    Point start;
    Point end;
};

Point operator + (const Point &a, const Point &b) { return {a.x + b.x, a.y + b.y}; }
Point operator - (const Point &a, const Point &b) { return {a.x - b.x, a.y - b.y}; }
Point operator * (const Point &a, double k) { return {a.x * k, a.y * k}; }
double crossProduct(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double dotProduct(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

double polygonArea(const vector<Point> &polygon) {
    double area = 0;
    int size = polygon.size();
    for (int i = 0; i < size; i++) {
        int next = (i + 1) % size;
        area += crossProduct(polygon[i], polygon[next]);
    }
    return area / 2;
}

bool isOriginInside(const vector<Point> &polygon) {
    int windingNumber = 0;
    int size = polygon.size();
    Point origin = {0, 0};
    for (int i = 0; i < size; i++) {
        Point first = polygon[i];
        Point second = polygon[(i + 1) % size];
        if (first.y <= origin.y && second.y > origin.y && crossProduct(second - first, origin - first) > EPS)
            windingNumber++;
        else if (first.y > origin.y && second.y <= origin.y && crossProduct(second - first, origin - first) < -EPS)
            windingNumber--;
    }
    return windingNumber != 0;
}

bool getIntersection(const Segment &first, const Segment &second, Point &intersection, double &firstParameter) {
    Point firstVector = first.end - first.start;
    Point secondVector = second.end - second.start;
    Point difference = second.start - first.start;
    double denominator = crossProduct(firstVector, secondVector);
    if (fabsl(denominator) < EPS)
        return false;
    double secondParameter = crossProduct(difference, firstVector) / denominator;
    firstParameter = crossProduct(difference, secondVector) / denominator;
    if (firstParameter < -EPS || firstParameter > 1 + EPS || secondParameter < -EPS || secondParameter > 1 + EPS)
        return false;
    intersection = first.start + firstVector * firstParameter;
    return true;
}

int getVertexId(const Point &point, vector<Point> &vertices) {
    for (int i = 0; i < (int)vertices.size(); i++)
        if (fabsl(vertices[i].x - point.x) < EPS && fabsl(vertices[i].y - point.y) < EPS)
            return i;
    vertices.push_back(point);
    return vertices.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<Segment> segments(n);
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments[i] = {{(double)x1, (double)y1}, {(double)x2, (double)y2}};
        }
        vector<Point> vertices;
        vector<vector<pair<double, int>>> segmentPoints(n);
        for (int i = 0; i < n; i++) {
            Point vector = segments[i].end - segments[i].start;
            double lengthSquared = dotProduct(vector, vector);
            int startId = getVertexId(segments[i].start, vertices);
            int endId = getVertexId(segments[i].end, vertices);
            segmentPoints[i].push_back({0, startId});
            segmentPoints[i].push_back({1, endId});
            for (int j = i + 1; j < n; j++) {
                Point intersection;
                double parameter;
                if (getIntersection(segments[i], segments[j], intersection, parameter)) {
                    int vertexId = getVertexId(intersection, vertices);
                    segmentPoints[i].push_back({parameter, vertexId});
                    Point otherVector = segments[j].end - segments[j].start;
                    double otherLengthSquared = dotProduct(otherVector, otherVector);
                    double otherParameter = dotProduct(intersection - segments[j].start, otherVector) / otherLengthSquared;
                    segmentPoints[j].push_back({otherParameter, vertexId});
                }
            }
        }
        vector<set<int>> graph(vertices.size());
        for (int i = 0; i < n; i++) {
            auto &points = segmentPoints[i];
            sort(points.begin(), points.end(), [](const pair<double, int> &a, const pair<double, int> &b) {
                return a.first < b.first;
            });
            vector<int> orderedVertices;
            for (auto &item : points)
                if (orderedVertices.empty() || orderedVertices.back() != item.second)
                    orderedVertices.push_back(item.second);
            for (int j = 0; j + 1 < (int)orderedVertices.size(); j++) {
                int first = orderedVertices[j];
                int second = orderedVertices[j + 1];
                if (first != second) {
                    graph[first].insert(second);
                    graph[second].insert(first);
                }
            }
        }
        vector<vector<int>> adjacency(vertices.size());
        for (int i = 0; i < (int)vertices.size(); i++) {
            for (int next : graph[i])
                adjacency[i].push_back(next);
            sort(adjacency[i].begin(), adjacency[i].end(), [&](int a, int b) {
                double angleA = atan2l(vertices[a].y - vertices[i].y, vertices[a].x - vertices[i].x);
                double angleB = atan2l(vertices[b].y - vertices[i].y, vertices[b].x - vertices[i].x);
                return angleA < angleB;
            });
        }
        map<pair<int, int>, bool> visited;
        bool trapped = false;
        for (int start = 0; start < (int)vertices.size(); start++) {
            for (int next : adjacency[start]) {
                if (visited[{start, next}]) continue;
                vector<int> faceVertices;
                int current = start;
                int following = next;
                while (!visited[{current, following}]) {
                    visited[{current, following}] = true;
                    faceVertices.push_back(current);
                    int position = 0;
                    while (adjacency[following][position] != current)
                        position++;
                    int degree = adjacency[following].size();
                    int nextPosition = (position - 1 + degree) % degree;
                    int newCurrent = following;
                    int newFollowing = adjacency[following][nextPosition];
                    current = newCurrent;
                    following = newFollowing;
                }
                if (faceVertices.size() < 3) continue;
                vector<Point> polygon;
                for (int vertexId : faceVertices)
                    polygon.push_back(vertices[vertexId]);
                if (polygonArea(polygon) > EPS && isOriginInside(polygon)) {
                    trapped = true;
                    break;
                }
            }
            if (trapped) break;
        }
        cout << (trapped ? "yes" : "no") << '\n';
    }
    return 0;
}
