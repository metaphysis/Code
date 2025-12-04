// Toboggan of Marbles
// UVa ID: 12483
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 点结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// 挡板结构体
struct Flap {
    int yi, xf, yf;
    int connX; // 固定端的x坐标
};

// 计算点p到线段ab的最短距离
double pointToSegmentDistance(Point p, Point a, Point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    
    // 如果线段退化为点
    if (fabs(dx) < 1e-9 && fabs(dy) < 1e-9)
        return sqrt((p.x - a.x) * (p.x - a.x) + (p.y - a.y) * (p.y - a.y));
    
    // 计算投影参数t
    double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (dx * dx + dy * dy);
    
    // 限制t在[0,1]范围内
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    
    // 计算投影点坐标
    Point proj(a.x + t * dx, a.y + t * dy);
    
    // 返回距离
    return sqrt((p.x - proj.x) * (p.x - proj.x) + (p.y - proj.y) * (p.y - proj.y));
}

int main() {
    int n;
    while (cin >> n) {
        int L, H;
        cin >> L >> H;
        
        vector<Flap> flaps(n);
        for (int i = 0; i < n; i++) {
            cin >> flaps[i].yi >> flaps[i].xf >> flaps[i].yf;
            // 奇数挡板(0-based)连左杆(0)，偶数挡板连右杆(L)
            flaps[i].connX = (i % 2 == 0) ? 0 : L;
        }
        
        double minDiameter = 1e9;
        
        // 1. 检查自由端到对侧木杆的距离
        for (int i = 0; i < n; i++) {
            double distance;
            if (i % 2 == 0) { // 奇数挡板，连左杆
                distance = L - flaps[i].xf; // 到右杆的距离
            } else { // 偶数挡板，连右杆
                distance = flaps[i].xf; // 到左杆的距离
            }
            minDiameter = min(minDiameter, distance);
        }
        
        // 2. 检查相邻挡板之间的过渡
        for (int i = 0; i < n - 1; i++) {
            // 挡板i的自由端
            Point p(flaps[i].xf, flaps[i].yf);
            
            // 挡板i+1的线段：从固定端到自由端
            Point a(flaps[i+1].connX, flaps[i+1].yi); // 固定端
            Point b(flaps[i+1].xf, flaps[i+1].yf);    // 自由端
            
            double distance = pointToSegmentDistance(p, a, b);
            minDiameter = min(minDiameter, distance);
        }
        
        cout << fixed << setprecision(2) << minDiameter << endl;
    }
    
    return 0;
}
