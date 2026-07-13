// The Robot's Grid
// UVa ID: 13214
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

long long comb[50][50];

void initComb() {
    for (int i = 0; i < 50; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; ++j)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
}

int main() {
    initComb();
    int T;
    scanf("%d", &T);
    while (T--) {
        int R, C;
        scanf("%d %d", &R, &C);
        int n = R + C - 2;
        int k = R - 1;          // 也可用 min(R-1, C-1)
        printf("%lld\n", comb[n][k]);
    }
    return 0;
}
