// Randomness
// UVa ID: 11429
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int R, N;
    while (cin >> R >> N && (R || N)) {
        vector<int> a(N), b(N);
        for (int i = 0; i < N; ++i) cin >> a[i] >> b[i];
        vector<int> rem(N, 1);
        double ans = 0.0;
        double powR = 1.0;
        for (int k = 0; ; ++k) {
            double fracSum = 0.0;
            for (int i = 0; i < N; ++i) {
                int num = (a[i] * rem[i]) % b[i];
                fracSum += (double)num / b[i];
            }
            double term = fracSum / powR;
            ans += term;
            if (k >= 200) break;
            for (int i = 0; i < N; ++i) rem[i] = (rem[i] * R) % b[i];
            powR *= R;
            if (powR > 1e100) break;
            if (fracSum < 1e-15) break;
            if (k > 0 && 1000.0 / (powR * (R - 1)) < 1e-9) break;
        }
        printf("%.6f\n", ans + 1e-9);
    }
    return 0;
}
