#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long xn, xd, yn, yd;
};

struct Wire {
    long long xa, ya, xb, yb;
    int type;
    vector<int> pointIds;
};

struct Dart {
    int from, to, rev, wire;
};

struct Cycle {
    vector<int> vertexIds;
    int firstDart;
    long double area;
};

vector<Point> points;
vector<Wire> wires;
map<string, int> pointMap;
vector<Dart> darts;
vector<vector<int>> graph;
vector<Cycle> cycles;
vector<int> dartCycle;
vector<int> cycleFace;
vector<vector<int>> cycleVertices;

long long gcdValue(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a == 0 ? 1 : a;
}

pair<long long, long long> makeFraction(long long numerator, long long denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    long long divisor = gcdValue(numerator, denominator);
    return {numerator / divisor, denominator / divisor};
}

string getPointKey(const Point &point) {
    return to_string(point.xn) + "/" + to_string(point.xd) + "#" + to_string(point.yn) + "/" + to_string(point.yd);
}

long double getX(const Point &point) {
    return (long double)point.xn / point.xd;
}

long double getY(const Point &point) {
    return (long double)point.yn / point.yd;
}

int addPoint(const Point &point) {
    string key = getPointKey(point);
    auto it = pointMap.find(key);
    if (it != pointMap.end()) return it->second;
    int id = (int)points.size();
    points.push_back(point);
    pointMap[key] = id;
    return id;
}

Point makeIntegerPoint(long long x, long long y) {
    Point point;
    point.xn = x;
    point.xd = 1;
    point.yn = y;
    point.yd = 1;
    return point;
}

bool onSegment(long double x, long double y, const Wire &wire) {
    long double cross = (x - wire.xa) * (wire.yb - wire.ya) - (y - wire.ya) * (wire.xb - wire.xa);
    if (fabsl(cross) > 1e-12L) return false;
    return x >= min(wire.xa, wire.xb) - 1e-12L && x <= max(wire.xa, wire.xb) + 1e-12L && y >= min(wire.ya, wire.yb) - 1e-12L && y <= max(wire.ya, wire.yb) + 1e-12L;
}

long long crossValue(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

void addCommonEndpoints(int first, int second) {
    Wire &a = wires[first];
    Wire &b = wires[second];
    if (onSegment(a.xa, a.ya, b)) wires[first].pointIds.push_back(addPoint(makeIntegerPoint(a.xa, a.ya)));
    if (onSegment(a.xb, a.yb, b)) wires[first].pointIds.push_back(addPoint(makeIntegerPoint(a.xb, a.yb)));
    if (onSegment(b.xa, b.ya, a)) wires[second].pointIds.push_back(addPoint(makeIntegerPoint(b.xa, b.ya)));
    if (onSegment(b.xb, b.yb, a)) wires[second].pointIds.push_back(addPoint(makeIntegerPoint(b.xb, b.yb)));
}

void addIntersection(int first, int second) {
    Wire &a = wires[first];
    Wire &b = wires[second];
    long long aa = a.ya - a.yb;
    long long ba = a.xb - a.xa;
    long long ca = a.xa * a.yb - a.xb * a.ya;
    long long ab = b.ya - b.yb;
    long long bb = b.xb - b.xa;
    long long cb = b.xa * b.yb - b.xb * b.ya;
    long long determinant = aa * bb - ab * ba;
    if (determinant == 0) {
        addCommonEndpoints(first, second);
        return;
    }
    auto xFraction = makeFraction(ba * cb - bb * ca, determinant);
    auto yFraction = makeFraction(ca * ab - cb * aa, determinant);
    Point point;
    point.xn = xFraction.first;
    point.xd = xFraction.second;
    point.yn = yFraction.first;
    point.yd = yFraction.second;
    long double x = getX(point);
    long double y = getY(point);
    if (!onSegment(x, y, a) || !onSegment(x, y, b)) return;
    int pointId = addPoint(point);
    wires[first].pointIds.push_back(pointId);
    wires[second].pointIds.push_back(pointId);
}

long double distanceParameter(int wireId, int pointId) {
    Wire &wire = wires[wireId];
    Point &point = points[pointId];
    long double dx = wire.xb - wire.xa;
    long double dy = wire.yb - wire.ya;
    return ((getX(point) - wire.xa) * dx + (getY(point) - wire.ya) * dy) / (dx * dx + dy * dy);
}

void buildEdges() {
    for (int i = 0; i < (int)wires.size(); i++) {
        auto &ids = wires[i].pointIds;
        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return distanceParameter(i, a) < distanceParameter(i, b);
        });
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        for (int j = 1; j < (int)ids.size(); j++) {
            int u = ids[j - 1], v = ids[j];
            int first = (int)darts.size();
            int second = first + 1;
            darts.push_back({u, v, second, i});
            darts.push_back({v, u, first, i});
            graph[u].push_back(first);
            graph[v].push_back(second);
        }
    }
}

long double getAngle(int dartId) {
    Dart &dart = darts[dartId];
    long double dx = getX(points[dart.to]) - getX(points[dart.from]);
    long double dy = getY(points[dart.to]) - getY(points[dart.from]);
    return atan2l(dy, dx);
}

long double polygonArea(const vector<int> &vertices) {
    long double result = 0;
    for (int i = 0; i < (int)vertices.size(); i++) {
        int j = (i + 1) % vertices.size();
        result += getX(points[vertices[i]]) * getY(points[vertices[j]]) - getY(points[vertices[i]]) * getX(points[vertices[j]]);
    }
    return result / 2;
}

void buildCycles() {
    vector<int> position(darts.size(), -1);
    for (int i = 0; i < (int)graph.size(); i++) {
        sort(graph[i].begin(), graph[i].end(), [&](int a, int b) {
            return getAngle(a) < getAngle(b);
        });
        for (int j = 0; j < (int)graph[i].size(); j++) position[graph[i][j]] = j;
    }
    vector<bool> visited(darts.size(), false);
    dartCycle.assign(darts.size(), -1);
    for (int i = 0; i < (int)darts.size(); i++) {
        if (visited[i]) continue;
        vector<int> vertices;
        int current = i;
        while (!visited[current]) {
            visited[current] = true;
            vertices.push_back(darts[current].from);
            int vertex = darts[current].to;
            int reverseDart = darts[current].rev;
            int index = position[reverseDart];
            current = graph[vertex][(index - 1 + graph[vertex].size()) % graph[vertex].size()];
        }
        int cycleId = (int)cycles.size();
        cycles.push_back({vertices, i, polygonArea(vertices)});
        for (int dartId : vertices) {
            (void)dartId;
        }
    }
    for (int i = 0; i < (int)cycles.size(); i++) {
        int current = cycles[i].firstDart;
        do {
            dartCycle[current] = i;
            int vertex = darts[current].to;
            int reverseDart = darts[current].rev;
            int index = position[reverseDart];
            current = graph[vertex][(index - 1 + graph[vertex].size()) % graph[vertex].size()];
        } while (current != cycles[i].firstDart);
    }
}

bool pointInPolygon(long double x, long double y, const vector<int> &vertices) {
    bool inside = false;
    for (int i = 0, j = (int)vertices.size() - 1; i < (int)vertices.size(); j = i++) {
        long double xi = getX(points[vertices[i]]), yi = getY(points[vertices[i]]);
        long double xj = getX(points[vertices[j]]), yj = getY(points[vertices[j]]);
        bool intersect = ((yi > y) != (yj > y)) && (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        if (intersect) inside = !inside;
    }
    return inside;
}

int locateFace(long double x, long double y, const vector<int> &positiveCycles, int outerFace) {
    int result = outerFace;
    long double bestArea = 1e100L;
    for (int i = 0; i < (int)positiveCycles.size(); i++) {
        int cycleId = positiveCycles[i];
        if (pointInPolygon(x, y, cycles[cycleId].vertexIds) && cycles[cycleId].area < bestArea) {
            bestArea = cycles[cycleId].area;
            result = i;
        }
    }
    return result;
}

int solveCase() {
    int m;
    long long x0, y0, x1, y1;
    if (!(cin >> m >> x0 >> y0 >> x1 >> y1)) return 1;
    points.clear();
    wires.clear();
    darts.clear();
    graph.clear();
    cycles.clear();
    pointMap.clear();
    vector<Wire> inputWires(m);
    for (int i = 0; i < m; i++) {
        cin >> inputWires[i].xa >> inputWires[i].ya >> inputWires[i].xb >> inputWires[i].yb;
        inputWires[i].type = 1;
    }
    long long minX = min(x0, x1), maxX = max(x0, x1), minY = min(y0, y1), maxY = max(y0, y1);
    for (auto &wire : inputWires) {
        minX = min(minX, min(wire.xa, wire.xb));
        maxX = max(maxX, max(wire.xa, wire.xb));
        minY = min(minY, min(wire.ya, wire.yb));
        maxY = max(maxY, max(wire.ya, wire.yb));
    }
    long long margin = 10;
    wires = inputWires;
    wires.push_back({minX - margin, minY - margin, maxX + margin, minY - margin, 0, {}});
    wires.push_back({maxX + margin, minY - margin, maxX + margin, maxY + margin, 0, {}});
    wires.push_back({maxX + margin, maxY + margin, minX - margin, maxY + margin, 0, {}});
    wires.push_back({minX - margin, maxY + margin, minX - margin, minY - margin, 0, {}});
    for (auto &wire : wires) {
        wire.pointIds.push_back(addPoint(makeIntegerPoint(wire.xa, wire.ya)));
        wire.pointIds.push_back(addPoint(makeIntegerPoint(wire.xb, wire.yb)));
    }
    for (int i = 0; i < (int)wires.size(); i++)
        for (int j = i + 1; j < (int)wires.size(); j++)
            addIntersection(i, j);
    graph.resize(points.size());
    buildEdges();
    buildCycles();
    vector<int> positiveCycles;
    for (int i = 0; i < (int)cycles.size(); i++)
        if (cycles[i].area > 1e-12L) positiveCycles.push_back(i);
    int outerFace = (int)positiveCycles.size();
    vector<int> faceOfCycle(cycles.size(), outerFace);
    for (int i = 0; i < (int)cycles.size(); i++) {
        if (cycles[i].area > 1e-12L) {
            faceOfCycle[i] = (int)(find(positiveCycles.begin(), positiveCycles.end(), i) - positiveCycles.begin());
            continue;
        }
        int current = cycles[i].firstDart;
        long double mx = (getX(points[darts[current].from]) + getX(points[darts[current].to])) / 2;
        long double my = (getY(points[darts[current].from]) + getY(points[darts[current].to])) / 2;
        long double dx = getX(points[darts[current].to]) - getX(points[darts[current].from]);
        long double dy = getY(points[darts[current].to]) - getY(points[darts[current].from]);
        long double len = sqrtl(dx * dx + dy * dy);
        long double sx = mx - dy / len * 1e-10L;
        long double sy = my + dx / len * 1e-10L;
        long double bestArea = 1e100L;
        for (int k = 0; k < (int)positiveCycles.size(); k++)
            if (pointInPolygon(sx, sy, cycles[positiveCycles[k]].vertexIds) && cycles[positiveCycles[k]].area < bestArea) {
                bestArea = cycles[positiveCycles[k]].area;
                faceOfCycle[i] = k;
            }
    }
    int faceCount = outerFace + 1;
    vector<vector<pair<int, int>>> dual(faceCount);
    for (int i = 0; i < (int)darts.size(); i++) {
        int j = darts[i].rev;
        if (i > j) continue;
        int firstFace = faceOfCycle[dartCycle[i]];
        int secondFace = faceOfCycle[dartCycle[j]];
        if (firstFace == secondFace) continue;
        int cost = darts[i].wire < m ? 1 : 0;
        dual[firstFace].push_back({secondFace, cost});
        dual[secondFace].push_back({firstFace, cost});
    }
    int startFace = locateFace(x0, y0, positiveCycles, outerFace);
    int endFace = locateFace(x1, y1, positiveCycles, outerFace);
    const int inf = 1e9;
    vector<int> dist(faceCount, inf);
    deque<int> que;
    dist[startFace] = 0;
    que.push_back(startFace);
    while (!que.empty()) {
        int u = que.front();
        que.pop_front();
        for (auto edge : dual[u]) {
            int v = edge.first, weight = edge.second;
            if (dist[v] <= dist[u] + weight) continue;
            dist[v] = dist[u] + weight;
            if (weight == 0) que.push_front(v);
            else que.push_back(v);
        }
    }
    cout << dist[endFace] << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (solveCase() == 0) {
    }
    return 0;
}
