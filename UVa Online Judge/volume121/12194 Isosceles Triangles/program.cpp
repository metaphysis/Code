// Isosceles Triangles
// UVa ID: 12194
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.630s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 计算两点间距离的平方（避免浮点数）
long long distSquared(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<Point> points(n);
        for (int i = 0; i < n; i++) 
            cin >> points[i].x >> points[i].y;
        
        long long result = 0;
        
        // 对于每个点作为等腰三角形的顶点
        for (int i = 0; i < n; i++) {
            vector<long long> distances;
            
            // 计算该点到所有其他点的距离平方
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                distances.push_back(distSquared(points[i], points[j]));
            }
            
            // 排序距离以便统计
            sort(distances.begin(), distances.end());
            
            // 统计相同距离的数量
            int count = 1;
            for (int j = 1; j < distances.size(); j++) {
                if (distances[j] == distances[j - 1]) {
                    count++;
                } else {
                    // 对于有count个相同距离的情况，可以形成C(count,2)个等腰三角形
                    result += (long long)count * (count - 1) / 2;
                    count = 1;
                }
            }
            // 处理最后一组
            result += (long long)count * (count - 1) / 2;
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
