// Download Manager
// UVa ID: 12231
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T, n, B;
    int caseNo = 1;
    while (scanf("%d%d%d", &T, &n, &B) == 3 && (T != 0 || n != 0 || B != 0)) {
        double totalRemaining = 0.0;
        for (int i = 0; i < T; ++i) {
            double S;
            int P;
            scanf("%lf%d", &S, &P);
            totalRemaining += S * (100 - P) / 100.0;
        }
        double timeInSeconds = totalRemaining / B;
        printf("Case %d: %.2f\n\n", caseNo++, timeInSeconds);
    }
    return 0;
}
