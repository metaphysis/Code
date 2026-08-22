#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

struct Point {
    double x, y, z;
    Point() : x(0), y(0), z(0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point operator + (const Point &b) const { return Point(x + b.x, y + b.y, z + b.z); }
    Point operator - (const Point &b) const { return Point(x - b.x, y - b.y, z - b.z); }
    Point operator * (double k) const { return Point(x * k, y * k, z * k); }
};

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(const Point &a, const Point &b) {
    return Point(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double length(const Point &a) { return sqrt(dot(a, a)); }

Point normalize(const Point &a) {
    double len = length(a);
    return a * (1.0 / len);
}

// 将向量 p 绕单位轴 axis 旋转 angle 度
Point rotatePoint(Point p, Point axis, double angle) {
    double rad = angle * PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    axis = normalize(axis);
    // Rodrigues 旋转公式：
    // p' = p*cos(a) + (axis × p)*sin(a)
    //      + axis*(axis·p)*(1-cos(a))
    return p * c + cross(axis, p) * s + axis * (dot(axis, p) * (1.0 - c));
}

double distance(const Point &a, const Point &b) {
    return length(a - b);
}

// 点 p 到线段 ab 的距离
 double pointToSegment(const Point &p, const Point &a, const Point &b) {
    Point ab = b - a;
    double ab2 = dot(ab, ab);
    if (ab2 < EPS) {
        return distance(p, a);
    }
    double t = dot(p - a, ab) / ab2;
    t = max(0.0, min(1.0, t));
    Point foot = a + ab * t;
    return distance(p, foot);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        Point S, target;
        cin >> n;
        cin >> S.x >> S.y >> S.z;
        cin >> target.x >> target.y >> target.z;
        Point cur = S;
        // X：前方，Y：右方，Z：上方
        Point X(1, 0, 0);
        Point Y(0, 1, 0);
        Point Z(0, 0, 1);
        double minDist = distance(cur, target);
        double maxDist = minDist;
        for (int i = 0; i < n; i++) {
            string command;
            double value;
            cin >> command >> value;
            if (command == "FORWARD") {
                Point next = cur + X * value;
                minDist = min(minDist, pointToSegment(target, cur, next));
                maxDist = max(maxDist, distance(target, next));
                cur = next;
            }
            else if (command == "PITCH") {
                X = normalize(rotatePoint(X, Y, -value));
                Z = normalize(cross(X, Y));
            }
            else if (command == "YAW") {
                X = normalize(rotatePoint(X, Z, -value));
                Y = normalize(cross(Z, X));
            }
            else if (command == "ROLL") {
                Y = normalize(rotatePoint(Y, X, value));
                Z = normalize(cross(X, Y));
            }
        }
        cout << "Case " << tc << ": "
             << fixed << setprecision(10)
             << minDist << ' ' << maxDist << '\n';
    }
    return 0;
}
