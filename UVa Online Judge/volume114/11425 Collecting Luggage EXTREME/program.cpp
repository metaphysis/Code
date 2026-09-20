#include <bits/stdc++.h>
using namespace std;

using Real = long double;

const Real eps = 1e-12L;
const Real inf = 1e100L;

struct Point {
    Real x, y;
    Point operator + (const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator * (Real k) const { return {x * k, y * k}; }
};

struct Interval {
    Real left, right;
};

int n;
Real luggageSpeed, personSpeed, perimeter, ratioSpeed, bestTime;
vector<Point> polygon, nodes;
vector<Real> edgeLen, prefixLen, shortest;
vector<vector<Real>> graph;

Real cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Real dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Real pointLength(Point a) {
    return sqrtl(dot(a, a));
}

int signOf(Real value) {
    if (value > eps) return 1;
    if (value < -eps) return -1;
    return 0;
}

bool entersInside(int id, Point dir) {
    Point incoming = polygon[id] - polygon[(id + n - 1) % n];
    Point outgoing = polygon[(id + 1) % n] - polygon[id];
    Real first = cross(incoming, dir);
    Real second = cross(outgoing, dir);
    Real turn = cross(incoming, outgoing);
    if (turn >= -eps) return first > eps && second > eps;
    return first > eps || second > eps;
}

bool isVisible(Point a, Point b) {
    Point dir = b - a;
    for (int i = 0; i < n; ++i) {
        Point c = polygon[i], d = polygon[(i + 1) % n];
        int first = signOf(cross(dir, c - a));
        int second = signOf(cross(dir, d - a));
        int third = signOf(cross(d - c, a - c));
        int fourth = signOf(cross(d - c, b - c));
        if (first * second < 0 && third * fourth < 0) return false;
        if (first == 0 && dot(c - a, c - b) <= eps) {
            if (entersInside(i, a - c) || entersInside(i, b - c)) return false;
        }
    }
    return true;
}

void buildShortest() {
    int total = n + 1;
    graph.assign(total, vector<Real>(total, inf));
    for (int i = 0; i < total; ++i) {
        graph[i][i] = 0;
        for (int j = i + 1; j < total; ++j) {
            if (isVisible(nodes[i], nodes[j])) {
                Real weight = pointLength(nodes[i] - nodes[j]);
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }
    shortest.assign(total, inf);
    vector<int> used(total, 0);
    shortest[n] = 0;
    for (int step = 0; step < total; ++step) {
        int id = -1;
        for (int i = 0; i < total; ++i)
            if (!used[i] && (id == -1 || shortest[i] < shortest[id]))
                id = i;
        if (id == -1 || shortest[id] >= inf / 2) break;
        used[id] = 1;
        for (int i = 0; i < total; ++i)
            shortest[i] = min(shortest[i], shortest[id] + graph[id][i]);
    }
}

void addBlocked(vector<Interval> &blocked, Real len, initializer_list<pair<Real, Real>> conditions) {
    Real left = 0, right = len;
    for (const auto &condition : conditions) {
        Real value = condition.first;
        Real slope = condition.second;
        if (fabsl(slope) <= eps) {
            if (value <= eps) return;
        } else {
            Real border = -value / slope;
            if (slope > 0) left = max(left, border);
            else right = min(right, border);
        }
        if (left >= right - eps) return;
    }
    left = max(left, (Real)0);
    right = min(right, len);
    if (left < right - eps) blocked.push_back({left, right});
}

void solveInterval(int sourceId, int edgeId, Real left, Real right) {
    if (left >= right - eps) return;
    Point source = nodes[sourceId];
    Point start = polygon[edgeId];
    Point unit = (polygon[(edgeId + 1) % n] - start) * (1 / edgeLen[edgeId]);
    Real projection = dot(source - start, unit);
    Real height = fabsl(cross(unit, source - start));
    Real prefix = prefixLen[edgeId];
    Real baseDist = shortest[sourceId];
    Real cycleBudget = ratioSpeed * perimeter;
    Real minPos = right;
    if (ratioSpeed < 1) {
        minPos = projection + ratioSpeed * height / sqrtl(1 - ratioSpeed * ratioSpeed);
        minPos = max(left, min(right, minPos));
    }
    auto getValue = [&](Real pos) {
        Real offset = pos - projection;
        return baseDist + sqrtl(offset * offset + height * height) - ratioSpeed * (prefix + pos);
    };
    Real minValue = getValue(minPos);
    long long cycleId = max(0LL, (long long)ceill(minValue / cycleBudget - eps));
    Real budget = cycleId * cycleBudget;
    if ((cycleId * perimeter + prefix + left) / luggageSpeed >= bestTime - eps) return;
    Real position = left;
    if (getValue(left) > budget + eps) {
        Real low = left, high = minPos;
        for (int step = 0; step < 80; ++step) {
            Real mid = (low + high) / 2;
            if (getValue(mid) <= budget) high = mid;
            else low = mid;
        }
        position = high;
    }
    Real currentTime = (cycleId * perimeter + prefix + position) / luggageSpeed;
    bestTime = min(bestTime, currentTime);
}

void solveEdge(int sourceId, int edgeId) {
    int nextId = (edgeId + 1) % n;
    Real len = edgeLen[edgeId];
    if (sourceId == edgeId || sourceId == nextId) {
        solveInterval(sourceId, edgeId, 0, len);
        return;
    }
    Point source = nodes[sourceId];
    Point start = polygon[edgeId];
    Point edge = polygon[nextId] - start;
    Point unit = edge * (1 / len);
    if (cross(edge, source - start) >= -eps) return;
    vector<Interval> blocked;
    blocked.reserve(n + 2);
    if (sourceId < n) {
        Point incoming = source - polygon[(sourceId + n - 1) % n];
        Point outgoing = polygon[(sourceId + 1) % n] - source;
        pair<Real, Real> first = {
            cross(incoming, start - source),
            cross(incoming, unit)
        };
        pair<Real, Real> second = {
            cross(outgoing, start - source),
            cross(outgoing, unit)
        };
        if (cross(incoming, outgoing) >= -eps)
            addBlocked(blocked, len, {first, second});
        else {
            addBlocked(blocked, len, {first});
            addBlocked(blocked, len, {second});
        }
    }
    for (int i = 0; i < n; ++i) {
        Point c = polygon[i];
        Point d = polygon[(i + 1) % n];
        Point side = d - c;
        int direction = signOf(cross(side, source - c));
        if (direction == 0) continue;
        pair<Real, Real> first = {
            -direction * cross(side, start - c),
            -direction * cross(side, unit)
        };
        pair<Real, Real> second = {
            -direction * cross(start - source, c - source),
            -direction * cross(unit, c - source)
        };
        pair<Real, Real> third = {
            direction * cross(start - source, d - source),
            direction * cross(unit, d - source)
        };
        addBlocked(blocked, len, {first, second, third});
    }
    sort(blocked.begin(), blocked.end(), [](const Interval &a, const Interval &b) {
        if (fabsl(a.left - b.left) > eps) return a.left < b.left;
        return a.right < b.right;
    });
    Real current = 0;
    for (const auto &interval : blocked) {
        if (interval.left > current + eps)
            solveInterval(sourceId, edgeId, current, interval.left);
        current = max(current, interval.right);
        if (current >= len - eps) break;
    }
    if (current < len - eps)
        solveInterval(sourceId, edgeId, current, len);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    while (cin >> n && n != 0) {
        polygon.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> polygon[i].x >> polygon[i].y;
        Point passenger;
        cin >> passenger.x >> passenger.y;
        cin >> luggageSpeed >> personSpeed;
        nodes = polygon;
        nodes.push_back(passenger);
        edgeLen.resize(n);
        prefixLen.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            edgeLen[i] = pointLength(polygon[(i + 1) % n] - polygon[i]);
            prefixLen[i + 1] = prefixLen[i] + edgeLen[i];
        }
        perimeter = prefixLen[n];
        ratioSpeed = personSpeed / luggageSpeed;
        buildShortest();
        Real firstArrival = shortest[0] / personSpeed;
        Real period = perimeter / luggageSpeed;
        bestTime = ceill(firstArrival / period - eps) * period;
        for (int sourceId = 0; sourceId <= n; ++sourceId) {
            if (shortest[sourceId] >= inf / 2) continue;
            for (int edgeId = 0; edgeId < n; ++edgeId)
                solveEdge(sourceId, edgeId);
        }
        long long totalSeconds = (long long)floorl(bestTime * 60 + 0.5L);
        cout << "Case " << ++caseId << ": Time = "
             << totalSeconds / 60 << ":"
             << setw(2) << setfill('0') << totalSeconds % 60
             << setfill(' ') << '\n';
    }
    return 0;
}
