#include <bits/stdc++.h>
using namespace std;

// 计算 5 个三角形的最优边长比例（二分搜索）
double solveForFiveTriangles() {
    const double PI = acos(-1.0);
    double lo = 0.55, hi = 0.56;

    for (int iter = 0; iter < 100; ++iter) {
        double a = (lo + hi) * 0.5;               // 三角形边长
        double h = sqrt(3.0) / 2.0 * a;           // 三角形的高

        // 水平方向总投影 = T2上边长度(a) + T3水平高(h)
        // 若未超过正方形宽度，还可以增大 a
        if (h + a <= 1.0) {
            lo = a;
            continue;
        }

        double overX = h + a - 1.0;               // 水平超出量
        double vertComp = overX * tan(PI / 6.0);  // 沿60°斜线转为垂直补偿

        // T1上顶角与T4下顶角水平线之间的垂直距离 = 1 - 2h
        // 减去垂直补偿，得到 T4下顶角相对于 T3左侧顶角水平线的垂直错位
        double vertGap = (1.0 - 2.0 * h) - vertComp;

        if (vertGap <= 0.0) {
            hi = a;
            continue;
        }

        // 水平剩余偏移 = 水平超出量 - (垂直错位对应的水平补偿)
        double horzRemain = overX - vertGap / tan(PI / 6.0);

        if (horzRemain <= 0.0) {
            lo = a;
            continue;
        }

        // 两条直角边：
        //   leg1 = a - horzRemain   (T4下顶角与左边界的水平距离)
        //   leg2 = vertComp + vertGap   (T4下顶角与T2上边之间的垂直距离)
        double leg1 = a - horzRemain;
        double leg2 = vertComp + vertGap;

        // 直角三角形成立条件：若 leg1² + leg2² < a²，则重叠 → a 太大
        if (leg1 * leg1 + leg2 * leg2 < a * a) hi = a;
        else lo = a;
    }

    return lo;   // 最优比例 ≈ 0.5545791573148570
}

int main() {
    vector<double> ratio = {
        // 1个等边三角形：三角形的边为斜边，正方形的边为直角边，两条边夹角为15度，根据三角函数可以计算
        1.0 / cos(15.0 / 180.0 * M_PI),
        // 2个等边三角形：高的两倍与正方形的对角线长度相等
        sqrt(6) / 3,
        // 3个等边三角形:令三角形的高为h，正方形的边长为S，根据几何关系可以得到：sqrt(2) * S - h = sqrt(2) * h
        2.0 * sqrt(2) / (sqrt(6) + sqrt(3)),
        // 4个等边三角形：令三角形的边长为a，正方形的边长为S，可以得到：(S - a) / (a / 2) = 2 / sqrt(3)
        sqrt(3) / (1 + sqrt(3)),
        // 5个等边三角形：
        0,
        // 6个等边三角形：令三角形的边长为a，正方形的边长为S，根据面积关系，可以得到：3 * sqrt(3) * a - (1 + sqrt(3)) * S = 0
        (1.0 + sqrt(3)) / (3 * sqrt(3)),
        // 7个等边三角形：令三角形的边长为a，正方形的边长为S，根据边长关系，可以得到：a = (3 + sqrt(3)) / (3 + 4 * sqrt(3)) * S
        (3 + sqrt(3)) / (3 + 4 * sqrt(3))
    };

    ratio[4] = solveForFiveTriangles();
    double S;
    while (cin >> S) {
        cout << fixed << setprecision(10);
        for (int i = 0; i < 7; i++) cout << ratio[i] * S << " \n"[i == 6];
    }
    return 0;
}
