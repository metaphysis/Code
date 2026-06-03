// Prisoners Boxes and Pieces of Paper
// UVa ID: 11118
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        scanf("%d", &n);
        double loseProb = 0.0;
        // 累加长度大于 n/2 的循环的概率
        for (int k = n / 2 + 1; k <= n; ++k)
            loseProb += 1.0 / k;
        double winProb = 1.0 - loseProb;
        double expectedRounds = 1.0 / winProb;
        // 输出，精度保证 8 位小数
        printf("Case #%d: %.8f %.8f\n", caseNo, winProb, expectedRounds);
    }
    return 0;
}
