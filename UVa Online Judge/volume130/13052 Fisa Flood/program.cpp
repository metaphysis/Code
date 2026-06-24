// Fisa Flood
// UVa ID: 13052
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; ++cs) {
        int A, B;
        scanf("%d %d", &A, &B);
        // 特判：没有任何罐子时，不存在最后一罐
        if (A == 0 && B == 0) {
            printf("Case %d: 0.000 0.000\n", cs);
            continue;
        }
        int x = A & 1;                  // 异或值（D=1, L=0）
        int n = A + B;                  // 总罐数
        int r = x ^ ((n + 1) & 1);      // 1->D, 0->L
        double p = r ? 1.0 : 0.0;
        double q = 1.0 - p;
        printf("Case %d: %.3f %.3f\n", cs, p, q);
    }
    return 0;
}
