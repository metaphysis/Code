// See Emily Play
// UVa ID: 12699
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    vector<int> Ns(T), ds(T), ss(T), as(T);
    int maxN = 0;
    for (int i = 0; i < T; ++i) {
        scanf("%d %d %d %d", &Ns[i], &ds[i], &ss[i], &as[i]);
        if (Ns[i] > maxN) maxN = Ns[i];
    }

    // 预处理 D 和 E（E 表示减法和加法的期望次数，两者相等）
    vector<double> D(maxN + 2, 0.0), E(maxN + 2, 0.0);
    if (maxN >= 1) {
        D[1] = 1.0;   // 2*0 + 1
        E[1] = 1.0;   // 2*0.5 + 0
    }

    for (int n = 2; n <= maxN; ++n) {
        if (n % 2 == 0) {
            D[n] = D[n / 2] + 1.0;
            E[n] = E[n / 2];
        } else {
            int n1 = n + 1;                     // n1 为偶数
            D[n1] = D[n1 / 2] + 1.0;
            E[n1] = E[n1 / 2];
            D[n] = (D[n - 1] + D[n1]) / 2.0;
            E[n] = 0.5 + (E[n - 1] + E[n1]) / 2.0;
        }
    }

    for (int i = 0; i < T; ++i) {
        double ans = ds[i] * D[Ns[i]] + (ss[i] + as[i]) * E[Ns[i]];
        printf("%.3f\n", ans);
    }
    return 0;
}
