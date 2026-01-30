// Trapezium Drawing
// UVa ID: 12404
// Verdict: Accepted
// Submission Date: 2026-01-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const double PI = 2 * acos(0.0);  // 定义π值

// 点/向量结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point operator+(Point p) { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) { return Point(x - p.x, y - p.y); }
    Point operator*(double k) { return Point(x * k, y * k); }
    Point operator/(double k) { return Point(x / k, y / k); }
    // 向量旋转（逆时针）
    Point rotate(double angle) { 
        return Point(x * cos(angle) - y * sin(angle), 
                     x * sin(angle) + y * cos(angle)); 
    }
};

typedef Point Vector;  // 向量类型

int main() {
    int t, caseNo = 1;
    scanf("%d", &t);
    while (t--) {
        double x1, y1, x2, y2, b, c, d;
        scanf("%lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &b, &c, &d);

        // 计算AB长度
        double a = hypot(x2 - x1, y2 - y1);

        // 余弦定理求角度
        // 辅助三角形1：边长(a-c), b, d，求∠DAB
        double angleDAB = acos((d * d + (a - c) * (a - c) - b * b) / (2 * d * (a - c)));
        // 辅助三角形2：边长(a-c), b, d，求∠CBA
        double angleCBA = acos((b * b + (a - c) * (a - c) - d * d) / (2 * b * (a - c)));

        // 计算点D：从A出发，沿AB方向走d，再逆时针旋转angleDAB
        Vector AB = Point(x2 - x1, y2 - y1) * (d / a);
        Point D = Point(x1, y1) + AB.rotate(angleDAB);

        // 计算点C：从B出发，沿BA方向走b，再逆时针旋转(2π - angleCBA)
        Vector BA = Point(x1 - x2, y1 - y2) * (b / a);
        Point C = Point(x2, y2) + BA.rotate(2 * PI - angleCBA);

        printf("Case %d:\n", caseNo++);
        printf("%.8lf %.8lf %.8lf %.8lf\n", C.x, C.y, D.x, D.y);
    }
    return 0;
}
