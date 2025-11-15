// Fractal
// UVa ID: 10609
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        if (fabs(x - other.x) > 1e-8) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point& other) const {
        return fabs(x - other.x) < 1e-8 && fabs(y - other.y) < 1e-8;
    }
};

vector<Point> points;

// 递归生成分形顶点
void generateFractal(const Point& a, const Point& b, double threshold) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    
    // 计算 C 和 D
    Point c(a.x + dx / 4, a.y + dy / 4);
    Point d(a.x + 3 * dx / 4, a.y + 3 * dy / 4);
    
    // 检查CD的长度是否小于阈值
    double cdDx = d.x - c.x;
    double cdDy = d.y - c.y;
    double cdDist = sqrt(cdDx * cdDx + cdDy * cdDy);
    
    if (cdDist < threshold) return;
    
    // 计算等边三角形顶点 E（在前进方向的右侧/上方）
    // 将CD向量逆时针旋转60度得到CE方向
    double angle = atan2(cdDy, cdDx);
    double newAngle = angle + M_PI / 3; // 逆时针旋转60度
    
    Point e(
        c.x + cdDist * cos(newAngle),
        c.y + cdDist * sin(newAngle)
    );
    
    // 添加点 C, D, E
    points.push_back(c);
    points.push_back(d);
    points.push_back(e);
    
    // 递归处理 CE 和 ED
    generateFractal(c, e, threshold);
    generateFractal(e, d, threshold);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double x1, y1, x2, y2, threshold;
    int caseNum = 1;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> threshold) {
        if (threshold < 1.0) break;
        
        points.clear();
        Point a(x1, y1), b(x2, y2);
        points.push_back(a);
        points.push_back(b);
        
        generateFractal(a, b, threshold);
        
        // 去重
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        
        // 输出
        cout << "Case " << caseNum++ << ":\n";
        cout << points.size() << "\n";
        cout << fixed << setprecision(5);
        for (const auto& p : points) {
            cout << p.x << " " << p.y << "\n";
        }
    }
    
    return 0;
}
