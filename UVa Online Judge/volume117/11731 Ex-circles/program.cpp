// Ex-circles
// UVa ID: 11731
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);  // 精确的π值

int main() {
    int caseNum = 1;
    double a, b, c;
    while (cin >> a >> b >> c, a > 0) {
        // 计算半周长和三角形面积
        double s = (a + b + c) / 2.0;
        double areaABC = sqrt(s * (s - a) * (s - b) * (s - c));
        // 使用余弦定理求三个角（弧度制）
        double cosA = (b * b + c * c - a * a) / (2 * b * c);
        double cosB = (a * a + c * c - b * b) / (2 * a * c);
        double cosC = (a * a + b * b - c * c) / (2 * a * b);
        double angleA = acos(cosA);  // 角A的弧度值
        double angleB = acos(cosB);  // 角B的弧度值
        double angleC = acos(cosC);  // 角C的弧度值
        // 计算三个旁切圆半径
        double ra = areaABC / (s - a);
        double rb = areaABC / (s - b);
        double rc = areaABC / (s - c);
        // 计算三个扇形对应的角度（弧度制）
        // 扇形角度 = π/2 - 对应角的一半
        double sectorAngleA = PI / 2.0 - angleA / 2.0;
        double sectorAngleB = PI / 2.0 - angleB / 2.0;
        double sectorAngleC = PI / 2.0 - angleC / 2.0;
        // 计算三个扇形面积之和（灰色区域总面积）
        double grayArea = 0.5 * (ra * ra * sectorAngleA + 
                                 rb * rb * sectorAngleB + 
                                 rc * rc * sectorAngleC);
        // 计算三角形DEF的面积（公式：S_DEF = 2Rs）
        double R = a * b * c / (4.0 * areaABC);  // 外接圆半径
        double areaDEF = 2.0 * R * s;
        // 输出结果
        printf("Case %d: %.2lf %.2lf\n", caseNum++, areaDEF, grayArea);
    }
    return 0;
}
