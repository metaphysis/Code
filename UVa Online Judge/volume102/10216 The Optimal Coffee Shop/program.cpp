// The Optimal Coffee Shop
// UVa ID: 10216
// Verdict: Accepted
// Submission Date: 2026-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算三角形面积（海伦公式）
double area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// 计算费马点最小距离和
double fermatDistance(double a, double b, double c, double delta) {
    double cosA = (b*b + c*c - a*a) / (2*b*c);
    double cosB = (a*a + c*c - b*b) / (2*a*c);
    double cosC = (a*a + b*b - c*c) / (2*a*b);
    
    // 若某角 >= 120度，费马点在该角顶点
    if (cosA <= -0.5) return b + c;
    if (cosB <= -0.5) return a + c;
    if (cosC <= -0.5) return a + b;
    
    // 所有角 < 120度，使用公式
    return sqrt(0.5 * (a*a + b*b + c*c + 4.0 * sqrt(3.0) * delta));
}

// 计算内心到三顶点距离和
double incenterSum(double a, double b, double c, double delta) {
    double s = (a + b + c) / 2.0;
    double AI = 2.0 * sqrt(b*c) * sqrt(s*(s-a)) / (a + b + c);
    double BI = 2.0 * sqrt(a*c) * sqrt(s*(s-b)) / (a + b + c);
    double CI = 2.0 * sqrt(a*b) * sqrt(s*(s-c)) / (a + b + c);
    return AI + BI + CI;
}

// 计算重心到三顶点距离和
double centroidSum(double a, double b, double c) {
    double ma = 0.5 * sqrt(2*b*b + 2*c*c - a*a);
    double mb = 0.5 * sqrt(2*a*a + 2*c*c - b*b);
    double mc = 0.5 * sqrt(2*a*a + 2*b*b - c*c);
    return (2.0/3.0) * (ma + mb + mc);
}

// 计算外心到三顶点距离和
double circumcenterSum(double a, double b, double c, double delta) {
    double R = (a*b*c) / (4.0 * delta);
    return 3.0 * R;
}

int main() {
    int S;
    scanf("%d", &S);
    
    while (S--) {
        double a, b, c;
        scanf("%lf %lf %lf", &a, &b, &c);
        
        // 排序便于判断退化情况
        double sides[3] = {a, b, c};
        sort(sides, sides + 3);
        double x = sides[0], y = sides[1], z = sides[2];
        
        bool degenerate = (fabs(x + y - z) < 1e-9);
        
        if (degenerate) {
            // 三点共线：费马点距离 = 最长边，内心距离 = 费马点距离，外心不存在
            double DM = z;
            double DG = centroidSum(a, b, c);
            printf("%.3f %.3f %.3f -1.000\n", DM, DM, DG);
            continue;
        }
        
        // 正常三角形
        double delta = area(a, b, c);
        double DM = fermatDistance(a, b, c, delta);
        double DI = incenterSum(a, b, c, delta);
        double DG = centroidSum(a, b, c);
        double DO = circumcenterSum(a, b, c, delta);
        
        printf("%.3f %.3f %.3f %.3f\n", DM, DI, DG, DO);
    }
    
    return 0;
}
