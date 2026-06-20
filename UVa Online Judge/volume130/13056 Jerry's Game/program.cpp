// Jerry's Game
// UVa ID: 13056
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    const double pi = acos(-1.0);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int R, V;
        scanf("%d %d", &R, &V);
        double ans = (pi / 2.0) * (double)R / (double)V;
        printf("Case %d: %.10f\n", caseNo, ans);
    }
    return 0;
}
