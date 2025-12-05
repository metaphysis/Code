// Rigid Circle Packing
// UVa ID: 10468
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 最优比例常数，来自几何推导
    const double ratio9 = 7.0225095034303809;
    const double ratio10 = 7.5191308906315991;
    double radius;
    while (cin >> radius) {
        double side9 = radius * ratio9;
        double side10 = radius * ratio10;
        cout << fixed << setprecision(5) << side9 << " " << side10 << endl;
    }
    return 0;
}
