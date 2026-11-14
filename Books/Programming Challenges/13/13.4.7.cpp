#include <bits/stdc++.h>

using namespace std;

const double INF = 1e20, EPS = 1e-6, PI = acos(-1.0);

struct point { double x, y; };

// 计算两点间的平面距离
double getDist(point p1, point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// 判断三点是否共线
bool isCollinear(point A, point B, point C) {
    return fabs((B.y - A.y) * (C.x - A.x) - (C.y - A.y) * (B.x - A.x)) < EPS;
}

// 计算内心
point getIncenter(point A, point B, point C) {
    // 三点共线，内心不存在
    if (isCollinear(A, B, C)) return {INF, INF};
    double a = getDist(B, C), b = getDist(A, C), c = getDist(A, B);
    double p = a + b + c;
    return {(a * A.x + b * B.x + c * C.x) / p,
        (a * A.y + b * B.y + c * C.y) / p};
}

// 计算外心
point getCircumcenter(point A, point B, point C) {
    // 三点共线，外心不存在
    if (isCollinear(A, B, C)) return {INF, INF};
    double d =
        2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    double a2 = A.x * A.x + A.y * A.y;
    double b2 = B.x * B.x + B.y * B.y;
    double c2 = C.x * C.x + C.y * C.y;
    return {(a2 * (B.y - C.y) + b2 * (C.y - A.y) + c2 * (A.y - B.y)) / d,
        (a2 * (C.x - B.x) + b2 * (A.x - C.x) + c2 * (B.x - A.x)) / d};
}

// 计算重心
point getCentroid(point A, point B, point C) {
    return {(A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3};
}

// 计算垂心
point getOrthocenter(point A, point B, point C) {
    point g = getCentroid(A, B, C);
    point o = getCircumcenter(A, B, C);
    return {3 * g.x - 2 * o.x, 3 * g.y - 2 * o.y};
}

// 计算旁心
vector<point> getExcenters(point A, point B, point C) {
    vector<point> ps;
    // 三点共线，旁心不存在
    if (isCollinear(A, B, C)) return ps;
    double a = getDist(B, C), b = getDist(A, C), c = getDist(A, B);
    // 对应与边a、边b的延长线、边c的延长线相切的圆的圆心
    ps.push_back({(-a * A.x + b * B.x + c * C.x) / (-a + b + c),
        (-a * A.y + b * B.y + c * C.y) / (-a + b + c)});
    // 对应与边b、边a的延长线、边c的延长线相切的圆的圆心
    ps.push_back({(a * A.x - b * B.x + c * C.x) / (a - b + c),
        (a * A.y - b * B.y + c * C.y) / (a - b + c)});
    // 对应与边c、边a的延长线、边b的延长线相切的圆的圆心
    ps.push_back({(a * A.x + b * B.x - c * C.x) / (a + b - c),
        (a * A.y + b * B.y - c * C.y) / (a + b - c)});
    return ps;
}

// 求两条直线交点
point lineIntersection(point A1, point A2, point B1, point B2) {
    double x1 = A1.x, y1 = A1.y;
    double x2 = A2.x, y2 = A2.y;
    double x3 = B1.x, y3 = B1.y;
    double x4 = B2.x, y4 = B2.y;
    
    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (fabs(d) < EPS) return {INF, INF}; // 平行
    
    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / d;
    return {x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
}

// 将点 p 绕点 o 逆时针旋转 angle 弧度
point rotate(point o, point p, double angle) {
    double dx = p.x - o.x, dy = p.y - o.y;
    double cosA = cos(angle), sinA = sin(angle);
    return {o.x + dx * cosA - dy * sinA,
            o.y + dx * sinA + dy * cosA};
}

// 计算费马点
point getFermatPoint(point A, point B, point C) {
    auto dotAngle = [](point a, point b, point c) {
        double abx = b.x - a.x, aby = b.y - a.y;
        double acx = c.x - a.x, acy = c.y - a.y;
        double ab = sqrt(abx * abx + aby * aby);
        double ac = sqrt(acx * acx + acy * acy);
        return (abx * acx + aby * acy) / (ab * ac);
    };
    double cosA = dotAngle(A, B, C);
    double cosB = dotAngle(B, A, C);
    double cosC = dotAngle(C, A, B);
    if (cosA <= -0.5) return A;  // 角 A ≥ 120°
    if (cosB <= -0.5) return B;  // 角 B ≥ 120°
    if (cosC <= -0.5) return C;  // 角 C ≥ 120°
    auto cross = [](point a, point b, point c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    };
    double angle60 = PI / 3.0;
    double side = cross(B, C, A);
    point Ap;
    if (side > 0) Ap = rotate(B, C, -angle60);
    else Ap = rotate(B, C, angle60);
    side = cross(A, C, B);
    point Bp;
    if (side > 0) Bp = rotate(A, C, -angle60);
    else Bp = rotate(A, C, angle60);
    point F = lineIntersection(A, Ap, B, Bp);
    return F;
}


// 计算费马点最小距离和
double getFermatDist(double a, double b, double c) {
    double cosA = (b * b + c * c - a * a) / (2 * b * c);
    double cosB = (a * a + c * c - b * b) / (2 * a * c);
    double cosC = (a * a + b * b - c * c) / (2 * a * b);
    if (cosA <= -0.5) return b + c;
    if (cosB <= -0.5) return a + c;
    if (cosC <= -0.5) return a + b;
    double p = (a + b + c) / 2.0;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return sqrt(0.5 * (a * a + b * b + c * c + 4.0 * sqrt(3.0) * s));
}

int main() {
    point A, B, C;
    while (cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y) {
        point p1 = getIncenter(A, B, C); cout << p1.x << ' ' << p1.y << '\n';
        point p2 = getCircumcenter(A, B, C); cout << p2.x << ' ' << p2.y << '\n';
        point p3 = getCentroid(A, B, C); cout << p3.x << ' ' << p3.y << '\n';
        point p4 = getOrthocenter(A, B, C); cout << p4.x << ' ' << p4.y << '\n';
        vector<point> ps = getExcenters(A, B, C);
            for (auto p5 : ps) cout << p5.x << ' ' << p5.y << '\n';
        point p6 = getFermatPoint(A, B, C); cout << p6.x << ' ' << p6.y << '\n';
        cout << "Fermat Distance:\n";
        double d1 = getDist(p6, A) + getDist(p6, B) + getDist(p6, C);
        cout << d1 << '\n';
        double a = getDist(B, C), b = getDist(A, C), c = getDist(A, B);
        cout << getFermatDist(a, b, c) << '\n';
        cout << '\n';
    }
    return 0;
}
