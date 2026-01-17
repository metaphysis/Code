// Touring Robot
// UVa ID: 11509
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 计算两点之间的向量
Point vectorBetween(const Point& a, const Point& b) {
    return Point(b.x - a.x, b.y - a.y);
}

// 计算从向量u旋转到向量v的逆时针角度（0到2π）
double rotationAngle(const Point& u, const Point& v) {
    double cross = u.x * v.y - u.y * v.x;  // 叉积
    double dot = u.x * v.x + u.y * v.y;    // 点积
    // 使用atan2计算角度，确保结果在[0, 2π)范围内
    double angle = atan2(cross, dot);
    if (angle < 0) angle += 2 * PI;
    return angle;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        vector<Point> points(n);
        for (int i = 0; i < n; i++) scanf("%d %d", &points[i].x, &points[i].y);
        // 多边形闭合，添加第一个点作为最后一个点以便计算
        points.push_back(points[0]);
        double totalAngle = 0.0;
        for (int i = 0; i < n; i++) {
            // 当前点
            Point current = points[i];
            // 前一个点
            Point prev = (i == 0) ? points[n - 1] : points[i - 1];
            // 下一个点
            Point next = points[i + 1];
            // 计算两个向量：从前一点到当前点，从当前点到下一点
            Point vec1 = vectorBetween(prev, current);
            Point vec2 = vectorBetween(current, next);
            // 累加旋转角度
            totalAngle += rotationAngle(vec1, vec2);
        }
        // 总旋转角度除以2π得到圈数，四舍五入到最接近的整数
        int turns = round(totalAngle / (2 * PI));
        printf("%d\n", turns);
    }
    return 0;
}
