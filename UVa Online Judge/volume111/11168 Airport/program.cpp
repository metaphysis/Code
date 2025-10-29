// Airport
// UVa ID: 11168
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.700s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    // 点减法
    Point operator - (const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    // 用于排序
    bool operator < (const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// 二维叉积
long long cross(const Point& a, const Point& b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

// 凸包算法 (Andrew's monotone chain)
vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return points;

    // 按 x 坐标排序，x 相同时按 y 排序
    sort(points.begin(), points.end());

    vector<Point> hull(2 * n);
    int k = 0;

    // 构建下凸包
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k - 1] - hull[k - 2], points[i] - hull[k - 2]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    // 构建上凸包
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(hull[k - 1] - hull[k - 2], points[i] - hull[k - 2]) <= 0) {
            k--;
        }
        hull[k++] = points[i];
    }

    // 移除重复的起点
    hull.resize(k - 1);
    return hull;
}

// 计算点 p 到直线 ab 的距离
double pointToLineDistance(const Point& p, const Point& a, const Point& b) {
    Point ab = b - a;      // 向量 AB
    Point ap = p - a;      // 向量 AP
    double area = abs(cross(ab, ap));  // 平行四边形面积
    double len = hypot(ab.x, ab.y);    // AB 的长度
    return area / len;                 // 高 = 面积 / 底边
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    cin >> T;

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int n;
        cin >> n;
        vector<Point> houses(n);

        for (int i = 0; i < n; ++i) cin >> houses[i].x >> houses[i].y;

        double minAvgDist = 1e20;  // 初始化为一个大数
        
        if (n <= 2) {
            // 点数为 1 或 2 时，总能找到平均距离为 0 的直线
            minAvgDist = 0.0;
        } else {
            // 计算凸包
            vector<Point> hull = convexHull(houses);
            int m = hull.size();
            
            if (m <= 2) {
                // 凸包退化，所有点共线
                minAvgDist = 0.0;
            } else {
                // 枚举凸包的每条边
                for (int i = 0; i < m; ++i) {
                    const Point& a = hull[i];
                    const Point& b = hull[(i + 1) % m];  // 循环到第一条边
                    
                    double totalDist = 0.0;
                    // 计算所有点到当前边的距离之和
                    for (const Point& p : houses) {
                        totalDist += pointToLineDistance(p, a, b);
                    }
                    
                    double avgDist = totalDist / n;
                    if (avgDist < minAvgDist) {
                        minAvgDist = avgDist;
                    }
                }
            }
        }
        
        // 输出结果，保留 3 位小数
        cout << "Case #" << caseNum << ": "
             << fixed << setprecision(3) << minAvgDist << "\n";
    }
    
    return 0;
}
