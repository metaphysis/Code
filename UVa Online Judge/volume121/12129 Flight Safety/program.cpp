#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-10;

struct Point {
    double x, y;
    Point operator + (const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator * (double k) const { return {x * k, y * k}; }
};

struct Interval {
    double l, r;
};

int continentCount, routeCount;
vector<Point> routePoint;
vector<vector<Point> > continent;
vector<Interval> allInterval;

double dotProduct(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

void addInterval(double l, double r) {
    l = max(l, 0.0);
    r = min(r, 1.0);
    if (l <= r + Eps)
        allInterval.push_back({l, r});
}

void addCircleInterval(Point s, Point v, Point c, double radius) {
    Point w = s - c;
    double a = dotProduct(v, v), b = 2.0 * dotProduct(w, v), cc = dotProduct(w, w) - radius * radius;
    double delta = b * b - 4.0 * a * cc;
    if (delta < -Eps)
        return;
    delta = max(delta, 0.0);
    double t1 = (-b - sqrt(delta)) / (2.0 * a), t2 = (-b + sqrt(delta)) / (2.0 * a);
    addInterval(t1, t2);
}

void addEdgeInterval(Point s, Point v, Point a, Point b, double radius) {
    Point e = b - a;
    double len = sqrt(dotProduct(e, e)), len2 = dotProduct(e, e);
    double sideA = crossProduct(e, v), sideB = crossProduct(e, s - a);
    double projectionA = dotProduct(s - a, e) / len2;
    double projectionB = dotProduct(v, e) / len2;
    if (fabs(sideA) < Eps) {
        if (fabs(sideB) <= radius * len + Eps) {
            double l = 0.0, r = 1.0;
            if (fabs(projectionB) < Eps) {
                if (projectionA >= -Eps && projectionA <= 1.0 + Eps)
                    addInterval(l, r);
            } else {
                double t1 = (0.0 - projectionA) / projectionB, t2 = (1.0 - projectionA) / projectionB;
                if (t1 > t2)
                    swap(t1, t2);
                addInterval(max(l, t1), min(r, t2));
            }
        }
    } else {
        double t1 = (-radius * len - sideB) / sideA, t2 = (radius * len - sideB) / sideA;
        if (t1 > t2)
            swap(t1, t2);
        double u1, u2;
        if (fabs(projectionB) < Eps) {
            if (projectionA >= -Eps && projectionA <= 1.0 + Eps)
                addInterval(t1, t2);
        } else {
            u1 = (0.0 - projectionA) / projectionB;
            u2 = (1.0 - projectionA) / projectionB;
            if (u1 > u2)
                swap(u1, u2);
            addInterval(max(t1, u1), min(t2, u2));
        }
    }
    addCircleInterval(s, v, a, radius);
    addCircleInterval(s, v, b, radius);
}

bool onSegment(Point p, Point a, Point b) {
    return fabs(crossProduct(b - a, p - a)) <= Eps && dotProduct(p - a, p - b) <= Eps;
}

bool inPolygon(Point p, const vector<Point> &poly) {
    bool result = false;
    int m = (int)poly.size();
    for (int i = 0; i < m; i++) {
        Point a = poly[i], b = poly[(i + 1) % m];
        if (onSegment(p, a, b))
            return true;
        if ((a.y > p.y) != (b.y > p.y)) {
            double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (x > p.x)
                result = !result;
        }
    }
    return result;
}

void addInsideIntervals(Point s, Point e, const vector<Point> &poly) {
    Point v = e - s;
    vector<double> cut;
    cut.push_back(0.0);
    cut.push_back(1.0);
    int m = (int)poly.size();
    for (int i = 0; i < m; i++) {
        Point a = poly[i], b = poly[(i + 1) % m], edge = b - a;
        double den = crossProduct(v, edge);
        if (fabs(den) < Eps) {
            if (fabs(crossProduct(a - s, v)) < Eps) {
                cut.push_back(max(0.0, min(1.0, dotProduct(a - s, v) / dotProduct(v, v))));
                cut.push_back(max(0.0, min(1.0, dotProduct(b - s, v) / dotProduct(v, v))));
            }
            continue;
        }
        double t = crossProduct(a - s, edge) / den, u = crossProduct(a - s, v) / den;
        if (t >= -Eps && t <= 1.0 + Eps && u >= -Eps && u <= 1.0 + Eps)
            cut.push_back(max(0.0, min(1.0, t)));
    }
    sort(cut.begin(), cut.end());
    vector<double> uniqueCut;
    for (double t : cut)
        if (uniqueCut.empty() || fabs(t - uniqueCut.back()) > Eps)
            uniqueCut.push_back(t);
    for (int i = 0; i + 1 < (int)uniqueCut.size(); i++) {
        double l = uniqueCut[i], r = uniqueCut[i + 1], mid = (l + r) * 0.5;
        if (inPolygon(s + v * mid, poly))
            addInterval(l, r);
    }
}

bool canReach(double distance) {
    for (int i = 0; i + 1 < routeCount; i++) {
        Point s = routePoint[i], e = routePoint[i + 1], v = e - s;
        allInterval.clear();
        for (const vector<Point> &poly : continent) {
            addInsideIntervals(s, e, poly);
            int m = (int)poly.size();
            for (int j = 0; j < m; j++)
                addEdgeInterval(s, v, poly[j], poly[(j + 1) % m], distance);
        }
        sort(allInterval.begin(), allInterval.end(), [](const Interval &a, const Interval &b) {
            return a.l < b.l;
        });
        double covered = 0.0;
        for (const Interval &item : allInterval) {
            if (item.l > covered + 1e-9)
                return true;
            covered = max(covered, item.r);
        }
        if (covered < 1.0 - 1e-9)
            return true;
    }
    return false;
}

double solve() {
    double low = 0.0, high = 30000.0;
    for (int i = 0; i < 60; i++) {
        double mid = (low + high) * 0.5;
        if (canReach(mid))
            low = mid;
        else
            high = mid;
    }
    return low;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> continentCount >> routeCount;
        routePoint.resize(routeCount);
        for (Point &p : routePoint)
            cin >> p.x >> p.y;
        continent.clear();
        continent.resize(continentCount);
        for (vector<Point> &poly : continent) {
            int vertexCount;
            cin >> vertexCount;
            poly.resize(vertexCount);
            for (Point &p : poly)
                cin >> p.x >> p.y;
        }
        cout << fixed << setprecision(6) << solve() << '\n';
    }
    return 0;
}
