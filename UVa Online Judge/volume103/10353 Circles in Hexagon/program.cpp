// Circles in Hexagon
// UVa ID: 10353
// Verdict: Accepted
// Submission Date: 2026-01-21
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
#define EPS 1e-14
using namespace std;

class Point {
public:
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
};

// 计算向量叉积（有向面积的两倍）
double cross(const Point &a, const Point &b, const Point &c) {
    Point ab = b - a;
    Point ac = c - a;
    return ab.x * ac.y - ab.y * ac.x;
}

int main() {
    int t;
    const double PI = acos(-1.0);
    const double SIN60 = sin(PI / 3.0);
    const double COS60 = cos(PI / 3.0);
    
    double r = 1.0;  // 固定半径计算比例系数
    
    // ---------- 计算5个圆的比例系数 ----------
    double lo5 = (2 * r) / SIN60;
    double hi5 = (4 * r) / SIN60;
    
    while (hi5 - lo5 > EPS) {
        double a = (lo5 + hi5) * 0.5;
        double x1 = r / SIN60;
        double y1 = 0;
        double y2 = a * SIN60 - r;
        
        // 计算圆心1和圆心2之间的水平距离
        double d = 4 * r * r - (y1 - y2) * (y1 - y2);
        if (d < 0) { hi5 = a; continue; }
        double x2 = sqrt(d) + x1;
        
        double y3 = r;
        d = 4 * r * r - (y3 - y2) * (y3 - y2);
        double x3 = sqrt(d) + x2;
        
        // 检查最右侧圆是否在六边形边界内
        double area = cross(Point(a * COS60 + a, a * SIN60),
                           Point(2 * a * COS60 + a, 0),
                           Point(x3, y3));
        if (area >= 0) { lo5 = a; continue; }
        
        // 计算点到直线的距离
        double dist = -area / a;
        if (dist < r) lo5 = a;
        else hi5 = a;
    }
    
    // ---------- 计算8个圆的比例系数 ----------
    double lo8 = (2 * r) / SIN60;
    double hi8 = (4 * r) / SIN60;
    
    while (hi8 - lo8 > EPS) {
        double a = (lo8 + hi8) * 0.5;
        double x1 = r / SIN60;
        double y1 = 0;
        double x2 = x1 + 2 * r * COS60;
        double y2 = 2 * r * SIN60;
        double y3 = a * SIN60 - r;
        
        // 计算圆心2和圆心3之间的水平距离
        double d = 4 * r * r - (y2 - y3) * (y2 - y3);
        if (d < 0) { hi8 = a; continue; }
        double x3 = sqrt(d) + x2;
        
        double y4 = r;
        d = 4 * r * r - (y4 - y3) * (y4 - y3);
        double x4 = sqrt(d) + x3;
        
        // 检查最右侧圆是否在六边形边界内
        double area = cross(Point(a * COS60 + a, a * SIN60),
                           Point(2 * a * COS60 + a, 0),
                           Point(x4, y4));
        if (area >= 0) { lo8 = a; continue; }
        
        // 计算点到直线的距离
        double dist = -area / a;
        if (dist < r) lo8 = a;
        else hi8 = a;
    }
    
    // ---------- 处理输入输出 ----------
    scanf("%d", &t);
    while (t--) {
        scanf("%lf", &r);
        printf("%.12lf %.12lf\n", lo5 * r, lo8 * r);
    }
    
    return 0;
}
