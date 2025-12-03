// Lattice Point or Not
// UVa ID: 11768
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        
        // 乘以10转换为整数坐标，避免浮点误差
        int X1 = round(x1 * 10);
        int Y1 = round(y1 * 10);
        int X2 = round(x2 * 10);
        int Y2 = round(y2 * 10);
        
        int dx = X2 - X1;
        int dy = Y2 - Y1;
        
        // 处理两点重合的特殊情况
        if (dx == 0 && dy == 0) {
            if (X1 % 10 == 0 && Y1 % 10 == 0) printf("1\n");
            else printf("0\n");
            continue;
        }
        
        // 计算dx和dy的最大公约数
        int g = __gcd(abs(dx), abs(dy));
        dx /= g;  // x方向每步增量
        dy /= g;  // y方向每步增量
        
        int count = 0;  // 统计整数格点数量
        for (int t = 0; t <= g; t++) {
            int x = X1 + t * dx;
            int y = Y1 + t * dy;
            // 检查是否为原坐标系中的整数点
            if (x % 10 == 0 && y % 10 == 0) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}
