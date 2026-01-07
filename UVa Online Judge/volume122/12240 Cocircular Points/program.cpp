// Cocircular Points
// UVa ID: 12240
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.670s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

// 判断三点是否共线（叉积为零）
bool isCollinear(const Point& a, const Point& b, const Point& c) {
    return (b.y - a.y) * (c.x - b.x) == (c.y - b.y) * (b.x - a.x);
}

// 计算通过不共线三点的圆的参数（整数精确计算）
// 圆心 (cxNum/cxDen, cyNum/cyDen)，半径平方的分子 rsqNum，分母 rsqDen = cxDen^2
bool findCircleExact(const Point& p1, const Point& p2, const Point& p3,
                     long long& cxNum, long long& cxDen,
                     long long& cyNum, long long& cyDen,
                     long long& rsqNum, long long& rsqDen) {
    long long A1 = 2LL * (p2.x - p1.x);
    long long B1 = 2LL * (p2.y - p1.y);
    long long C1 = (1LL * p2.x * p2.x - 1LL * p1.x * p1.x) + 
                   (1LL * p2.y * p2.y - 1LL * p1.y * p1.y);
    
    long long A2 = 2LL * (p3.x - p1.x);
    long long B2 = 2LL * (p3.y - p1.y);
    long long C2 = (1LL * p3.x * p3.x - 1LL * p1.x * p1.x) + 
                   (1LL * p3.y * p3.y - 1LL * p1.y * p1.y);
    
    long long D = A1 * B2 - A2 * B1;
    if (D == 0) return false; // 三点共线
    
    cxNum = C1 * B2 - C2 * B1;
    cyNum = A1 * C2 - A2 * C1;
    cxDen = cyDen = D;
    
    // 计算半径平方：R^2 = (x1 - cx)^2 + (y1 - cy)^2
    // 通分到分母 D^2
    long long dx = cxDen * p1.x - cxNum;
    long long dy = cyDen * p1.y - cyNum;
    rsqNum = dx * dx + dy * dy;
    rsqDen = cxDen * cxDen;  // D^2
    
    return true;
}

// 判断点 p 是否在圆上（精确比较）
bool isOnCircle(const Point& p, 
                long long cxNum, long long cxDen,
                long long cyNum, long long cyDen,
                long long rsqNum, long long rsqDen) {
    long long dx = cxDen * p.x - cxNum;
    long long dy = cyDen * p.y - cyNum;
    long long distSqNum = dx * dx + dy * dy;
    // 分母相同（都是 rsqDen），只需比较分子
    return distSqNum == rsqNum;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;

        int answer = min(n, 2); // 至少为 2（如果 n>=2），否则为 1
        
        if (n >= 3) {
            for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k) {
                if (isCollinear(points[i], points[j], points[k])) continue;
                
                long long cxNum, cxDen, cyNum, cyDen, rsqNum, rsqDen;
                if (!findCircleExact(points[i], points[j], points[k],
                                     cxNum, cxDen, cyNum, cyDen, rsqNum, rsqDen)) continue;
                
                int cnt = 3; // 三点本身在圆上
                for (int m = 0; m < n; ++m) {
                    if (m == i || m == j || m == k) continue;
                    if (isOnCircle(points[m], cxNum, cxDen, cyNum, cyDen, rsqNum, rsqDen)) cnt++;
                }
                answer = max(ans, cnt);
            }
        }
        
        cout << answer << endl;
    }
    return 0;
}
