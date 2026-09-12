// A Dangerous Maze (II)
// UVa ID: 12411
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int n, K;
        scanf("%d %d", &n, &K);
        int P = 0, N = 0;
        double Spos = 0.0, Sneg = 0.0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            if (x > 0) { ++P; Spos += x; }
            else { ++N; Sneg += -x; }
        }
        if (P == 0) {
            printf("Case %d: -1.000\n", tc);
            continue;
        }
        double c; // 每个负门期望被选次数
        int Kk = min(K, N);
        if (Kk == 0) {
            c = 1.0 / P;
        } else {
            vector<vector<double>> g(Kk + 1, vector<double>(Kk + 1, 0.0));
            vector<double> f(Kk + 1, 0.0);
            double M = P + N - Kk;
            double alpha = (double)(N - Kk) / M;
            double fK = 1.0 / (P + 1 - pow(alpha, Kk));
            f[Kk] = fK;
            for (int a = 0; a < Kk; ++a)
                g[Kk][a] = pow(alpha, Kk - a) * fK;
            for (int b = Kk - 1; b >= 0; --b) {
                double Mb = P + N - b;
                for (int a = 0; a < b; ++a)
                    g[b][a] = ((double)(N - b) / Mb) * g[b + 1][a + 1];
                double term = (1.0 / Mb) * (1.0 + g[b + 1][0]);
                if (N - b - 1 >= 0)
                    term += ((double)(N - b - 1) / Mb) * f[b + 1];
                f[b] = term;
            }
            c = f[0];
        }
        double ans = Spos / P + Sneg * c;
        ans += 1e-9;
        printf("Case %d: %.3f\n", tc, ans);
    }
    return 0;
}
