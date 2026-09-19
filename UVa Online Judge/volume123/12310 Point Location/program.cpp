#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Edge {
    int leftId, rightId;
};

struct Event {
    long double x, y, sweepX;
    int kind, id;
};

struct Dsu {
    vector<int> parent, nodeSize;
    void init(int nodeCount) {
        parent.resize(nodeCount);
        nodeSize.assign(nodeCount, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int findRoot(int nodeId) {
        if (parent[nodeId] != nodeId) parent[nodeId] = findRoot(parent[nodeId]);
        return parent[nodeId];
    }

    void unite(int firstId, int secondId) {
        firstId = findRoot(firstId);
        secondId = findRoot(secondId);
        if (firstId == secondId) return;
        if (nodeSize[firstId] < nodeSize[secondId]) swap(firstId, secondId);
        parent[secondId] = firstId;
        nodeSize[firstId] += nodeSize[secondId];
    }
};

vector<Point> points;
vector<Edge> edges;
long double probeX, probeY;

bool pointLess(int firstId, int secondId) {
    if (points[firstId].x != points[secondId].x) return points[firstId].x < points[secondId].x;
    return points[firstId].y < points[secondId].y;
}

long long getCross(const Point &base, const Point &first, const Point &second) {
    return (first.x - base.x) * (second.y - base.y) - (first.y - base.y) * (second.x - base.x);
}

long double getProbeCross(int edgeId) {
    const Point &leftPoint = points[edges[edgeId].leftId], &rightPoint = points[edges[edgeId].rightId];
    return (rightPoint.x - leftPoint.x) * (probeY - leftPoint.y) - (rightPoint.y - leftPoint.y) * (probeX - leftPoint.x);
}

struct EdgeCmp {
    bool operator()(int firstId, int secondId) const {
        if (firstId == secondId) return false;
        if (firstId == -1) return getProbeCross(secondId) < 0;
        if (secondId == -1) return getProbeCross(firstId) > 0;
        const Edge &firstEdge = edges[firstId], &secondEdge = edges[secondId];
        if (firstEdge.leftId == secondEdge.leftId) return getCross(points[firstEdge.leftId], points[firstEdge.rightId], points[secondEdge.rightId]) > 0;
        if (pointLess(firstEdge.leftId, secondEdge.leftId)) return getCross(points[firstEdge.leftId], points[firstEdge.rightId], points[secondEdge.leftId]) > 0;
        return getCross(points[secondEdge.leftId], points[secondEdge.rightId], points[firstEdge.leftId]) < 0;
    }
};

bool eventLess(const Event &firstEvent, const Event &secondEvent) {
    if (firstEvent.sweepX != secondEvent.sweepX) return firstEvent.sweepX < secondEvent.sweepX;
    if (firstEvent.kind != secondEvent.kind) return firstEvent.kind < secondEvent.kind;
    return firstEvent.id < secondEvent.id;
}

void solveCase(int n, int m, int p, int q) {
    const long double shearBase = 2000001.0L;
    int outerId = 2 * m;
    vector<vector<int> > startEdges(n), endEdges(n);
    vector<Event> events;
    vector<int> labelSide(p), querySide(q), regionLabel(2 * m + 1, 0);
    Dsu dsu;
    EdgeCmp edgeCmp;
    set<int, EdgeCmp> activeEdges;
    points.resize(n);
    edges.resize(m);
    events.reserve(n + p + q);
    dsu.init(2 * m + 1);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        long double x = points[i].x, y = points[i].y;
        events.push_back(Event{x, y, x + y / shearBase, 0, i});
    }
    for (int i = 0; i < m; i++) {
        int leftId, rightId;
        cin >> leftId >> rightId;
        leftId--;
        rightId--;
        if (pointLess(rightId, leftId)) swap(leftId, rightId);
        edges[i] = Edge{leftId, rightId};
        startEdges[leftId].push_back(i);
        endEdges[rightId].push_back(i);
    }
    for (int i = 0; i < p; i++) {
        long double x, y;
        cin >> x >> y;
        events.push_back(Event{x, y, x + y / shearBase, 1, i});
    }
    for (int i = 0; i < q; i++) {
        long double x, y;
        cin >> x >> y;
        events.push_back(Event{x, y, x + y / shearBase, 2, i});
    }
    for (int i = 0; i < n; i++) {
        sort(startEdges[i].begin(), startEdges[i].end(), edgeCmp);
        sort(endEdges[i].begin(), endEdges[i].end(), edgeCmp);
    }
    sort(events.begin(), events.end(), eventLess);
    for (const Event &event : events) {
        probeX = event.x;
        probeY = event.y;
        if (event.kind == 0) {
            const vector<int> &starts = startEdges[event.id], &ends = endEdges[event.id];
            for (int i = 1; i < (int)ends.size(); i++) dsu.unite(2 * ends[i - 1], 2 * ends[i] + 1);
            for (int i = 1; i < (int)starts.size(); i++) dsu.unite(2 * starts[i - 1], 2 * starts[i] + 1);
            for (int edgeId : ends) activeEdges.erase(edgeId);
            auto highIt = activeEdges.lower_bound(-1);
            int lowSide = outerId, highSide = outerId;
            if (highIt != activeEdges.begin()) lowSide = 2 * (*prev(highIt));
            if (highIt != activeEdges.end()) highSide = 2 * (*highIt) + 1;
            if (!ends.empty()) {
                dsu.unite(lowSide, 2 * ends.front() + 1);
                dsu.unite(highSide, 2 * ends.back());
            }
            if (!starts.empty()) {
                dsu.unite(lowSide, 2 * starts.front() + 1);
                dsu.unite(highSide, 2 * starts.back());
            }
            if (ends.empty() || starts.empty()) dsu.unite(lowSide, highSide);
            for (int edgeId : starts) activeEdges.insert(edgeId);
        } else {
            auto highIt = activeEdges.lower_bound(-1);
            int sideId = outerId;
            if (highIt != activeEdges.begin()) sideId = 2 * (*prev(highIt));
            if (event.kind == 1) labelSide[event.id] = sideId;
            else querySide[event.id] = sideId;
        }
    }
    for (int i = 0; i < p; i++) regionLabel[dsu.findRoot(labelSide[i])] = i + 1;
    for (int i = 0; i < q; i++) cout << regionLabel[dsu.findRoot(querySide[i])] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, p, q;
    while (cin >> n >> m >> p >> q) {
        if (n == 0 && m == 0 && p == 0 && q == 0) break;
        solveCase(n, m, p, q);
    }
    return 0;
}
