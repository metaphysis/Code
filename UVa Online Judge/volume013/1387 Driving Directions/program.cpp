#include <bits/stdc++.h>
using namespace std;

using Real = long double;

const Real pi = acosl(-1.0L);
const Real eps = 1e-10L;
const Real angEps = 1e-12L;
const Real inf = 1e100L;

struct Point {
    Real x, y;
    Point operator + (const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator * (Real k) const { return {x * k, y * k}; }
};

struct Rect {
    Real x1, y1, x2, y2;
};

struct Edge {
    int to;
    Real len;
};

struct ArcNode {
    Real ang;
    int id;
};

struct Circle {
    Point c;
    Real base;
    vector<ArcNode> nodes;
};

Real radius, radiusSq;
vector<Rect> rects;
vector<Circle> circles;
vector<Point> points;
vector<vector<Edge>> graph;

Real dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Real normSq(Point a) {
    return dot(a, a);
}

Real pointRectDistSq(Point p, const Rect &rect) {
    Real dx = max(0.0L, max(rect.x1 - p.x, p.x - rect.x2));
    Real dy = max(0.0L, max(rect.y1 - p.y, p.y - rect.y2));
    return dx * dx + dy * dy;
}

Real pointSegDistSq(Point p, Point a, Point b) {
    Point v = b - a;
    Real lenSq = normSq(v);
    if (lenSq < eps * eps) return normSq(p - a);
    Real t = max(0.0L, min(1.0L, dot(p - a, v) / lenSq));
    return normSq(p - (a + v * t));
}

bool clipAxis(Real pos, Real dir, Real low, Real high, Real &left, Real &right) {
    if (fabsl(dir) < angEps) return pos >= low && pos <= high;
    Real t1 = (low - pos) / dir, t2 = (high - pos) / dir;
    if (t1 > t2) swap(t1, t2);
    left = max(left, t1);
    right = min(right, t2);
    return left <= right;
}

Real segRectDistSq(Point a, Point b, const Rect &rect) {
    Point v = b - a;
    Real left = 0, right = 1;
    if (clipAxis(a.x, v.x, rect.x1, rect.x2, left, right) &&
        clipAxis(a.y, v.y, rect.y1, rect.y2, left, right)) return 0;
    Real ans = min(pointRectDistSq(a, rect), pointRectDistSq(b, rect));
    Point corners[4] = {
        {rect.x1, rect.y1}, {rect.x1, rect.y2},
        {rect.x2, rect.y1}, {rect.x2, rect.y2}
    };
    for (int i = 0; i < 4; ++i) ans = min(ans, pointSegDistSq(corners[i], a, b));
    return ans;
}

bool pointFree(Point p) {
    for (const Rect &rect : rects) if (pointRectDistSq(p, rect) + eps < radiusSq) return false;
    return true;
}

bool segFree(Point a, Point b) {
    for (const Rect &rect : rects) if (segRectDistSq(a, b, rect) + eps < radiusSq) return false;
    return true;
}

int addNode(Point p) {
    int id = (int)points.size();
    points.push_back(p);
    graph.emplace_back();
    return id;
}

void addEdge(int u, int v, Real len) {
    graph[u].push_back({v, len});
    graph[v].push_back({u, len});
}

Point arcPoint(int circleId, Real ang) {
    const Circle &circle = circles[circleId];
    Real theta = circle.base + ang;
    return circle.c + Point{cosl(theta), sinl(theta)} * radius;
}

int addArcNode(int circleId, Point p) {
    Circle &circle = circles[circleId];
    Point v = p - circle.c;
    Real ang = atan2l(v.y, v.x) - circle.base;
    while (ang < 0) ang += 2 * pi;
    while (ang >= 2 * pi) ang -= 2 * pi;
    if (ang > 2 * pi - angEps) ang = 0;
    if (ang > pi / 2 + angEps) return -1;
    ang = max(0.0L, min(pi / 2, ang));
    int id = addNode(p);
    circle.nodes.push_back({ang, id});
    return id;
}

void tryStraight(int u, int v) {
    if (segFree(points[u], points[v])) addEdge(u, v, sqrtl(normSq(points[u] - points[v])));
}

void addPointTangents(int pointId, int circleId) {
    Point p = points[pointId], v = p - circles[circleId].c;
    Real distSq = normSq(v), dist = sqrtl(distSq);
    if (dist + eps < radius) return;
    Point unit = v * (1 / dist), perp = {-unit.y, unit.x};
    Real cosVal = min(1.0L, radius / dist);
    Real sinVal = sqrtl(max(0.0L, 1 - cosVal * cosVal));
    for (int sign = -1; sign <= 1; sign += 2) {
        Point dir = unit * cosVal + perp * (sign * sinVal);
        Point touch = circles[circleId].c + dir * radius;
        int id = addArcNode(circleId, touch);
        if (id != -1) tryStraight(pointId, id);
    }
}

void addCircleTangents(int firstId, int secondId) {
    Point v = circles[secondId].c - circles[firstId].c;
    Real dist = sqrtl(normSq(v));
    Point unit = v * (1 / dist), perp = {-unit.y, unit.x};
    for (int kind = -1; kind <= 1; kind += 2) {
        Real cosVal = radius * (1 - kind) / dist;
        if (cosVal > 1 + angEps) continue;
        cosVal = min(1.0L, cosVal);
        Real sinVal = sqrtl(max(0.0L, 1 - cosVal * cosVal));
        for (int sign = -1; sign <= 1; sign += 2) {
            Point dir = unit * cosVal + perp * (sign * sinVal);
            Point first = circles[firstId].c + dir * radius;
            Point second = circles[secondId].c + dir * (kind * radius);
            int u = addArcNode(firstId, first), vId = addArcNode(secondId, second);
            if (u != -1 && vId != -1) tryStraight(u, vId);
        }
    }
}

void addCircleIntersections(int firstId, int secondId) {
    Point delta = circles[secondId].c - circles[firstId].c;
    Real distSq = normSq(delta);
    if (distSq > 4 * radiusSq + eps) return;
    Real dist = sqrtl(distSq), height = sqrtl(max(0.0L, radiusSq - distSq / 4));
    Point mid = (circles[firstId].c + circles[secondId].c) * 0.5L;
    Point perp = {-delta.y / dist, delta.x / dist};
    for (int sign = -1; sign <= 1; sign += 2) {
        Point p = mid + perp * (sign * height);
        int u = addArcNode(firstId, p), v = addArcNode(secondId, p);
        if (u != -1 && v != -1 && pointFree(p)) addEdge(u, v, 0);
    }
}

void addLineIntersections(int circleId, const Rect &rect) {
    Point center = circles[circleId].c;
    Real xVals[2] = {rect.x1 - radius, rect.x2 + radius};
    Real yVals[2] = {rect.y1 - radius, rect.y2 + radius};
    for (int i = 0; i < 2; ++i) {
        Real dx = xVals[i] - center.x, remain = radiusSq - dx * dx;
        if (remain >= -eps) {
            Real dy = sqrtl(max(0.0L, remain));
            addArcNode(circleId, {xVals[i], center.y + dy});
            addArcNode(circleId, {xVals[i], center.y - dy});
        }
        Real dy = yVals[i] - center.y;
        remain = radiusSq - dy * dy;
        if (remain >= -eps) {
            Real offset = sqrtl(max(0.0L, remain));
            addArcNode(circleId, {center.x + offset, yVals[i]});
            addArcNode(circleId, {center.x - offset, yVals[i]});
        }
    }
}

void buildArcs() {
    for (int i = 0; i < (int)circles.size(); ++i) {
        vector<ArcNode> &nodes = circles[i].nodes;
        sort(nodes.begin(), nodes.end(), [](const ArcNode &a, const ArcNode &b) {
            return a.ang < b.ang;
        });
        vector<char> valid(nodes.size());
        for (int j = 0; j < (int)nodes.size(); ++j) valid[j] = pointFree(points[nodes[j].id]);
        for (int j = 1; j < (int)nodes.size(); ++j) {
            if (!valid[j - 1] || !valid[j]) continue;
            Real left = nodes[j - 1].ang, right = nodes[j].ang;
            if (pointFree(arcPoint(i, (left + right) / 2))) addEdge(nodes[j - 1].id, nodes[j].id, radius * (right - left));
        }
    }
}

Real shortestPath() {
    vector<Real> dist(points.size(), inf);
    priority_queue<pair<Real, int>, vector<pair<Real, int>>, greater<pair<Real, int>>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        Real curDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (curDist > dist[u]) continue;
        if (u == 1) return curDist;
        for (const Edge &edge : graph[u]) {
            Real nextDist = curDist + edge.len;
            if (nextDist < dist[edge.to]) {
                dist[edge.to] = nextDist;
                pq.push({nextDist, edge.to});
            }
        }
    }
    return inf;
}

Real solve(Point start, Point finish) {
    circles.clear();
    points.clear();
    graph.clear();
    addNode(start);
    addNode(finish);
    for (const Rect &rect : rects) {
        Point centers[4] = {
            {rect.x2, rect.y2}, {rect.x1, rect.y2},
            {rect.x1, rect.y1}, {rect.x2, rect.y1}
        };
        int endIds[4][2];
        for (int i = 0; i < 4; ++i) {
            int circleId = (int)circles.size();
            circles.push_back({centers[i], i * pi / 2, {}});
            endIds[i][0] = addArcNode(circleId, arcPoint(circleId, 0));
            endIds[i][1] = addArcNode(circleId, arcPoint(circleId, pi / 2));
        }
        for (int i = 0; i < 4; ++i) tryStraight(endIds[i][1], endIds[(i + 1) % 4][0]);
    }
    tryStraight(0, 1);
    int circleCount = (int)circles.size();
    for (int i = 0; i < circleCount; ++i) {
        addPointTangents(0, i);
        addPointTangents(1, i);
        for (const Rect &rect : rects) addLineIntersections(i, rect);
        for (int j = i + 1; j < circleCount; ++j) {
            addCircleTangents(i, j);
            addCircleIntersections(i, j);
        }
    }
    buildArcs();
    return shortestPath();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> radius >> n) {
        Point start, finish;
        cin >> start.x >> start.y >> finish.x >> finish.y;
        radiusSq = radius * radius;
        rects.resize(n);
        for (Rect &rect : rects) cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
        Real ans = solve(start, finish);
        if (ans >= inf / 2) cout << "no solution\n";
        else cout << fixed << setprecision(6) << ans << '\n';
    }
    return 0;
}
