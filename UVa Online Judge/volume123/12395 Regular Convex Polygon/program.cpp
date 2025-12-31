// Regular Convex Polygon
// UVa ID: 12395
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-5;  // 经过测试，1e-5是最合适的精度要求
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
};

// 计算三角形外接圆圆心
Point circumcenter(const Point& a, const Point& b, const Point& c) {
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
}

// 计算两点距离
double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 使用余弦定理计算圆心角（度）
double computeAngle(const Point& a, const Point& b, const Point& center) {
    double oa = distance(a, center);
    double ob = distance(b, center);
    double ab = distance(a, b);
    
    // 余弦定理：cosθ = (oa² + ob² - ab²) / (2·oa·ob)
    double cosTheta = (oa * oa + ob * ob - ab * ab) / (2 * oa * ob);
    
    // 防止浮点误差
    if (cosTheta > 1.0) cosTheta = 1.0;
    else if (cosTheta < -1.0) cosTheta = -1.0;
    
    return acos(cosTheta) * 180.0 / PI;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        vector<Point> points(3);
        for (int i = 0; i < 3; ++i) {
            if (!(cin >> points[i].x >> points[i].y)) {
                string endCheck;
                cin.clear();
                cin >> endCheck;
                return 0;
            }
        }
        
        // 计算外接圆圆心
        Point center = circumcenter(points[0], points[1], points[2]);
        
        // 计算三个圆心角（度）
        vector<double> angles(3);
        angles[0] = computeAngle(points[0], points[1], center);
        angles[1] = computeAngle(points[1], points[2], center);
        angles[2] = computeAngle(points[2], points[0], center);
        
        // 枚举边数n，找到最小的满足条件的n
        int answer = 1000;
        for (int n = 3; n <= 1000; ++n) {
            double unitAngle = 360.0 / n;  // 正n边形每个圆心角（度）
            bool valid = true;
            
            for (double angle : angles) {
                double k = angle / unitAngle;
                double rounded = round(k);
                if (fabs(k - rounded) > EPS) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                answer = n;
                break;  // 找到最小的n就退出
            }
        }
        
        cout << answer << "\n";
    }
    
    return 0;
}
