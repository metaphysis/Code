// Beautiful Points
// UVa ID: 10750
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// 比较函数：按 x 坐标排序
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// 比较函数：按 y 坐标排序  
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 计算两点距离的平方
double dist2(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 分治法求最近点对
pair<Point, Point> closestPairUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        // 小规模情况，直接暴力
        double minDist2 = numeric_limits<double>::max();
        pair<Point, Point> closest;
        
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                double d2 = dist2(points[i], points[j]);
                if (d2 < minDist2) {
                    minDist2 = d2;
                    closest = {points[i], points[j]};
                }
            }
        }
        return closest;
    }
    
    int mid = (left + right) / 2;
    Point midPoint = points[mid];
    
    // 递归求解左右两半
    auto leftClosest = closestPairUtil(points, left, mid);
    auto rightClosest = closestPairUtil(points, mid + 1, right);
    
    // 确定当前最小距离
    double leftDist2 = dist2(leftClosest.first, leftClosest.second);
    double rightDist2 = dist2(rightClosest.first, rightClosest.second);
    
    double minDist2 = min(leftDist2, rightDist2);
    pair<Point, Point> closest = (leftDist2 < rightDist2) ? leftClosest : rightClosest;
    
    // 检查跨越中线的点
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        double dx = points[i].x - midPoint.x;
        if (dx * dx < minDist2) {
            strip.push_back(points[i]);
        }
    }
    
    // 按 y 坐标排序 strip 中的点
    sort(strip.begin(), strip.end(), compareY);
    
    // 检查 strip 中的点对
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < minDist2; ++j) {
            double d2 = dist2(strip[i], strip[j]);
            if (d2 < minDist2) {
                minDist2 = d2;
                closest = {strip[i], strip[j]};
            }
        }
    }
    
    return closest;
}

// 最近点对的主函数
pair<Point, Point> closestPair(vector<Point>& points) {
    // 先按 x 坐标排序
    sort(points.begin(), points.end(), compareX);
    return closestPairUtil(points, 0, points.size() - 1);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        
        // 找到最近点对
        auto closest = closestPair(points);
        
        // 输出中点
        Point mid;
        mid.x = (closest.first.x + closest.second.x) / 2.0;
        mid.y = (closest.first.y + closest.second.y) / 2.0;
        
        cout << fixed << setprecision(3) << mid.x << " " << mid.y << "\n";
        
        if (T) cout << "\n";
    }
    
    return 0;
}
