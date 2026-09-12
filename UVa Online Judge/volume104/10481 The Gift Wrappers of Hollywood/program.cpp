#include <bits/stdc++.h>
using namespace std;

int main() {
    // 令圆的半径为r，三角形的边长为a，下层中间三角形的顶点与圆心的水平距离为x，可以得到方程：
    // 4 * x^2 + a^2 - 2 * a * x = r^2
    // (a - (sqrt(3) * r - 3 * a / 2 - 6 * x) / 3)^2 + (r - sqrt(3) * a / 2)^2 = r^2
    // 求解可得
    // r = 0.980597929091272 * a
    double r4 = 0.980597929091272;
    // 令圆的半径为r，三角形的边长为a，下层中间三角形的底边与圆弧所构成的弓形的矢高为x，可以得到方程：
    // (r - x)^2 + (a / 2)^2 = r^2
    // (3 * a / 2 - (2 * r - 2 * x - 3 * sqrt(3) * a / 2) / sqrt(3))^2 + (r - x - sqrt(3) * a / 2)^2 = r^2
    // 求解可得
    // r = sqrt(910 - 30 * sqrt(657)) / 8 * a
    double r11 = sqrt(910 - 30 * sqrt(657)) / 8;
    double L;
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> L;
        L = sqrt(4 * L / sqrt(3));
        cout << fixed << setprecision(12) << r4 * L << ' ' << r11 * L << '\n';
    }
    return 0;
}
