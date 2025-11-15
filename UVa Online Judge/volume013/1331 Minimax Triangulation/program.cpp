// Minimax Triangulation
// UVa ID: 1331
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class MinimaxTriangulation {
private:
    vector<Point> points;
    vector<vector<double>> dp;
    int numVertices;

    // 计算三角形面积
    double calculateArea(const Point& a, const Point& b, const Point& c) {
        return fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) / 2.0;
    }

    // 判断三角形内部是否包含其他顶点
    bool isValidTriangle(int a, int b, int c) {
        for (int i = 0; i < numVertices; i++) {
            if (i == a || i == b || i == c) continue;
            double totalArea = calculateArea(points[a], points[b], points[i]) 
                             + calculateArea(points[a], points[c], points[i]) 
                             + calculateArea(points[b], points[c], points[i]);
            double triangleArea = calculateArea(points[a], points[b], points[c]);
            // 如果点在三角形内部，总面积会等于三角形面积
            if (fabs(totalArea - triangleArea) < 1e-8) {
                return false;
            }
        }
        return true;
    }

public:
    void solve() {
        int testCases;
        cin >> testCases;
        
        while (testCases--) {
            cin >> numVertices;
            points.resize(numVertices);
            
            for (int i = 0; i < numVertices; i++) {
                cin >> points[i].x >> points[i].y;
            }

            // 初始化DP表
            dp.assign(numVertices, vector<double>(numVertices, 0.0));

            // 动态规划计算最小化最大三角形面积
            for (int left = numVertices - 3; left >= 0; left--) {
                dp[left][left + 1] = 0.0; // 两个相邻点无法形成三角形
                
                for (int right = left + 2; right < numVertices; right++) {
                    dp[left][right] = 1e18; // 初始化为一个大数
                    
                    for (int mid = left + 1; mid < right; mid++) {
                        if (isValidTriangle(left, mid, right)) {
                            double triangleArea = calculateArea(points[left], points[mid], points[right]);
                            double maxArea = max(triangleArea, max(dp[left][mid], dp[mid][right]));
                            dp[left][right] = min(dp[left][right], maxArea);
                        }
                    }
                }
            }

            cout << fixed << setprecision(1) << dp[0][numVertices - 1] << endl;
        }
    }
};

int main() {
    MinimaxTriangulation solver;
    solver.solve();
    return 0;
}
