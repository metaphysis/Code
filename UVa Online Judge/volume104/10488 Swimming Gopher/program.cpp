// Swimming Gopher
// UVa ID: 10488
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    double D, L, xs, ys, xt, yt;
    while (cin >> D >> L >> xs >> ys >> xt >> yt) {
        int k = abs((int)floor(ys / D) - (int)floor(yt / D));
        double swim = k * 2 * L;
        double yv = yt - (yt > ys ? k * 2 * L : -k * 2 * L);
        double walk = hypot(xt - xs, yv - ys);
        printf("The gopher has to swim %.2lf meters and walk %.2lf meters.\n", swim, walk);
    }
    return 0;
}
