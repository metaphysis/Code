// Flipping Colors
// UVa ID: 10998
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstdio>
using namespace std;

bool getColor(double H, double V, double h, double v, double x, double y, int flipCount) {
    double xSplit = h * H;
    double ySplit = v * V;

    if (x < xSplit && y < ySplit) {
        // 左下区域：继续递归，颜色翻转一次
        return getColor(xSplit, ySplit, h, v, x, y, flipCount + 1);
    } else if (x >= xSplit && y >= ySplit) {
        // 右上区域：继续递归，颜色翻转一次
        return getColor(H - xSplit, V - ySplit, h, v, x - xSplit, y - ySplit, flipCount + 1);
    } else {
        // 左上或右下区域：停止递归，当前翻转次数决定颜色
        return (flipCount % 2 == 0);
    }
}

int main() {
    double H, V, h, v;
    int caseNum = 1;

    while (cin >> H >> V >> h >> v) {
        if (H == 0 && V == 0 && h == 0 && v == 0) break;

        int n;
        cin >> n;

        cout << "Case " << caseNum++ << ":" << endl;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            bool isBlack = getColor(H, V, h, v, x, y, 0);
            cout << (isBlack ? "black" : "white") << endl;
        }
    }

    return 0;
}
