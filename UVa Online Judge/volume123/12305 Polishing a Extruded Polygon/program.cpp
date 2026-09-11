#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10L;
const long double keyScale = 1e8L;

struct Point2 {
    long double x, y;
};

struct Point3 {
    long double x, y, z;
};

struct Triangle {
    Point3 a, b, c;
};

struct PointKey {
    long long x, y, z;
    bool operator < (const PointKey &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

struct SegmentKey {
    PointKey a, b;
    bool operator < (const SegmentKey &other) const {
        if (a.x != other.a.x) return a.x < other.a.x;
        if (a.y != other.a.y) return a.y < other.a.y;
        if (a.z != other.a.z) return a.z < other.a.z;
        if (b.x != other.b.x) return b.x < other.b.x;
        if (b.y != other.b.y) return b.y < other.b.y;
        return b.z < other.b.z;
    }
};

struct Segment {
    Point3 a, b;
};

int n, h, m;
vector<Point2> poly;
vector<Triangle> mesh;
long double cutA, cutB, cutC, cutD;

Point3 addPoint(const Point3 &a, const Point3 &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Point3 subPoint(const Point3 &a, const Point3 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point3 mulPoint(const Point3 &a, long double k) {
    return {a.x * k, a.y * k, a.z * k};
}

long double dotPoint(const Point3 &a, const Point3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3 crossPoint(const Point3 &a, const Point3 &b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

long double normPoint(const Point3 &a) {
    return sqrtl(dotPoint(a, a));
}

Point3 normalizePoint(const Point3 &a) {
    long double len = normPoint(a);
    return mulPoint(a, 1.0L / len);
}

PointKey getPointKey(const Point3 &p) {
    return {
        llround(p.x * keyScale),
        llround(p.y * keyScale),
        llround(p.z * keyScale)
    };
}

long double cross2(const Point2 &a, const Point2 &b, const Point2 &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double polygonArea2(const vector<Point2> &points) {
    long double result = 0;
    int size = points.size();
    for (int i = 0; i < size; i++) {
        int j = (i + 1) % size;
        result += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return result;
}

bool pointInTriangle(const Point2 &p, const Point2 &a, const Point2 &b, const Point2 &c) {
    long double c1 = cross2(a, b, p);
    long double c2 = cross2(b, c, p);
    long double c3 = cross2(c, a, p);
    return c1 >= -eps && c2 >= -eps && c3 >= -eps;
}

vector<array<int, 3>> triangulatePolygon(const vector<Point2> &points) {
    vector<array<int, 3>> result;
    vector<int> ids;
    int size = points.size();
    for (int i = 0; i < size; i++) ids.push_back(i);
    while (ids.size() > 3) {
        bool found = false;
        int count = ids.size();
        for (int i = 0; i < count; i++) {
            int pre = ids[(i - 1 + count) % count];
            int now = ids[i];
            int nxt = ids[(i + 1) % count];
            if (cross2(points[pre], points[now], points[nxt]) <= eps) continue;
            bool valid = true;
            for (int j = 0; j < count; j++) {
                int id = ids[j];
                if (id == pre || id == now || id == nxt) continue;
                if (pointInTriangle(points[id], points[pre], points[now], points[nxt])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
            result.push_back({pre, now, nxt});
            ids.erase(ids.begin() + i);
            found = true;
            break;
        }
        if (!found) break;
    }
    if (ids.size() == 3) result.push_back({ids[0], ids[1], ids[2]});
    return result;
}

long double valueAt(const Point3 &p) {
    return cutA * p.x + cutB * p.y + cutC * p.z + cutD;
}

Point3 getIntersection(const Point3 &a, const Point3 &b, long double va, long double vb) {
    long double t = va / (va - vb);
    return addPoint(a, mulPoint(subPoint(b, a), t));
}

void addSegment(map<SegmentKey, Segment> &segments, const Point3 &a, const Point3 &b) {
    PointKey ka = getPointKey(a), kb = getPointKey(b);
    if (ka.x == kb.x && ka.y == kb.y && ka.z == kb.z) return;
    if (kb < ka) swap(ka, kb);
    SegmentKey key = {ka, kb};
    auto it = segments.find(key);
    if (it == segments.end()) segments[key] = {a, b};
    else segments.erase(it);
}

vector<Point3> clipTriangle(const Triangle &tri, map<SegmentKey, Segment> &segments) {
    vector<Point3> input = {tri.a, tri.b, tri.c}, output, intersections;
    for (int i = 0; i < 3; i++) {
        Point3 a = input[i], b = input[(i + 1) % 3];
        long double va = valueAt(a), vb = valueAt(b);
        bool ina = va <= eps, inb = vb <= eps;
        if (ina && inb) {
            output.push_back(b);
        } else if (ina && !inb) {
            Point3 p = getIntersection(a, b, va, vb);
            output.push_back(p);
            intersections.push_back(p);
        } else if (!ina && inb) {
            Point3 p = getIntersection(a, b, va, vb);
            output.push_back(p);
            output.push_back(b);
            intersections.push_back(p);
        }
    }
    vector<Point3> uniqueIntersections;
    map<PointKey, bool> used;
    for (const Point3 &p : intersections) {
        PointKey key = getPointKey(p);
        if (!used[key]) {
            used[key] = true;
            uniqueIntersections.push_back(p);
        }
    }
    if (uniqueIntersections.size() == 2) addSegment(segments, uniqueIntersections[0], uniqueIntersections[1]);
    vector<Point3> uniqueOutput;
    used.clear();
    for (const Point3 &p : output) {
        PointKey key = getPointKey(p);
        if (!used[key]) {
            used[key] = true;
            uniqueOutput.push_back(p);
        }
    }
    return uniqueOutput;
}

void addTriangulatedPolygon(const vector<Point3> &points, vector<Triangle> &newMesh) {
    if (points.size() < 3) return;
    for (int i = 1; i + 1 < (int)points.size(); i++)
        newMesh.push_back({points[0], points[i], points[i + 1]});
}

void addCaps(const map<SegmentKey, Segment> &segments, vector<Triangle> &newMesh) {
    if (segments.empty()) return;
    map<PointKey, int> nodeId;
    vector<Point3> nodes;
    vector<vector<pair<int, int>>> graph;
    vector<Segment> edgeList;
    for (const auto &item : segments) {
        const Segment &seg = item.second;
        PointKey ka = getPointKey(seg.a), kb = getPointKey(seg.b);
        if (!nodeId.count(ka)) {
            nodeId[ka] = nodes.size();
            nodes.push_back(seg.a);
            graph.push_back({});
        }
        if (!nodeId.count(kb)) {
            nodeId[kb] = nodes.size();
            nodes.push_back(seg.b);
            graph.push_back({});
        }
        int u = nodeId[ka], v = nodeId[kb];
        int id = edgeList.size();
        edgeList.push_back(seg);
        graph[u].push_back({v, id});
        graph[v].push_back({u, id});
    }
    vector<bool> used(edgeList.size(), false);
    Point3 normal = normalizePoint({cutA, cutB, cutC});
    Point3 base = fabsl(normal.x) < 0.8L ? Point3{1, 0, 0} : Point3{0, 1, 0};
    Point3 axisX = normalizePoint(crossPoint(base, normal));
    Point3 axisY = crossPoint(normal, axisX);
    for (int startEdge = 0; startEdge < (int)edgeList.size(); startEdge++) {
        if (used[startEdge]) continue;
        PointKey startKey = getPointKey(edgeList[startEdge].a);
        int start = nodeId[startKey], current = start;
        vector<int> loop;
        int previousEdge = -1;
        while (true) {
            loop.push_back(current);
            int nextEdge = -1, nextNode = -1;
            for (const auto &item : graph[current]) {
                if (item.second == previousEdge || used[item.second]) continue;
                nextNode = item.first;
                nextEdge = item.second;
                break;
            }
            if (nextEdge == -1) break;
            used[nextEdge] = true;
            current = nextNode;
            previousEdge = nextEdge;
            if (current == start) break;
        }
        if (loop.size() < 3 || current != start) continue;
        vector<Point2> projected;
        for (int id : loop)
            projected.push_back({dotPoint(nodes[id], axisX), dotPoint(nodes[id], axisY)});
        if (polygonArea2(projected) < 0) reverse(loop.begin(), loop.end());
        vector<int> ids = loop;
        while (ids.size() > 3) {
            bool found = false;
            int count = ids.size();
            for (int i = 0; i < count; i++) {
                int pre = ids[(i - 1 + count) % count];
                int now = ids[i];
                int nxt = ids[(i + 1) % count];
                Point2 a = {dotPoint(nodes[pre], axisX), dotPoint(nodes[pre], axisY)};
                Point2 b = {dotPoint(nodes[now], axisX), dotPoint(nodes[now], axisY)};
                Point2 c = {dotPoint(nodes[nxt], axisX), dotPoint(nodes[nxt], axisY)};
                if (cross2(a, b, c) <= eps) continue;
                bool valid = true;
                for (int j = 0; j < count; j++) {
                    int id = ids[j];
                    if (id == pre || id == now || id == nxt) continue;
                    Point2 p = {dotPoint(nodes[id], axisX), dotPoint(nodes[id], axisY)};
                    if (pointInTriangle(p, a, b, c)) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                newMesh.push_back({nodes[pre], nodes[now], nodes[nxt]});
                ids.erase(ids.begin() + i);
                found = true;
                break;
            }
            if (!found) break;
        }
        if (ids.size() == 3)
            newMesh.push_back({nodes[ids[0]], nodes[ids[1]], nodes[ids[2]]});
    }
}

void cutMesh() {
    vector<Triangle> newMesh;
    map<SegmentKey, Segment> segments;
    for (const Triangle &tri : mesh) {
        vector<Point3> points = clipTriangle(tri, segments);
        if (points.size() >= 3) addTriangulatedPolygon(points, newMesh);
    }
    addCaps(segments, newMesh);
    mesh.swap(newMesh);
}

long double getArea() {
    long double result = 0;
    for (const Triangle &tri : mesh)
        result += normPoint(crossPoint(subPoint(tri.b, tri.a), subPoint(tri.c, tri.a))) / 2.0L;
    return result;
}

long double getVolume() {
    long double result = 0;
    for (const Triangle &tri : mesh)
        result += dotPoint(tri.a, crossPoint(tri.b, tri.c)) / 6.0L;
    return fabsl(result);
}

void buildMesh() {
    vector<array<int, 3>> faces = triangulatePolygon(poly);
    vector<Point3> bottom(n), top(n);
    for (int i = 0; i < n; i++) {
        bottom[i] = {poly[i].x, poly[i].y, 0};
        top[i] = {poly[i].x, poly[i].y, (long double)h};
    }
    for (const auto &face : faces) {
        mesh.push_back({bottom[face[2]], bottom[face[1]], bottom[face[0]]});
        mesh.push_back({top[face[0]], top[face[1]], top[face[2]]});
    }
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        mesh.push_back({bottom[i], bottom[j], top[j]});
        mesh.push_back({bottom[i], top[j], top[i]});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(3);
    while (cin >> n >> h >> m) {
        if (n == 0 && h == 0 && m == 0) break;
        poly.resize(n);
        mesh.clear();
        for (int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;
        buildMesh();
        cout << (double)getVolume() << ' ' << (double)getArea() << '\n';
        for (int i = 0; i < m; i++) {
            cin >> cutA >> cutB >> cutC >> cutD;
            cutMesh();
            cout << (double)getVolume() << ' ' << (double)getArea() << '\n';
        }
    }
    return 0;
}
