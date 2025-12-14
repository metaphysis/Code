// Firemen Barracks
// UVa ID: 10697
// Verdict: Accepted
// Submission Date: 2025-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;  // 精度误差

// 符号函数：判断浮点数正负或零
int sgn(double x) {
    if (fabs(x) < EPS) return 0;   // 视为0
    if (x > 0) return 1;           // 正数
    return -1;                     // 负数
}

// 二维点结构体
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
    
    // 向量运算
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double t) const { return Point(x * t, y * t); }
    Point operator/(double t) const { return Point(x / t, y / t); }
    
    // 点积和叉积
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    
    // 重载相等运算符，考虑精度误差
    bool operator==(const Point& p) { 
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0; 
    }
};

// 求两条直线的交点（假设不平行）
Point lineIntersect(Point p1, Point v1, Point p2, Point v2) {
    double t = (p2 - p1).cross(v2) / v1.cross(v2);
    return p1 + v1 * t;
}

int main() {
    int n; 
    cin >> n;
    cout << fixed << setprecision(1);
    
    while (n--) {
        Point a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        
        // 情况1：有两点重合 → 无穷多解
        if (a == b || a == c || b == c) {
            cout << "There is an infinity of possible locations.\n";
            continue;
        }
        
        // 情况2：三点共线 → 无解
        if (sgn((b - a).cross(c - a)) == 0) {
            cout << "There is no possible location.\n";
            continue;
        }
        
        // 情况3：三点不共线 → 有唯一外心
        // 求ab边的垂直平分线
        Point abMid = (a + b) / 2.0;
        Point abPerp(b.y - a.y, a.x - b.x);  // 法向量（旋转90度）
        
        // 求ac边的垂直平分线
        Point acMid = (a + c) / 2.0;
        Point acPerp(c.y - a.y, a.x - c.x);
        
        // 求两条垂直平分线的交点（外心）
        Point center = lineIntersect(abMid, abPerp, acMid, acPerp);
        
        // 处理输出，避免出现 -0.0
        if (center.x < 0.05 - EPS && center.x > -0.05 + EPS) center.x = 0;
        if (center.y < 0.05 - EPS && center.y > -0.05 + EPS) center.y = 0;
        
        cout << "The equidistant location is (" 
             << center.x << ", " << center.y << ").\n";
    }
    
    return 0;
}
