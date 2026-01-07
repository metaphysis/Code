// Predator II
// UVa ID: 11030
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

typedef vector<Point> Polygon;

// 计算向量叉积 (a->b) × (a->c)
long long cross(const Point& a, const Point& b, const Point& c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

// 判断点c是否在线段ab上
bool onSegment(const Point& a, const Point& b, const Point& c) {
    // 首先判断点c在线段ab的边界框内
    if (min(a.x, b.x) > c.x || c.x > max(a.x, b.x)) return false;
    if (min(a.y, b.y) > c.y || c.y > max(a.y, b.y)) return false;
    // 然后判断叉积是否为0（三点共线）
    return cross(a, b, c) == 0;
}

// 射线法判断点是否在多边形内部（不包括边界）
bool pointInPolygon(const Point& p, const Polygon& poly) {
    int n = poly.size();
    bool inside = false;
    
    // 遍历多边形的每条边
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Point& p1 = poly[i];
        const Point& p2 = poly[j];
        
        // 检查点是否在当前边上
        if (onSegment(p1, p2, p)) return false;
        
        // 检查射线是否与边相交
        // 条件1: 边的两个端点分别在射线上下两侧
        // 条件2: 交点在点p的右侧
        if ((p1.y > p.y) != (p2.y > p.y)) {
            // 计算交点x坐标（使用整数运算避免浮点误差）
            // 由直线两点式推导：x = x1 + (y - y1) * (x2 - x1) / (y2 - y1)
            long long xinters = 1LL * (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            
            // 如果交点在点p的右侧
            if (p.x < xinters) inside = !inside;
        }
    }
    
    return inside;
}

int main() {
    int T, caseNo = 1;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<Polygon> polygons(n);

        // 读取多边形
        for (int i = 0; i < n; ++i) {
            int S;
            cin >> S;
            polygons[i].resize(S);
            for (int j = 0; j < S; ++j) cin >> polygons[i][j].x >> polygons[i][j].y;
        }

        int Q;
        cin >> Q;
        cout << "Case " << caseNo++ << ":" << endl;

        // 处理每个查询
        for (int q = 0; q < Q; ++q) {
            Point start, end;
            cin >> start.x >> start.y >> end.x >> end.y;

            int startInside = 0, endInside = 0, common = 0;

            // 统计起点和终点在每个多边形内部的情况
            for (const auto& poly : polygons) {
                bool sIn = pointInPolygon(start, poly);
                bool eIn = pointInPolygon(end, poly);
                if (sIn) startInside++;
                if (eIn) endInside++;
                if (sIn && eIn) common++;
            }

            // 计算最小跳跃次数
            int hops = startInside + endInside - 2 * common;
            cout << hops << endl;
        }
    }

    return 0;
}
