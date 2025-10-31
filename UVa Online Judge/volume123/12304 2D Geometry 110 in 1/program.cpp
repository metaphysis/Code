// 2D Geometry 110 in 1
// UVa ID: 12304
// Verdict: Accepted
// Submission Date: 2025-10-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/154121047

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
    Point operator / (double k) const { return Point(x / k, y / k); }
    
    double length() const { return sqrt(x * x + y * y); }
    Point normalize() const { return *this / length(); }
    Point rotate90() const { return Point(-y, x); }
};

double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
double distance(const Point& a, const Point& b) { return (a - b).length(); }

struct Line {
    Point p, v;
    Line(const Point& p, const Point& v) : p(p), v(v) {}
};

struct Circle {
    Point center;
    double radius;
    Circle(const Point& center = Point(), double radius = 0) : center(center), radius(radius) {}
};

// 判断两个浮点数是否相等
bool equal(double a, double b) { return fabs(a - b) < EPS; }

// 格式化输出
string format(double x) {
    stringstream ss;
    ss << fixed << setprecision(6) << x;
    return ss.str();
}

string format(const Point& p) {
    return "(" + format(p.x) + "," + format(p.y) + ")";
}

string formatCircle(const Circle& c) {
    return "(" + format(c.center.x) + "," + format(c.center.y) + "," + format(c.radius) + ")";
}

// 1. 外接圆
Circle circumscribedCircle(double x1, double y1, double x2, double y2, double x3, double y3) {
    Point A(x1, y1), B(x2, y2), C(x3, y3);
    
    double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) + 
                 (B.x * B.x + B.y * B.y) * (C.y - A.y) + 
                 (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) + 
                 (B.x * B.x + B.y * B.y) * (A.x - C.x) + 
                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;
    
    Point center(Ux, Uy);
    double radius = distance(center, A);
    
    return Circle(center, radius);
}

// 2. 内切圆
Circle inscribedCircle(double x1, double y1, double x2, double y2, double x3, double y3) {
    Point A(x1, y1), B(x2, y2), C(x3, y3);
    
    double a = distance(B, C);
    double b = distance(A, C);
    double c = distance(A, B);
    double perimeter = a + b + c;
    
    double Ix = (a * A.x + b * B.x + c * C.x) / perimeter;
    double Iy = (a * A.y + b * B.y + c * C.y) / perimeter;
    
    Point center(Ix, Iy);
    
    // 计算半径：面积 * 2 / 周长
    double area = fabs(cross(B - A, C - A)) / 2.0;
    double radius = 2 * area / perimeter;
    
    return Circle(center, radius);
}

// 3. 过点的圆的切线
vector<double> tangentLineThroughPoint(double xc, double yc, double r, double xp, double yp) {
    Point C(xc, yc), P(xp, yp);
    double d = distance(C, P);
    vector<double> angles;
    if (d < r - EPS) {
        // 点在圆内，无切线
        return angles;
    }
    if (fabs(d - r) < EPS) {
        // 点在圆上，一条切线
        Point v = P - C;
        double angle = atan2(v.y, v.x) * 180 / PI + 90;
        if (angle < 0) angle += 180;
        if (angle >= 180) angle -= 180;
        angles.push_back(angle);
    } else {
        // 点在圆外，两条切线
        double alpha = asin(r / d) * 180 / PI;
        Point v = P - C;
        double base_angle = atan2(v.y, v.x) * 180 / PI;
        double angle1 = base_angle + alpha;
        double angle2 = base_angle - alpha;
        // 标准化角度到 [0, 180)
        angle1 = fmod(angle1 + 360, 180);
        angle2 = fmod(angle2 + 360, 180);
        angles.push_back(angle1);
        angles.push_back(angle2);
        sort(angles.begin(), angles.end());
    }
    return angles;
}

// 4. 过定点且与定直线相切的圆
vector<Point> circleThroughAPointAndTangentToALineWithRadius(double xp, double yp, 
                                                           double x1, double y1, 
                                                           double x2, double y2, 
                                                           double r) {
    Point P(xp, yp), A(x1, y1), B(x2, y2);
    vector<Point> centers;
    
    // 直线的方向向量和单位法向量
    Point dir = B - A;
    Point normal = dir.rotate90().normalize();
    
    // 两条平行线（距离直线r）
    vector<Line> parallel_lines = {
        Line(A + normal * r, dir),
        Line(A - normal * r, dir)
    };
    
    // 求每条平行线与圆的交点
    for (const Line& line : parallel_lines) {
        Point v = line.v;
        Point w = line.p - P;
        
        // 解二次方程: |v|²t² + 2(v·w)t + |w|² - r² = 0
        double a = dot(v, v);
        double b = 2 * dot(v, w);
        double c = dot(w, w) - r * r;
        
        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < -EPS) continue;
        if (fabs(a) < EPS) continue;
        
        double sqrt_d = sqrt(max(0.0, discriminant));
        double t1 = (-b + sqrt_d) / (2 * a);
        double t2 = (-b - sqrt_d) / (2 * a);
        
        centers.push_back(line.p + v * t1);
        if (fabs(discriminant) > EPS) { // 两个不同解
            centers.push_back(line.p + v * t2);
        }
    }
    
    // 排序
    sort(centers.begin(), centers.end(), [](const Point& a, const Point& b) {
        if (fabs(a.x - b.x) < EPS) return a.y < b.y;
        return a.x < b.x;
    });
    
    return centers;
}

// 5. 与两条直线相切的圆
vector<Point> circleTangentToTwoLinesWithRadius(double x1, double y1, double x2, double y2,
                                              double x3, double y3, double x4, double y4,
                                              double r) {
    Point A1(x1, y1), A2(x2, y2), B1(x3, y3), B2(x4, y4);
    vector<Point> centers;
    
    // 两条直线的方向向量
    Point dirA = A2 - A1;
    Point dirB = B2 - B1;
    
    // 法向量
    Point normalA = dirA.rotate90().normalize();
    Point normalB = dirB.rotate90().normalize();
    
    // 四个可能的偏移组合
    vector<pair<Point, Point>> offsets = {
        {normalA * r, normalB * r},
        {normalA * r, normalB * -r},
        {normalA * -r, normalB * r},
        {normalA * -r, normalB * -r}
    };
    
    for (auto& offset : offsets) {
        // 偏移后的直线
        Line LA(A1 + offset.first, dirA);
        Line LB(B1 + offset.second, dirB);
        
        // 求交点
        double det = cross(LA.v, LB.v);
        if (fabs(det) < EPS) continue; // 平行
        
        double t = cross(LB.p - LA.p, LB.v) / det;
        Point center = LA.p + LA.v * t;
        centers.push_back(center);
    }
    
    // 排序
    sort(centers.begin(), centers.end(), [](const Point& a, const Point& b) {
        if (fabs(a.x - b.x) < EPS) return a.y < b.y;
        return a.x < b.x;
    });
    
    return centers;
}

// 6. 与两个圆外切的圆
vector<Point> circleTangentToTwoDisjointCirclesWithRadius(double x1, double y1, double r1,
                                                        double x2, double y2, double r2,
                                                        double r) {
    Point C1(x1, y1), C2(x2, y2);
    vector<Point> centers;
    
    // 将问题转化为求与两个圆的圆心距离为r1+r和r2+r的圆的圆心
    double d = distance(C1, C2);
    double R1 = r1 + r;
    double R2 = r2 + r;
    
    // 检查是否有解
    if (d > R1 + R2 + EPS || d < fabs(R1 - R2) - EPS) {
        return centers;
    }
    
    // 计算交点
    double a = (R1 * R1 - R2 * R2 + d * d) / (2 * d);
    double h = sqrt(R1 * R1 - a * a);
    
    Point P = C1 + (C2 - C1) * (a / d);
    Point perpendicular = (C2 - C1).rotate90().normalize() * h;
    
    centers.push_back(P + perpendicular);
    centers.push_back(P - perpendicular);
    
    // 排序
    sort(centers.begin(), centers.end(), [](const Point& a, const Point& b) {
        if (fabs(a.x - b.x) < EPS) return a.y < b.y;
        return a.x < b.x;
    });
    
    return centers;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string command;
    while (cin >> command) {
        if (command == "CircumscribedCircle") {
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            Circle circle = circumscribedCircle(x1, y1, x2, y2, x3, y3);
            cout << formatCircle(circle) << "\n";
        }
        else if (command == "InscribedCircle") {
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            Circle circle = inscribedCircle(x1, y1, x2, y2, x3, y3);
            cout << formatCircle(circle) << "\n";
        }
        else if (command == "TangentLineThroughPoint") {
            double xc, yc, r, xp, yp;
            cin >> xc >> yc >> r >> xp >> yp;
            vector<double> angles = tangentLineThroughPoint(xc, yc, r, xp, yp);
            cout << "[";
            for (size_t i = 0; i < angles.size(); i++) {
                cout << format(angles[i]);
                if (i < angles.size() - 1) cout << ",";
            }
            cout << "]\n";
        }
        else if (command == "CircleThroughAPointAndTangentToALineWithRadius") {
            double xp, yp, x1, y1, x2, y2, r;
            cin >> xp >> yp >> x1 >> y1 >> x2 >> y2 >> r;
            vector<Point> centers = circleThroughAPointAndTangentToALineWithRadius(xp, yp, x1, y1, x2, y2, r);
            cout << "[";
            for (size_t i = 0; i < centers.size(); i++) {
                cout << format(centers[i]);
                if (i < centers.size() - 1) cout << ",";
            }
            cout << "]\n";
        }
        else if (command == "CircleTangentToTwoLinesWithRadius") {
            double x1, y1, x2, y2, x3, y3, x4, y4, r;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> r;
            vector<Point> centers = circleTangentToTwoLinesWithRadius(x1, y1, x2, y2, x3, y3, x4, y4, r);
            cout << "[";
            for (size_t i = 0; i < centers.size(); i++) {
                cout << format(centers[i]);
                if (i < centers.size() - 1) cout << ",";
            }
            cout << "]\n";
        }
        else if (command == "CircleTangentToTwoDisjointCirclesWithRadius") {
            double x1, y1, r1, x2, y2, r2, r;
            cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> r;
            vector<Point> centers = circleTangentToTwoDisjointCirclesWithRadius(x1, y1, r1, x2, y2, r2, r);
            cout << "[";
            for (size_t i = 0; i < centers.size(); i++) {
                cout << format(centers[i]);
                if (i < centers.size() - 1) cout << ",";
            }
            cout << "]\n";
        }
    }
    
    return 0;
}
