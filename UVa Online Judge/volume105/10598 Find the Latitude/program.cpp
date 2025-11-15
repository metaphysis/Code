// Find the Latitude
// UVa ID: 10598
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
int main() {
    int caseNumber = 1;
    double R, n;
    while (cin >> R >> n) {
        if (R == 0 && n == 0) break;
        cout << "Case " << caseNumber++ << ":" << endl;
        vector<double> latitudes;
        // k 是向东走的圈数
        for (int k = 1; k <= 10; ++k) {
            double denominator = 2.0 * PI * R * k;
            double cosValue = n / denominator;
            double phiRad = acos(cosValue) - (n / R);
            double phiDeg = phiRad * 180.0 / PI;
            latitudes.push_back(phiDeg);
        }
        // 按纬度从大到小排序（题目要求前10个最小的解，即纬度最大的）
        sort(latitudes.begin(), latitudes.end());
        // 输出前10个
        for (size_t i = 0; i < latitudes.size() && i < 10; ++i) {
            cout << fixed << setprecision(5) << latitudes[i] << endl;
        }
    }
    return 0;
}
