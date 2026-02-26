// Land Surveyor's Job
// UVa ID: 10936
// Verdict: Accepted
// Submission Date: 2026-02-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

double toRadians(int deg, int min, int sec) {
    return (deg + min / 60.0 + sec / 3600.0) * M_PI / 180.0;
}

double distance(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        vector<double> dist(n), ang(n);
        vector<int> deg(n), min(n), sec(n);
        
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                scanf("%lf %d", &dist[0], &deg[0]);  // 站点 1 角度为 0
                min[0] = sec[0] = 0;
                ang[0] = 0;
            } else {
                scanf("%lf %d%*c%d%*c%d%*c", &dist[i], &deg[i], &min[i], &sec[i]);
                ang[i] = toRadians(deg[i], min[i], sec[i]);
            }
        }
        
        // 站点 1 实际坐标 (0,0)，站点 2 实际坐标 (dist[0], 0)
        vector<Point> P(n);
        P[0] = Point(0, 0);
        P[1] = Point(dist[0], 0);
        
        // 从站点 2 开始递推
        for (int i = 1; i < n - 1; ++i) {
            // 后视向量 P[i-1] - P[i]
            double bx = P[i-1].x - P[i].x;
            double by = P[i-1].y - P[i].y;
            double lenB = sqrt(bx * bx + by * by);
            // 顺时针旋转角度 ang[i]
            double fx = (bx * cos(ang[i]) + by * sin(ang[i])) / lenB * dist[i];
            double fy = (-bx * sin(ang[i]) + by * cos(ang[i])) / lenB * dist[i];
            P[i+1] = Point(P[i].x + fx, P[i].y + fy);
        }
        
        // 计算预测的站点 1
        int last = n - 1;
        double bx = P[last-1].x - P[last].x;
        double by = P[last-1].y - P[last].y;
        double lenB = sqrt(bx * bx + by * by);
        double fx = (bx * cos(ang[last]) + by * sin(ang[last])) / lenB * dist[last];
        double fy = (-bx * sin(ang[last]) + by * cos(ang[last])) / lenB * dist[last];
        Point P1_pred(P[last].x + fx, P[last].y + fy);
        
        // 总长度
        double totalLen = 0;
        for (int i = 0; i < n; ++i) totalLen += dist[i];
        
        double err = distance(P[0], P1_pred);
        if (err < totalLen * 0.001)
            printf("Acceptable\n");
        else
            printf("Not acceptable\n");
    }
    return 0;
}
