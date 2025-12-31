// Bridge
// UVa ID: 1356
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算单段缆索长度
double cableLength(double d, double H, double h) {
    double m = 4.0 * (H - h) / d;
    double sqrtTerm = sqrt(1.0 + m * m);
    double term1 = d / 2.0 * sqrtTerm;
    // 避免除以0
    if (H - h < 1e-12) return d;
    double term2 = d * d / (8.0 * (H - h)) * log(m + sqrtTerm);
    return term1 + term2;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        if (t > 1) cout << endl;

        double D, H, B, L;
        cin >> D >> H >> B >> L;

        // 最少塔数
        int n = (int)ceil(B / D) + 1;
        double d = B / (n - 1);

        // 二分法求h
        double left = 0.0, right = H;
        for (int iter = 0; iter < 80; ++iter) {
            double mid = (left + right) / 2.0;
            double totalCable = (n - 1) * cableLength(d, H, mid);
            if (totalCable < L) 
                right = mid;  // 缆太短，需要降低最低点（减小h）
            else 
                left = mid;
        }

        double h = (left + right) / 2.0;
        cout << "Case " << t << ":" << endl;
        cout << fixed << setprecision(2) << h << endl;
    }
    return 0;
}
