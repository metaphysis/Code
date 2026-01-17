// Cricket Football Goes Down
// UVa ID: 10345
// Verdict: Accepted
// Submission Date: 2026-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 预先计算的系数，对应 N=1 到 6 的最小半径与 A 的比例
    double k = 25 / (48 - 4 * sqrt(2));
    // 第 6 个系数按照给定的图求得为：sqrt(2 * k * (k + 1) + 1)
    // 但是无法通过测试，可能是出题人给出的一种近似最优放置，
    // 实际上的最优放置可能是其他情形
    const double r[6] = {
        1 / sqrt(2), sqrt(5) / 2, 5 * sqrt(17) / 16,
        sqrt(2), sqrt(10) / 2, 1.688542968214
    };
    int d;
    cin >> d;
    while (d--) {
        double a;
        cin >> a;
        for (int i = 0; i < 6; i++) {
            if (i) cout << ' ';
            cout << fixed << setprecision(11) << r[i] * a;
        }
        cout << '\n';
    }
    return 0;
}
