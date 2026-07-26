// Water Tanks
// UVa ID: 1066
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163211486

#include <bits/stdc++.h>
using namespace std;

double root(double b, double c) { return b / 2 - sqrt(b * b / 4 - c); }

int main() {
    int n, cases = 1;
    const double f = 0.097;
    double tank[16], pipe[16], h0, dh, V, V0, p, sum;
    while (cin >> n, n) {
        V = 0;
        for (int i = 0; i < n; i++) {
            cin >> tank[i];
            if (i) V += tank[i];
        }
        for (int i = 1; i < n; i++) cin >> pipe[i];
        V -= pipe[1], p = 1, sum = pipe[1];
        for (int i = 1; i < n; i++) {
            dh = pipe[i + 1] - pipe[i];
            if (i < n - 1) h0 = pipe[i + 1] + (p * V / (V - dh) - 1) / f;
            if (h0 > tank[0] || i == n - 1) {
                dh = tank[0] - pipe[i];
                sum += root(dh + V + 1 / f, dh * V + (1 - p) * V / f);
                break;
            }
            sum += dh;
            p *= V / (V - dh);
            V -= dh;
            h0 = pipe[i + 1] + (p * V / (V - pipe[i + 1]) - 1) / f;
            if (h0 > tank[0]) {
                sum += V - V * p / (1 + (tank[0] - pipe[i + 1]) * f);
                break;
            }
            p *= V / (V - pipe[i + 1]);
            V -= tank[i];
            V0 = tank[i] - pipe[i + 1];
            dh = tank[0] - pipe[i + 1];
            sum += pipe[i + 1] + root(dh + V0 + 1 / f, dh * V0 + (1 - p) * V0 / f);
        }
        sum += tank[0];
        cout << "Case " << cases++ << ": " << fixed << setprecision(3) << sum << "\n\n";
    }
    return 0;
}
