// Shooter
// UVa ID: 10535
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.150s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const doubel EPS = 1e-6;
const double FAR_DISTANCE = 50000.0;  // 射线延伸距离，确保覆盖所有墙壁

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator*(double t) const { return Point(x * t, y * t); }
    double cross(const Point& p) const { return x * p.y - y * p.x; }  // 叉积
    double dot(const Point& p) const { return x * p.x + y * p.y; }    // 点积
};

struct Segment {
    Point a, b;  // 线段端点
};

// 判断点p是否在线段seg上
bool onSegment(const Point& p, const Segment& seg) {
    // 检查点是否在线段的边界框内
    if (p.x < min(seg.a.x, seg.b.x) || p.x > max(seg.a.x, seg.b.x) ||
        p.y < min(seg.a.y, seg.b.y) || p.y > max(seg.a.y, seg.b.y)) {
        return false;
    }
    // 检查三点共线（只在叉积处使用精度控制）
    Point v1 = seg.b - seg.a;
    Point v2 = p - seg.a;
    return fabs(v1.cross(v2)) < 1e-6;
}

// 判断两个线段是否相交
bool segmentsIntersect(const Segment& seg1, const Segment& seg2) {
    Point v1 = seg1.b - seg1.a;
    Point v2 = seg2.b - seg2.a;
    
    // 跨立实验：检查两个线段是否相互跨越
    double cross1 = v1.cross(seg2.a - seg1.a);
    double cross2 = v1.cross(seg2.b - seg1.a);
    double cross3 = v2.cross(seg1.a - seg2.a);
    double cross4 = v2.cross(seg1.b - seg2.a);
    
    // 如果两个线段相互跨越，则相交
    if ((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)) {
        if ((cross3 > 0 && cross4 < 0) || (cross3 < 0 && cross4 > 0)) {
            return true;
        }
    }
    
    // 检查端点是否在另一个线段上
    if (onSegment(seg1.a, seg2) || onSegment(seg1.b, seg2) ||
        onSegment(seg2.a, seg1) || onSegment(seg2.b, seg1)) {
        return true;
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N != 0) {
        vector<Segment> walls(N);
        for (int i = 0; i < N; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            walls[i] = {{x1, y1}, {x2, y2}};
        }

        double sx, sy;
        cin >> sx >> sy;
        Point shooter(sx, sy);

        // 收集所有墙壁端点相对于射手的方向
        vector<Point> directions;
        for (const auto& wall : walls) {
            directions.push_back(wall.a - shooter);
            directions.push_back(wall.b - shooter);
        }

        int max_destroy = 0;
        // 枚举所有可能的方向（最优解必然经过某个端点）
        for (const Point& dir : directions) {
            if (dir.x == 0 && dir.y == 0) continue;  // 跳过零向量

            // 单位化方向向量
            double len = sqrt(dir.x * dir.x + dir.y * dir.y);
            Point unit(dir.x / len, dir.y / len);
            
            // 将射线转换为长线段
            Point far_point = shooter + unit * FAR_DISTANCE;
            Segment laser = {shooter, far_point};

            // 统计该方向能击中的墙壁数量
            int count = 0;
            for (const auto& wall : walls) {
                if (segmentsIntersect(laser, wall)) {
                    count++;
                }
            }
            max_destroy = max(max_destroy, count);
        }

        cout << max_destroy << "\n";
    }

    return 0;
}
