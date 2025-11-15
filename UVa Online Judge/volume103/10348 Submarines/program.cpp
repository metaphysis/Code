// Submarines
// UVa ID: 10348
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Line {
    Point p1, p2;
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}
};

// 判断点是否在线段上
bool onSegment(const Point& p, const Point& q, const Point& r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return true;
    }
    return false;
}

// 计算叉积
int crossProduct(const Point& p, const Point& q, const Point& r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

// 判断两条线段是否相交
bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = crossProduct(p1, q1, p2);
    int o2 = crossProduct(p1, q1, q2);
    int o3 = crossProduct(p2, q2, p1);
    int o4 = crossProduct(p2, q2, q1);

    if (o1 * o2 < 0 && o3 * o4 < 0) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// 判断点是否在多边形内部（射线法）
bool isPointInPolygon(const Point& p, const vector<Point>& polygon) {
    int n = polygon.size();
    if (n < 3) return false;

    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if ((polygon[i].y > p.y) != (polygon[j].y > p.y) &&
            p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (double)(polygon[j].y - polygon[i].y) + polygon[i].x) {
            inside = !inside;
        }
    }
    return inside;
}

// 判断线段是否与多边形相交
bool isLineIntersectPolygon(const Line& line, const vector<Point>& polygon) {
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        if (doIntersect(line.p1, line.p2, polygon[i], polygon[next])) {
            return true;
        }
    }
    return false;
}

int main() {
    int numSubmarines;
    cin >> numSubmarines;
    vector<Line> submarines;
    for (int i = 0; i < numSubmarines; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        submarines.push_back(Line(Point(x1, y1), Point(x2, y2)));
    }

    int numIslands;
    cin >> numIslands;
    vector<vector<Point>> islands;
    for (int i = 0; i < numIslands; i++) {
        int numPoints;
        cin >> numPoints;
        vector<Point> polygon;
        for (int j = 0; j < numPoints; j++) {
            int x, y;
            cin >> x >> y;
            polygon.push_back(Point(x, y));
        }
        islands.push_back(polygon);
    }

    for (int i = 0; i < numSubmarines; i++) {
        Line sub = submarines[i];
        bool intersectAny = false;
        bool completelyOnLand = false;
        bool completelyInWater = true;

        // 检查是否与任何岛屿边界相交
        for (const auto& island : islands) {
            if (isLineIntersectPolygon(sub, island)) {
                intersectAny = true;
                break;
            }
        }

        // 如果没有相交，检查端点位置
        if (!intersectAny) {
            for (const auto& island : islands) {
                bool frontIn = isPointInPolygon(sub.p1, island);
                bool rearIn = isPointInPolygon(sub.p2, island);
                
                if (frontIn && rearIn) {
                    // 两个端点都在同一个岛屿内部
                    completelyOnLand = true;
                    completelyInWater = false;
                    break;
                } else if (frontIn || rearIn) {
                    // 只有一个端点在岛屿内部
                    completelyInWater = false;
                }
            }
        } else {
            // 如果与边界相交，肯定不在水中
            completelyInWater = false;
        }

        if (completelyOnLand) {
            cout << "Submarine " << i + 1 << " is completely on land." << endl;
        } else if (completelyInWater) {
            cout << "Submarine " << i + 1 << " is still in water." << endl;
        } else {
            cout << "Submarine " << i + 1 << " is partially on land." << endl;
        }
    }

    return 0;
}
