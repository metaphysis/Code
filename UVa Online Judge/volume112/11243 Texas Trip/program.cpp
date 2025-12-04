// Texas Trip
// UVa ID: 11243
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;
const double INF = 1e20;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    // 将点绕原点逆时针旋转 angle 弧度
    Point rotate(double angle) const {
        double c = cos(angle), s = sin(angle);
        return Point(x * c - y * s, x * s + y * c);
    }
};

// 计算在给定角度 angle 下，覆盖所有点的最小正方形边长
double minSquareSideForAngle(const vector<Point>& points, double angle) {
    double minX = INF, maxX = -INF, minY = INF, maxY = -INF;
    
    for (const auto& p : points) {
        // 将点旋转 -angle 角度，使正方形边与坐标轴平行
        Point rotated = p.rotate(angle);
        minX = min(minX, rotated.x);
        maxX = max(maxX, rotated.x);
        minY = min(minY, rotated.y);
        maxY = max(maxY, rotated.y);
    }
    
    double width = maxX - minX;
    double height = maxY - minY;
    // 正方形边长取宽度和高度的最大值
    return max(width, height);
}

// 在区间 [0, PI/2] 内三分搜索最小正方形边长
double ternarySearch(const vector<Point>& points) {
    double left = 0, right = PI / 2.0;
    
    // 迭代 60 次保证足够精度
    for (int iter = 0; iter < 60; ++iter) {
        double mid1 = left + (right - left) / 3.0;
        double mid2 = right - (right - left) / 3.0;
        
        double side1 = minSquareSideForAngle(points, mid1);
        double side2 = minSquareSideForAngle(points, mid2);
        
        if (side1 < side2) {
            right = mid2;
        } else {
            left = mid1;
        }
    }
    
    double bestAngle = (left + right) / 2.0;
    return minSquareSideForAngle(points, bestAngle);
}

double solveCase(const vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return 0.0;
    
    // 三分搜索得到最小边长
    double bestSide = ternarySearch(points);
    
    // 检查轴对齐的情况（角度为 0）
    bestSide = min(bestSide, minSquareSideForAngle(points, 0));
    
    // 检查角度为 45 度的情况
    bestSide = min(bestSide, minSquareSideForAngle(points, PI/4.0));
    
    // 返回面积
    return bestSide * bestSide;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T;
    cout << fixed << setprecision(2);
    
    while (T--) {
        int n; cin >> n;
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) 
            cin >> points[i].x >> points[i].y;
        double ans = solveCase(points);
        cout << ans << endl;
    }
    
    return 0;
}
