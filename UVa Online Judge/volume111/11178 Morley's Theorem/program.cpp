// Morley's Theorem
// UVa ID: 11178
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// 定义点结构体
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

// 向量加法
Point operator+(const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
// 向量减法
Point operator-(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }
// 向量数乘
Point operator*(const Point& a, double t) { return Point(a.x * t, a.y * t); }
// 向量点积
double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
// 向量叉积
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
// 向量长度
double len(const Point& a) { return sqrt(dot(a, a)); }
// 向量逆时针旋转
Point rotate(const Point& a, double rad) {
    return Point(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

// 求两条直线的交点
Point lineIntersection(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    double a1 = cross(p2 - p1, q1 - p1);
    double a2 = cross(p2 - p1, q2 - p1);
    return (q1 * a2 - q2 * a1) * (1.0 / (a2 - a1));
}

// 计算点D：靠近BC边的三等分线交点
Point getD(const Point& A, const Point& B, const Point& C, double tB, double tC) {
    Point vBC = C - B;  // 从B到C的向量
    Point vCB = B - C;  // 从C到B的向量
    Point ray1 = rotate(vBC, tB);   // 在B点，从BC逆时针旋转θB
    Point ray2 = rotate(vCB, -tC);  // 在C点，从CB顺时针旋转θC
    return lineIntersection(B, B + ray1, C, C + ray2);
}

// 计算点E：靠近CA边的三等分线交点
Point getE(const Point& A, const Point& B, const Point& C, double tC, double tA) {
    Point vCA = A - C;  // 从C到A的向量
    Point vAC = C - A;  // 从A到C的向量
    Point ray1 = rotate(vCA, tC);   // 在C点，从CA逆时针旋转θC
    Point ray2 = rotate(vAC, -tA);  // 在A点，从AC顺时针旋转θA
    return lineIntersection(C, C + ray1, A, A + ray2);
}

// 计算点F：靠近AB边的三等分线交点
Point getF(const Point& A, const Point& B, const Point& C, double tA, double tB) {
    Point vAB = B - A;  // 从A到B的向量
    Point vBA = A - B;  // 从B到A的向量
    Point ray1 = rotate(vAB, tA);   // 在A点，从AB逆时针旋转θA
    Point ray2 = rotate(vBA, -tB);  // 在B点，从BA顺时针旋转θB
    return lineIntersection(A, A + ray1, B, B + ray2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);  // 设置输出精度

    int N;
    cin >> N;
    while (N--) {
        Point A, B, C;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

        // 计算各边向量
        Point AB = B - A, AC = C - A;
        Point BA = A - B, BC = C - B;
        Point CA = A - C, CB = B - C;

        // 计算三个内角（使用点积公式）
        double angA = acos(dot(AB, AC) / (len(AB) * len(AC)));
        double angB = acos(dot(BA, BC) / (len(BA) * len(BC)));
        double angC = acos(dot(CA, CB) / (len(CA) * len(CB)));

        // 计算三等分角
        double tA = angA / 3;
        double tB = angB / 3;
        double tC = angC / 3;

        // 计算D、E、F三点坐标
        Point D = getD(A, B, C, tB, tC);
        Point E = getE(A, B, C, tC, tA);
        Point F = getF(A, B, C, tA, tB);

        // 输出结果
        cout << D.x << " " << D.y << " "
             << E.x << " " << E.y << " "
             << F.x << " " << F.y << "\n";
    }
    return 0;
}
