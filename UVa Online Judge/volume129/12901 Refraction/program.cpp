// Refraction
// UVa ID: 12901
// Verdict: Accepted
// Submission Date: 2023-04-11
// UVa Run Time: 0.180s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cout << fixed << setprecision(4);
    double W, H, x, xe, ye, u;
    for (int cs = 1; cs <= T; cs++) {
        cin >> W >> H >> x >> xe >> ye >> u;
        double L = (xe - W) * H / (ye - H);
        double b1 = W - L;
        double a = asin((xe - W) / hypot(xe - W, ye - H) / u);
        double b2 = W - H * tan(a);
        if (x > b2) cout << "Impossible\n";
        else if (x <= b1) cout << "0.0000\n";
        else cout << (W - L - x) / (tan(a) - L / H) << '\n';
    }
    return 0;
}
