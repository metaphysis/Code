// Tobby and the Line Game
// UVa ID: 13099
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int xL, yL, xR, yR;
    while (scanf("%d%d%d%d", &xL, &yL, &xR, &yR) != EOF) {
        double dx = xR - xL;
        double dy = yR - yL;
        double result = (dx * dx + dy * dy) / 6.0;
        printf("%.15f\n", result);
    }
    return 0;
}
