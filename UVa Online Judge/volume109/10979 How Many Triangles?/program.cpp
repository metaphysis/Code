// How Many Triangles?
// UVa ID: 10979
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point& p) const {
        if (fabs(x - p.x) > EPS) return x < p.x;
        return y < p.y;
    }
    bool operator==(const Point& p) const {
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
    }
};

struct Segment {
    Point p1, p2;
    Segment(Point a = Point(), Point b = Point()) : p1(a), p2(b) {}
    bool operator<(const Segment& s) const {
        if (p1 == s.p1) return p2 < s.p2;
        return p1 < s.p1;
    }
};

double cross(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

bool onSegment(const Point& p, const Point& a, const Point& b) {
    if (fabs(cross(a, b, p)) > EPS) return false;
    double minX = min(a.x, b.x), maxX = max(a.x, b.x);
    double minY = min(a.y, b.y), maxY = max(a.y, b.y);
    return (minX <= p.x && p.x <= maxX && minY <= p.y && p.y <= maxY);
}

bool segmentsIntersect(const Segment& s1, const Segment& s2) {
    double d1 = cross(s1.p1, s1.p2, s2.p1), d2 = cross(s1.p1, s1.p2, s2.p2);
    double d3 = cross(s2.p1, s2.p2, s1.p1), d4 = cross(s2.p1, s2.p2, s1.p2);
    if (d1 * d2 < -EPS && d3 * d4 < -EPS) return true;
    if (fabs(d1) < EPS && onSegment(s2.p1, s1.p1, s1.p2)) return true;
    if (fabs(d2) < EPS && onSegment(s2.p2, s1.p1, s1.p2)) return true;
    if (fabs(d3) < EPS && onSegment(s1.p1, s2.p1, s2.p2)) return true;
    if (fabs(d4) < EPS && onSegment(s1.p2, s2.p1, s2.p2)) return true;
    return false;
}

Point getIntersection(const Segment& s1, const Segment& s2) {
    double a1 = s1.p2.y - s1.p1.y, b1 = s1.p1.x - s1.p2.x;
    double c1 = a1 * s1.p1.x + b1 * s1.p1.y;
    double a2 = s2.p2.y - s2.p1.y, b2 = s2.p1.x - s2.p2.x;
    double c2 = a2 * s2.p1.x + b2 * s2.p1.y;
    double det = a1 * b2 - a2 * b1;
    // 平行或共线，返回无效点
    if (fabs(det) < EPS) return Point(1e9, 1e9);
    double x = (b2 * c1 - b1 * c2) / det, y = (a1 * c2 - a2 * c1) / det;
    return Point(x, y);
}

bool areCollinear(const Point& a, const Point& b, const Point& c) {
    return fabs(cross(a, b, c)) < EPS;
}

int main() {
    int n;
    while (cin >> n) {
        vector<Segment> originalSegs(n);
        for (int i = 0; i < n; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            // 保证线段的端点有序
            if (x1 > x2 || (x1 == x2 && y1 > y2)) swap(x1, x2), swap(y1, y2);
            originalSegs[i] = Segment(Point(x1, y1), Point(x2, y2));
        }
        // 排序线段便于处理
        sort(originalSegs.begin(), originalSegs.end());
        // 步骤1：合并共线线段
        vector<bool> done(n, false);
        vector<Segment> segs;
        for (int i = 0; i < n; ++i) {
            if (done[i]) continue;
            Point A = originalSegs[i].p1, B = originalSegs[i].p2;
            for (int j = i + 1; j < n; ++j) {
                if (done[j]) continue;
                Point C = originalSegs[j].p1, D = originalSegs[j].p2;
                // 检查是否共线且相连
                if (onSegment(C, A, B) && fabs(cross(A, B, D)) <= EPS) {
                    done[j] = true;
                    if (B < D) B = D;
                }
            }
            segs.push_back(Segment(A, B));
        }
        // 步骤2：收集所有交点（包括线段端点）
        vector<Point> points;
        // 添加所有端点
        for (const Segment& seg : segs) {
            points.push_back(seg.p1);
            points.push_back(seg.p2);
        }
        // 计算线段之间的交点
        for (int i = 0; i < segs.size(); ++i)
            for (int j = i + 1; j < segs.size(); ++j)
                if (segmentsIntersect(segs[i], segs[j])) {
                    Point p = getIntersection(segs[i], segs[j]);
                    // 根据题目约束检查是否是有效交点
                    if (p.x < 1024) points.push_back(p);
                }
        // 排序交点并去重
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        int m = points.size();
        // 步骤3：建立邻接矩阵
        vector<vector<bool>> g(m, vector<bool>(m, false));
        // 对每条线段，将其上的点连接
        for (const Segment& seg : segs) {
            vector<int> idxs;
            for (int i = 0; i < m; ++i)
                if (onSegment(points[i], seg.p1, seg.p2))
                    idxs.push_back(i);
            // 连接这条线段上的所有点对
            for (int a = 0; a < idxs.size(); ++a)
                for (int b = a + 1; b < idxs.size(); ++b) {
                    int u = idxs[a], v = idxs[b];
                    g[u][v] = g[v][u] = true;
                }
        }
        // 步骤4：统计三角形
        int triangleCount = 0;
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j) {
                if (!g[i][j]) continue;
                for (int k = j + 1; k < m; ++k)
                    if (g[i][k] && g[j][k])
                        if (!areCollinear(points[i], points[j], points[k]))
                            triangleCount++;
            }
        cout << triangleCount << '\n';
    }
    return 0;
}
