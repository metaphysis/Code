#include <bits/stdc++.h>
using namespace std;

const double pi = 4 * atan(1.0);
const double eps = 1e-8;
const double inf = 0x3f3f3f3f3f3f3f;

int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    bool operator == (const Point& u) const {
        return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0;
    }
    bool operator < (const Point& u) const {
        return x < u.x || (dcmp(x - u.x) == 0 && y < u.y);
    }
    bool operator > (const Point& u) const {
        return u < *this;
    }
    bool operator <= (const Point& u) const {
        return *this < u || *this == u;
    }
    bool operator >= (const Point& u) const {
        return *this > u || *this == u;
    }
    Point operator + (const Point& u) const {
        return Point(x + u.x, y + u.y);
    }
    Point operator - (const Point& u) const {
        return Point(x - u.x, y - u.y);
    }
    Point operator * (double u) const {
        return Point(x * u, y * u);
    }
    Point operator / (double u) const {
        return Point(x / u, y / u);
    }
    double operator * (const Point& u) const {
        return x * u.y - y * u.x;
    }
};

typedef Point Vector;

double getDot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double getCross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double getLength(Vector a) {
    return sqrt(getDot(a, a));
}

double getAngle(Vector a) {
    return atan2(a.y, a.x);
}

double getAngle(Vector a, Vector b) {
    double value = getDot(a, b) / getLength(a) / getLength(b);
    value = max(-1.0, min(1.0, value));
    return acos(value);
}

Vector rotate(Vector a, double rad) {
    return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

double getDistance(Point a, Point b) {
    return getLength(a - b);
}

bool onSegment(Point p, Point a, Point b) {
    if (p == a || p == b) return true;
    return dcmp(getCross(a - p, b - p)) == 0 && dcmp(getDot(a - p, b - p)) < 0;
}

bool haveIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = getCross(a2 - a1, b1 - a1), c2 = getCross(a2 - a1, b2 - a1);
    double c3 = getCross(b2 - b1, a1 - b1), c4 = getCross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
}

bool getIntersection(Point p, Vector v, Point q, Vector w, Point& o) {
    if (dcmp(getCross(v, w)) == 0) return false;
    Vector u = p - q;
    double k = getCross(w, u) / getCross(v, w);
    o = p + v * k;
    return true;
}

struct Segment {
    Point s, e;
    Segment() {}
    Segment(Point s, Point e): s(s), e(e) {}
};

struct Circle {
    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r = 0): o(o), r(r) {}
    Point point(double rad) {
        return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }
};

int getLineCircleIntersection(Point p, Point q, Circle o, double& t1, double& t2, vector<Point>& sol) {
    Vector v = q - p;
    double a = getDot(v, v);
    double b = 2 * getDot(v, p - o.o);
    double c = getDot(p - o.o, p - o.o) - o.r * o.r;
    double delta = b * b - 4 * a * c;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -b / (2 * a);
        sol.push_back(p + v * t1);
        return 1;
    }
    t1 = (-b - sqrt(delta)) / (2 * a);
    t2 = (-b + sqrt(delta)) / (2 * a);
    sol.push_back(p + v * t1);
    sol.push_back(p + v * t2);
    return 2;
}

int getCircleCircleIntersection(Circle o1, Circle o2, vector<Point>& sol) {
    double d = getLength(o1.o - o2.o);
    if (dcmp(d) == 0) {
        if (dcmp(o1.r - o2.r) == 0) return -1;
        return 0;
    }
    if (dcmp(o1.r + o2.r - d) < 0) return 0;
    if (dcmp(fabs(o1.r - o2.r) - d) > 0) return 0;
    double base = getAngle(o2.o - o1.o);
    double delta = acos((o1.r * o1.r + d * d - o2.r * o2.r) / (2 * o1.r * d));
    Point p1 = o1.point(base - delta), p2 = o1.point(base + delta);
    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

const int maxn = 205;

double radius;
int n, itemCount, indexList[maxn], segmentCount, circleCount;
Point points[maxn], path[maxn];
Segment segments[maxn];
Circle circles[maxn];

void init() {
    itemCount = 0;
    segmentCount = circleCount = 1;
    for (int i = 0; i < n; i++) points[i].read();
    int count = 0;
    path[count++] = Point(0, 0);
    for (int i = 0; i < n; i++) {
        if (dcmp(points[i].x))
            path[count++] = Point(path[count - 1].x + points[i].x, path[count - 1].y);
        if (dcmp(points[i].y))
            path[count++] = Point(path[count - 1].x, path[count - 1].y + points[i].y);
    }
    for (int i = 0; i < count; i++) {
        if (i) {
            if (dcmp(path[i - 1].x - path[i].x) == 0) {
                if (dcmp(path[i - 1].y - path[i].y) < 0)
                    segments[segmentCount] = Segment(Point(path[i - 1].x - radius, path[i - 1].y), Point(path[i].x - radius, path[i].y));
                else
                    segments[segmentCount] = Segment(Point(path[i - 1].x + radius, path[i - 1].y), Point(path[i].x + radius, path[i].y));
            } else {
                segments[segmentCount] = Segment(Point(path[i - 1].x, path[i - 1].y + radius), Point(path[i].x, path[i].y + radius));
            }
            indexList[itemCount++] = -segmentCount++;
        }
        circles[circleCount] = Circle(path[i], radius);
        indexList[itemCount++] = circleCount++;
    }
}

void handle(int u, int v, Point& point, int& best, int current, Point origin) {
    Point target(inf, inf);
    double k1, k2;
    vector<Point> solution;
    if (u < 0 && v < 0) {
        u = -u;
        v = -v;
        if (haveIntersection(segments[u].s, segments[u].e, segments[v].s, segments[v].e)) {
            getIntersection(segments[u].s, segments[u].e - segments[u].s, segments[v].s, segments[v].e - segments[v].s, target);
            k1 = getLength(target - segments[u].s) / getLength(segments[u].e - segments[u].s);
            k2 = getLength(point - segments[u].s) / getLength(segments[u].e - segments[u].s);
            if (best == 0 || dcmp(k1 - k2) < 0 || (dcmp(k1 - k2) == 0 && best < current)) {
                best = current;
                point = target;
            }
        }
    } else if (u < 0 && v > 0) {
        u = -u;
        double t1, t2;
        int count = getLineCircleIntersection(segments[u].s, segments[u].e, circles[v], t1, t2, solution);
        for (int i = 0; i < count; i++)
            if (onSegment(solution[i], segments[u].s, segments[u].e)) {
                k1 = getLength(solution[i] - segments[u].s) / getLength(segments[u].e - segments[u].s);
                k2 = getLength(target - segments[u].s) / getLength(segments[u].e - segments[u].s);
                if (dcmp(k1 - k2) < 0) target = solution[i];
            }
        k1 = getLength(target - segments[u].s) / getLength(segments[u].e - segments[u].s);
        k2 = getLength(point - segments[u].s) / getLength(segments[u].e - segments[u].s);
        if (best == 0 || dcmp(k1 - k2) < 0 || (dcmp(k1 - k2) == 0 && best < current)) {
            best = current;
            point = target;
        }
    } else if (u > 0 && v < 0) {
        v = -v;
        double rad = inf;
        double t1, t2;
        int count = getLineCircleIntersection(segments[v].s, segments[v].e, circles[u], t1, t2, solution);
        for (int i = 0; i < count; i++)
            if (onSegment(solution[i], segments[v].s, segments[v].e)) {
                double temp = origin == solution[i] ? 0 : getAngle(origin - circles[u].o, solution[i] - circles[u].o);
                if (dcmp((origin - circles[u].o) * (solution[i] - circles[u].o)) > 0) temp = 2 * pi - temp;
                if (dcmp(rad - temp) >= 0) {
                    rad = temp;
                    target = solution[i];
                }
            }
        double angle = origin == point ? 0 : getAngle(origin - circles[u].o, point - circles[u].o);
        if (dcmp((origin - circles[u].o) * (point - circles[u].o)) > 0) angle = 2 * pi - angle;
        if (best == 0 || dcmp(rad - angle) < 0 || (dcmp(rad - angle) == 0 && best < current)) {
            best = current;
            point = target;
        }
    } else if (u > 0 && v > 0) {
        double rad = inf;
        int count = getCircleCircleIntersection(circles[u], circles[v], solution);
        for (int i = 0; i < count; i++) {
            double temp = origin == solution[i] ? 0 : getAngle(origin - circles[u].o, solution[i] - circles[u].o);
            if (dcmp((origin - circles[u].o) * (solution[i] - circles[u].o)) > 0) temp = 2 * pi - temp;
            if (dcmp(rad - temp) >= 0) {
                rad = temp;
                target = solution[i];
            }
        }
        double angle = origin == point ? 0 : getAngle(origin - circles[u].o, point - circles[u].o);
        if (dcmp((origin - circles[u].o) * (point - circles[u].o)) > 0) angle = 2 * pi - angle;
        if (best == 0 || dcmp(rad - angle) < 0 || (dcmp(rad - angle) == 0 && best < current)) {
            best = current;
            point = target;
        }
    }
}

double solve() {
    int current = 0;
    double answer = 0, rotateAngle = 0;
    Point start = path[0] + Point(0, radius);
    while (current + 1 < itemCount) {
        int best = 0;
        Point end;
        for (int i = current + 1; i < itemCount; i++)
            handle(indexList[current], indexList[i], end, best, i, start);
        if (indexList[current] > 0) {
            int circleId = indexList[current];
            double angle = getAngle(start - circles[circleId].o, end - circles[circleId].o);
            if (dcmp((start - circles[circleId].o) * (end - circles[circleId].o)) > 0) angle = 2 * pi - angle;
            rotateAngle += angle;
        } else if (dcmp(start.x - end.x) == 0) {
            answer += fabs(end.y - start.y);
        } else if (dcmp(start.y - end.y) == 0) {
            answer += fabs(end.x - start.x);
        }
        start = end;
        current = best;
    }
    return answer + rotateAngle * radius;
}

int main() {
    int testCase = 1;
    while (scanf("%lf%d", &radius, &n) == 2) {
        if (dcmp(radius) == 0 && n == 0) break;
        init();
        printf("Case %d: Distance = %.3f\n\n", testCase++, solve());
    }
    return 0;
}
