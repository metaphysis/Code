// Hot or Cold?
// UVa ID: 1524
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<double> coeff(n + 1);
        // 读入系数，从最高次到常数项
        for (int i = 0; i <= n; ++i) cin >> coeff[i];
        double s, e;
        cin >> s >> e;
        double integral = 0.0;
        // 计算定积分
        for (int i = 0; i <= n; ++i) {
            int power = n - i; // 当前项的次数
            integral += coeff[i] * (pow(e, power + 1) - pow(s, power + 1)) / (power + 1);
        }
        double average = integral / (e - s);
        cout << fixed << setprecision(3) << average << endl;
    }
    return 0;
}
