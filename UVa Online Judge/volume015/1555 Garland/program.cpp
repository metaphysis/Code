// Garland
// UVa ID: 1555
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;
double A;

// 检查给定的B是否满足所有灯的高度都不低于地面
bool check(double B) {
    double C1 = (B - A - (n * n - 1)) / (n - 1);
    double C2 = A - 1 - C1;
    for (int i = 1; i <= n; i++) {
        double hi = i * i + C1 * i + C2;
        if (hi < 0) return false;
    }
    return true;
}

int main() {
    // 处理多个测试用例
    while (cin >> n >> A) {
        // 二分搜索寻找最小的B
        double left = 0, right = 1e10;
        for (int iter = 0; iter < 100; iter++) {
            double mid = (left + right) / 2;
            if (check(mid)) right = mid;
            else left = mid;
        }
        // 输出结果，保留两位小数
        printf("%.2f\n", right);
    }
    return 0;
}
