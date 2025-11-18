// Maximal Quadrilateral
// UVa ID: 10545
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p, a, b;
        cin >> p >> a >> b;
        double s = p / 2.0;
        double c = s - a;
        double d = s - b;
        if (a <= 0 || b <= 0 || c <= 0 || d <= 0) {
            cout << "Case " << i << ": Eta Shombhob Na.\n";
            continue;
        }
        double area = sqrt((s - a) * (s - b) * (s - c) * (s - d));
        double radius = area / s;
        cout << "Case " << i << ": " << fixed << setprecision(6) << radius << "\n";
    }
    return 0;
}
