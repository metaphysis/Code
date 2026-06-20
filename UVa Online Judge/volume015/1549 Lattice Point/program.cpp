// Lattice Point
// UVa ID: 1549
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算 D(r)，r 为非负整数
long long countLatticePoints(long long r) {
    if (r == 0) return 1;
    long long r2 = r * r;
    long long y = r;
    long long sum = 0;
    for (long long x = 1; x <= r; ++x) {
        while (y * y + x * x > r2) --y;   // 调整 y 使 (x,y) 在圆内
        sum += y;                         // 累加该列上格点数（y=1..floor(sqrt(...))）
    }
    // 原点1个 + 坐标轴上4r个 + 四个象限内4*sum个
    return 1 + 4 * r + 4 * sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    while (cin >> n) {
        cout << n << '\n';
        cout << countLatticePoints(n) << '\n';
    }
    return 0;
}
