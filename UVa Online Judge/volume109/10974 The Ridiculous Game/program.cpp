#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

struct Point {
    double x, y;
};

struct Edge {
    int from, to;
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dot(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

double distance2(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool samePoint(Point a, Point b) {
    return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}

bool onSegment(Point a, Point b, Point p) {
    if (fabs(cross(a, b, p)) >= eps)
        return false;
    return p.x >= min(a.x, b.x) - eps && p.x <= max(a.x, b.x) + eps &&
           p.y >= min(a.y, b.y) - eps && p.y <= max(a.y, b.y) + eps;
}

bool pointInPolygon(const vector<Point> &poly, Point p) {
    int n = (int)poly.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[j], b = poly[i];
        if (onSegment(a, b, p))
            return true;
        bool crossY = (a.y > p.y) != (b.y > p.y);
        if (crossY) {
            double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (x > p.x)
                inside = !inside;
        }
    }
    return inside;
}

int getPointId(vector<Point> &points, Point p) {
    for (int i = 0; i < (int)points.size(); i++)
        if (samePoint(points[i], p))
            return i;
    points.push_back(p);
    return (int)points.size() - 1;
}

double lineValue(Point a, Point b, Point p) {
    return cross(a, b, p);
}

double polygonArea(const vector<Point> &poly) {
    double area = 0;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++)
        area += poly[i].x * poly[(i + 1) % n].y - poly[(i + 1) % n].x * poly[i].y;
    return area / 2.0;
}

void simplifyPolygon(vector<Point> &poly) {
    vector<Point> temp;
    for (Point p : poly)
        if (temp.empty() || !samePoint(temp.back(), p))
            temp.push_back(p);
    if (temp.size() > 1 && samePoint(temp.front(), temp.back()))
        temp.pop_back();
    bool changed = true;
    while (changed && temp.size() >= 3) {
        changed = false;
        vector<Point> next;
        int n = (int)temp.size();
        for (int i = 0; i < n; i++) {
            Point prev = temp[(i + n - 1) % n], now = temp[i], after = temp[(i + 1) % n];
            if (fabs(cross(prev, now, after)) < eps) {
                changed = true;
                continue;
            }
            next.push_back(now);
        }
        temp = next;
    }
    poly = temp;
}

void rotatePolygon(vector<Point> &poly) {
    int pos = 0;
    for (int i = 1; i < (int)poly.size(); i++) {
        if (poly[i].y < poly[pos].y - eps ||
            (fabs(poly[i].y - poly[pos].y) < eps && poly[i].x < poly[pos].x - eps))
            pos = i;
    }
    rotate(poly.begin(), poly.begin() + pos, poly.end());
}

vector<vector<Point>> buildSide(const vector<Point> &poly, Point lineA, Point lineB, int side) {
    int n = (int)poly.size();
    vector<Point> points = poly;
    vector<Edge> edges;
    vector<int> linePointIds;
    set<pair<int, int>> edgeSet;
    double lineLen2 = distance2(lineA, lineB);
    for (int i = 0; i < n; i++)
        if (fabs(lineValue(lineA, lineB, poly[i])) < eps)
            linePointIds.push_back(i);
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        double den = cross(lineA, lineB, Point{b.x - a.x + lineA.x, b.y - a.y + lineA.y});
        vector<pair<double, int>> cuts;
        cuts.push_back({0.0, i});
        cuts.push_back({1.0, (i + 1) % n});
        if (fabs(den) >= eps) {
            double num = cross(lineA, lineB, a);
            double t = -num / den;
            if (t > eps && t < 1.0 - eps) {
                Point p{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
                int id = getPointId(points, p);
                cuts.push_back({t, id});
                linePointIds.push_back(id);
            }
        }
        sort(cuts.begin(), cuts.end());
        vector<pair<double, int>> uniqueCuts;
        for (auto item : cuts) {
            if (uniqueCuts.empty() || fabs(uniqueCuts.back().first - item.first) >= eps)
                uniqueCuts.push_back(item);
        }
        bool edgeOnLine = fabs(lineValue(lineA, lineB, a)) < eps &&
                          fabs(lineValue(lineA, lineB, b)) < eps;
        if (!edgeOnLine) {
            for (int j = 0; j + 1 < (int)uniqueCuts.size(); j++) {
                int u = uniqueCuts[j].second, v = uniqueCuts[j + 1].second;
                Point mid{(points[u].x + points[v].x) / 2.0, (points[u].y + points[v].y) / 2.0};
                double value = lineValue(lineA, lineB, mid);
                if ((side > 0 && value > eps) || (side < 0 && value < -eps)) {
                    pair<int, int> key = {u, v};
                    if (edgeSet.insert(key).second)
                        edges.push_back({u, v});
                }
            }
        }
    }
    sort(linePointIds.begin(), linePointIds.end());
    linePointIds.erase(unique(linePointIds.begin(), linePointIds.end()), linePointIds.end());
    sort(linePointIds.begin(), linePointIds.end(), [&](int a, int b) {
        double ta = ((points[a].x - lineA.x) * (lineB.x - lineA.x) +
                     (points[a].y - lineA.y) * (lineB.y - lineA.y)) / lineLen2;
        double tb = ((points[b].x - lineA.x) * (lineB.x - lineA.x) +
                     (points[b].y - lineA.y) * (lineB.y - lineA.y)) / lineLen2;
        return ta < tb;
    });
    for (int i = 0; i + 1 < (int)linePointIds.size(); i++) {
        int u = linePointIds[i], v = linePointIds[i + 1];
        Point mid{(points[u].x + points[v].x) / 2.0, (points[u].y + points[v].y) / 2.0};
        if (!pointInPolygon(poly, mid))
            continue;
        if (side < 0)
            swap(u, v);
        pair<int, int> key = {u, v};
        if (edgeSet.insert(key).second)
            edges.push_back({u, v});
    }
    vector<vector<int>> graph(points.size());
    for (int i = 0; i < (int)edges.size(); i++)
        graph[edges[i].from].push_back(i);
    vector<bool> used(edges.size(), false);
    vector<vector<Point>> result;
    for (int start = 0; start < (int)edges.size(); start++) {
        if (used[start])
            continue;
        vector<int> ids;
        int edgeId = start, startFrom = edges[start].from;
        while (!used[edgeId]) {
            used[edgeId] = true;
            ids.push_back(edges[edgeId].from);
            int from = edges[edgeId].from, to = edges[edgeId].to;
            int nextEdge = -1;
            double inAngle = atan2(points[from].y - points[to].y, points[from].x - points[to].x);
            for (int candidate : graph[to]) {
                if (used[candidate])
                    continue;
                double outAngle = atan2(points[edges[candidate].to].y - points[to].y,
                                        points[edges[candidate].to].x - points[to].x);
                double turn = inAngle - outAngle;
                while (turn < 0)
                    turn += 2.0 * pi;
                while (turn >= 2.0 * pi)
                    turn -= 2.0 * pi;
                if (nextEdge == -1)
                    nextEdge = candidate;
                else {
                    double oldAngle = atan2(points[edges[nextEdge].to].y - points[to].y,
                                            points[edges[nextEdge].to].x - points[to].x);
                    double oldTurn = inAngle - oldAngle;
                    while (oldTurn < 0)
                        oldTurn += 2.0 * pi;
                    while (oldTurn >= 2.0 * pi)
                        oldTurn -= 2.0 * pi;
                    if (turn < oldTurn)
                        nextEdge = candidate;
                }
            }
            if (nextEdge == -1)
                break;
            edgeId = nextEdge;
            if (edges[edgeId].from == startFrom && edgeId == start)
                break;
        }
        if (ids.size() < 3)
            continue;
        vector<Point> current;
        for (int id : ids)
            current.push_back(points[id]);
        simplifyPolygon(current);
        if (current.size() < 3 || polygonArea(current) < eps)
            continue;
        rotatePolygon(current);
        result.push_back(current);
    }
    return result;
}

bool polygonLess(const vector<Point> &a, const vector<Point> &b) {
    int n = min(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        if (fabs(a[i].x - b[i].x) >= eps)
            return a[i].x < b[i].x;
        if (fabs(a[i].y - b[i].y) >= eps)
            return a[i].y < b[i].y;
    }
    return a.size() < b.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, testCase = 1;
    while (cin >> n && n) {
        vector<Point> poly(n);
        for (Point &p : poly)
            cin >> p.x >> p.y;
        Point lineA, lineB;
        cin >> lineA.x >> lineA.y >> lineB.x >> lineB.y;
        vector<vector<Point>> answer = buildSide(poly, lineA, lineB, 1);
        vector<vector<Point>> other = buildSide(poly, lineA, lineB, -1);
        answer.insert(answer.end(), other.begin(), other.end());
        sort(answer.begin(), answer.end(), polygonLess);
        if (testCase > 1)
            cout << '\n';
        cout << "Test Case #" << testCase++ << '\n';
        cout << answer.size() << '\n';
        cout << fixed << setprecision(5);
        for (const vector<Point> &current : answer) {
            for (int i = 0; i < (int)current.size(); i++) {
                if (i)
                    cout << ' ';
                cout << current[i].x << ' ' << current[i].y;
            }
            cout << '\n';
        }
    }
    return 0;
}
