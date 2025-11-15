// Sphere
// UVa ID: 10175
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = 2 * acos(0.0);

int main() {
    int n;
    cin >> n;
    while (n--) {
        double r1, r2, d, w, s;
        cin >> r1 >> r2 >> d >> w >> s;

        // 计算球冠高度
        double h1 = r1 - (d * d - r2 * r2 + r1 * r1) / (2 * d);
        double h2 = r2 - (d * d - r1 * r1 + r2 * r2) / (2 * d);
        
        // 计算相交部分体积
        double capVol1 = (PI * h1 * h1 * (3 * r1 - h1)) / 3.0;
        double capVol2 = (PI * h2 * h2 * (3 * r2 - h2)) / 3.0;
        double intersectVol = capVol1 + capVol2;
        
        // 计算总体积
        double vol1 = (4.0 / 3.0) * PI * r1 * r1 * r1;
        double vol2 = (4.0 / 3.0) * PI * r2 * r2 * r2;
        double totalVol = vol1 + vol2 - intersectVol;

        // 计算表面积
        double capArea1 = 2 * PI * r1 * h1;
        double capArea2 = 2 * PI * r2 * h2;
        double totalArea = 4 * PI * (r1 * r1 + r2 * r2) - capArea1 - capArea2;

        cout << fixed << setprecision(4) << totalVol << " " << totalArea << endl;
        if (w <= totalVol * s) {
            cout << "The Paired-Sphere Floats." << endl;
        } else {
            cout << "The Paired-Sphere Sinks." << endl;
        }
    }
    return 0;
}
