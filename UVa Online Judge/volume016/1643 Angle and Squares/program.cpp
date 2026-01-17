// Angle and Squares
// UVa ID: 1643
// Verdict: Accepted
// Submission Date: 2026-01-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        double xa, ya, xb, yb;
        cin >> xa >> ya >> xb >> yb;
        double k1 = ya / xa, k2 = yb / xb;
        if (k1 > k2) swap(k1, k2); // 确保 k1 <= k2
        double S = 0.0;
        double sumSquares = 0.0;
        for (int i = 0; i < n; ++i) {
            double a;
            cin >> a;
            S += a;
            sumSquares += a * a;
        }
        double triangleArea = 0.5 * S * S * (k1 + 1.0) * (k2 + 1.0) / (k2 - k1);
        double result = triangleArea - 0.5 * sumSquares;
        cout << fixed << setprecision(3) << result << '\n';
    }
    return 0;
}
