#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h, n;
    while (cin >> w >> h >> n) {
        double a = (double)h / w;
        double cVal = 2.0 / (1.0 - a * a);
        double beta = (1.0 + 2.0 * a - a * a) / 4.0;

        vector<double> low(n + 1), mid(n + 1), up(n + 1), rhs(n + 1), s(n + 2);
        low[1] = 0.0;
        for (int i = 2; i <= n; ++i) low[i] = 1.0;
        for (int i = 1; i <= n; ++i) {
            mid[i] = -cVal;
            up[i] = (i == n) ? 0.0 : 1.0;
            rhs[i] = (i == n) ? -w : 0.0;
        }

        // Thomas algorithm
        for (int i = 2; i <= n; ++i) {
            double m = low[i] / mid[i - 1];
            mid[i] -= m * up[i - 1];
            rhs[i] -= m * rhs[i - 1];
        }
        s[n] = rhs[n] / mid[n];
        for (int i = n - 1; i >= 1; --i)
            s[i] = (rhs[i] - up[i] * s[i + 1]) / mid[i];

        s[0] = 0.0;
        s[n + 1] = w;

        double cost = 0.0;
        for (int i = 0; i <= n; ++i) {
            double d = s[i + 1] - s[i];
            cost += a * d * s[i] + beta * d * d;
        }
        for (int i = 1; i <= n + 1; ++i)
            cost += (a * a / 2.0) * s[i] * s[i];

        printf("%.6f\n", cost);
        int cnt = min(n, 10);
        for (int i = 1; i <= cnt; ++i)
            printf("%.6f\n", s[i]);
    }
    return 0;
}
