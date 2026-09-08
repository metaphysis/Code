#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-10;
const double FlatEps = 1e-7;
const double GridSize = 0.05;
const int MaxDepth = 22;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }
};

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double pointDistance(Point a, Point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

double pointLineDistance(Point p, Point a, Point b) {
    Point d = b - a;
    double len = hypot(d.x, d.y);
    if (len < Eps)
        return pointDistance(p, a);
    return fabs(crossProduct(p - a, d)) / len;
}

struct Segment {
    Point a, b;
    double u1, u2;
};

struct Curve {
    int n, m, degree;
    vector<Point> point;
    vector<double> weight, knot;
    double basis(int i, int d, double u) const {
        if (d == 0) {
            if (knot[i] <= u && u < knot[i + 1])
                return 1.0;
            if (fabs(u - knot[m - 1]) < Eps && i == n - 1)
                return 1.0;
            return 0.0;
        }
        double result = 0;
        double den1 = knot[i + d] - knot[i];
        double den2 = knot[i + d + 1] - knot[i + 1];
        if (fabs(den1) > Eps)
            result += (u - knot[i]) / den1 * basis(i, d - 1, u);
        if (fabs(den2) > Eps)
            result += (knot[i + d + 1] - u) / den2 * basis(i + 1, d - 1, u);
        return result;
    }
    Point eval(double u) const {
        double sx = 0, sy = 0, sw = 0;
        for (int i = 0; i < n; i++) {
            double value = weight[i] * basis(i, degree, u);
            sx += value * point[i].x;
            sy += value * point[i].y;
            sw += value;
        }
        if (fabs(sw) < Eps)
            return point.front();
        return Point(sx / sw, sy / sw);
    }
    Point derivative(double u) const {
        double left = knot.front(), right = knot.back();
        double h = 1e-6 * (right - left);
        double u1 = max(left, u - h), u2 = min(right, u + h);
        if (u2 - u1 < Eps)
            return Point();
        return (eval(u2) - eval(u1)) / (u2 - u1);
    }
};

void splitCurve(const Curve &curve, double u1, double u2, Point p1, Point p2, vector<Segment> &segment, int depth) {
    double um = (u1 + u2) * 0.5;
    double u25 = (u1 + um) * 0.5;
    double u75 = (um + u2) * 0.5;
    Point pm = curve.eval(um);
    Point p25 = curve.eval(u25);
    Point p75 = curve.eval(u75);
    bool flat = pointLineDistance(pm, p1, p2) < FlatEps;
    flat = flat && pointLineDistance(p25, p1, p2) < FlatEps;
    flat = flat && pointLineDistance(p75, p1, p2) < FlatEps;
    if (flat || depth >= MaxDepth || u2 - u1 < 1e-10) {
        segment.push_back({p1, p2, u1, u2});
        return;
    }
    splitCurve(curve, u1, um, p1, pm, segment, depth + 1);
    splitCurve(curve, um, u2, pm, p2, segment, depth + 1);
}

vector<Segment> flattenCurve(const Curve &curve) {
    vector<Segment> result;
    for (int i = 0; i + 1 < curve.m; i++) {
        if (curve.knot[i + 1] - curve.knot[i] < Eps)
            continue;
        double u1 = curve.knot[i], u2 = curve.knot[i + 1];
        Point p1 = curve.eval(u1), p2 = curve.eval(u2);
        splitCurve(curve, u1, u2, p1, p2, result, 0);
    }
    return result;
}

long long getCellKey(int x, int y) {
    return (static_cast<long long>(x) << 32) ^ static_cast<unsigned int>(y);
}

void getRange(const Segment &segment, int &x1, int &x2, int &y1, int &y2) {
    double minX = min(segment.a.x, segment.b.x) - 1e-9;
    double maxX = max(segment.a.x, segment.b.x) + 1e-9;
    double minY = min(segment.a.y, segment.b.y) - 1e-9;
    double maxY = max(segment.a.y, segment.b.y) + 1e-9;
    x1 = static_cast<int>(floor(minX / GridSize));
    x2 = static_cast<int>(floor(maxX / GridSize));
    y1 = static_cast<int>(floor(minY / GridSize));
    y2 = static_cast<int>(floor(maxY / GridSize));
}

bool boxIntersect(const Segment &a, const Segment &b) {
    double aMinX = min(a.a.x, a.b.x), aMaxX = max(a.a.x, a.b.x);
    double aMinY = min(a.a.y, a.b.y), aMaxY = max(a.a.y, a.b.y);
    double bMinX = min(b.a.x, b.b.x), bMaxX = max(b.a.x, b.b.x);
    double bMinY = min(b.a.y, b.b.y), bMaxY = max(b.a.y, b.b.y);
    return aMaxX + 1e-8 >= bMinX && bMaxX + 1e-8 >= aMinX && aMaxY + 1e-8 >= bMinY && bMaxY + 1e-8 >= aMinY;
}

bool lineIntersection(const Segment &a, const Segment &b, double &x, double &y) {
    Point d1 = a.b - a.a, d2 = b.b - b.a;
    double den = crossProduct(d1, d2);
    if (fabs(den) < 1e-13)
        return false;
    Point d = b.a - a.a;
    x = crossProduct(d, d2) / den;
    y = crossProduct(d, d1) / den;
    return x > -1e-8 && x < 1 + 1e-8 && y > -1e-8 && y < 1 + 1e-8;
}

bool refineIntersection(const Curve &c1, const Curve &c2, double &u, double &v, Point &answer) {
    double l1 = c1.knot.front(), r1 = c1.knot.back();
    double l2 = c2.knot.front(), r2 = c2.knot.back();
    for (int iter = 0; iter < 30; iter++) {
        Point p1 = c1.eval(u), p2 = c2.eval(v), f = p1 - p2;
        if (hypot(f.x, f.y) < 1e-10)
            break;
        Point d1 = c1.derivative(u), d2 = c2.derivative(v);
        double det = crossProduct(d1, d2);
        if (fabs(det) < 1e-13)
            return false;
        double du = crossProduct(f, d2) / det;
        double dv = crossProduct(f, d1) / det;
        if (fabs(du) > 0.2 * (r1 - l1) || fabs(dv) > 0.2 * (r2 - l2))
            return false;
        u = max(l1, min(r1, u - du));
        v = max(l2, min(r2, v - dv));
        if (fabs(du) + fabs(dv) < 1e-13)
            break;
    }
    Point p1 = c1.eval(u), p2 = c2.eval(v);
    if (pointDistance(p1, p2) >= 1e-7)
        return false;
    answer = (p1 + p2) * 0.5;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        Curve c1, c2;
        Curve *curveList[2] = {&c1, &c2};
        for (int type = 0; type < 2; type++) {
            Curve &curve = *curveList[type];
            cin >> curve.n >> curve.m;
            curve.point.resize(curve.n);
            curve.weight.resize(curve.n);
            curve.knot.resize(curve.m);
            for (int i = 0; i < curve.n; i++)
                cin >> curve.point[i].x >> curve.point[i].y >> curve.weight[i];
            for (int i = 0; i < curve.m; i++)
                cin >> curve.knot[i];
            curve.degree = curve.m - curve.n - 1;
        }
        vector<Segment> s1 = flattenCurve(c1), s2 = flattenCurve(c2);
        unordered_map<long long, vector<int> > grid;
        for (int i = 0; i < static_cast<int>(s2.size()); i++) {
            int x1, x2, y1, y2;
            getRange(s2[i], x1, x2, y1, y2);
            for (int x = x1; x <= x2; x++)
                for (int y = y1; y <= y2; y++)
                    grid[getCellKey(x, y)].push_back(i);
        }
        vector<Point> answer;
        unordered_set<unsigned long long> used;
        for (int i = 0; i < static_cast<int>(s1.size()); i++) {
            int x1, x2, y1, y2;
            getRange(s1[i], x1, x2, y1, y2);
            for (int x = x1; x <= x2; x++) {
                for (int y = y1; y <= y2; y++) {
                    long long cellKey = getCellKey(x, y);
                    if (!grid.count(cellKey))
                        continue;
                    for (int j : grid[cellKey]) {
                        unsigned long long pairKey = static_cast<unsigned long long>(i) * s2.size() + j;
                        if (!used.insert(pairKey).second)
                            continue;
                        if (!boxIntersect(s1[i], s2[j]))
                            continue;
                        double a, b;
                        if (!lineIntersection(s1[i], s2[j], a, b))
                            continue;
                        double u = s1[i].u1 + (s1[i].u2 - s1[i].u1) * a;
                        double v = s2[j].u1 + (s2[j].u2 - s2[j].u1) * b;
                        Point p;
                        if (!refineIntersection(c1, c2, u, v, p))
                            continue;
                        bool repeated = false;
                        for (const Point &q : answer)
                            if (pointDistance(p, q) < 1e-6)
                                repeated = true;
                        if (!repeated)
                            answer.push_back(p);
                    }
                }
            }
        }
        sort(answer.begin(), answer.end(), [](const Point &a, const Point &b) {
            if (fabs(a.x - b.x) > 1e-9)
                return a.x < b.x;
            return a.y < b.y;
        });
        cout << "Case " << caseId << ": " << answer.size() << '\n';
        cout << fixed << setprecision(3);
        for (Point p : answer) {
            if (fabs(p.x) < 0.0005)
                p.x = 0;
            if (fabs(p.y) < 0.0005)
                p.y = 0;
            cout << '(' << p.x << ", " << p.y << ")\n";
        }
        cout << '\n';
    }
    return 0;
}
